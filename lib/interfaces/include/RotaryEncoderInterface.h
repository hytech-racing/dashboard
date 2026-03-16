#ifndef ROTARY_ENCODER_INTERFACE_H
#define ROTARY_ENCODER_INTERFACE_H

struct rotary_encoder_s {
    int position = 0;
    int delta = 0;
    int last_state = 0;

    bool button_pressed = false; // are we using the button im confused


};

class RotaryEncoderInterface 
{
public:
    RotaryEncoderInterface() = default;

    void setup_encoders();
    void update_encoders();

    int get_dial1_position() const;
    int get_dial2_position() const;

    int get_dial1_delta();
    int get_dial2_delta();

    //
private:
    void update_single_encoder(rotary_encoder_s &encoder, bool a, bool b);

    rotary_encoder_s _dial1_encoder;
    rotary_encoder_s _dial2_encoder;
};


#endif