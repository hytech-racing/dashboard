#include <Arduino.h>

#include <SPI.h>
//#include "CANInterface.h"
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

#include "HT_SPI.h"
#include "HT_Display.h"


#define LED_PIN PA3
#define SHARP_CS PC14
#define SHARP_CLK PB10
#define SHARP_MOSI PB15
#define CHOPPED_SIZE 10080

uint32_t last_blink = 0;
uint32_t last_print = 0;
uint16_t chopped_len = CHOPPED_SIZE;
bool led_state = false;
int count = 0;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};
static uint8_t chopped_display[CHOPPED_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

void custom_handle_error(int num) {
  while(1) {
    digitalWrite(PA3, HIGH);
    delay(500);
    digitalWrite(PA3, LOW);
    delay(500);
  }
}

void Check_DMA_SPI_Errors(SPI_HandleTypeDef *hspi)
{
    DMA_HandleTypeDef *hdma = hspi->hdmatx;

    SerialUSB.printf("\n--- DMA / SPI Diagnostic ---\n");

    // 1️⃣ DMA-level error flags
    SerialUSB.printf("DMA ErrorCode: 0x%08lX\n", hdma->ErrorCode);
    if (hdma->ErrorCode & HAL_DMA_ERROR_TE)  SerialUSB.printf(" -> Transfer error (TEIF)\n");
    if (hdma->ErrorCode & HAL_DMA_ERROR_FE)  SerialUSB.printf(" -> FIFO error (FEIF)\n");
    if (hdma->ErrorCode & HAL_DMA_ERROR_DME) SerialUSB.printf(" -> Direct mode error (DMEIF)\n");
    if (hdma->ErrorCode & HAL_DMA_ERROR_TIMEOUT) SerialUSB.printf(" -> Timeout error\n");
    if (hdma->ErrorCode & HAL_DMA_ERROR_PARAM)   SerialUSB.printf(" -> Invalid parameters\n");
    if (hdma->ErrorCode == HAL_DMA_ERROR_NONE)   SerialUSB.printf(" -> No DMA error\n");

    // 2️⃣ SPI-level error flags
    SerialUSB.printf("SPI ErrorCode: 0x%08lX\n", hspi->ErrorCode);
    if (hspi->ErrorCode & HAL_SPI_ERROR_MODF)   SerialUSB.printf(" -> Mode fault\n");
    if (hspi->ErrorCode & HAL_SPI_ERROR_CRC)    SerialUSB.printf(" -> CRC error\n");
    if (hspi->ErrorCode & HAL_SPI_ERROR_OVR)    SerialUSB.printf(" -> Overrun\n");
    if (hspi->ErrorCode & HAL_SPI_ERROR_FRE)    SerialUSB.printf(" -> Frame error\n");
    if (hspi->ErrorCode & HAL_SPI_ERROR_DMA)    SerialUSB.printf(" -> DMA transfer error\n");
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)  SerialUSB.printf(" -> No SPI error\n");

    // 3️⃣ DMA Stream hardware flags (optional: direct register access)
    uint32_t isr = DMA1->LISR; // or HISR depending on stream
    SerialUSB.printf("DMA LISR/HISR: 0x%08lX\n", isr);

    // 4️⃣ SPI Status Register
    uint32_t sr = hspi->Instance->SR;
    SerialUSB.printf("SPI SR: 0x%08lX\n", sr);

    if (sr & SPI_SR_OVR)  SerialUSB.printf(" -> OVR set\n");
    if (sr & SPI_SR_MODF) SerialUSB.printf(" -> MODF set\n");
    if (sr & SPI_SR_UDR)  SerialUSB.printf(" -> UDR set\n");
    // if (sr & SPI_SR_FRE)  SerialUSB.printf(" -> FRE set\n");

    SerialUSB.printf("SPI SR: 0x%08lX\n", hspi2.Instance->SR);
SerialUSB.printf("SPI CFG1: 0x%08lX\n", hspi2.Instance->CFG1);
SerialUSB.printf("SPI CFG2: 0x%08lX\n", hspi2.Instance->CFG2);
SerialUSB.printf("SPI CR1:  0x%08lX\n", hspi2.Instance->CR1);
SerialUSB.printf("SPI CR2:  0x%08lX\n", hspi2.Instance->CR2);

    // 5️⃣ State fields
    SerialUSB.printf("DMA State: %d, SPI State: %d\n", hdma->State, hspi->State);

    SerialUSB.printf("--- End of diagnostics ---\n");
}

extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    SerialUSB.printf("SPI Error Callback triggered!\n");
    Check_DMA_SPI_Errors(hspi);
}
 
