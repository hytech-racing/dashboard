#ifndef ENCODERINTERFACE_H
#define ENCODERINTERFACE_H

#include <Arduino.h>
#include <Encoder.h>

#include "etl/singleton.h"
#include <etl/delegate.h>

#define CLK_1//Dial 1_A
#define D1_B = // Dial_1_B
#define CLK_2 = // Dial_2_A
#define D2_B = // DIAL_2_B


struct rotary_encoder_s {

};

class EncoderInterface
{
    public:
        //wtf? EncoderInterface() :
        //_ccu_data(ccu_data) {Serial.begin(9600);};

        void setupEncoder();
        void updateEncoder();
        static void isr1();
        void setValue(int dt_value);

        bool isButtonPressed() const { return _encoder_data.state; };
    private:
        rotary_encoder_s _encoder_data;
};

using EncoderInterfaceInstance = etl::singleton<RotaryEncoderInterface>;

#endif
