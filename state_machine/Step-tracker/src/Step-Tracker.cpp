#include "Calibration.h"
#include "StepTracking.h"

void setup() {
    startCalibration(); // Starts calibration process (only runs once)
    // Optional: set up display, EEPROM, etc.
}

void loop() 
{
    updateCalibratedValues();  // Continuously updates XG, YG, ZG
    // Wait until calibration is complete
    if (isCalibrationDone()) 
    {
        checkForSteps();
    }
    
}