// void dump_dma_spi_state(void)
// {
//     DMA_HandleTypeDef *hdma = hspi2.hdmatx;
//     SerialUSB.printf("---- DMA runtime ----\n");
//     SerialUSB.printf("DMA Instance: %p\n", (void*)Instance);
//     // NDTR = number of remaining transfers
//     SerialUSB.printf("NDTR: %lu\n", (uint32_t)hdma->Instance->NDTR);
//     // Peripheral and memory addresses
//     SerialUSB.printf("PAR (periph addr): 0x%08lX\n", (uint32_t)hdma->Instance->PAR);
//     SerialUSB.printf("M0AR (mem addr):   0x%08lX\n", (uint32_t)hdma->Instance->M0AR);
//     #if defined(M0AR_MA)
//     SerialUSB.printf("M1AR (mem2 addr):  0x%08lX\n", (uint32_t)hdma->Instance->M1AR);
//     #endif
//     // Stream configuration register SxCR
//     SerialUSB.printf("CR (SxCR): 0x%08lX\n", (uint32_t)hdma->Instance->CR);
//     SerialUSB.printf("FCR (SxFCR): 0x%08lX\n", (uint32_t)hdma->Instance->FCR);
//     SerialUSB.printf("ISR: 0x%08lX\n", (uint32_t)hdma->Instance->ISR);
//     SerialUSB.printf("IFCR: 0x%08lX\n", (uint32_t)hdma->Instance->IFCR);
//     SerialUSB.printf("hdma->Init: Dir=%d MemInc=%d PDataAlign=%d MDataAlign=%d Mode=%d FIFOMode=%d MemBurst=%d PeriphBurst=%d\n",
//         hdma->Init.Direction,
//         hdma->Init.MemInc,
//         hdma->Init.PeriphDataAlignment,
//         hdma->Init.MemDataAlignment,
//         hdma->Init.Mode,
//         hdma->Init.FIFOMode,
//         hdma->Init.MemBurst,
//         hdma->Init.PeriphBurst
//     );
//     SerialUSB.printf("---- SPI registers ----\n");
//     SerialUSB.printf("SPI SR: 0x%08lX\n", (uint32_t)hspi2.Instance->SR);
//     SerialUSB.printf("SPI CFG1: 0x%08lX\n", (uint32_t)hspi2.Instance->CFG1);
//     SerialUSB.printf("SPI CR1: 0x%08lX\n", (uint32_t)hspi2.Instance->CR1);
// }
  


// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
// HT_TASK::Task screen_task(&init_screen_task, &screen_refresh_task, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period

HyTech_SharpMem testDisplay(SHARP_CS, 320, 240, 2000000); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now

void setup() {

  pinMode(PA3, OUTPUT);
  pinMode(PC14, OUTPUT);

  digitalWrite(PC14, LOW);

  SerialUSB.begin(115200);
  delay(3000);
  SerialUSB.println("Starting");

  
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
  
  //HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  // HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  HT_SPI_Init();

  
  testDisplay.begin();
  //testDisplay.drawPixel(1, 1, 1); //should draw a pixel on the display
  //testDisplay.drawPixel(10, 10, 1); //should draw another pixel on the display

  //SerialUSB.println(testDisplay.getBufferSize());
  //SerialUSB.println(((320 * 240) / 8) + (2*240));
  //SerialUSB.println(testDisplay.getBuffer()[0]);

// for (int i = 0; i < CHOPPED_SIZE; i += 1){//(320/8)+2){

//     // save address byte

//     chopped_display[i] = i;//((i) / (42)) + 1;
//     SerialUSB.println(chopped_display[i]);
//   }
//   chopped_display[0] = 0x01;
//   chopped_display[1] = 0x02;

}

void loop() {
    // HT_SCHED::Scheduler::getInstance().run();

    //uint8_t *ptr = testDisplay.getBuffer();
    if (millis() - last_blink > 100) {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
      

      //SerialUSB.SerialUSB.printf("%p\n", (void*)ptr);
      //SerialUSB.println(chopped_display[0], HEX);
      

      
      
      // HAL_SPI_Transmit(&hspi2, testDisplay.getBuffer(), testDisplay.getBufferSize(), HAL_MAX_DELAY); // Transmit the display buffer using DMA
      //SerialUSB.println(testDisplay.getBufferSize());
      //SerialUSB.SerialUSB.printf("Count: %d\n", count);  
  }

  if (millis() - last_print > 1000) {

    //dump_dma_spi_state();
    last_print = millis();
  


      digitalWrite(PC14, HIGH); // set CS high before transmit, low in callback after transmit
      SerialUSB.println("Starting DMA Transmit");
//    SerialUSB.printf("SPI SR: 0x%08lX\n", hspi2.Instance->SR);
// SerialUSB.printf("SPI CFG1: 0x%08lX\n", hspi2.Instance->CFG1);
// SerialUSB.printf("SPI CFG2: 0x%08lX\n", hspi2.Instance->CFG2);
// SerialUSB.printf("SPI CR1:  0x%08lX\n", hspi2.Instance->CR1);
SerialUSB.printf("SPI CR2:  0x%08lX\n", hspi2.Instance->CR2);
      SCB_CleanDCache_by_Addr((uint32_t*)testDisplay.getBuffer(), testDisplay.getBufferSize()); // Clean D-Cache before DMA transfer
      hspi2.Instance->CR1 &= ~SPI_CR1_SPE;
      HAL_SPI_Transmit_DMA(&hspi2, testDisplay.getBuffer(), testDisplay.getBufferSize()); // Transmit the display buffer using DMA
    
// Clear any stale flags before enabling DMA

// __HAL_SPI_CLEAR_EOTFLAG(&hspi2);

// __HAL_SPI_CLEAR_TXTFFLAG(&hspi2);

// // Start DMA transmission

// HAL_SPI_Transmit_DMA(&hspi2, testDisplay.getBuffer(), testDisplay.getBufferSize());
 
// // Force SPI to start sending

// SET_BIT(hspi2.Instance->CR1, SPI_CR1_CSTART);
 
// // Ensure DMA requests stay enabled

// SET_BIT(hspi2.Instance->CFG1, SPI_CFG1_TXDMAEN);

 delay(100);
      spi_tx_complete = false;
    
}
}
