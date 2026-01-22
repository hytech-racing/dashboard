#ifndef LCDINTERFACE_H
#define LCDINTERFACE_H

// LCD Libraries
#include "HT_Display.h"
#include "Adafruit_GFX.h"

// Fonts
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include "HT_SPI.h"

#include "bitmaps.h"

#include "etl/singleton.h"

// Defines

#define LED_PIN PA3
#define SHARP_CS PB4
#define SHARP_CLK PB10
#define SHARP_MOSI PB15

class HTX_Display
{
public:
    HyTech_SharpMem _display; // bigger display is 320x240 smaller one is 400x240
    HTX_Display(uint8_t cs) : _display(cs, 320, 240) {}
    void init(SPI_HandleTypeDef *hspi);
    void startup();
    void hytech_animation();
    // void driver_animation(StartupAnimations);
    void draw_background();
    void clear_display_buffer() { _display.clearDisplayBuffer(); }
    void draw_vertical_pedal_bar(float val, int initial_x_coord);
    void draw_battery_bar(int percent);
    void display_speeds(float rpm);
    void draw_icons(uint8_t vn_status, uint8_t car_state, bool db_in_ctrl);
    void invert_display(bool invert_criteria);
    void draw_popup(String title);
    void send_display_buffer(SPI_HandleTypeDef *hspi);
    uint8_t current_page = 0;

private:
    void draw_rectangle_right_corner(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    String twoDigits(int number);
    bool blink();

    bool last_blink = false;
    uint32_t last_blink_millis = 0;
    uint16_t _black = 0x00;
    uint16_t _white = 0xFF;

    /* SPI Sending */
    uint8_t vcom = SHARPMEM_BIT_VCOM; // VCOM toggle command
    SPI_HandleTypeDef *_hspi = NULL;
    HAL_StatusTypeDef _spi_status;
};

using HTXDisplayInstance = etl::singleton<HTX_Display>;

namespace conversions
{
    // MPH conversion
    const float GEARBOX_RATIO = 11.86;                                                     // TODO: Need to update
    const float WHEEL_DIAMETER = 0.4064;                                                   // meters NEED to update
    const float RPM_TO_METERS_PER_SECOND = WHEEL_DIAMETER * 3.1415 / GEARBOX_RATIO / 60.0; // TODO: Need to update
    const float METERS_PER_SECOND_TO_RPM = 1.0 / RPM_TO_METERS_PER_SECOND;
    const float METERS_PER_SECOND_TO_MPH = 2.2369;
}

enum StartupAnimations
{
    NONE,
    MIKHAIL_CAT,
    DAVID_KNIGHT_GLIZZY,
    DAVID_KNIGHT_2,
    ICE_SPICE
};

#endif /* LCDINTERFACE_H */