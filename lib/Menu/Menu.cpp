#include "Menu.h"
#include "MainScreen.h"
#include "Settings/SettingsScreen.h"
#include "RadioStations/RadioStations.h"

// Variables inner
static Adafruit_SH110X *oled;
static int pinS1, pinS2, pinSW;
static int lastStateCLK = LOW;
static int step = 0;
static unsigned long lastInteraction = 0;
static int selectedOption = 0;
static bool inMenu = false;

static const int menuSize = 3;
static const char *menuItems[menuSize] = {"Radio stations", "Settings", "Exit"};

// ------------------ FUNCTIONS ------------------

static void showMenu(int selected)
{
    oled->clearDisplay();
    oled->setTextSize(1);
    for (int i = 0; i < menuSize; i++)
    {
        if (i == selected)
        {
            oled->fillRect(0, i * 16, 128, 16, SH110X_WHITE);
            oled->setTextColor(SH110X_BLACK);
        }
        else
        {
            oled->setTextColor(SH110X_WHITE);
        }
        // oled->setCursor(2, i * 18);
        // unsigned int a = i + 1;
        oled->setCursor(8, i * 16 + 4);
        oled->println(menuItems[i]);
    }
    oled->display();
}

static void showMainScreen()
{
    // extern bool wifiConnect; // extern mean that wifiConnect is already declared
    displayHelloMsg(*oled, wifiConnect);
}

// ------------------ API ------------------

void initMenu(Adafruit_SH110X &display, int s1, int s2, int sw)
{
    oled = &display;
    pinS1 = s1;
    pinS2 = s2;
    pinSW = sw;

    pinMode(pinS1, INPUT_PULLUP);
    pinMode(pinS2, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    lastStateCLK = digitalRead(pinS1);
    showMainScreen();
}

void handleMenu()
{
    if (inRadioMenu)
        return;

    if (digitalRead(pinSW) == LOW)
    {
        delay(50);
        if (digitalRead(pinSW) == LOW)
        {
            if (!inMenu)
            {
                inMenu = true;
                selectedOption = 0;
                showMenu(selectedOption);
            }
            else
            {
                Serial.print("Wybrano opcję: ");
                Serial.println(menuItems[selectedOption]);

                if (strcmp(menuItems[selectedOption], "Settings") == 0)
                {
                    showIpAddress(*oled);
                }
                else if (strcmp(menuItems[selectedOption], "Radio stations") == 0)
                {
                    inRadioMenu = true;
                    inMenu = false;
                    handleRadioStations(*oled, pinS1, pinS2, pinSW);
                }
                else if (strcmp(menuItems[selectedOption], "Exit") == 0)
                {
                    inMenu = false;
                    showMainScreen();
                }
            }
            lastInteraction = millis();
            while (digitalRead(pinSW) == LOW)
            {
            }
        }
    }

    // Encoder
    if (inMenu)
    {
        int currentState = digitalRead(pinS2);
        if (currentState != lastStateCLK)
        {
            if (digitalRead(pinS1) != currentState)
            {
                step++;
            }
            else
            {
                step--;
            }

            if (step >= 4)
            {
                selectedOption = (selectedOption + 1) % menuSize;
                showMenu(selectedOption);
                step = 0;
                lastInteraction = millis();
            }
            else if (step <= -4)
            {
                selectedOption = (selectedOption - 1 + menuSize) % menuSize;
                showMenu(selectedOption);
                step = 0;
                lastInteraction = millis();
            }
        }
        lastStateCLK = currentState;

        // Timeout return to main screen
        if (millis() - lastInteraction > MENU_TIMEOUT && lastInteraction != 0)
        {
            inMenu = false;
            showMainScreen();
        }
    }
}

bool isInMenu()
{
    return inMenu;
}