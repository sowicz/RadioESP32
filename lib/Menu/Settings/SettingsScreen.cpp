#include "SettingsScreen.h"
#include <WiFi.h>

void showIpAddress(Adafruit_SH110X &display)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);

    display.setCursor(0, 0);
    display.println("Device IP:");

    String ip = WiFi.localIP().toString();

    display.setCursor(0, 16);
    display.println(ip);

    display.display();
}
