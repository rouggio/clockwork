#include "CrankSensor.h"
#include "Arduino.h"

CrankSensor::CrankSensor(int hallSensorPin, void (*isrCallback)) {

  pinMode(HALL_SENSOR_PIN, INPUT);

  // Attach hardware interrupt to callback function upon falling that when the tooth transition is completed
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), isrCallback, FALLING);

  resetBuffer();

}

/**
 * we received a pulse from the hall sensor, store the time it happened
 */
void CrankSensor::sensorCallback() {

  // the pulse instant
  unsigned long pulseInstant = micros();
  
  /* 
   *  todo - check how we stand with the number of teeth and calculate phase
   *  
   *  - calculate current duration
   *  - compare against last known duration
   *  - if current duration similar, increase current tooth
   *  - if current duration similar to estimated gaps duration, flag turn
   *    - set current tooth to zero
   *    - store revolution duration
   *  - store last known duration
   */

  // time distance since the last transition
  unsigned int currentDuration = pulseInstant - lastSeenToothTime;

  // approximated duration in comparison to other tooth-tooth durations
  int durationFactor = durationComparison(currentDuration, lastObservedDuration, 1);
  
  if (durationFactor == 1) {

    // current duration looks like one simple tooth duration, increase index
    lastSeenToothIndex++;

  } else if (durationFactor == TEETH_MISSING) {

    // current duration looks like missing teeth gap duration, this denotes a completed revolution

    // set current tooth to zero
    lastSeenToothIndex = 0;

    // store revolution duration
    unsigned int lastRevDuration = pulseInstant - lastRevTime;

    // store time of completed revolution
    lastRevTime = pulseInstant;
  }
  
  // store last known tooth - tooth duration
  lastObservedDuration = currentDuration;
}

int CrankSensor::durationComparison(unsigned int newDuration, unsigned int referenceDuration, unsigned int factor) {

  if (newDuration <= referenceDuration * factor) {

    // the new duration is smaller than reference, return factor
    return factor;
    
  } else if (newDuration <= referenceDuration * factor * DURATION_COMPARISON_FACTOR) {

    // within upper bound tolerance, return factor
    return factor;
  
  } else {

    // recurse with an increased factor, that is try if we fit within boundaries of one additional gear position
    return durationComparison(newDuration, referenceDuration, factor + 1);
    
  }
  
}

/**
 * clear all entries in the circular buffer
 */
void CrankSensor::resetBuffer() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    hallSensorReads.push(0);
  }
}

int CrankSensor::instantRpm() {

  if (lastRevDuration > (1000L * 1000L * 3L)) {
    // too long wait, engine is not running
    return 0;
  } else {
    // calculate rpm 
    return ONE_MINUTE_IN_MICROS / lastRevDuration;
  }

}
