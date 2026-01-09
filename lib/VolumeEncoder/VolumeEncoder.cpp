#include "volumeEncoder.h"
#include "showVolume.h"

// Variables definition
volatile int step = 0;
volatile int counter = 0;
int lastStateCLK = LOW;
unsigned long lastUpdate = 0;
const int showTime = 1000;



void volumeEncoder(int currentStatePinS1, int currentStatePinS2, Adafruit_SH110X &display) {
  if (currentStatePinS2 != lastStateCLK) {
    // Sprawdzamy kierunek na podstawie stanu DT
    if (currentStatePinS1 != currentStatePinS2) {
        step++;
    } else {   
        step--;
    }

    // jeśli step osiągnie 2 lub -2, dopiero wtedy zmieniamy counter
    if (step >= 2) {
      if (counter <= 49) {
        counter++;
      }
      step = 0;
      showVolume(counter, display);
      lastUpdate = millis();

    } else if (step <= -2) {
      if (counter >= 1) {
        counter--;
      }
      step = 0;
      showVolume(counter, display);
      lastUpdate = millis();
    }
  }

  lastStateCLK = currentStatePinS2;

  // jeśli minęła sekunda od ostatniego ruchu, wróć do main view
  if (millis() - lastUpdate > showTime && lastUpdate != 0) {
    // tu używasz display przekazanego jako referencja
    displayHelloMsg(display, true); // lub false jeśli nie ma wifi
    lastUpdate = 0; // żeby nie powtarzało
  }
}
