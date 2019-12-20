#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {

  private:
    Adafruit_SSD1306 * screenPtr;
    CrankSensor * crankSensorPtr;

  public:
    Display(unsigned long, void (*), CrankSensor*);
    void refreshDisplay();
};

#endif
