#include "showVolume.h"

void showVolume(int counter, Adafruit_SH110X &display) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(4, 12);
  display.print("Volume: ");
  display.print(counter);

  // Lewy nawias [
  display.drawLine(12, 36, 12, 48, SH110X_WHITE);   // pionowa kreska
  display.drawLine(12, 36, 21, 36, SH110X_WHITE);   // górna kreska
  display.drawLine(12, 48, 21, 48, SH110X_WHITE);   // dolna kreska

  // Prawy nawias ]
  display.drawLine(116, 36, 116, 48, SH110X_WHITE); // pionowa kreska
  display.drawLine(107, 36, 116, 36, SH110X_WHITE); // górna kreska
  display.drawLine(107, 48, 116, 48, SH110X_WHITE); // dolna kreska

  // Pasek głośności (od x=15 do x=114, ~99 px szerokości)
  int barWidth = map(counter, 0, 50, 0, 99);
  display.fillRect(15, 39, barWidth, 7, SH110X_WHITE);

  display.display();
}
