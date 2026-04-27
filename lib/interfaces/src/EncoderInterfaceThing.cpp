#include "EncoderInterfaceThing.h"


Encoder::Encoder(int pin1, int pin2, int button, Rotary enc)
    : m_pin1 { pin1 }
    , m_pin2 { pin2 }
    , m_button { button }
    //, m_enc() { enc }
{}



void Encoder::enc_init(Rotary enc) {

    // encoder pins? pull up?
    Rotary enc(m_pin1, m_pin2, m_button);
    pinMode(m_pin1, INPUT);
    pinMode(m_pin2, INPUT);
    pinMode(m_button, INPUT);
    attachInterrupt(digitalPinToInterrupt(m_pin1), Encoder::enc_rotate(enc), CHANGE);
    attachInterrupt(digitalPinToInterrupt(m_pin2), Encoder::enc_rotate(enc), CHANGE);
    attachInterrupt(digitalPinToInterrupt(m_button), Encoder::enc_press(enc), CHANGE);
};


void Encoder::enc_rotate(Rotary enc) {
      unsigned char result = enc.process();
    if (result == enc.clockwise()) {
        enc_counter--;
        //Serial.println("cw turn");
        enc_moved = true;
    } else if (result == enc.counterClockwise()) {
        enc_counter++; 
        //Serial.println("ccw turn");
        enc_moved = true;

    } 
    //Serial.println(enc1_counter);
;}

void Encoder::enc_press(Rotary enc) {
      if (enc.buttonPressedReleased(20)) {
        Serial.println("Button pressed");
        Serial.println(int(enc_counter/2));

    }
  
};


