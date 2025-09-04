#ifndef LED_H
#define LED_H

#include <stdint.h>

#define NUM_NEOPIXELS 4

uint32_t hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l);

void led_set_RGBW(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void led_set_RGB(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void led_render();

#endif
