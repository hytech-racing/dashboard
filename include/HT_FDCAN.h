#ifndef HT_FDCAN_WRAPPER
#define HT_FDCAN_WRAPPER

#include "stm32h7xx_hal.h"
#include "stm32h750xx.h"

int FDCAN_Init();
void FDCAN1_GPIO_Init_PD0D1(void);
int FDCAN_write(uint32_t id, const uint8_t *data, uint8_t len);
int FDCAN_read(uint32_t *id, uint8_t *data, uint8_t *len);
#endif