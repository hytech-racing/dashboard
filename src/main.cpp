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

#include "HT_SPI.h"


#define LED_PIN PA3
#define SHARP_CS PB7
#define SHARP_CLK PB10
#define SHARP_MOSI PB15

static CAN_message_t telem_can_rx_msg;
STM32_CAN stm_can(FDCAN1);

uint32_t last_blink = 0;
bool led_state = false;
int count = 0;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};

void custom_handle_error(int num) {
  while(1) {
    digitalWrite(PA3, HIGH);
    delay(500);
    digitalWrite(PA3, LOW);
    delay(500);
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

  pinMode(PA3, OUTPUT);

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
  
  HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  // HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  HT_SPI_Init();
  
}

void loop() {
    // HT_SCHED::Scheduler::getInstance().run();

    if (millis() - last_blink > 100) {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
      digitalWrite(PB7, LOW); // set CS low before transmit, high in callback after transmit
      SerialUSB.println("Starting DMA Transmit");
      HAL_SPI_Transmit_DMA(&hspi2, test_tx, sizeof(test_tx));
      SerialUSB.println("DMA Transmit Done");
      SerialUSB.printf("Count: %d\n", count);
    }
    
  }

  
