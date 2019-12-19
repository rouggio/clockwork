#include "Telemetry.h"

Telemetry::Telemetry(CrankSensor* ptr) {
  crankSensorPtr = ptr;
//  Timer1.initialize(1000 * 1000);
//  Timer1.attachInterrupt(refreshRPMs);
}

//int refreshRPMs() {
//  unsigned long lastTransit = cranksensor::hallSensorReads[BUFFER_SIZE - 1];
//  unsigned long secondLastTransit = cranksensor::hallSensorReads[BUFFER_SIZE - 2];
//  unsigned long lastKnownDuration = lastTransit - secondLastTransit;
//  unsigned long instantDuration = micros() - lastTransit;
//  if (instantDuration > (1000L * 1000L * 3L)) {
    // too long wait, engine is not turning
//    runtime::rpms = 0;
//  } else {
//    runtime::rpms = averageRPMs();
//  }
//}

int Telemetry::instantRPMs() {
  unsigned long averageDuration = 0;
//  int components = 0;
//  for (int i = 1; i < BUFFER_SIZE; i++) {
//    unsigned long pairDuration = computeDuration(i - 1, i);
//    if (pairDuration > 0) {
//      averageDuration += pairDuration;
//      components++;
//    }
//}

  //  unsigned long lastRead = hallSensorReads.last();
  //  unsigned long now = micros();
  //if we are past the due transit as per last revolution, factor in an instant read as well
  //  if (now >
  //  averageDuration += micros() - hallSensorReads.last();

//  averageDuration = averageDuration / components;
//  Serial.println(components);
//  return RPM_FACTOR / averageDuration;
return 0;
}

int computeDuration(int prevSampleIndex, int nextSampleIndex) {
//  unsigned long nextTransit = cranksensor::hallSensorReads[nextSampleIndex];
//  unsigned long previousTransit = cranksensor::hallSensorReads[prevSampleIndex];
//  if (nextTransit > 0 && previousTransit > 0) {
//    return nextTransit - previousTransit;
//  } else {
    return 0;
//  }
}
