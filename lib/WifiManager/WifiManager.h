#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "MainScreen.h"


bool connectToWifi(const char* ssid, const char* password, Adafruit_SH110X &display);
bool isWifiConnected();

#endif