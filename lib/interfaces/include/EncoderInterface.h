#ifndef ENCODERINTERFACE_H
#define ENCODERINTERFACE_H

#include <Arduino.h>
#include <STM32encoder.h>

#include "etl/singleton.h"
#include <etl/delegate.h>

#define CLK_1 = PD4//Dial 1_A
#define D1_B = PD5// Dial_1_B
#define CLK_2 = PD6// Dial_2_A
#define D2_B = PD7// DIAL_2_B


struct rotary_encoder_s {

};

class EncoderInterface
{
    public:
        EncoderInterface();
        //_ccu_data(ccu_data) {Serial.begin(9600);};

        void setupEncoders();
        void updateEncoder();
        static void isr1();
        static void isr2();
        void setValue(int dt_value);

        bool isButtonPressed() const { return _encoder_data.state; };
    private:
        rotary_encoder_s _encoder_data;
};

using EncoderInterfaceInstance = etl::singleton<EncoderInterface>;

#endif
