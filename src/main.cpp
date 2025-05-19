

#include <Arduino.h>


#include "DASH_CONSTANTS.h"
#include "lcdInterface.h"
#include <SPI.h>


//SPIClass spi(MOSI, MISO, SCLK);

// put function declarations here:


void setup() {
  dashDisplay::init();
  dashDisplay::startup();
}

void loop() {
    dashDisplay::display_refresh();
    delay(500); // 1/2 sec delay
}
