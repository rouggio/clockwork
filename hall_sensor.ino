// constants
#define HALL_SENSOR_PIN 2
#define BUFFER_SIZE 8

// modules
#include "cranksensor.h"
#include "display.h"
#include "rpm.h"

void setup() {
  Serial.begin(9600);
  Serial.println("setup started");

  // Crank sensor
  initialiseCrankSensor(HALL_SENSOR_PIN);

  // RPM calulation
  initialiseRPMsCalculator();

  // display
  initialiseDisplay();
  
  Serial.println("setup completed");
}

void loop() {
  refreshDisplay();
  delay(20);
}
