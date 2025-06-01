#include "Calibration.h"
#include "PaceTracking.h"
#include "StepTracking.h"
#include "LCD.h"

int Setup = 1;

void setup() {
   // startCalibration(); // Starts calibration process (only runs once)
    // Optional: set up display, EEPROM, etc.

    LCD_Setup();
}

void loop() 
{
    switch (Setup)
    {
    case 1:
    //Set-Up Menu
    //gives the options of selecting self-test routine or calibration
    case 2:
        //setup

        break;
    
    default:

        break;
    }

/*
    updateCalibratedValues();  // Continuously updates XG, YG, ZG
    // Wait until calibration is complete
    if (isCalibrationDone()) 
    {
        checkForSteps();

        classifyPace();
    }
*/
}
