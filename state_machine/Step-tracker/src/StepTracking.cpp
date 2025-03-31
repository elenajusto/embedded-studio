#include "StepTracking.h"
#include "Calibration.h"  // For XG, YG

// Variables used in logic
int stepCount = 0;
unsigned long lastStepTime = 0;

// Define constants for step detection
const float STEP_THRESHOLD = 1.1;
const unsigned long STEP_DEBOUNCE_MS = 300;
const unsigned long SAMPLE_INTERVAL_MS = 10;

void checkForSteps() {
    // Wait until calibration is complete
        // Step 1: Calculate magnitude of vertical acceleration
        float magnitude = sqrt(XG * XG + YG * YG);  // Or use XG, ZG depending on your need
        Serial.print(">Magnitude: "); 
        Serial.println(magnitude);
        
        // Step 2: Get current time in milliseconds
        unsigned long currentTime = millis();

        // Step 3: Check if magnitude exceeds threshold
        if (magnitude > STEP_THRESHOLD && (currentTime - lastStepTime > STEP_DEBOUNCE_MS)) {
            stepCount++;  // Increment step count
            lastStepTime = currentTime;  // Update last step time
            Serial.println(stepCount);   // Optionally print step count
        }

        // Step 4: Repeat every sampling interval
        delay(SAMPLE_INTERVAL_MS);  // Optional: adjust if needed
    
}
