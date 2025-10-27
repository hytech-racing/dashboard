#include "HT_Display.h"

#define TOGGLE_VCOM                                                            \
  do {                                                                         \
    _sharpmem_vcom = _sharpmem_vcom ? 0x00 : SHARPMEM_BIT_VCOM;                \
  } while (0);

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

/**
 * @brief Construct a new Adafruit_SharpMem object with software SPI
 *
 * @param clk The clock pin
 * @param mosi The MOSI pin
 * @param cs The display chip select pin - **NOTE** this is ACTIVE HIGH!
 * @param width The display width
 * @param height The display height
 * @param freq The SPI clock frequency desired (unlikely to be that fast in soft
 * spi mode!)
 */
HyTech_SharpMem::HyTech_SharpMem(uint8_t cs, uint16_t w, uint16_t h, uint32_t freq)
    : Adafruit_GFX(w, h) {
  //_stm_spi = stm_spi;
  _cs = cs;
  _height = 320;
  _width = 240;
}

/**
 * @brief Start the driver object, setting up pins and configuring a buffer for
 * the screen contents
 *
 * @return boolean true: success false: failure
 */
bool HyTech_SharpMem::begin(void) {
  // this display is weird in that _cs is active HIGH not LOW like every other
  // SPI device
  digitalWrite(_cs, LOW);

  // Set the vcom bit to a defined state
  _sharpmem_vcom = SHARPMEM_BIT_VCOM;

  sharpmem_buffer = (uint8_t *)malloc(((_width * _height) / 8) + (2*_height)); //create a buffer that is the size of the display (bytes) + the 2 extra pixels on edge
  _size_of_buffer = ((_width * _height) / 8) + (2*_height);
  int bytes_per_line = _width / 8;

  if (!sharpmem_buffer)
    return false;

  for (int i = 0; i < sizeof(sharpmem_buffer); i += WIDTH) {
    uint8_t line[bytes_per_line + 2];

    // save address byte
    sharpmem_buffer[i * bytes_per_line] = ((i + 1) / (WIDTH / 8)) + 1; // [i+byytes_per_line get the first index on each row (equals to is stolen from adafruit lib)]
  }
  setRotation(0);
  
  return true;
}

// 1<<n is a costly operation on AVR -- table usu. smaller & faster
static const uint8_t PROGMEM set[] = {1, 2, 4, 8, 16, 32, 64, 128},
                             clr[] = {(uint8_t)~1,  (uint8_t)~2,  (uint8_t)~4,
                                      (uint8_t)~8,  (uint8_t)~16, (uint8_t)~32,
                                      (uint8_t)~64, (uint8_t)~128};

                                      
/**************************************************************************/
/*!
    @brief Draws a single pixel in image buffer is adjusted to be able to send one continuous message with DMA

    @param[in]  x
                The x position (0 based)
    @param[in]  y
                The y position (0 based)
    @param color The color to set:
    * **0**: Black
    * **1**: White
*/

/**************************************************************************/
void HyTech_SharpMem::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return;

  switch (rotation) {
  case 1:
    _swap_int16_t(x, y);
    x = WIDTH - 1 - x;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = HEIGHT - 1 - y;
    break;
  }

  if (color) {
    sharpmem_buffer[((y * WIDTH + 1) + x + 1) / 8] |= pgm_read_byte(&set[x & 7]);
  } else {
    sharpmem_buffer[((y * WIDTH +1)  + x + 1) / 8] &= pgm_read_byte(&clr[x & 7]);
  }
}

/**************************************************************************/
/*!
    @brief Renders the contents of the pixel buffer on the LCD
*/
/**************************************************************************/
void HyTech_SharpMem::refresh_buffer(void) {
  uint16_t i, currentline;

  uint8_t bytes_per_line = WIDTH / 8;
  uint8_t actual_usable_bytes_per_line = bytes_per_line - 1;
  uint16_t totalbytes = (WIDTH * HEIGHT) / 8;

  for (i = 0; i < totalbytes; i += bytes_per_line) { //index over the bytes in the line
    uint8_t line[bytes_per_line + 2];

    // Send address byte
    currentline = ((i + 1) / (WIDTH / 8)) + 1;
    line[0] = currentline;
    // copy over this line
    memcpy(line + 1, sharpmem_buffer + i, bytes_per_line);
    // Send end of line
    line[bytes_per_line + 1] = 0x00;
    // send it!
    spidev->transfer(line, bytes_per_line + 2);
  }

  // Send another trailing 8 bits for the last line
  spidev->transfer(0x00);
  digitalWrite(_cs, LOW);
  spidev->endTransaction();
}

/**************************************************************************/
/*!
    @brief Clears the screen
*/
/**************************************************************************/
void HyTech_SharpMem::clearDisplay() {
  memset(sharpmem_buffer, 0xff, (WIDTH * HEIGHT) / 8);

  spidev->beginTransaction();
  // Send the clear screen command rather than doing a HW refresh (quicker)
  digitalWrite(_cs, HIGH);

  uint8_t clear_data[2] = {(uint8_t)(_sharpmem_vcom | SHARPMEM_BIT_CLEAR),
                           0x00};
  spidev->transfer(clear_data, 2);

  TOGGLE_VCOM;
  digitalWrite(_cs, LOW);
  spidev->endTransaction();
}