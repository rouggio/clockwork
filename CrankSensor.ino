#include "CrankSensor.h"
#include "Arduino.h"

CrankSensor::CrankSensor(int hallSensorPin, void (*isrCallback)) {

  pinMode(HALL_SENSOR_PIN, INPUT);

  // Attach hardware interrupt to callback function upon falling that when the tooth transition is completed
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), isrCallback, FALLING);

}

/**
 *  we received a pulse from the hall sensor, store the time it happened
 *  
 *  check how we stand with the number of teeth and calculate phase
 *  
 *  - calculate current duration
 *  - compare against last known duration
 *  - if current duration similar, increase current tooth
 *  - if current duration similar to estimated gaps duration, flag turn
 *    - set current tooth to zero
 *    - store revolution duration
 *  - store last known duration
 */
void CrankSensor::sensorCallback() {

  // the pulse instant
  unsigned long pulseInstant = micros();
  
  // time distance since the last transition
  unsigned long currentDuration = pulseInstant - lastSeenToothTime;

  // approximated duration in comparison to other tooth-tooth durations
  int durationFactor = durationComparison(currentDuration, lastObservedDuration, 1);

  if (durationFactor == 1) {

    // current duration looks like one simple tooth duration, increase index
    lastSeenToothIndex++;

  } else if (durationFactor == TEETH_MISSING + 1) {

    // current duration looks like missing teeth gap duration, this denotes a completed revolution

    // set current tooth to zero
    lastSeenToothIndex = 0;

    // store revolution duration
    lastRevDuration = pulseInstant - lastRevTime;

    // store time of completed revolution
    lastRevTime = pulseInstant;

  }
  
  // store last known tooth - tooth duration and instant
  lastObservedDuration = currentDuration;
  lastSeenToothTime = pulseInstant;
  
}

int CrankSensor::durationComparison(unsigned long newDuration, unsigned long referenceDuration, unsigned int factor) {

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

unsigned long CrankSensor::instantRpm() {

  if (micros() - lastSeenToothTime > MAX_TOOTH_WAIT_TIME) {
    
    // too long since last tooth, engine is not running
    return 0L;
    
  } else {

    // calculate rpm 
    return (long) ONE_MINUTE_IN_MICROS / lastRevDuration;

  }

}
