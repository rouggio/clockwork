#include "CrankSensor.h"
#include "Arduino.h"

CrankSensor::CrankSensor(int hallSensorPin, void (*isrCallback)) {

  pinMode(HALL_SENSOR_PIN, INPUT);

  // Crank sensor
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), isrCallback, FALLING);

  resetBuffer();

}

/**
 * we received a pulse from the hall sensor, store the time it happened
 */
void CrankSensor::sensorCallback() {
  hallSensorReads.push(micros());
  // todo - check how we stand with the number of teeth and calculate phase
}

void CrankSensor::resetBuffer() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    hallSensorReads.push(0);
  }
}

int CrankSensor::instantRPMs() {
  unsigned long averageDuration = 0;
  int components = 0;

  unsigned long last = hallSensorReads.last();
  unsigned long last_2 = hallSensorReads[BUFFER_SIZE - 2];
  
  unsigned long pairDuration = last - last_2;

  if (pairDuration > (1000L * 1000L * 3L)) {
    // too long wait, engine is not running
    crankSensorPtr->resetBuffer();
    return 0;
  } else {
    return RPM_FACTOR / pairDuration;
  }

}


/**
 * calculates the time difference between two instants in time
 */
unsigned long CrankSensor::computeDurationMicros(int prevSampleIndex, int nextSampleIndex) {
  unsigned long nextTransitMicros = hallSensorReads[nextSampleIndex];
  unsigned long previousTransitMicros = hallSensorReads[prevSampleIndex];

  if (previousTransitMicros > 0 && nextTransitMicros > previousTransitMicros) {
    return nextTransitMicros - previousTransitMicros;
//Serial.println("non zero");
  } else {
    return 0;
  }
}
