#include "cranksensor.h"
#include "Arduino.h"

  void hallSensorChange() {
    cranksensor::hallSensorReads.push(micros());  
  }
    
  void initialiseCrankSensor(int hallSensorPin) {

    // Crank sensor
    attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorChange, FALLING);
  
    for (int i = 0; i < BUFFER_SIZE; i++) {
      cranksensor::hallSensorReads.push(0);
    }
  
  }
  
