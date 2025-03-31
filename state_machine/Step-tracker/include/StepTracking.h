#ifndef STEP_TRACKER_H
#define STEP_TRACKER_H

#include <Arduino.h>

// Declare external variables
extern int stepCount;
extern unsigned long lastStepTime;

// Constants for step detection
extern const float STEP_THRESHOLD;
extern const unsigned long STEP_DEBOUNCE_MS;
extern const unsigned long SAMPLE_INTERVAL_MS;

// Declare function for step tracking
void checkForSteps();  // Call this from main loop

#endif
