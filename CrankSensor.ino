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
  boolean isGap = gapBridged(currentDuration, lastObservedDuration);

  if (!isGap) {

    // current duration looks like one simple tooth duration, increase index
    lastSeenToothIndex++;

  } else {

    if (lastSeenToothIndex != TEETH_PRESENT - TEETH_MISSING) {
      Serial.println(lastSeenToothIndex);
    }
    
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

boolean CrankSensor::gapBridged(unsigned long newDuration, unsigned long referenceDuration) {

  if (newDuration <= referenceDuration || newDuration <= referenceDuration * DURATION_COMPARISON_FACTOR) {

    // within upper bound tolerance, return factor
    return false;
  
  } else {

    // time exceeded, must have passed the gap
    return true;
    
  }

}

float CrankSensor::instantRpm() {

    // calculate rpm 
    return ONE_MINUTE_IN_MICROS / lastRevDuration;
//    return lastRevDuration;
}
