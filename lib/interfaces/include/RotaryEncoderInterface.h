#ifndef ROTARY_ENCODER_INTERFACE_H
#define ROTARY_ENCODER_INTERFACE_H

#include <Arduino.h>
#include "STM32encoder.h"

struct rotary_encoder_s {
    int16_t counter = 0;      
    int32_t pos;     
    int32_t prev_pos = 0; 
    int32_t pos_change = 0;   
    int8_t direction;  
};

class RotaryEncoderInterface
{
public:

    void setup_encoder(counter);
    void update_encoder();

private:
    STM32Encoder _enc = STM32ENcoder(TIM2, 0x07);  // change depending on pin
    rotary_encoder_s _encoder_data;

};

#endif


