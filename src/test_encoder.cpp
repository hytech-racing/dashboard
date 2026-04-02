#include <Arduino.h>
#include <Rotary.h>

// for encoder 1
#define ENC1_A PD4
#define ENC1_B PD5
#define ENC1_BTN PA8 // Wtf is this pin

Rotary enc1(ENC1_A, ENC1_B, ENC1_BTN);//, ENC1_BTN);


//list? for the screens or something?

static int enc1_counter = 0;  // represents postiion, not event
static bool enc1_moved = false; 

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

    if (digitalRead(67) == HIGH) { //idk if low is pressed or high is pressed...
        Serial.println("Dial1 Button Pressed");
        //delay(200); // crude debounce????
    }


}

void enc1_rotate() {
    unsigned char result = enc1.process();
    if (result == enc1.clockwise()) {
        //enc1_counter++;
        Serial.println("cw turn");
        enc1_moved = true;
    } else if (result == enc1.counterClockwise()) {
        //enc1_counter--; 
        Serial.println("ccw turn");
        enc1_moved = true;

    } 
    //Serial.println(enc1_counter);
}

void enc1_press() {
    if (enc1.buttonPressedReleased(20)) {
        Serial.println("Button pressed");
        enc1_counter++;
        Serial.println(enc1_counter);

    }
}


void setup() { // this will be replaced w/ init, serial goes in main.cpp.
    Serial.begin(115200);

    // encoder pins? pull up?
    pinMode(ENC1_A, INPUT);
    pinMode(ENC1_B, INPUT);
    pinMode(ENC1_BTN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC1_A), enc1_rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_B), enc1_rotate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_BTN), enc1_press, CHANGE);

  
}


void loop() {
    //Serial.println(enc1_counter);
}
