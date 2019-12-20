#ifndef CRANK_SENSOR_H
#define CRANK_SENSOR_H


#include <CircularBuffer.h>

/**
 * The crank sensor is responsible of:
 * 
 * - collecting hall sensor signals and their timestamps
 * - providing the latest know shaft phase in degrees
 * - providing the latest rpm speed
 */
class CrankSensor {

  private:
    
    const unsigned int TEETH_PRESENT = 3;
    const unsigned int TEETH_MISSING = 1;
    const unsigned int TEETH_TOTAL = TEETH_PRESENT + TEETH_MISSING;
    const unsigned long RPM_FACTOR = 60L * 1000L * 1000L;
    
    volatile unsigned int rpm;
    volatile unsigned int phase;
    
    void resetBuffer();
    unsigned long computeDurationMicros(int prevSampleIndex, int nextSampleIndex);

  public:
    
    CrankSensor(int hallSensorPin, void (*isrCallback));
    volatile CircularBuffer<unsigned long, BUFFER_SIZE> hallSensorReads;
    void sensorCallback();
    int instantRPMs();

};

#endif
