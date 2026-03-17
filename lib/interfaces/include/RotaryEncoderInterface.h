#ifndef ROTARY_ENCODER_INTERFACE_H
#define ROTARY_ENCODER_INTERFACE_H

#include <Arduino.h>
#include "STM32encoder.h" //come back to this

struct rotary_encoder_s {
    int16_t counter = 0;      
    int32_t pos = 0;     
    int32_t prev_pos = 0; 
    int32_t pos_change = 0;   
    int8_t direction = 0;  
};

class RotaryEncoderInterface
{
public:
    RotaryEncoderInterface() = default;

private:
    STM32Encoder _enc = STM32ENcoder(TIM2, 0x07);  // change depending on pin

}

#endif


