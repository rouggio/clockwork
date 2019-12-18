#ifndef RPM_H
#define RPM_H

const unsigned long RPM_FACTOR = 60L * 1000 * 1000;

volatile int rpms = 0;

void initialiseRPMsCalculator();

#endif
