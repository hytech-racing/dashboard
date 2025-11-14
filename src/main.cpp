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
//#include "lcdInterface.h"
#include "newDisplay.h"
#include "VCFInterface.h"
#include "ACUInterface.h"
#include "VCRInterface.h"

#include "main.h"

#include "HT_SPI.h"
#include "HT_Display.h"
#include "HT_FDCAN.h"


#define LED_PIN PA3
#define SHARP_CS PB7
#define SHARP_CLK PB10
#define SHARP_MOSI PB15
#define CHOPPED_SIZE 10080
#define SHARPMEM_BIT_WRITECMD (0x01) // 0x80 in LSB format
#define SHARPMEM_BIT_VCOM (0x02)     // 0x40 in LSB format
#define SHARPMEM_BIT_CLEAR (0x04)    // 0x20 in LSB format

uint32_t last_blink = 0;
uint32_t last_print = 0;
uint16_t chopped_len = CHOPPED_SIZE;
bool led_state = false;
int count = 0;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};
static uint8_t chopped_display[CHOPPED_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

// CAN setup
uint32_t rxId;
uint8_t rxData[8];
uint8_t rxLen;

uint8_t tx[8] = {0x11, 0x22, 0x33};

uint8_t vcom = SHARPMEM_BIT_VCOM; //VCOM toggle command

void send_display_buffer();

void custom_handle_error(int num) {
  while(1) {
    digitalWrite(PA3, HIGH);
    delay(500);
    digitalWrite(PA3, LOW);
    delay(500);
  }
}

extern "C" void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    SerialUSB.printf("SPI Error Callback triggered!\n");
}


// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
// HT_TASK::Task screen_task(&init_screen_task, &screen_refresh_task, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period

HyTech_SharpMem testDisplay(SHARP_CS, 320, 240); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now

void setup() {

  pinMode(PA3, OUTPUT);
  pinMode(PB7, OUTPUT);
  pinMode(PC14, OUTPUT);

  digitalWrite(PB7, LOW);
  digitalWrite(PC14, LOW);

  SerialUSB.begin(115200);
  delay(3000);
  SerialUSB.println("Starting");


  
  // Create Interfaces
  ACUInterfaceInstance::create();
  VCRInterfaceInstance::create();
  VCFInterfaceInstance::create(sys_time::hal_millis(), 50UL); //TODO: needs to be updated to use constexpr
  //dashDisplayInstance::create(PB7, 320, 240); 
  
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
  FDCAN_Init();

  //dashDisplayInstance::instance().init();
  
  testDisplay.begin();
// for (int i = 0; i < CHOPPED_SIZE; i += 1){//(320/8)+2){

//     // save address byte

//     chopped_display[i] = i;//((i) / (42)) + 1;
//     SerialUSB.println(chopped_display[i]);
//   }
//   chopped_display[0] = 0x01;
//   chopped_display[1] = 0x02;

}

void loop() {
    testDisplay.drawBitmap(hytech_logo_x, hytech_logo_y, epd_bitmap_Hytech_Logo, hytech_logo_size, hytech_logo_size, 0);

    ///@brief blink led
    if (millis() - last_blink > 100)
    {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
    }

  if (millis() - last_print > 1000) {

    //dump_dma_spi_state();
    last_print = millis();
    send_display_buffer();

    FDCAN_write(0x55, tx, 3);

    if (FDCAN_read(&rxId, rxData, &rxLen))
    {
      SerialUSB.print("Received ID: 0x");
      SerialUSB.print(rxId, HEX);
      SerialUSB.print(" Data: ");
      for (int i = 0; i < rxLen; i++)
      {
        SerialUSB.print(rxData[i], HEX);
        SerialUSB.print(" ");
      }
      Serial.println();
    }

    spi_tx_complete = false;
    last_print = millis();
}
}


void send_display_buffer()
{
  digitalWrite(PB7, HIGH); // set CS high before transmit, low in callback after transmit
  digitalWrite(PC14, HIGH);
  //SerialUSB.println("Starting DMA Transmit");


  uint8_t toggle_vcom[] = {vcom | SHARPMEM_BIT_WRITECMD};
  HAL_SPI_Transmit(&hspi2, toggle_vcom, sizeof(toggle_vcom), HAL_MAX_DELAY); // Test transmit to ensure SPI is working
  vcom = vcom ? 0x00 : SHARPMEM_BIT_VCOM;

  SCB_CleanDCache_by_Addr((uint32_t *)testDisplay.getBuffer(), testDisplay.getBufferSize()); // Clean D-Cache before DMA transfer
  hspi2.Instance->CR1 &= ~SPI_CR1_SPE;
  HAL_SPI_Transmit_DMA(&hspi2, testDisplay.getBuffer(), testDisplay.getBufferSize()); // Transmit the display buffer using DMA
}