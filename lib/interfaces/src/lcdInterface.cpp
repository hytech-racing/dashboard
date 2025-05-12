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

// void dashDisplay::driver_animation(StartupAnimations animation) {
//     switch (animation) {
//         case StartupAnimations::DAVID_KNIGHT_GLIZZY:
//             _display.drawBitmap(0,0, epd_bitmap_glizzy, 320, 240, BLACK);
//             _display.refresh();
//             delay(3000);
//             break;
//         case StartupAnimations::DAVID_KNIGHT_2:
//             _display.drawBitmap(0,0, epd_bitmap_david, 320, 240, BLACK);
//             _display.refresh();
//             delay(3000);
//             break;
//         case StartupAnimations::MIKHAIL_CAT:
//             _display.drawBitmap(60,25, epd_bitmap_cat, 200, 200, BLACK);
//             _display.refresh();
//             delay(3000);
//             break;
//         case StartupAnimations::ICE_SPICE:
//             for (int i = 0; i < 10; i++) {
//                 switch(i) {
//                     case 1:
//                         _display.drawBitmap(0,0, isp1, 320, 240, BLACK);
//                         break;
//                     case 2:
//                         _display.drawBitmap(0,0, isp2, 320, 240, BLACK);
//                         break;
//                     case 3:
//                         _display.drawBitmap(0,0, isp3, 320, 240, BLACK);
//                         break;
//                     case 4:
//                         _display.drawBitmap(0,0, isp4, 320, 240, BLACK);
//                         break;
//                     case 5:
//                         _display.drawBitmap(0,0, isp5, 320, 240, BLACK);
//                         break;
//                     case 6:
//                         _display.drawBitmap(0,0, isp6, 320, 240, BLACK);
//                         break;
//                     case 7:
//                         _display.drawBitmap(0,0, isp7, 320, 240, BLACK);
//                         break;
//                     case 8:
//                         _display.drawBitmap(0,0, isp8, 320, 240, BLACK);
//                         break;
//                     case 9:
//                         _display.drawBitmap(0,0, isp9, 320, 240, BLACK);
//                         break;
//                     case 10:
//                         _display.drawBitmap(0,0, isp10, 320, 240, BLACK);
//                         break;
//                 }
//             _display.refresh();
//             delay(100);
//             _display.clearDisplayBuffer();
//             }
//         default:
//             break;
//     }
//     _display.clearDisplayBuffer();
//     _display.drawBitmap(0,0, epd_bitmap_hytech_dashboard, 320, 240, BLACK);
// }

void dashDisplay::display_refresh() {

    _display.refresh();
}