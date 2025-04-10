#include "Calibration.h"
#include "PaceTracking.h"
#include "StepTracking.h"

int Setup = 1;

void setup() {
    startCalibration(); // Starts calibration process (only runs once)
    // Optional: set up display, EEPROM, etc.
}

void loop() 
{
    switch (Setup)
    {
    case 1:
    //Self-Test
    
    case 2:
        //setup
        updateCalibratedValues();
        break;
    
    default:
        //menu
        break;
    }


    updateCalibratedValues();  // Continuously updates XG, YG, ZG
    // Wait until calibration is complete
    if (isCalibrationDone()) 
    {
        checkForSteps();

        classifyPace();
    }
    
}
