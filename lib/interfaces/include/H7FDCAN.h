#ifndef STM32_FDCAN_H
#define STM32_FDCAN_H

#include <Arduino.h>


#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"


typedef struct {
    uint32_t id;
    uint8_t extended;
    uint8_t dlc;
    uint8_t data[64];
    uint8_t* buf;
    uint8_t len;
} CAN_message_t;


class STM32_FDCAN {
private:
    FDCAN_HandleTypeDef hfdcan;
    FDCAN_TxHeaderTypeDef txHeader;
    FDCAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[64];
    uint8_t txData[64];
    
    // Pin configuration
    GPIO_TypeDef* rx_port;
    GPIO_TypeDef* tx_port;
    uint32_t rx_pin;
    uint32_t tx_pin;
    uint32_t alternate_function;
    
    // Internal configuration
    FDCAN_TypeDef* fdcan_instance;
    IRQn_Type fdcan_irq;
    
    void configureGPIO();
    void configureFDCAN(uint32_t baudrate);
    
public:
    STM32_FDCAN(FDCAN_TypeDef* instance);
    
    // Initialize with default pins and baudrate
    bool init();
    bool init(uint32_t baudrate);
    bool init(GPIO_TypeDef* rx_port, uint32_t rx_pin, 
              GPIO_TypeDef* tx_port, uint32_t tx_pin, 
              uint32_t baudrate = 500000);
    
    // Write CAN message
    bool write(CAN_message_t &msg);
    bool write(uint32_t id, uint8_t ext, uint8_t rtr, uint8_t len, uint8_t *data);
    
    // Read CAN message
    bool read(CAN_message_t &msg);
    
    // Check if message available
    bool available();
    
    // Enable/disable interrupts
    void enableInterrupt();
    void disableInterrupt();
    
    // Get FDCAN handle for advanced usage
    FDCAN_HandleTypeDef* getHandle() { return &hfdcan; }
};

// Implementation
STM32_FDCAN::STM32_FDCAN(FDCAN_TypeDef* instance) {
    fdcan_instance = instance;
    
    // Set default pins for FDCAN1 on STM32H750VB
    if (instance == FDCAN1) {
        rx_port = GPIOD;
        rx_pin = GPIO_PIN_0;
        tx_port = GPIOD;
        tx_pin = GPIO_PIN_1;
        alternate_function = GPIO_AF9_FDCAN1;
        fdcan_irq = FDCAN1_IT0_IRQn;
    }
    // Add FDCAN2 support if needed
    else if (instance == FDCAN2) {
        rx_port = GPIOB;
        rx_pin = GPIO_PIN_5;
        tx_port = GPIOB;
        tx_pin = GPIO_PIN_6;
        alternate_function = GPIO_AF9_FDCAN2;
        fdcan_irq = FDCAN2_IT0_IRQn;
    }
}

