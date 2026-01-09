#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>



// Bitmaps
extern const unsigned char wifi_bitmap[] PROGMEM;
extern const unsigned char wifi_nok_bitmap[] PROGMEM;

extern const int wifi_bitmap_allArray_LEN;
extern const unsigned char* wifi_bitmap_allArray[2];


// Functions

void displayHelloMsg(Adafruit_SH110X &display, bool wifiConnect);
void showClockOLED(bool force);


#endif