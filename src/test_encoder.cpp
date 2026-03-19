#include <Arduino.h>
#include <Rotary.h>

// for encoder 1
#define ENC1_A PD4
#define ENC1_B PD5
#define ENC1_BTN PA8 // actual button

Rotary enc1(ENC1_A, ENC1_B);


//list? for the screens or something?

volatile int enc1_counter = 0;  // represents postiion, not event
volatile bool enc1_moved = false; 

void enc1_init() {
    attachInterrupt(digitalPinToInterrupt(ENC1_A), enc1_rotate, CHANGE); // add enc1
    attachInterrupt(digitalPinToInterrupt(ENC1_B), enc1_rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_BTN), enc1_press, CHANGE);

}

void enc1_rotate() {
    unsigned char result = enc1.process();
    if (result == DIR_CW) {
        enc1_counter++;
        Serial.println(enc1_counter);
        enc1_moved = true;
  } else if (result == DIR_CCW) {
        enc1_counter--; 
        Serial.println(enc1_counter);
        enc1_moved = true;

  } 
  enc1_check();
}

void enc1_press() {
    if (digitalRead(ENC1_BTN) == LOW) { //dial buttons are pulled up to 3.3v, so ithink it'll be read on low. we can always test
        Serial.println("Dial1 Button Pressed");
        delay(200); // crude debounce???? use millis in real application
    }
}

//commenting out stuff that belongs in main

//void setup() { // this will be replaced w/ init, serial goes in main.cpp.
    //Serial.begin(115200);

    // encoder pins? pull up?
    
    //attachInterrupt(digitalPinToInterrupt(ENC1_A), enc1_rotate, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(ENC1_B), enc1_rotate, CHANGE);
  
//}

void enc1_check() { // renamed this to check, usable in the main loop, only issue is that 
    static int last1 = 0;
    // this'll be called in the enc1_rotate because it's attached to an itnerrupt
    noInterrupts(); //don't want to keep redeclaring in loop, why not just use enc1_counter and moved vars?
    int c1 = enc1_counter;
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

