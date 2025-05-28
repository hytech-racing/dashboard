#ifndef DASH_CONSTANTS_H
#define DASH_CONSTANTS_H



//HT Scheduler Constants
constexpr unsigned long NEOPIXEL_UPDATE_PRIORITY = 90;
constexpr unsigned long NEOPIXEL_UPDATE_PERIOD = 100000;      // 100 000 us = 10 Hz

constexpr unsigned long SCREEN_REFRESH_PRIORITY = 100;
constexpr unsigned long SCREEN_REFRESH_PERIOD = 33333;        // 33 333 us = 30 Hz

#endif /* DASH_CONSTANTS_H */