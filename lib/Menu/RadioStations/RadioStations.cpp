#include <Arduino.h>
#include "RadioStations.h"
#include "EncoderInput.h"
#include "Screens.h"

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

void handleRadioStations(Adafruit_SH110X &display, const InputEvent &ev, AppScreen &currentScreen)
{
    if (!inRadioMenu)
    {
        inRadioMenu = true;
        selector = currentStationIndex;
        lastInteraction = millis();
        showRadioStations(display, selector);
        return;
    }

    if (ev.btn == SHORT)
    {
        currentStationIndex = selector;
        inRadioMenu = false;
        currentScreen = MENU_SCREEN;

        // test
        Serial.print("Wybrano radio stacje: ");
        Serial.println(stationsName[currentStationIndex]);
        return;
    }

    if (inRadioMenu && ev.delta != 0)
    {
        int step = (ev.delta > 0) ? 1 : -1;
        int newSelector = (selector + step + stationsQty) % stationsQty;
        if (newSelector != selector)
        {
            selector = newSelector;
            showRadioStations(display, selector);
        }
        lastInteraction = millis();
    }

    // if (millis() - lastInteraction > RADIO_MENU_TIMEOUT && lastInteraction != 0)
    if (inRadioMenu && lastInteraction != 0 && (millis() - lastInteraction > RADIO_MENU_TIMEOUT))
    {
        inRadioMenu = false;
        currentScreen = MENU_SCREEN;
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