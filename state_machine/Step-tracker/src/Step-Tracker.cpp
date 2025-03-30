#include "Calibration.h"
#include "StepTracking.h"

// Variables used in logic
int stepCount = 0;
unsigned long lastStepTime = 0;

// Constants
const float STEP_THRESHOLD = 1.1;
const unsigned long STEP_DEBOUNCE_MS = 300;
const unsigned long SAMPLE_INTERVAL_MS = 10;

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
        // ----- STEP DETECTION -----
        // Step 1: Calculate magnitude of vertical acceleration
        float magnitude = sqrt(XG*XG + YG*YG);
        Serial.print(">Magnitude: "); Serial.println(magnitude);
        
        // Step 2: Get current time in milliseconds
        unsigned long currentTime = millis();

        // Step 3: Check if magnitude exceeds threshold
        if (magnitude > STEP_THRESHOLD && (currentTime - lastStepTime > STEP_DEBOUNCE_MS)) {
            stepCount++;
            lastStepTime = currentTime;
            Serial.println(stepCount);

            // Optional: log step or update display
        }

        // Step 4: Repeat every sampling interval
        delay(SAMPLE_INTERVAL_MS);  // e.g. 10 ms
        
    }
    
}
