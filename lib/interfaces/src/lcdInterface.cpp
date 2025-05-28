#include "lcdInterface.h"

Adafruit_SharpMem _display(SHARP_CLK, SHARP_MOSI, SHARP_CS, 400, 240);


void dashDisplay::init() {
    // set non-needed Display pins low
    pinMode(PC5, OUTPUT);
    pinMode(PB1, OUTPUT);
    pinMode(PA3, OUTPUT);
    digitalWrite(PC5, LOW);
    digitalWrite(PB1, LOW);
}

void dashDisplay::startup() {
    hytech_animation();
    //driver_animation(StartupAnimations::NONE);
}

// @brief Function to display general hytech startup animation
// @note Taken from 2024 dash code

void dashDisplay::hytech_animation() {
    _display.begin();
    _display.clearDisplay();
    _display.setRotation(0);
    _display.drawBitmap(hytech_logo_x, hytech_logo_y, epd_bitmap_Hytech_Logo, hytech_logo_size, hytech_logo_size, BLACK);
    _display.refresh();
    delay(2000);
    for (int i = 1; i > -116; i-=3) {
        _display.clearDisplayBuffer();
        _display.drawBitmap(hytech_logo_x + i, hytech_logo_y, epd_bitmap_Hytech_Logo, hytech_logo_size, hytech_logo_size, BLACK);
        _display.refresh();
    }
    delay(20);
    _display.drawBitmap(hytech_words_x + 45, hytech_words_y, epd_bitmap_HytechWords, hytech_words_x_size, hytech_words_y_size, BLACK);
    _display.refresh();
    _display.setFont(&FreeSans12pt7b);
    String greeting = "Cook";
    int length = greeting.length();
    _display.setCursor(hytech_logo_x-length*3, hytech_logo_y + hytech_logo_size + 30);
    _display.setTextColor(BLACK);
    _display.setTextSize(1);
    _display.println(greeting);
    _display.refresh();
    delay(2000);
    _display.clearDisplay();
}

void dashDisplay::draw_background_bitmap() {
    _display.clearDisplayBuffer();
    _display.drawBitmap(0,0, epd_bitmap_hytech_dashboard, 320, 240, BLACK);
    _display.fillRect(320-40, 30, 40, 200, WHITE);
    _display.fillRect(283, 36, 305-283, 210-36, BLACK);
    _display.fillRect(283-3, (36 + 210 - 36)/2+15, 25, 7, WHITE);
    _display.fillRect(0, 215, 130, 25, WHITE);
    // _display.fillRect(100, 5, 100, 20, BLACK);
}

// draws white rect top down
void dashDisplay::draw_vertical_pedal_bar(float val, int initial_x_coord) {
    double ZERO_PERCENT_VAL = 175;
    val = (val > 100) ? val = 100 : (val < 0) ? val = 0 : val = val;
    int i = (int) (100-val) * (ZERO_PERCENT_VAL/100.0);
    _display.fillRect(initial_x_coord, 35, 18, i, WHITE);
}

void dashDisplay::draw_battery_bar(int percent) {
    // 0%: 59
    // 100% 0
    int w = (100-percent) * (59.0/100);
    lcdHelper::draw_rectangle_right_corner(103, 220, w, 8, WHITE);
}

void lcdHelper::display_refresh() 
{
    _display.refresh();
}
void lcdHelper::draw_rectangle_right_corner(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int16_t i = x; i > x-w; i--) {
        _display.writeFastVLine(i, y, h, color);
    }
    // _display.refresh();
}