#include <Arduino.h>

#include <SPI.h>
#include <STM32_CAN.h>

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
static CAN_message_t CAN_RX_msg;


HT_TASK::TaskResponse read_can_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    DashCANInterfaceObjects& dash_interface_objects = DashCAN::DashCANInterfaceObjectsInstance::instance();
    CANInterfaces& dash_can_interfaces = DashCAN::CANInterfacesInstance::instance(); 
    process_ring_buffer(stm_can, dash_interface_objects.CAN_inMsg, dash_can_interfaces, sys_time::hal_millis(), dash_interface_objects.can_recv_switch);
    return HT_TASK::TaskResponse::YIELD;
}

// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);


void setup() {

  // Initialize CAN
  stm_can.begin();
  stm_can.setBaudRate(115200);
  
  // Create Interfaces
  ACUInterfaceInstance::create();
  VCRInterfaceInstance::create();
  VCFInterfaceInstance::create(sys_time::hal_millis(), 50UL); //needs to be updated to use constexpr

  VCRData_sInstance::create();
  VCFData_sInstance::create();

  // Create can singletons
  DashCAN::CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance()); 
  auto main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<DashCAN::dash_read_switch>();
  //DashCAN::DashCANInterfaceObjectsInstance::create(main_can_recv, &stm_can); // NOLINT (Not sure why it's uninitialized. I think it is.)


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
