#ifndef STM32_CAN_H
#define STM32_CAN_H

#include "stm32h7xx_hal.h"
#include "stm32h750xx.h"
#include <stdint.h>

#define FDCAN_TypeDef FDCAN_GlobalTypeDef
#include "stm32h7xx_hal_fdcan.h"
// You can adjust this to fit your message structure
typedef struct {
    uint32_t id;
    uint8_t extended;
    uint8_t dlc;
    uint8_t data[64];
    uint8_t* buf;
    uint8_t len;
} CAN_message_t;

class STM32_CAN {
public:
    STM32_CAN(FDCAN_TypeDef* instance);

    bool begin();
    bool read(CAN_message_t& msg);
    bool write(const CAN_message_t& msg);

private:
    FDCAN_HandleTypeDef hfdcan;
};

#endif
