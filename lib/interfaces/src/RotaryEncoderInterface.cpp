#include "STM32encoder.h"

STM32Encoder enc(TIM2, 0x07); 

int16_t enc_counter = 0;
int32_t enc_prev_pos = 0;

void setup() {
  Serial.begin(115200);
  enc.bind(&enc_counter, 1, 1, 100);
  enc.dynamic(20, 30);
}

void loop() {
  if (enc.isUpdated()) {
    enc_pos = enc.pos();
    Serial.printf(
      "pos:%5ld dir:%2d counter:%3d, pos_change: %3d\n"
      , pos
      , enc.dir()
      , enc_counter,
      , enc_pos - enc_prev_pos);
    enc_prev_pos = enc_pos;
  }
}