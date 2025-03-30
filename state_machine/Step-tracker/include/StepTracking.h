#ifndef STEP_TRACKER_H
#define STEP_TRACKER_H

#include <Arduino.h>

extern int stepCount;

void checkForSteps();  // Call this from main loop

#endif
