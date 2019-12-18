#ifndef RPM_H
#define RPM_H

const unsigned long RPM_FACTOR = 60L * 1000 * 1000;

void initialiseRPMsCalculator();

namespace runtime {
  volatile int rpms = 0;
}

#endif
