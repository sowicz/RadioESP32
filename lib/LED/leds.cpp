#include "leds.h"
#include <FastLED.h>

// =========================
// WS2812B LED
// =========================
#define LED_PIN 4
#define NUM_LEDS 8
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LED_BRIGHTNESS 50

CRGB leds[NUM_LEDS];
static int currentIndex = 0;

void leds_init()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(LED_BRIGHTNESS);
}

void leds_update()
{
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 150;

    unsigned long now = millis();
    if (now - lastUpdate < interval)
        return;

    lastUpdate = now;

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[currentIndex] = CRGB::White;
    FastLED.show();

    currentIndex++;
    if (currentIndex >= NUM_LEDS)
    {
        currentIndex = 0;
    }
}
