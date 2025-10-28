#include <Adafruit_GFX.h>
#include <Arduino.h>

#define SHARPMEM_BIT_WRITECMD (0x01) // 0x80 in LSB format
#define SHARPMEM_BIT_VCOM (0x02)     // 0x40 in LSB format
#define SHARPMEM_BIT_CLEAR (0x04)    // 0x20 in LSB format

/**
 * @brief Class to control the Sharp memory display
 *
 */
class HyTech_SharpMem : public Adafruit_GFX {
public:
  HyTech_SharpMem(uint8_t cs, uint16_t w = 320, uint16_t h = 240, uint32_t freq = 2000000);
  bool begin();
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint8_t getPixel(uint16_t x, uint16_t y);
  void clearDisplay();
  void refresh_buffer(void);
  void clearDisplayBuffer();
  /**
   * @brief Get a pointer to the display buffer.
   * This allows direct access to the internal framebuffer.
   *
   * @return uint8_t* Pointer to the framebuffer memory.
   */
  uint8_t *getBuffer() { return sharpmem_buffer; }
  uint16_t getBufferSize() { return _size_of_buffer; }
  

private:
  Adafruit_SPIDevice *spidev = NULL; //need to figure this one out
  uint8_t *sharpmem_buffer = NULL;
  uint16_t _size_of_buffer;
  uint16_t _display_width = 320;
  uint16_t _display_height = 240;
  uint16_t _test = 240;
  uint8_t _cs;
  uint8_t * _stm_spi;
  uint8_t _sharpmem_vcom;
};