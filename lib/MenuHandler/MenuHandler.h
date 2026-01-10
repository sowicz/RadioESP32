#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <Arduino.h>
#include "EncoderInput.h" // InputEvent

enum MenuState
{
    MS_MAIN_SCREEN,
    MS_MAIN_MENU,
    MS_RADIO_MENU,
    MS_SETTINGS,
    MS_EXIT_CONFIRM
};

void menuInit();     // init internal state, display pointer itp.
void updateInputs(); // inputRead
void handleMenu();   // main menu handler
void render();       // screen refresh
bool isInMenu();     // helper methods
bool isInRadioMenu();

#endif // MENU_HANDLER_H
