#include "Display.h"

Display::Display(int refreshRate, void (*isrCallback), Telemetry* telemetryPtr) {

  screenPtr = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!screenPtr->begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  screenPtr->clearDisplay();
  screenPtr->setTextSize(2);
  screenPtr->setTextColor(SSD1306_WHITE);

  Timer1.initialize(refreshRate);
  Timer1.attachInterrupt(isrCallback);
  
}

void Display::refreshDisplay() {
  screenPtr->clearDisplay();
  screenPtr->setCursor(10, 0);
  screenPtr->println(telemetryPtr->instantRPMs());
  screenPtr->display();
}
