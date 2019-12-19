#ifndef CRANK_SENSOR_H
#define CRANK_SENSOR_H

#include <CircularBuffer.h>

class CrankSensor {

  private:
    void resetBuffer();
        
  public:
    CrankSensor(int hallSensorPin, void (*isrCallback));
    volatile CircularBuffer<unsigned long, BUFFER_SIZE> hallSensorReads;
    void sensorCallback();
};

#endif
