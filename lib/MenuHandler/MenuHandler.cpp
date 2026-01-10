#include "MenuHandler.h"
#include "EncoderInput.h"
#include <Wire.h>

// external methods
extern void showMainScreen();
extern void showMainMenu(int sel);
extern void showRadioMenu(int sel);
extern void showSettings();
extern void applyStation(int idx);
extern void exitApp();

static MenuState currentState = MS_MAIN_SCREEN;
static int mainMenuIndex = 0;
static int radioIndex = 0;
static int mainMenuCount = 3; // Radio / Settings / Exit
static int radioCount = 10;   // Radio station quantity
static InputEvent lastEvent = {0, NONE};

void menuInit()
{
    currentState = MS_MAIN_SCREEN;
    mainMenuIndex = 0;
    radioIndex = 0;
}

// read inputs and save to lastEvent
void updateInputs()
{
    lastEvent = readInput();
}

// main menu dispatcher
void handleMenu()
{
    switch (currentState)
    {
    case MS_MAIN_SCREEN:
        // encoder change volume
        if (lastEvent.btn == SHORT)
        {
            currentState = MS_MAIN_MENU;
            mainMenuIndex = 0;
        }
        // delta should be used in target function - example volume handler in main loop
        break;

    case MS_MAIN_MENU:
        if (lastEvent.delta != 0)
        {
            mainMenuIndex = (mainMenuIndex + lastEvent.delta + mainMenuCount) % mainMenuCount;
        }
        if (lastEvent.btn == SHORT)
        {
            // Choose
            if (mainMenuIndex == 0)
                currentState = MS_RADIO_MENU;
            else if (mainMenuIndex == 1)
                currentState = MS_SETTINGS;
            else if (mainMenuIndex == 2)
                currentState = MS_EXIT_CONFIRM;
        }
        if (lastEvent.btn == LONG)
        {
            // back to main screen
            currentState = MS_MAIN_SCREEN;
        }
        break;

    case MS_RADIO_MENU:
        if (lastEvent.delta != 0)
        {
            radioIndex = (radioIndex + lastEvent.delta + radioCount) % radioCount;
        }
        if (lastEvent.btn == SHORT)
        {
            applyStation(radioIndex); // play radio station
                                      // optional - back to main menu  or main screen
        }
        if (lastEvent.btn == LONG)
        {
            currentState = MS_MAIN_MENU; // return
        }
        break;

    case MS_SETTINGS:
        // here need to add settings handler
        if (lastEvent.btn == LONG)
            currentState = MS_MAIN_MENU;
        break;

    case MS_EXIT_CONFIRM:
        if (lastEvent.btn == SHORT)
        {
            exitApp();
        }
        else if (lastEvent.btn == LONG)
        {
            currentState = MS_MAIN_MENU;
        }
        break;
    }
}

void render()
{
    switch (currentState)
    {
    case MS_MAIN_SCREEN:
        showMainScreen();
        break;
    case MS_MAIN_MENU:
        showMainMenu(mainMenuIndex);
        break;
    case MS_RADIO_MENU:
        showRadioMenu(radioIndex);
        break;
    case MS_SETTINGS:
        showSettings();
        break;
    case MS_EXIT_CONFIRM:
        break;
    }
}

bool isInMenu()
{
    return currentState != MS_MAIN_SCREEN;
}

bool isInRadioMenu()
{
    return currentState == MS_RADIO_MENU;
}
