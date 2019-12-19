#ifndef CRANK_SENSOR_H
#define CRANK_SENSOR_H

#include <CircularBuffer.h>

void initialiseCrankSensor(int hallSensorPin);

class CrankSensor {

  private:
    
  public:
    CrankSensor(int hallSensorPin, void (*isrCallback));
    volatile CircularBuffer<unsigned long, BUFFER_SIZE> hallSensorReads;
    void sensorCallback();
};

#endif
