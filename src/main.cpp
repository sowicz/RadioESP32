#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <WiFi.h>

#include "secrets.h"

#ifndef WIFI_SSID
#define WIFI_SSID "UNKNOWN_SSID"
#endif
#ifndef WIFI_PASS
#define WIFI_PASS "UNKNOWN_PASS"
#endif

const char *ssid = WIFI_SSID;
const char *pass = WIFI_PASS;

#include "EncoderInput.h"
#include "Config.h"
#include "time.h"
#include "ClockView.h"
#include "MainScreen.h"
#include "TurnOnAnimation.h"
#include "VolumeEncoder.h"
#include "WifiManager.h"
#include "Menu.h"
#include "RadioStations/RadioStations.h"

// #include <Audio.h>

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool wifiConnect = false;

// ------------------------------------------
// |             main program               |
// ------------------------------------------

// Audio audio;

void setup()
{
  Serial.begin(115200);

  // =======================
  //  ENCODER
  // =======================
  encoderInit(PIN_S1, PIN_S2, PIN_SW);

  Wire.begin(SDA_PIN, SCL_PIN);

  wifiConnect = connectToWifi(ssid, pass, display);
  display.begin(I2C_ADDRESS, true);

  // ====================
  // Loading animation
  // ====================
  // turnOnAnimation(display);

  // TIMEZONE
  // configTime - first parametr is timezone offset (winter / summer )
  configTime(3600, 0, NTP_SERVER);       // connect ntp to get real time
  displayHelloMsg(display, wifiConnect); // show main screen

  initClock(display); // Clock view
  initMenu(display);

  // ==========================
  // Audio library
  // ==========================
  //   audio.setPinout(I2S_BCK, I2S_WS, I2S_DATA_OUT);
  //   audio.setVolume(21);            // zakres 0...21
  //   audio.connecttohost("https://rs101-krk.rmfstream.pl/rmf_maxxx_lom");
};

void loop()
{

  InputEvent ev = readInput();

  if (isInRadioMenu())
  {
    // Choose radio station
    handleRadioStations(display, ev);
  }
  else
  {
    // main menu
    handleMenu(ev);
  }

  if (!isInMenu())
  {
    volumeChange(ev, display);
    clockTimerView();
    showClockOLED(false);
  }

  // ==========================
  // Audio library
  // ==========================
  //   audio.loop();
  //   vTaskDelay(1);
};

// --------------- SERIAL PRINTS FOR AUDIO LIBRARY ----------------

// void audio_info(const char *info){
//     Serial.print("info        "); Serial.println(info);
// }
// void audio_id3data(const char *info){  //id3 metadata
//     Serial.print("id3data     ");Serial.println(info);
// }
// void audio_eof_mp3(const char *info){  //end of file
//     Serial.print("eof_mp3     ");Serial.println(info);
// }
// void audio_showstation(const char *info){
//     Serial.print("station     ");Serial.println(info);
// }
// void audio_showstreamtitle(const char *info){
//     Serial.print("streamtitle ");Serial.println(info);
// }
// void audio_bitrate(const char *info){
//     Serial.print("bitrate     ");Serial.println(info);
// }
// void audio_commercial(const char *info){  //duration in sec
//     Serial.print("commercial  ");Serial.println(info);
// }
// void audio_icyurl(const char *info){  //homepage
//     Serial.print("icyurl      ");Serial.println(info);
// }
// void audio_lasthost(const char *info){  //stream URL played
//     Serial.print("lasthost    ");Serial.println(info);
// }
// void audio_eof_speech(const char *info){
//     Serial.print("eof_speech  ");Serial.println(info);
