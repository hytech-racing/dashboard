#ifndef TEST_ENCODER_H
#define TEST_ENCODER_H


#include <Arduino.h>
#include <Rotary.h>

#include "SharedFirmwareTypes.h"
#include "hytech.h"

#define ENC1_A PD4
#define ENC1_B PD5
#define ENC1_BTN PA8

volatile int enc1_counter; 
volatile bool enc1_moved; 

void enc1_init();
void enc1_rotate();
void enc1_press();
void enc1_check();

#endif