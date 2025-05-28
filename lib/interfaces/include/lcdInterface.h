#ifndef LCDINTERFACE_H
#define LCDINTERFACE_H

// LCD Libraries
#include "Adafruit_SharpMem.h"
#include "Adafruit_GFX.h"

// Fonts
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include "bitmaps.h"

// Defines
#define BLACK 0
#define WHITE 1

#define LED_PIN PA3
#define SHARP_CS PC4
#define SHARP_CLK PC10
#define SHARP_MOSI PB0




namespace dashDisplay 
{
    void init();
    void startup();
    void hytech_animation();
    //void driver_animation(StartupAnimations);

    void draw_background_bitmap();
    void draw_vertical_pedal_bar(float val, int initial_x_coord);
    void draw_battery_bar(int percent);

    int curr_page = 0;
};

namespace lcdHelper
{
    void draw_rectangle_right_corner(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void display_refresh();
};

enum StartupAnimations {
    NONE,
    MIKHAIL_CAT,
    DAVID_KNIGHT_GLIZZY,
    DAVID_KNIGHT_2,
    ICE_SPICE
};

#endif /* LCDINTERFACE_H */