// constants

// pin for shaft hall sensor signal
#define HALL_SENSOR_PIN 2

// size of shaft sample set
#define BUFFER_SIZE 8

// display refresh rate in ms
#define DISPLAY_REFRESH_RATE 20

// modules
#include "CrankSensor.h"
#include "Telemetry.h"
#include "Display.h"

CrankSensor * crankSensorPtr;
Telemetry * telemetryPtr;
Display * displayPtr;

void setup() {
  Serial.begin(9600);
  Serial.println("setup started");

  // Initialise crank sensor
  crankSensorPtr = new CrankSensor(
    HALL_SENSOR_PIN, 
    [](void) -> void {crankSensorPtr->sensorCallback();}
  );

  // Initialise telemetry
  telemetryPtr = new Telemetry(crankSensorPtr);

  // Initialise display
  displayPtr = new Display(
    DISPLAY_REFRESH_RATE, 
    [](void)->void{displayPtr->refreshDisplay();},
    telemetryPtr
  );
  
  Serial.println("setup completed");
}

/**
 * the main loop does nothing, all activities happens in the modules
 */
void loop() {
}
