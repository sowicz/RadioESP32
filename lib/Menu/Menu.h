#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "EncoderInput.h"

const int MENU_TIMEOUT = 5000;
extern bool wifiConnect;

void initMenu(Adafruit_SH110X &display);
void handleMenu(const InputEvent &ev);
bool isInMenu();

#endif