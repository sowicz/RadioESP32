#ifndef SHOWVOLUME_H
#define SHOWVOLUME_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Funkcja do wyświetlania głośności
void showVolume(int counter, Adafruit_SH110X &display);

#endif
