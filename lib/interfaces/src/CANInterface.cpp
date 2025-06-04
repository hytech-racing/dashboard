#include "CanInterface.h"

// Constructor: sets up the instance pointer
STM32_CAN::STM32_CAN(FDCAN_TypeDef* instance) {
    hfdcan.Instance = instance;
}

// Initialize CAN hardware
bool STM32_CAN::begin() {
    hfdcan.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan.Init.AutoRetransmission = ENABLE;
    hfdcan.Init.TransmitPause = DISABLE;
    hfdcan.Init.ProtocolException = DISABLE;
    hfdcan.Init.NominalPrescaler = 1;
    hfdcan.Init.NominalSyncJumpWidth = 1;
    hfdcan.Init.NominalTimeSeg1 = 13;
    hfdcan.Init.NominalTimeSeg2 = 2;
    hfdcan.Init.DataPrescaler = 1;
    hfdcan.Init.DataSyncJumpWidth = 1;
    hfdcan.Init.DataTimeSeg1 = 13;
    hfdcan.Init.DataTimeSeg2 = 2;
    hfdcan.Init.StdFiltersNbr = 1;
    hfdcan.Init.ExtFiltersNbr = 0;
    hfdcan.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;


    if (HAL_FDCAN_Init(&hfdcan) != HAL_OK) {
        return false;
    }

    // Basic receive filter to allow all standard IDs
    FDCAN_FilterTypeDef sFilterConfig = {};
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x7FF;

    if (HAL_FDCAN_ConfigFilter(&hfdcan, &sFilterConfig) != HAL_OK) {
        return false;
    }

    if (HAL_FDCAN_Start(&hfdcan) != HAL_OK) {
        return false;
    }

    return true;
}

// Read a CAN message
bool STM32_CAN::read(CAN_message_t& msg) {
    FDCAN_RxHeaderTypeDef rxHeader;

    if (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan, FDCAN_RX_FIFO0) == 0) {
        return false;
    }

    if (HAL_FDCAN_GetRxMessage(&hfdcan, FDCAN_RX_FIFO0, &rxHeader, msg.data) != HAL_OK) {
        return false;
    }

    msg.id = rxHeader.Identifier;
    msg.extended = (rxHeader.IdType == FDCAN_EXTENDED_ID);
    msg.dlc = rxHeader.DataLength >> 16;
    msg.len = msg.dlc;
    msg.buf = msg.data;

    return true;
}

// Write a CAN message
bool STM32_CAN::write(const CAN_message_t& msg) {
    FDCAN_TxHeaderTypeDef txHeader;
    txHeader.Identifier = msg.id;
    txHeader.IdType = msg.extended ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
    txHeader.DataLength = (msg.dlc << 16);  // must be left-shifted
    txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    txHeader.BitRateSwitch = FDCAN_BRS_OFF;
    txHeader.FDFormat = FDCAN_CLASSIC_CAN;
    txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    txHeader.MessageMarker = 0;

    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan, &txHeader, msg.data) != HAL_OK) {
        return false;
    }

    return true;
}