void STM32_FDCAN::configureGPIO() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // Enable GPIO clocks
    if (rx_port == GPIOA || tx_port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if (rx_port == GPIOB || tx_port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if (rx_port == GPIOD || tx_port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    if (rx_port == GPIOH || tx_port == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
    
    // Configure RX pin
    GPIO_InitStruct.Pin = rx_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = alternate_function;
    HAL_GPIO_Init(rx_port, &GPIO_InitStruct);
    
    // Configure TX pin
    GPIO_InitStruct.Pin = tx_pin;
    HAL_GPIO_Init(tx_port, &GPIO_InitStruct);
}

void STM32_FDCAN::configureFDCAN(uint32_t baudrate) {
    // Enable FDCAN clock
    if (fdcan_instance == FDCAN1) {
        __HAL_RCC_FDCAN_CLK_ENABLE();
    }
    
    hfdcan.Instance = fdcan_instance;
    hfdcan.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan.Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan.Init.AutoRetransmission = ENABLE;
    hfdcan.Init.TransmitPause = DISABLE;
    hfdcan.Init.ProtocolException = DISABLE;
    
    // Calculate bit timing for desired baudrate
    // Assuming 80MHz FDCAN clock
    uint32_t prescaler = 1;
    uint32_t tseg1 = 13;
    uint32_t tseg2 = 2;
    
    // Simple baudrate calculation for common rates
    switch(baudrate) {
        case 125000:  // 125 kbps
            prescaler = 40;
            break;
        case 250000:  // 250 kbps
            prescaler = 20;
            break;
        case 500000:  // 500 kbps
            prescaler = 10;
            break;
        case 1000000: // 1 Mbps
            prescaler = 5;
            break;
        default:
            prescaler = 10; // Default to 500k
            break;
    }
    
    hfdcan.Init.NominalPrescaler = prescaler;
    hfdcan.Init.NominalSyncJumpWidth = 1;
    hfdcan.Init.NominalTimeSeg1 = tseg1;
    hfdcan.Init.NominalTimeSeg2 = tseg2;
    
    // Data bit timing (same as nominal for classic CAN)
    hfdcan.Init.DataPrescaler = prescaler;
    hfdcan.Init.DataSyncJumpWidth = 1;
    hfdcan.Init.DataTimeSeg1 = tseg1;
    hfdcan.Init.DataTimeSeg2 = tseg2;
    
    // Message RAM configuration
    hfdcan.Init.MessageRAMOffset = 0;
    hfdcan.Init.StdFiltersNbr = 1;
    hfdcan.Init.ExtFiltersNbr = 1;
    hfdcan.Init.RxFifo0ElmtsNbr = 8;
    hfdcan.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan.Init.RxFifo1ElmtsNbr = 0;
    hfdcan.Init.RxBuffersNbr = 0;
    hfdcan.Init.TxEventsNbr = 0;
    hfdcan.Init.TxBuffersNbr = 0;
    hfdcan.Init.TxFifoQueueElmtsNbr = 8;
    hfdcan.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
    hfdcan.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
}

bool STM32_FDCAN::init() {
    return init(500000); // Default 500kbps
}

bool STM32_FDCAN::init(uint32_t baudrate) {
    configureGPIO();
    configureFDCAN(baudrate);
    
    if (HAL_FDCAN_Init(&hfdcan) != HAL_OK) {
        return false;
    }
    
    // Configure global filter to accept all messages
    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x7FF;
    
    if (HAL_FDCAN_ConfigFilter(&hfdcan, &sFilterConfig) != HAL_OK) {
        return false;
    }
    
    // Configure extended ID filter
    sFilterConfig.IdType = FDCAN_EXTENDED_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterID1 = 0x00000000;
    sFilterConfig.FilterID2 = 0x1FFFFFFF;
    
    if (HAL_FDCAN_ConfigFilter(&hfdcan, &sFilterConfig) != HAL_OK) {
        return false;
    }
    
    // Start FDCAN
    if (HAL_FDCAN_Start(&hfdcan) != HAL_OK) {
        return false;
    }
    
    return true;
}

bool STM32_FDCAN::init(GPIO_TypeDef* rx_port_new, uint32_t rx_pin_new, 
                      GPIO_TypeDef* tx_port_new, uint32_t tx_pin_new, 
                      uint32_t baudrate) {
    rx_port = rx_port_new;
    rx_pin = rx_pin_new;
    tx_port = tx_port_new;
    tx_pin = tx_pin_new;
    
    return init(baudrate);
}

bool STM32_FDCAN::write(CAN_message_t &msg) {
    return write(msg.id, msg.ext, msg.rtr, msg.len, msg.data);
}

bool STM32_FDCAN::write(uint32_t id, uint8_t ext, uint8_t rtr, uint8_t len, uint8_t *data) {
    if (len > 8) len = 8;
    
    // Configure TX header
    if (ext) {
        txHeader.Identifier = id & 0x1FFFFFFF;
        txHeader.IdType = FDCAN_EXTENDED_ID;
    } else {
        txHeader.Identifier = id & 0x7FF;
        txHeader.IdType = FDCAN_STANDARD_ID;
    }
    
    txHeader.TxFrameType = rtr ? FDCAN_REMOTE_FRAME : FDCAN_DATA_FRAME;
    txHeader.DataLength = len << 16; // Convert to FDCAN format
    txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    txHeader.BitRateSwitch = FDCAN_BRS_OFF;
    txHeader.FDFormat = FDCAN_CLASSIC_CAN;
    txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    txHeader.MessageMarker = 0;
    
    // Copy data
    for (int i = 0; i < len; i++) {
        txData[i] = data[i];
    }
    
    // Send message
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan, &txHeader, txData) != HAL_OK) {
        return false;
    }
    
    return true;
}

bool STM32_FDCAN::read(CAN_message_t &msg) {
    if (!available()) {
        return false;
    }
    
    if (HAL_FDCAN_GetRxMessage(&hfdcan, FDCAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK) {
        return false;
    }
    
    // Convert from FDCAN format to CAN_message_t
    msg.id = rxHeader.Identifier;
    msg.ext = (rxHeader.IdType == FDCAN_EXTENDED_ID) ? 1 : 0;
    msg.rtr = (rxHeader.RxFrameType == FDCAN_REMOTE_FRAME) ? 1 : 0;
    msg.len = (rxHeader.DataLength >> 16) & 0x0F;
    
    for (int i = 0; i < msg.len && i < 8; i++) {
        msg.data[i] = rxData[i];
    }
    
    return true;
}

bool STM32_FDCAN::available() {
    return HAL_FDCAN_GetRxFifoFillLevel(&hfdcan, FDCAN_RX_FIFO0) > 0;
}

void STM32_FDCAN::enableInterrupt() {
    HAL_FDCAN_ActivateNotification(&hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    HAL_NVIC_SetPriority(fdcan_irq, 0, 0);
    HAL_NVIC_EnableIRQ(fdcan_irq);
}

void STM32_FDCAN::disableInterrupt() {
    HAL_FDCAN_DeactivateNotification(&hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
    HAL_NVIC_DisableIRQ(fdcan_irq);
}


#endif // STM32_FDCAN_H