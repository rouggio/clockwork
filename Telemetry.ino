#include "Telemetry.h"

Telemetry::Telemetry(CrankSensor* ptr) {
  crankSensorPtr = ptr;
}

int Telemetry::instantRPMs() {
  unsigned long averageDuration = 0;
  int components = 0;
  for (int i = 1; i < crankSensorPtr->hallSensorReads.size(); i++) {
    unsigned long pairDuration = computeDuration(i - 1, i);
    if (pairDuration > 0) {
      averageDuration += pairDuration;
      components++;
    }
  }
  
  //unsigned long lastRead = crankSensorPtr->hallSensorReads.last();
  //unsigned long now = micros();
  //if we are past the due transit as per last revolution, factor in an instant read as well
  //  if (now >
  //  averageDuration += micros() - hallSensorReads.last();

  averageDuration = averageDuration / components;

  if (averageDuration > (1000L * 1000L * 3L)) {
    // too long wait, engine is not turning
    crankSensorPtr->resetBuffer();
    return 0;
  } else {
    return RPM_FACTOR / averageDuration;
  }

}


/**
 * calculates the time difference between two instants in time
 */
int Telemetry::computeDuration(int prevSampleIndex, int nextSampleIndex) {
  unsigned long nextTransit = crankSensorPtr->hallSensorReads[nextSampleIndex];
  unsigned long previousTransit = crankSensorPtr->hallSensorReads[prevSampleIndex];
  if (nextTransit > 0 && previousTransit > 0) {
    return nextTransit - previousTransit;
  } else {
    return 0;
  }
}
