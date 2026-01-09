#ifndef CLOCKVIEW_H
#define CLOCKVIEW_H

#include <Arduino.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Initialize clock in main
void initClock(Adafruit_SH110X &oled);

// Timer change every 1 sec.
void clockTimerView();

// Display clock in oled screen
void showClockOLED(bool force = false);

// Helper function
int getHour();
int getMinute();

#endif