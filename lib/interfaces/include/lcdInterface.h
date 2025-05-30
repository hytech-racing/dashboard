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
    void display_speeds(float rpm);
    extern uint8_t current_page;
    void draw_icons(uint8_t vn_status, uint8_t car_state, bool is_latched, bool db_in_ctrl);
};

namespace lcdHelper
{
    void draw_rectangle_right_corner(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void display_refresh();
    String twoDigits(int number);
    void draw_popup(String title);
    bool blink();
    extern bool last_blink;
    extern uint32_t last_blink_millis;
};

namespace conversions
{
        // MPH conversion
    const float GEARBOX_RATIO =             11.86; //TODO: Need to update
    const float WHEEL_DIAMETER =            0.4064; // meters NEED to update
    const float RPM_TO_METERS_PER_SECOND =  WHEEL_DIAMETER * 3.1415 / GEARBOX_RATIO / 60.0; //TODO: Need to update
    const float METERS_PER_SECOND_TO_RPM =  1.0 / RPM_TO_METERS_PER_SECOND;
    const float METERS_PER_SECOND_TO_MPH =  2.2369;
}

enum StartupAnimations {
    NONE,
    MIKHAIL_CAT,
    DAVID_KNIGHT_GLIZZY,
    DAVID_KNIGHT_2,
    ICE_SPICE
};

#endif /* LCDINTERFACE_H */