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

#include "SysClock_Config.h"

#include "HT_SPI.h"
#include "HT_Display.h"
#include "HT_FDCAN.h"


#define LED_PIN PA3
#define SHARP_CS PB4
#define SHARP_CLK PB10
#define SHARP_MOSI PB15


uint32_t last_blink = 0;
uint32_t last_print = 0;
bool led_state = false;
int count = 0;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};

// CAN setup
uint32_t rxId;
uint8_t rxData[8];
uint8_t rxLen;

uint8_t tx[8] = {0x11, 0x22, 0x33};

bool spi_tx_complete = true;

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


/* Scheduler setup */
HT_SCHED::Scheduler &scheduler = HT_SCHED::Scheduler::getInstance();

// Task Init
HT_TASK::Task heartbeat_task(&init_heartbeat, &heartbeat, 1000, 500000); // .5 second period
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
HT_TASK::Task screen_task(&init_screen, &screen_refresh, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period

//HTX_Display testDisplay(SHARP_CS); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now

void setup() {

  pinMode(PA3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PC14, OUTPUT);

  digitalWrite(PB4, LOW);
  digitalWrite(PC14, LOW);

  SerialUSB.begin(115200);

  
  // Create Interfaces
  ACUInterfaceInstance::create();
  VCRInterfaceInstance::create();
  VCFInterfaceInstance::create(sys_time::hal_millis(), 50UL); //TODO: needs to be updated to use constexpr


  
  //Global Data Singletons (should work on removing)
  VCRData_sInstance::create();
  VCFData_sInstance::create();
  
  // Create can singletons
  CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance(), DrivebrainInterfaceInstance::instance()); 

  scheduler.setTimingFunction(micros);
  
  HT_SCHED::Scheduler::getInstance().schedule(heartbeat_task);
  HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  FDCAN_Init();
  
  spi_tx_complete = true;
}

void loop() {
  scheduler.run();
    

    
    // ///@brief blink led
    // if (millis() - last_blink > 100)
    // {
    //   last_blink = millis();
    //   led_state = !led_state;
    //   digitalWrite(PA3, led_state);
    // }
    

    // if (millis() - last_print > 200)
    // {
    //   SerialUSB.print("looping");

    //   // dump_dma_spi_state();
    //   last_print = millis();

    //   FDCAN_write(0x55, tx, 3);

    // FDCAN_read(CANInterfacesInstance::instance(), millis());
    // Serial.println(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.accel_is_implausible);
    // Serial.println(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent);
    //}
}

