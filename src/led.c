#include "led.h"
#include "stm32h7xx_hal.h"

// period = 59  . 32% of 59 about 19
#define PWM_LO (19)

#define BPP 4 // 4 bytes per pixel (RGBW)
#define NUM_BYTES (NUM_NEOPIXELS * BPP)

// 8 bytes per byte of data per pixel (pwm period for 0 and 1)
// times two for two pixels in a buffer
#define BUFFER_LEN (BPP * 8 * 2)
uint8_t dma_buffer[BUFFER_LEN] = {0};
uint_fast8_t dma_buffer_p = 0;

// pull in variables from main.c
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch1;

//buffer for LED data
uint8_t led_data[NUM_BYTES] = {0};

// function to scale 8 bit values to modify brightness. Used in this lib to compensate for perceived brightness of colors
static inline uint8_t scale8(uint8_t x, uint8_t scale) {
  return ((uint16_t)x * scale) >> 8;
}

// Fast hsl2rgb algorithm: https://stackoverflow.com/questions/13105185/fast-algorithm-for-rgb-hsl-conversion
uint32_t hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l) {
	if(l == 0) return 0;

	volatile uint8_t  r, g, b, lo, c, x, m;
	volatile uint16_t h1, l1, H;
	l1 = l + 1;
	if (l < 128)    c = ((l1 << 1) * s) >> 8;
	else            c = (512 - (l1 << 1)) * s >> 8;

	H = h * 6;              // 0 to 1535 (actually 1530)
	lo = H & 255;           // Low byte  = primary/secondary color mix
	h1 = lo + 1;

	if ((H & 256) == 0)   x = h1 * c >> 8;          // even sextant, like red to yellow
	else                  x = (256 - h1) * c >> 8;  // odd sextant, like yellow to green

	m = l - (c >> 1);
	switch(H >> 8) {       // High byte = sextant of colorwheel
	 case 0 : r = c; g = x; b = 0; break; // R to Y
	 case 1 : r = x; g = c; b = 0; break; // Y to G
	 case 2 : r = 0; g = c; b = x; break; // G to C
	 case 3 : r = 0; g = x; b = c; break; // C to B
	 case 4 : r = x; g = 0; b = c; break; // B to M
	 default: r = c; g = 0; b = x; break; // M to R
	}

	return (((uint32_t)r + m) << 16) | (((uint32_t)g + m) << 8) | ((uint32_t)b + m);
}

void led_set_RGBW(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    if (index >= NUM_NEOPIXELS) return;

    led_data[(BPP * index) + 0] = scale8(g, 0xB0);
    led_data[(BPP * index) + 1] = r;
    led_data[(BPP * index) + 2] = scale8(b, 0xF0);
    led_data[(BPP * index) + 3] = w;
}

void led_set_RGB(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    led_set_RGBW(index, r, g, b, 0x00);
}

void led_render() {

    // If render is called before prev dma sequence is done, restart
    // TODO: if this is interrupted, it may not reset the LED order
    if (dma_buffer_p != 0 || hdma_tim2_ch1.State != HAL_DMA_STATE_READY) {
        for(uint8_t i = 0; i < BUFFER_LEN; ++i) dma_buffer[i] = 0;
        dma_buffer_p = 0;
        HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
            return;
    }

    // start by loading first two pixels from rgb buffer into dma buffer
    for (uint_fast8_t i = 0; i < 8; i++) {
        dma_buffer[i +  0] = PWM_LO << (((led_data[0] << i) & 0x80) > 0);
        dma_buffer[i +  8] = PWM_LO << (((led_data[1] << i) & 0x80) > 0);
        dma_buffer[i + 16] = PWM_LO << (((led_data[2] << i) & 0x80) > 0);
        dma_buffer[i + 24] = PWM_LO << (((led_data[3] << i) & 0x80) > 0);
        dma_buffer[i + 32] = PWM_LO << (((led_data[4] << i) & 0x80) > 0);
        dma_buffer[i + 40] = PWM_LO << (((led_data[5] << i) & 0x80) > 0);
        dma_buffer[i + 48] = PWM_LO << (((led_data[6] << i) & 0x80) > 0);
        dma_buffer[i + 56] = PWM_LO << (((led_data[7] << i) & 0x80) > 0);         
    }

    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)dma_buffer, BUFFER_LEN);
    dma_buffer_p = 2; // finished loading first 2 pixels
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {

    if (dma_buffer_p < NUM_NEOPIXELS) {
        // DMA finished first half
        // load next pixel into the first half of buffer
        for (uint_fast8_t i = 0; i < 8; i++) {
            dma_buffer[i +  0] = PWM_LO << (((led_data[BPP * dma_buffer_p + 0] << i) & 0x80) > 0);
            dma_buffer[i +  8] = PWM_LO << (((led_data[BPP * dma_buffer_p + 1] << i) & 0x80) > 0);
            dma_buffer[i + 16] = PWM_LO << (((led_data[BPP * dma_buffer_p + 2] << i) & 0x80) > 0);
            dma_buffer[i + 24] = PWM_LO << (((led_data[BPP * dma_buffer_p + 3] << i) & 0x80) > 0);
        }
        dma_buffer_p++;
    } else if (dma_buffer_p < NUM_NEOPIXELS + 2) {
        // Send nothing for two cycles at the end
        for(uint8_t i = 0; i < BUFFER_LEN / 2; i++) dma_buffer[i] = 0;
        dma_buffer_p++;
    }

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {

    if (dma_buffer_p < NUM_NEOPIXELS) {
        // DMA finished first half
        // load next pixel into the first half of buffer
        for (uint_fast8_t i = 0; i < 8; i++) {
            dma_buffer[i + 32] = PWM_LO << (((led_data[BPP * dma_buffer_p + 0] << i) & 0x80) > 0);
            dma_buffer[i + 40] = PWM_LO << (((led_data[BPP * dma_buffer_p + 1] << i) & 0x80) > 0);
            dma_buffer[i + 48] = PWM_LO << (((led_data[BPP * dma_buffer_p + 2] << i) & 0x80) > 0);
            dma_buffer[i + 56] = PWM_LO << (((led_data[BPP * dma_buffer_p + 3] << i) & 0x80) > 0);
        }
        dma_buffer_p++;
    } else if (dma_buffer_p < NUM_NEOPIXELS + 2) {
        // Send nothing for two cycles at the end
        for(uint8_t i = BUFFER_LEN / 2; i < BUFFER_LEN; i++) dma_buffer[i] = 0;
        dma_buffer_p++;
    } else {
        dma_buffer_p = 0;
        HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
    }
}