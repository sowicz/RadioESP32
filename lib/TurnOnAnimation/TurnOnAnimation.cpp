#include "TurnOnAnimation.h"


const int interval = 15;
int helloTextX = 128;


void turnOnAnimation(Adafruit_SH110X &display) {
    unsigned long helloTimeFrame = millis();

    while (helloTextX > 0){
        unsigned long actualTimeFrame = millis();

        if (helloTimeFrame - actualTimeFrame >= interval){
            helloTimeFrame = actualTimeFrame;
            helloTextX--;
            display.clearDisplay();
            display.setTextWrap(false);
            display.setTextSize(2);
            display.setTextColor(SH110X_WHITE);
            display.setCursor(helloTextX, 24);
            display.println("Hello");

            display.display();
        }
    }
}