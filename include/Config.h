#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==========================
//  OLED SCREEN SETTINGS
// ==========================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define I2C_ADDRESS 0x3c

// ==========================
//  I2C PINS
// ==========================
#define SDA_PIN 21
#define SCL_PIN 22

// ==========================
//  PCM5100A DAC (I2S)
// ==========================
#define I2S_BCK 26      // Bit Clock
#define I2S_WS 25       // Word Select (LCK)
#define I2S_DATA_OUT 27 // Data Out (DIN)

// ==========================
//  ENCODER PINS
// ==========================
#define PIN_S1 18
#define PIN_S2 19
#define PIN_SW 17 // Encoder switch button

// ==========================
//  NTP SERVER
// ==========================
const char *NTP_SERVER = "tempus1.gum.gov.pl";

#endif