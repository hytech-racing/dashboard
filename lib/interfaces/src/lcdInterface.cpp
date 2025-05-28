#include "lcdInterface.h"

Adafruit_SharpMem _display(SHARP_CLK, SHARP_MOSI, SHARP_CS, 320, 240); //bigger display is 320x240 smaller one is 400x240


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
    _display.fillRect(100, 5, 100, 20, BLACK);
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
    int w = (100-percent) * (96.0/100);
    lcdHelper::draw_rectangle_right_corner(197, 7, w, 16, WHITE);
}


void dashDisplay::display_speeds(float rpm) {
    _display.setFont(&FreeSans24pt7b);
    _display.setTextSize(2);

    _display.setCursor(100, 140);
    /** TODO: convert from RPM to MPH*/
    double wheelspeed = abs(rpm * conversions::RPM_TO_METERS_PER_SECOND);
    // SerialUSB.println(wheelspeed);
    uint16_t mph = (int) (wheelspeed * conversions::METERS_PER_SECOND_TO_MPH);
    // SerialUSB.println(mph);
    _display.println(lcdHelper::twoDigits(mph));
    // _display.println(HYTECH_low_voltage_ro_fromS(bms_voltages->low_voltage_ro));

    // _display.println(mph);
    _display.setTextSize(1);
    _display.setFont(&FreeSans12pt7b);
    _display.setCursor(125, 165);
    _display.print("MPH");
    _display.setFont(&FreeSans12pt7b);
}

// void dashDisplay::draw_icons(MCU_STATUS_t *m, VN_STATUS_t *v) {

//     /* no gps icon   = 0 */
//     /* vn flashing   = 1 */
//     /* vn solid      = 2 */

//     /* all units are pixels */
//     int offset = 3;
//     int icon_size = 27;

//     /* horizontal icons on top of the screen */
//     int gps_icon_pos_x = 270 - icon_size - offset;
//     int rtd_icon_pos_x = gps_icon_pos_x - icon_size - offset;
//     int latched_icon_pos_x = rtd_icon_pos_x - icon_size - 1;
//     int icon_pos_y = 40;

//     if (v->vn_gps_status >= 2) {
//         _display.drawBitmap(gps_icon_pos_x, icon_pos_y, epd_bitmap_gps, 27, 27, BLACK);
//     } else if (v->vn_gps_status == 1){
//         if (blink()) { _display.drawBitmap(gps_icon_pos_x, icon_pos_y, epd_bitmap_gps, 27, 27, BLACK); }
//     } else if (v->vn_gps_status == 0) {
//         _display.drawBitmap(gps_icon_pos_x, icon_pos_y, epd_bitmap_nogps, 27, 27, BLACK);
//     }

//     if (check_ready_to_drive(m)) {
//         _display.drawBitmap(rtd_icon_pos_x, icon_pos_y, epd_bitmap_rtd, 27, 27, BLACK);
//     } else {
//         if (blink()) { _display.drawBitmap(rtd_icon_pos_x, icon_pos_y, epd_bitmap_rtd, 27, 27, BLACK); }
//     }

//     if (check_latched(m)) {
//         _display.drawBitmap(latched_icon_pos_x, icon_pos_y, epd_bitmap_latch_symbol, 27, 27, BLACK);
//     } else {
//         if (blink()) { _display.drawBitmap(latched_icon_pos_x, icon_pos_y, epd_bitmap_latch_symbol, 27, 27, BLACK); }
//     }
// }

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
String lcdHelper::twoDigits(int number) {
    if(number <= 9) {
        return "0" + String(number);
    }
    if(number >= 10 && number <= 99) {
        return String(number);
    }
    if(number >=100 && number <=999) {
        return String(number/10);
    }
    return String(number);
}

void lcdHelper::draw_popup(String title) {
    int width = 200;
    int height = 150;
    _display.fillRect(160-(width/2), 120 - (height/2), width, height, BLACK);
    width-=10;
    height-=10;
    _display.fillRect(160-(width/2), 120 - (height/2), width, height, WHITE);
    _display.setFont(&FreeSansBold12pt7b);
    _display.setCursor(160-(width/2)+1, 120 - (height/2)+20);
    int x = _display.getCursorX();
    _display.println(title);
    _display.setFont(&FreeSans12pt7b);
    _display.setCursor(x, _display.getCursorY());
}