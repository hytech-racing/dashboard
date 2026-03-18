#include "EncoderInterfaceThing.h"
#include <MD_REncoder.h>
int pin1 = PD4;
int pin2 = PD5;

MD_REncoder enc = MD_REncoder(pin1, pin2);

void init_encoder(int pin1, int pin2) // whys this here????
{
    //MD_REncoder enc = MD_REncoder(pin1, pin2);
    
    attachInterrupt(digitalPinToInterrupt(pin1), rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pin2), rotate, CHANGE);
  // add above 2 lines to main setup
}


void rotate() {
  int counter = 0;

  unsigned char result = enc.read();
  if (result == DIR_CW) {
    counter++;
    Serial.println(counter);
  } else if (result == DIR_CCW) {
    counter--;
    Serial.println(counter);
  }
}