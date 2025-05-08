#include "Adafruit_SharpMem.h"

static const uint8_t set[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
static const uint8_t clr[] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};


void Adafruit_SharpMem::drawPixel(int16_t x, int16_t y, uint16_t color) {
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
    // Set pixel is an OR with bit pattern
    sharpmem_buffer[(y * WIDTH + x) / 8] |= set[x & 7];
  } else {
    // Clear pixel is an AND with bit pattern
    sharpmem_buffer[(y * WIDTH + x) / 8] &= clr[x & 7];
  }
}
