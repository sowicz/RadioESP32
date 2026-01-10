#include "EncoderInput.h"

// Default timers
static unsigned long ENC_DEBOUNCE_MS = 5;
static unsigned long BTN_DEBOUNCE_MS = 20;
static unsigned long LONG_PRESS_MS = 800;
static unsigned long DOUBLE_CLICK_MS = 400;

// Pins - set in encoderInit
static uint8_t ENC_A_PIN = 255;
static uint8_t ENC_B_PIN = 255;
static uint8_t BTN_PIN = 255;

// Inner state
static unsigned long lastEncTime = 0;
static unsigned long lastBtnTime = 0;
static int encPos = 0;
static int lastEncA = HIGH;
static int lastEncB = HIGH;
static int btnState = HIGH;
static int btnLastState = HIGH;
static unsigned long btnPressedAt = 0;
static int clickCount = 0;

// ENCODER STEP
static int encAccum = 0;
static int ENC_STEP_SIZE = 1;
static int ENC_THRESHOLD = 2;

void encoderSetStepSize(int s)
{
    if (s < 1)
        s = 1;
    ENC_STEP_SIZE = s;
}
void encoderSetThreshold(int t)
{
    if (t < 1)
        t = 1;
    ENC_THRESHOLD = t;
}

void encoderInit(uint8_t encAPin, uint8_t encBPin, uint8_t btnPin)
{
    ENC_A_PIN = encAPin;
    ENC_B_PIN = encBPin;
    BTN_PIN = btnPin;

    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
    pinMode(BTN_PIN, INPUT_PULLUP);

    lastEncA = digitalRead(ENC_A_PIN);
    lastEncB = digitalRead(ENC_B_PIN);
    btnState = digitalRead(BTN_PIN);
    btnLastState = btnState;
}

void encoderSetDebounceEnc(unsigned long ms) { ENC_DEBOUNCE_MS = ms; }
void encoderSetDebounceBtn(unsigned long ms) { BTN_DEBOUNCE_MS = ms; }
void encoderSetLongPressMs(unsigned long ms) { LONG_PRESS_MS = ms; }
void encoderSetDoubleClickMs(unsigned long ms) { DOUBLE_CLICK_MS = ms; }

InputEvent readInput()
{
    InputEvent ev{0, NONE};
    unsigned long now = millis();

    if (now - lastEncTime > ENC_DEBOUNCE_MS)
    {
        lastEncTime = now;
        int a = digitalRead(ENC_A_PIN);
        int b = digitalRead(ENC_B_PIN);
        if (a != lastEncA)
        {
            int raw = (a == b) ? +1 : -1;
            encAccum += raw;
            if (abs(encAccum) >= ENC_THRESHOLD)
            {
                int sign = (encAccum > 0) ? +1 : -1;
                encPos += sign * ENC_STEP_SIZE;
                ev.delta = sign * ENC_STEP_SIZE;
                encAccum = 0;
            }
        }
        lastEncA = a;
        lastEncB = b;
    }

    // Encoder button - debounce and check long/short press
    int s = digitalRead(BTN_PIN);
    if (s != btnLastState)
    {
        lastBtnTime = now;
        btnLastState = s;
    }
    if (now - lastBtnTime > BTN_DEBOUNCE_MS)
    {
        if (s == LOW && btnState == HIGH)
        { // press
            btnPressedAt = now;
            clickCount++;
        }
        else if (s == HIGH && btnState == LOW)
        { // release
            unsigned long held = now - btnPressedAt;
            if (held >= LONG_PRESS_MS)
            {
                ev.btn = LONG;
                clickCount = 0;
            }
            else
            {
                ev.btn = SHORT; // short / can be double
            }
        }
        btnState = s;
    }

    // simple double click detection
    static unsigned long lastClickTime = 0;
    if (ev.btn == SHORT)
    {
        if (lastClickTime != 0 && (now - lastClickTime) < DOUBLE_CLICK_MS)
        {
            ev.btn = DOUBLE_PRESS;
            lastClickTime = 0;
            clickCount = 0;
        }
        else
        {
            lastClickTime = now;
        }
    }

    return ev;
}
