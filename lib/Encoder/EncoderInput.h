#ifndef ENCODER_INPUT_H
#define ENCODER_INPUT_H

#include <Arduino.h>

enum ButtonEvent
{
    NONE,
    SHORT,
    LONG,
    DOUBLE_PRESS
};
struct InputEvent
{
    int delta;
    ButtonEvent btn;
};

// initialize encoder: pin s1, pin s2, pin sw
void encoderInit(uint8_t encAPin, uint8_t encBPin, uint8_t btnPin);

// Read input event: delta encoder (-1/0/+1) and btn even handler
InputEvent readInput();

// optional: set edge and timer ms
void encoderSetDebounceEnc(unsigned long ms);
void encoderSetDebounceBtn(unsigned long ms);
void encoderSetLongPressMs(unsigned long ms);
void encoderSetDoubleClickMs(unsigned long ms);

#endif // ENCODER_INPUT_H
