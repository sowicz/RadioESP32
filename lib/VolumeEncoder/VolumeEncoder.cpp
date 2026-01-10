#include "volumeEncoder.h"
#include "showVolume.h"

// Variables definition
volatile int step = 0;
volatile int counter = 0;
int lastStateCLK = LOW;
unsigned long lastUpdate = 0;
const int showTime = 1000;

void volumeChange(const InputEvent &ev, Adafruit_SH110X &display)
{
  if (ev.delta == 0)
  {
    if (lastUpdate != 0 && (millis() - lastUpdate > showTime))
    {
      displayHelloMsg(display, true);
      lastUpdate = 0;
    }
    return;
  }
  int step = (ev.delta > 0) ? 1 : -1;
  if (step > 0)
  {
    if (counter < 50)
    {
      counter++;
    }
  }
  else
  {
    if (counter > 0)
    {
      counter--;
    }
  }
  showVolume(counter, display);
  lastUpdate = millis();
}