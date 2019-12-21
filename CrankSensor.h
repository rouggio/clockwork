#ifndef CRANK_SENSOR_H
#define CRANK_SENSOR_H

/**
 * The crank sensor is responsible of:
 * 
 * - collecting hall sensor signals and their timestamps
 * - providing the latest know shaft phase in degrees
 * - providing the latest rpm speed
 */
class CrankSensor {

  private:

    // Constants
    
    // overall number of gear positions (teeth and gaps)
    static const unsigned int TEETH_TOTAL = TEETH_PRESENT + TEETH_MISSING;

    // factor for one minute in microseconds
    static const unsigned long ONE_MINUTE_IN_MICROS = 60L * 1000L * 1000L;

    // duration tolerance to assume two transition durations are similar
    static const float DURATION_COMPARISON_FACTOR = 1.25;
    
    // Fields

    // the last seen gear tooth index, zero based, initially set to an unknown (-1) value.
    volatile int lastSeenToothIndex = -1;

    // the last seen gear tooth transition time, in microseconds
    volatile int lastSeenToothTime;

    // the last observed tooth-tooth duration, microseconds
    volatile unsigned int lastObservedDuration;

    // time of last observed completed revolution in micros
    volatile unsigned int lastRevTime;

    // duration of last observed revolution in micros
    volatile unsigned int lastRevDuration;

    // Methods
    
    // compares this duration against other known durations to determine whether how many gaps we are observing now.
    int durationComparison(unsigned int newDuration, unsigned int referenceDuration, unsigned int factor);

  public:
    
    CrankSensor(int hallSensorPin, void (*isrCallback));
   
    // called back from interrupt to notify the current sensor pulse
    void sensorCallback();

    // returns the last known rpm
    int instantRpm();

};

#endif
