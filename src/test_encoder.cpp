#include <Arduino.h>
#include <Rotary.h>

// for encoder 1
#define ENC1_A PD4
#define ENC1_B PD5
#define ENC1_BTN PA7

Rotary enc1(ENC1_A, ENC1_B);
//list? for the screens or something?

volatile int enc1_counter = 0;  // represents postiion, not event
volatile bool enc1_moved = false; 

void enc1_rotate() {
    unsigned char result = rotary.process();
    if (result == DIR_CW) {
        enc1_counter++;
        Serial.println(enc1_counter);
        enc1_moved = true;
  } else if (result == DIR_CCW) {
        enc1_counter--; 
        Serial.println(enc1_counter);
        enc1_moved = true;
  } 
}

void setup() {
    Serial.begin(115200);

    // encoder pins? pull up?

    attachInterrupt(digitalPinToInterrupt(ENC1_A), enc1_rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_B), enc1_rotate, CHANGE);
  
}

void loop() {
    static int last1 = 0;

    noInterrupts();
    int c1 = enc1_count;
    bool m1 = enc1_moved;
    enc1_moved = false;
    interrupts();


    if (m1 && c1 != last1) { // if moved and count changed
        Serial.print("Dial1: ");
        Serial.println(c1);
        last1 = c1;
    }

    if (digitalRead(ENC1_BTN) == LOW) { //idk if low is pressed or high is pressed...
        Serial.println("Dial1 Button Pressed");
        delay(200); // crude debounce????
    }

    }

