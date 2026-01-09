#ifndef RADIOSTATIONS_H
#define RADIOSTATIONS_H

#include <Adafruit_SH110X.h>

const int RADIO_MENU_TIMEOUT = 5000;

extern int currentStationIndex;
extern bool inRadioMenu;

void showRadioStations(Adafruit_SH110X &display, int selected);
void handleRadioStations(Adafruit_SH110X &display, int pinS1, int pinS2, int pinSW);
bool isInRadioMenu();

#endif
