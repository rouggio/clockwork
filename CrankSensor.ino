#include "cranksensor.h"
#include "Arduino.h"
  
CrankSensor::CrankSensor(int hallSensorPin, void (*isrCallback)) {

  // Crank sensor
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), isrCallback, FALLING);

//    for (int i = 0; i < BUFFER_SIZE; i++) {
//      cranksensor::hallSensorReads.push(0);
//    }

}

void CrankSensor::sensorCallback() {
  hallSensorReads.push(micros());  
}
