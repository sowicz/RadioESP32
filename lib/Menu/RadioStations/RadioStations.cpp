#include "RadioStations.h"
#include <Arduino.h>

static const int stationsQty = 3;
static const char *stationsName[stationsQty] = {"RMF", "AntyRadio", "ESKA"};

static unsigned long lastInteraction = 0;
int currentStationIndex = 0;
static int selector = 0;
static int step = 0;
static int lastStateCLK = HIGH;
bool inRadioMenu = false;

void showRadioStations(Adafruit_SH110X &display, int selected)
{
    display.clearDisplay();
    display.setTextSize(1);

    for (int i = 0; i < stationsQty; i++)
    {
        if (i == selected)
        {
            display.fillRect(0, i * 16, 128, 16, SH110X_WHITE);
            display.setTextColor(SH110X_BLACK);
        }
        else
        {
            display.setTextColor(SH110X_WHITE);
        }

        display.setCursor(8, i * 16 + 4);
        display.println(stationsName[i]);
    }

    display.display();
}

void handleRadioStations(Adafruit_SH110X &display, int pinS1, int pinS2, int pinSW)
{
    if (!inRadioMenu)
    {
        inRadioMenu = true;
        selector = currentStationIndex;
        lastStateCLK = digitalRead(pinS1);
        showRadioStations(display, selector);
    }

    if (digitalRead(pinSW) == LOW)
    {
        delay(50);
        if (digitalRead(pinSW) == LOW)
        {
            currentStationIndex = selector;
            inRadioMenu = false;
            return;
        }
    }

    int currentState = digitalRead(pinS1);
    if (currentState != lastStateCLK)
    {
        if (digitalRead(pinS2) != currentState)
            step++;
        else
            step--;

        if (step >= 4)
        {
            selector = (selector + 1) % stationsQty;
            showRadioStations(display, selector);
            step = 0;
        }
        else if (step <= -4)
        {
            selector = (selector - 1 + stationsQty) % stationsQty;
            showRadioStations(display, selector);
            step = 0;
        }
    }

    lastStateCLK = currentState;
    if (millis() - lastInteraction > RADIO_MENU_TIMEOUT && lastInteraction != 0)
    {
        inRadioMenu = false;
        return;
    }
}
