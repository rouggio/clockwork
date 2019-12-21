// *********
// constants
// *********

// pin for shaft hall sensor signal
const int HALL_SENSOR_PIN = 2;

const unsigned int TEETH_PRESENT = 3;
const unsigned int TEETH_MISSING = 1;

// display refresh rate in ms
const unsigned long DISPLAY_REFRESH_RATE = 60;

// modules
#include "CrankSensor.h"
#include "Display.h"

CrankSensor * crankSensorPtr;
Display * displayPtr;

void setup() {
  Serial.begin(9600);
  Serial.println("setup started");
 
  // Initialise crank sensor
  crankSensorPtr = new CrankSensor(
    HALL_SENSOR_PIN, 
    [](void) -> void {crankSensorPtr->sensorCallback();}
  );

  // Initialise display
  displayPtr = new Display(
    DISPLAY_REFRESH_RATE,
    [](void)->void{displayPtr->refreshDisplay();},
    crankSensorPtr
  );

  Serial.println("setup completed");
}

/**
 * the main loop only refreshes the display
 */
void loop() {
  //todo intended to be a timer but it broke the display, investigate why...
  displayPtr->refreshDisplay();
  delay(DISPLAY_REFRESH_RATE);
}
