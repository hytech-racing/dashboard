#include <Arduino.h>

#include <SPI.h>
//#include "CANInterface.h"
#include <cstdint>
#include "test_encoder.h"

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



bool spi_tx_complete = true;

/* Scheduler setup */
HT_SCHED::Scheduler &scheduler = HT_SCHED::Scheduler::getInstance();

// Task Init
HT_TASK::Task heartbeat_task(&init_heartbeat, &heartbeat, 1000, 500000); // .5 second period
HT_TASK::Task can_task(&init_can, &can_read, 80, 10000); // 10 ms period
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
HT_TASK::Task screen_task(&init_screen, &screen_refresh, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period
int count = 0;
//HTX_Display testDisplay(SHARP_CS); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now


void enc1_press() {
  count++;
}
void enc1_init() {
    //attachInterrupt(digitalPinToInterrupt(ENC1_A), enc1_rotate, CHANGE); // add enc1
    //attachInterrupt(digitalPinToInterrupt(ENC1_B), enc1_rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PA8), enc1_press, CHANGE);

}


void setup() {
  
  Serial.begin(115200);
  Serial.print("yo");
  //Global Data Singletons (should work on removing)
  // VCRData_sInstance::create();
  // VCFData_sInstance::create();
  //Rotary enc1(ENC1_A, ENC1_B);
  // // added here, since we have interrupts we don't tneed to write much
  Rotary enc1(ENC1_A, ENC1_B);
  pinMode(PA8, INPUT);
  enc1_init();
  scheduler.setTimingFunction(micros);
  
  HT_SCHED::Scheduler::getInstance().schedule(heartbeat_task);
  HT_SCHED::Scheduler::getInstance().schedule(can_task);
  HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  spi_tx_complete = true;
}

void loop() {
  scheduler.run();
  Serial.println(count);
}

