#ifndef VOLUMEENCODER_H
#define VOLUMEENCODER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "EncoderInput.h"

// Global variables (extern - that mean will be define in .cpp)
extern volatile int counter;
extern unsigned long lastUpdate;
extern const int showTime;

// funcs
void volumeEvent(const InputEvent &ev, Adafruit_SH110X &display);
void showVolume(int counter, Adafruit_SH110X &display); // decraled somewhere
void displayHelloMsg(Adafruit_SH110X &display, bool wifiConnect);

#endif
