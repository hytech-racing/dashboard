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
#define SHARP_CS PB7
#define SHARP_CLK PB10
#define SHARP_MOSI PB15
#define CHOPPED_SIZE 4

uint32_t last_blink = 0;
bool led_state = false;
int count = 0;

uint8_t test_tx[] = {0xDE, 0xAD, 0xBE, 0xEF};
uint8_t chopped_display[CHOPPED_SIZE] = {0x00, 0x01, 0x02, 0x03};

void custom_handle_error(int num) {
  while(1) {
    digitalWrite(PA3, HIGH);
    delay(500);
    digitalWrite(PA3, LOW);
    delay(500);
  }
}


// Task Init
HT_TASK::Task neopixels_task(&init_neopixels_task, &run_update_neopixels_task, NEOPIXEL_UPDATE_PRIORITY, NEOPIXEL_UPDATE_PERIOD);
// HT_TASK::Task screen_task(&init_screen_task, &screen_refresh_task, SCREEN_REFRESH_PRIORITY, SCREEN_REFRESH_PERIOD); // 100 ms period

HyTech_SharpMem testDisplay(SHARP_CS, 320, 240, 2000000); // Initialize display with CS pin, width, height, frequency, and no SPI pointer for now

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

  
  testDisplay.begin();
  //testDisplay.drawPixel(1, 1, 1); //should draw a pixel on the display
  //testDisplay.drawPixel(10, 10, 1); //should draw another pixel on the display

  //SerialUSB.println(testDisplay.getBufferSize());
  //SerialUSB.println(((320 * 240) / 8) + (2*240));
  SerialUSB.println(testDisplay.getBuffer()[0]);

for (int i = 0; i < CHOPPED_SIZE; i += 1){//(320/8)+2){

    // save address byte

    chopped_display[i] = i;//((i) / (42)) + 1;
    SerialUSB.println(chopped_display[i]);
  }

}

void loop() {
    // HT_SCHED::Scheduler::getInstance().run();

    if (millis() - last_blink > 100) {
      last_blink = millis();
      led_state = !led_state;
      digitalWrite(PA3, led_state);
      digitalWrite(PB7, HIGH); // set CS low before transmit, high in callback after transmit
      SerialUSB.println("Starting DMA Transmit");

      chopped_display[0] = 0x01;
      chopped_display[1] = 0x02;
      SerialUSB.println(chopped_display[0], HEX);
      uint8_t *bruh = chopped_display;
      SerialUSB.println(bruh[0], HEX);
      HAL_SPI_Transmit_DMA(&hspi2, bruh, sizeof(chopped_display)); // Transmit the display buffer using DMA
      //SerialUSB.println(testDisplay.getBufferSize());
      //SerialUSB.printf("Count: %d\n", count);
    }    
  }
