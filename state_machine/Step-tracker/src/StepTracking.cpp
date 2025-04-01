#include "StepTracking.h"
#include "Calibration.h"  // For XG, YG
#include "PaceTracking.h"

// Variables used in logic
int stepCount = 0;
unsigned long lastStepTime = 0;

// Define constants for step detection
const float STEP_THRESHOLD = 1.1;
const unsigned long STEP_DEBOUNCE_MS = 300;
const unsigned long SAMPLE_INTERVAL_MS = 10;

unsigned long lastSampleTime = 0;  // To track the last time we sampled the accelerometer

void checkForSteps() {
    unsigned long currentTime = millis();

    // Only check steps every SAMPLE_INTERVAL_MS (non-blocking)
    if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_MS) {
        // Step 1: Calculate magnitude of vertical acceleration
        float magnitude = sqrt(XG * XG + YG * YG);  // Or use XG, ZG depending on your need
        Serial.print(">Magnitude: ");
        Serial.println(magnitude);
        
        // Step 2: Get current time in milliseconds
        // Step 3: Check if magnitude exceeds threshold
        if (magnitude > STEP_THRESHOLD && (currentTime - lastStepTime > STEP_DEBOUNCE_MS)) {
            stepCount++;  // Increment step count
            lastStepTime = currentTime;  // Update last step time
            Serial.println(stepCount);   // Optionally print step count
            
            // Update the current step time for pace classification
            updateStepTime();  // Update the step time after a step is detected
        }

        // Update the last sample time to current time after checking steps
        lastSampleTime = currentTime;
    }
}


