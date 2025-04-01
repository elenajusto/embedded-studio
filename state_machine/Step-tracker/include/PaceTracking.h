#ifndef PACE_TRACKING_H
#define PACE_TRACKING_H

#include <Arduino.h>

// Constants for pace classification based on time between steps (in ms)
extern const int WALKING_THRESHOLD_TIME;  // Walking time threshold (ms)
extern const int JOGGING_THRESHOLD_TIME;  // Jogging time threshold (ms)
extern const int RUNNING_THRESHOLD_TIME;  // Running time threshold (ms)

// Declare external variables for pace tracking
extern String previousPace;  // Store previous pace for comparison
extern unsigned long lastPaceTime;  // Last time a step was recorded for pace calculation
extern unsigned long currentStepTime;  // Current time of step detection

// Function prototypes
void classifyPace();  // Classify the pace based on the time between steps
void updateStepTime();  // Update the current step time when a step is detected

#endif  // PACE_TRACKING_H
