#ifndef CRANK_SENSOR_H
#define CRANK_SENSOR_H

#include <CircularBuffer.h>

void initialiseCrankSensor(int hallSensorPin);

namespace cranksensor {
  
  volatile CircularBuffer<unsigned long, BUFFER_SIZE> hallSensorReads;
  
}

#endif
