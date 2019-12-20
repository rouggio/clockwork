#ifndef TELEMETRY_H
#define TELEMETRY_H

const unsigned long RPM_FACTOR = 60L * 1000 * 1000;

class Telemetry {

  public:
    Telemetry::Telemetry(CrankSensor *);
    int instantRPMs();
    
  private:
    CrankSensor* crankSensorPtr;
    volatile int rpms = 0;
    int computeDuration(int prevSampleIndex, int nextSampleIndex);
    
};

#endif
