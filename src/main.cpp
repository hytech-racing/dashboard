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
#define SHARP_CS PB7
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
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
//HT_TASK::Task screen_task(&init_screen_task, &screen_refresh_task, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period

HTX_Display testDisplay(SHARP_CS); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now

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
  //HTXDisplayInstance::create(PB7); 
  
  VCRData_sInstance::create();
  VCFData_sInstance::create();
  
  // Create can singletons
  CANInterfacesInstance::create(VCFInterfaceInstance::instance(), ACUInterfaceInstance::instance(), VCRInterfaceInstance::instance(), DrivebrainInterfaceInstance::instance()); 
  //auto main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<DashCAN::dash_read_switch>();
  //DashCANInterfaceObjectsInstance::create(main_can_recv, &stm_can); // NOLINT (Not sure why it's uninitialized. I think it is.)
  
  scheduler.setTimingFunction(micros);
  
  //HT_SCHED::Scheduler::getInstance().schedule(neopixels_task);
  //HT_SCHED::Scheduler::getInstance().schedule(screen_task);
  
  HT_SPI_Init();
  FDCAN_Init();

  //dashDisplayInstance::instance().init();
  
  testDisplay.init(&hspi2);
  testDisplay.hytech_animation();
  spi_tx_complete = true;

}
int brake = 0;
void loop() {
  //scheduler.run();
    
    if (spi_tx_complete)
    {
    testDisplay.draw_background();
    testDisplay.invert_display(VCFInterfaceInstance::instance().is_mech_brake_pressed());
    testDisplay.draw_vertical_pedal_bar(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent, 17);
    testDisplay.draw_battery_bar(ACUInterfaceInstance::instance().get_curr_data().pack_voltage * 100.0 / 530.0);
    testDisplay.draw_icons(DrivebrainInterfaceInstance::instance().get_db_state_data().vn_status, VCRInterfaceInstance::instance().get_curr_car_state().drivetrain_state, DrivebrainInterfaceInstance::instance().get_db_state_data().drivebrain_in_ctrl);
    testDisplay.display_speeds(VCRInterfaceInstance::instance().get_curr_wheel_data().actual_speed);
    testDisplay.send_display_buffer(&hspi2);
    spi_tx_complete = false;
    }
    
    ///@brief blink led
    if (millis() - last_blink > 100)
    {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
    }
    

    if (millis() - last_print > 200)
    {
      SerialUSB.print("looping");

      // dump_dma_spi_state();
      last_print = millis();

      FDCAN_write(0x55, tx, 3);

    FDCAN_read(CANInterfacesInstance::instance(), millis());
    Serial.println(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.accel_is_implausible);
    Serial.println(VCFInterfaceInstance::instance().get_curr_data().stamped_pedals.pedals_data.brake_percent);
    }
}

