#include "display.h"


void initialiseDisplay() {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display::screen.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

}

void refreshDisplay() {
  display::screen.clearDisplay();
  display::screen.setTextSize(2);
  display::screen.setTextColor(SSD1306_WHITE);
  display::screen.setCursor(10, 0);
  display::screen.println(runtime::rpms);
  display::screen.display();
}
