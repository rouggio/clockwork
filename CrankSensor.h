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
    volatile unsigned long lastSeenToothTime = micros();

    // the last observed tooth-tooth duration, microseconds
    volatile unsigned long lastObservedDuration;

    // time of last observed completed revolution in micros
    volatile unsigned long lastRevTime;

    // duration of last observed revolution in micros
    volatile unsigned long lastRevDuration;

    // Methods
    
    // checks whether the duration feels like right after a missing tooth
    boolean gapBridged(unsigned long newDuration, unsigned long referenceDuration);

  public:
    
    CrankSensor(int hallSensorPin, void (*isrCallback));
   
    // called back from interrupt to notify the current sensor pulse
    void sensorCallback();

    // returns the last known rpm
    float instantRpm();

};

#endif
