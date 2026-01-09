#include "ClockView.h"

static struct tm timeinfo;
static uint32_t lastClockUpdate = 0;
static uint32_t clockInterval = 1000;

static int lastDisplayedHour = -1;
static int lastDisplayedMinute = -1;

// pointer for display (transfered via initClock)
static Adafruit_SH110X *displayPtr = nullptr;

// ---- implementation ----
void initClock(Adafruit_SH110X &oled)
{
    displayPtr = &oled;
}

void clockTimerView()
{
    if (millis() - lastClockUpdate >= clockInterval)
    {
        lastClockUpdate = millis();

        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Can't reach timedata");
            return;
        }
    }
}

int getHour()
{
    return timeinfo.tm_hour;
}

int getMinute()
{
    return timeinfo.tm_min;
}

void showClockOLED(bool force)
{
    if (!displayPtr)
        return; // no display provided so return null

    int h = getHour();
    int m = getMinute();

    if (!force && h == lastDisplayedHour && m == lastDisplayedMinute)
        return;

    // TIME WINTER or SUMMER
    lastDisplayedHour = h;
    lastDisplayedMinute = m;

    // clear partial display
    displayPtr->fillRect(64, 2, 64, 16, SH110X_BLACK);

    // display in HH:MM
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", h, m);

    displayPtr->setTextSize(2);
    displayPtr->setTextColor(SH110X_WHITE);
    displayPtr->setCursor(64, 2);
    displayPtr->print(buf);

    displayPtr->display();
}