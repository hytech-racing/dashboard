#include "STM32encoder.h"

STM32Encoder enc(TIM2, 0x07); 

int16_t enc_counter = 0;
int32_t enc_prev_pos = 0;

void RotaryEncoderInterface::setup_encoder(counter) {
  Serial.begin(115200);
  enc.bind(counter, 1, 0, 2);
  enc.circular(true);
}

void RotaryEncoderInterface::update_encoder(pos, prev_pos, pos_change, direction, counter) {
  if (enc.isUpdated()) {
    pos = enc.pos();
    direction = enc.dir();
    pos_change = pos - prev_pos;
    Serial.printf(
      "pos:%5ld dir:%2d counter:%3d, pos_change: %3d\n"
      , pos
      , direction
      , counter,
      , pos_change);
    pos = prev_pos;
  }
}