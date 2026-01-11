#include "Menu.h"
#include "MainScreen.h"
#include "Settings/SettingsScreen.h"
#include "RadioStations/RadioStations.h"
#include "EncoderInput.h"
#include "Screens.h"

// Variables inner
static Adafruit_SH110X *oled;
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
        oled->setCursor(8, i * 16 + 4);
        oled->println(menuItems[i]);
    }
    oled->display();
}

static void showMainScreen()
{
    displayHelloMsg(*oled, wifiConnect);
}

// ------------------ API ------------------

void initMenu(Adafruit_SH110X &display)
{
    oled = &display;
    showMainScreen();
}

void handleMenu(const InputEvent &ev, AppScreen &currentScreen)
{
    if (isInRadioMenu())
        return;

    if (ev.btn == SHORT)
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
                // currentScreen = SETTINGS_SCREEN;
                showIpAddress(*oled);
            }
            else if (strcmp(menuItems[selectedOption], "Radio stations") == 0)
            {
                currentScreen = RADIO_STATIONS_SCREEN;
                // handleRadioStations(*oled, ev);
            }
            else if (strcmp(menuItems[selectedOption], "Exit") == 0)
            {
                inMenu = false;
                currentScreen = MAIN_SCREEN;
                showMainScreen();
            }
        }
        lastInteraction = millis();
    }
    else if (ev.btn == LONG)
    {
        if (inMenu)
        {
            inMenu = false;
            currentScreen = MAIN_SCREEN;
            showMainScreen();
            lastInteraction = 0;
        }
    }

    // Encoder
    if (inMenu && ev.delta != 0)
    {
        int step = (ev.delta > 0) ? 1 : -1;
        selectedOption = (selectedOption + step + menuSize) % menuSize;
        showMenu(selectedOption);
        lastInteraction = millis();
    }
    // Timeout return to main screen
    if (inMenu && lastInteraction != 0 && (millis() - lastInteraction > MENU_TIMEOUT))
    {
        inMenu = false;
        currentScreen = MAIN_SCREEN;
        showMainScreen();
        lastInteraction = 0;
    }
}

bool isInMenu()
{
    return inMenu;
}