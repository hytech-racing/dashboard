#include <Arduino.h>

#include <SPI.h>
#include "CANInterface.h"
#include <cstdint>
#include "Dash_Constants.h"
#include "Dash_Globals.h"
#include "DashCANInterfaceImpl.h"
#include "SharedFirmwareTypes.h"
#include "Dash_Tasks.h"
#include "etl/singleton.h"

#include "ht_task.hpp"
#include "ht_sched.hpp"

#include "CANInterface.h"
#include "lcdInterface.h"
#include "VCFInterface.h"
#include "ACUInterface.h"
#include "VCRInterface.h"

#include "main.h"


#define LED_PIN PA3
#define SHARP_CS PB7
#define SHARP_CLK PB10
#define SHARP_MOSI PB15

static CAN_message_t telem_can_rx_msg;
STM32_CAN stm_can(FDCAN1);

uint32_t last_blink = 0;
bool led_state = false;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};

// Hadware SPI and DMA
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

void custom_handle_error(int num) {
  while(1) {
    SerialUSB.printf("Error at: %d\n", num);
    delay(100);
  }
}

extern "C" void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hspi->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
    PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      custom_handle_error(2);
    }

    /* Peripheral clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PB10     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI2 DMA Init */
    /* SPI2_TX Init */
    hdma_spi2_tx.Instance = DMA1_Stream0;
    hdma_spi2_tx.Init.Request = DMA_REQUEST_SPI2_TX;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi2_tx.Init.Mode = DMA_NORMAL;
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
    {
      custom_handle_error(3);
    }

    __HAL_LINKDMA(hspi,hdmatx,hdma_spi2_tx);

    /* SPI2 interrupt Init */
    HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }

}



HT_TASK::TaskResponse init_can_task()
{
    stm_can.begin();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse read_can_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    if (stm_can.read(telem_can_rx_msg))
    {
      CANInterfaces& dash_can_interfaces = CANInterfacesInstance::instance(); 
      DashCAN::dash_read_switch(dash_can_interfaces, telem_can_rx_msg, sysMicros);
    }
    return HT_TASK::TaskResponse::YIELD;
}

// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
// HT_TASK::Task screen_task(&init_screen_task, &screen_refresh_task, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period


void setup() {

  pinMode(PB7, OUTPUT);
  pinMode(PA3, OUTPUT);
  digitalWrite(PB7, HIGH);

  SerialUSB.begin(115200);

  // SystemClock_Config();

  
  // Create Interfaces
  ACUInterfaceInstance::create();
  VCRInterfaceInstance::create();
  VCFInterfaceInstance::create(sys_time::hal_millis(), 50UL); //TODO: needs to be updated to use constexpr
  // dashDisplayInstance::create(SHARP_CLK, SHARP_MOSI, SHARP_CS, 320, 240); 
  
  VCRData_sInstance::create();
  VCFData_sInstance::create();
  
  // Create can singletons
  CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance(), DrivebrainInterfaceInstance::instance()); 
  auto main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<DashCAN::dash_read_switch>();
  //DashCANInterfaceObjectsInstance::create(main_can_recv, &stm_can); // NOLINT (Not sure why it's uninitialized. I think it is.)
  
  
  
  // Setup scheduler
  HT_SCHED::Scheduler::getInstance().setTimingFunction(micros);
  
  HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  // HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  // Initialize SPI and DMA
  // __HAL_RCC_GPIOB_CLK_ENABLE(); // IDK if this is done already or not
  
  // Init DMA for SPI2
  __HAL_RCC_DMA1_CLK_ENABLE();
  
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128; // 2MHz @ 192MHz SYSCLK
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x0;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    custom_handle_error(1);
  }

  __HAL_SPI_ENABLE(&hspi2);
  
  
  
}

void loop() {
    // HT_SCHED::Scheduler::getInstance().run();


    // digitalWrite(PB7, LOW);
    // // bool tx_success = HAL_SPI_Transmit_DMA(&hspi2, test_tx, sizeof(test_tx)) == HAL_OK;
    // HAL_SPI_Transmit(&hspi2, test_tx, sizeof(test_tx), HAL_MAX_DELAY);
    // digitalWrite(PB7, HIGH);
    // delay(500);
    // SerialUSB.println("TEST");
    // // delay(500);

    if (millis() - last_blink > 100) {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
      HAL_SPI_Transmit(&hspi2, test_tx, sizeof(test_tx), HAL_MAX_DELAY);
    }
    
  }

  
