#ifndef ENCODER_INTERFACE_THING_H
#define ENCODER_INTERFACE_THING_H

#include <Arduino.h>
#include <Rotary.h>
#include "SharedFirmwareTypes.h"
#include "hytech.h"

class Encoder {

    private:
        int m_pin1{};
        int m_pin2{};
        int m_button{};
        Rotary m_enc(){};
    public: 
        Encoder(int pin1, int pin2, int button, Rotary enc);
        void enc_init(Rotary enc); 
        void enc_rotate(Rotary enc);
        void enc_press(Rotary enc);
       // int enc_counter();
       static int enc_counter;
       static bool enc_moved;

};

void Encoder::enc_init(Rotary enc) {}
void Encoder::enc_rotate(Rotary enc) {}
void Encoder::enc_press(Rotary enc) {}


#endif