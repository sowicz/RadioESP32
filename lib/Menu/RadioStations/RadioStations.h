#ifndef RADIOSTATIONS_H
#define RADIOSTATIONS_H

#include "EncoderInput.h"
#include <Adafruit_SH110X.h>

const int RADIO_MENU_TIMEOUT = 5000;

extern int currentStationIndex;
extern bool inRadioMenu;

void showRadioStations(Adafruit_SH110X &display, int selected);
void handleRadioStations(Adafruit_SH110X &display, const InputEvent &ev);
bool isInRadioMenu();
int getCurrentStationIndex();
const char *getCurrentStationName();

#endif
