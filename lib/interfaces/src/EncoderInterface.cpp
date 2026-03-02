#include "EncoderInterface.h"

const int bounce_delay = 100;
volatile unsigned long last_interrupt_time = 0;

void EncoderInterace::isr1() {
    unsigned long current_time = millis();
    if (current_time - last_interrupt_time > bounce_delay) {
        int enc b_value = digitalRead(DT);
        EncoderInterfaceInstance::instance().setValue(enc_b_value);
        last_interrupt_time = current_time;
    }
}

void EncoderInterface::setValue(int enc_b_value) {

}

void EncoderInterface::setupEncoders() {

    
    pinMode(CLK_1, INPUT_PULLUP) //
    pinMode(D1_B, INPUT_PULLUP) // 
    pinMode(CLK_2, INPUT_PULLUP) // 
    pinMode(D2_B, INPUT_PULLUP) // 

    
    attachInterrupt(digitalPinToInterrupt(CLK), EncoderInterface::isr1, FALLING)
}

void EncoderInterface::updateEncoder() {
    int button_state = digitalRead(SW);

    if (_encoder.data.encoder.value != prev_value)
    {
        //print statements.
        Serial.println(_encoder.data.encoder_value);
    }
    prev_value = _encoder.data.state.encoder_value;

    if (button_state == LOW)
    {
       if (millis() - _encoder_data.last_button_press > bounce_delay) {
            _encoder.data.state = !_encoder.data.state;
            Serial.println("pressed");
            if (_encoder.data.state == false) {
                value = 0;
            } else {
                interrupts();
            }
       }
       _encoder.data.state.last_button_press = millis();
    }
    
    

}