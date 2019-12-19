// constants

// pin for shaft hall sensor signal
#define HALL_SENSOR_PIN 2

// size of shaft sample set
#define BUFFER_SIZE 8

// modules
#include "CrankSensor.h"
#include "display.h"
#include "rpm.h"

CrankSensor * crankSensorPtr;

void setup() {
  Serial.begin(9600);
  Serial.println("setup started");

  // Initialise crank sensor
  crankSensorPtr = new CrankSensor(
    HALL_SENSOR_PIN, 
    [](void) -> void {crankSensorPtr->sensorCallback();}
  );

  // RPM calulation
  initialiseRPMsCalculator();

  // display
  initialiseDisplay();
  
  Serial.println("setup completed");
}

/**
 * the main loop does nothing important, just refresh the display
 */
void loop() {
  
  refreshDisplay();
  
  delay(20);
  
}
