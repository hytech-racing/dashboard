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
 * @brief Start the driver object, setting up pins and configuring a buffer for
 * the screen contents
 *
 * @return boolean true: success false: failure
 */
boolean HyTech_SharpMem::begin(void) {
  // this display is weird in that _cs is active HIGH not LOW like every other
  // SPI device
  digitalWrite(_cs, LOW);

  // Set the vcom bit to a defined state
  _sharpmem_vcom = SHARPMEM_BIT_VCOM;

  sharpmem_buffer = (uint8_t *)malloc(((WIDTH * HEIGHT) / 8) + (2*HEIGHT)); //malloc of a buffer that is the size of the display in pixels + the 2 extra pixels on either side for datasheet

  if (!sharpmem_buffer)
    return false;

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
    @brief Draws a single pixel in image buffer

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
  if ((x < 0) || (x >= _width + 1) || (y < 0) || (y >= _height))
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
    sharpmem_buffer[(y * WIDTH + x) / 8] |= pgm_read_byte(&set[x & 7]);
  } else {
    sharpmem_buffer[(y * WIDTH + x) / 8] &= pgm_read_byte(&clr[x & 7]);
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