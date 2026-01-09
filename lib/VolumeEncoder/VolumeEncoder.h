#ifndef VOLUMEENCODER_H
#define VOLUMEENCODER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


// Global variables (extern - that mean will be define in .cpp)
extern volatile int step;
extern volatile int counter;
extern int lastStateCLK;
extern unsigned long lastUpdate;
extern const int showTime;


// funcs
void volumeEncoder(int currentStatePinS1, int currentStatePinS2, Adafruit_SH110X &display);
void showVolume(int counter, Adafruit_SH110X &display);      // decraled somewhere
void displayHelloMsg(Adafruit_SH110X &display, bool wifiConnect); 

#endif
