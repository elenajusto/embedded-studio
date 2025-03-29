#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Arduino.h>

// Global variables to access calibrated g-values
extern float XG, YG, ZG;

// Setup + Loop replacement
void startCalibration();         // Call this once in setup()
void updateCalibratedValues();  // Call repeatedly in loop()

#endif