#include "Display.h"

Display::Display(unsigned long refreshRate, void (*isrCallback), CrankSensor* ptr) {

  screenPtr = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  crankSensorPtr = ptr;
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!screenPtr->begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  screenPtr->clearDisplay();
  screenPtr->setTextSize(2);
  screenPtr->setTextColor(SSD1306_WHITE);
  screenPtr->setCursor(10, 0);
  screenPtr->println("ClockWork");
  screenPtr->display();
  
}

void Display::refreshDisplay() {
  if (screenPtr && crankSensorPtr) {
    screenPtr->clearDisplay();
    screenPtr->setCursor(10, 0);
    screenPtr->setTextSize(2);
    screenPtr->setTextColor(SSD1306_WHITE);
    screenPtr->println(crankSensorPtr->instantRpm());
    screenPtr->display();
  }
}
