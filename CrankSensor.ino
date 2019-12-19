#include "CrankSensor.h"
#include "Arduino.h"
  
CrankSensor::CrankSensor(int hallSensorPin, void (*isrCallback)) {

  // Crank sensor
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), isrCallback, FALLING);

  resetBuffer();

}

void CrankSensor::sensorCallback() {
  hallSensorReads.push(micros());  
}

void CrankSensor::resetBuffer() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    hallSensorReads.push(0);
  }
}
