#include "RotaryEncoderInterface.h"



void RotaryEncoderInterface::setup_encoders()
{
    bool dial1_a = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4);
    bool dial1_b = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5);
    bool dial2_a = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6);
    bool dial2_b = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);

    //
}


void RotaryEncoderInterface::update_encoders()
{

}



void RotaryEncoderInterface::update_single_encoder(rotary_encoder_s &encoder, bool a, bool b)
{

}



int RotaryEncoderInterface::get_dial1_position() const
{
    return _dial1_encoder.position;
}

int RotaryEncoderInterface::get_dial2_position() const
{
    return _dial2_encoder.position;
}

