#include <Arduino.h>
#include "RadioStations.h"
#include "EncoderInput.h"

static const int stationsQty = 3;
static const char *stationsName[stationsQty] = {"RMF", "AntyRadio", "ESKA"};

static unsigned long lastInteraction = 0;
static int selector = 0;
static int step = 0;
static int lastStateCLK = HIGH;
static int pinS1, pinS2, pinSW;
int currentStationIndex = 0;
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

void handleRadioStations(Adafruit_SH110X &display, const InputEvent &ev)
{
    selector = currentStationIndex;
    showRadioStations(display, selector);

    if (!inRadioMenu)
    {
        inRadioMenu = true;
        selector = currentStationIndex;
        showRadioStations(display, selector);
    }

    if (ev.btn == SHORT)
    {
        currentStationIndex = selector;
        inRadioMenu = false;
        return;
    }

    if (inRadioMenu && ev.delta != 0)
    {
        int step = (ev.delta > 0) ? 1 : -1;
        selector = (selector + step + stationsQty) % stationsQty;
        showRadioStations(display, selector);
        lastInteraction = millis();
        // if (digitalRead(pinS2) != currentState)
        //     step++;
        // else
        //     step--;

        // if (step >= 4)
        // {
        //     selector = (selector + 1) % stationsQty;
        //     showRadioStations(display, selector);
        //     step = 0;
        // }
        // else if (step <= -4)
        // {
        //     selector = (selector - 1 + stationsQty) % stationsQty;
        //     showRadioStations(display, selector);
        //     step = 0;
        // }
    }

    // if (millis() - lastInteraction > RADIO_MENU_TIMEOUT && lastInteraction != 0)
    if (inRadioMenu && lastInteraction != 0 && (millis() - lastInteraction > RADIO_MENU_TIMEOUT))
    {
        inRadioMenu = false;
        return;
    }
}

bool isInRadioMenu()
{
    return inRadioMenu;
}

int getCurrentStationIndex()
{
    return currentStationIndex;
}

const char *getCurrentStationName()
{
    return stationsName[currentStationIndex];
}