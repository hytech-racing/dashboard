#include <Arduino.h>

#include <SPI.h>
#include <STM32_CAN.h>
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


STM32_CAN stm_can(CAN1, ALT, RX_SIZE_256, TX_SIZE_16);
static CAN_message_t telem_can_rx_msg;



HT_TASK::TaskResponse init_can_task()
{
    stm_can.begin();
    stm_can.setBaudRate(115200);
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse read_can_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    if (stm_can.read(telem_can_rx_msg))
    {
      CANInterfaces& vcf_can_interfaces = CANInterfacesInstance::instance(); 
      DashCAN::dash_read_switch(vcf_can_interfaces, telem_can_rx_msg, sysMicros);
    }
    return HT_TASK::TaskResponse::YIELD;
}

// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);



void setup() {
  
  // Create Interfaces
  ACUInterfaceInstance::create();
  VCRInterfaceInstance::create();
  VCFInterfaceInstance::create(sys_time::hal_millis(), 50UL); //needs to be updated to use constexpr

  VCRData_sInstance::create();
  VCFData_sInstance::create();

  // Create can singletons
  CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance()); 
  auto main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<DashCAN::dash_read_switch>();
  //DashCANInterfaceObjectsInstance::create(main_can_recv, &stm_can); // NOLINT (Not sure why it's uninitialized. I think it is.)


  dashDisplay::init();
  dashDisplay::startup();


  // Setup scheduler
  HT_SCHED::Scheduler::getInstance().setTimingFunction(micros);

  HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);



}

void loop() {
    dashDisplay::display_refresh();
    delay(500); // 1/2 sec delay
    HT_SCHED::Scheduler::getInstance().run();
}
