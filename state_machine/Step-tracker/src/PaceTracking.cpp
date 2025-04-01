#include "PaceTracking.h"
#include "Calibration.h"  // For XG, YG

// Constants for pace classification based on time between steps (in ms)
const int WALKING_THRESHOLD_TIME = 800;  // Time in milliseconds for walking (e.g., 800 ms between steps)
const int JOGGING_THRESHOLD_TIME = 400;  // Time for jogging (e.g., 400 ms between steps)
const int RUNNING_THRESHOLD_TIME = 200;  // Time for running (e.g., 200 ms between steps)

String previousPace = "";  // Variable to store previous pace

unsigned long lastPaceTime = 0;  // Time of the previous step
unsigned long currentStepTime = 0;  // Time of the current step

void classifyPace() 
{
    // Calculate the time difference between two steps (in milliseconds)
    unsigned long timeDiff = currentStepTime - lastPaceTime;

    String currentPace = "";

    // Classify pace based on the time difference between steps
    if (timeDiff >= WALKING_THRESHOLD_TIME) {
        currentPace = "Walking";
    } 
    else if (timeDiff >= JOGGING_THRESHOLD_TIME && timeDiff < WALKING_THRESHOLD_TIME) {
        currentPace = "Jogging";
    } 
    else if (timeDiff <= RUNNING_THRESHOLD_TIME) {
        currentPace = "Running";
    }

    // Print only if the pace has changed
    if (currentPace != previousPace) {
        Serial.print("Pace: ");
        Serial.println(currentPace);
        previousPace = currentPace;  // Update the previous pace to current pace
    }

    // Update lastPaceTime to the current step time after classifying the pace
    lastPaceTime = currentStepTime;
}


// Call this function from checkForSteps() to set currentStepTime
void updateStepTime() 
{
    currentStepTime = millis();  // Store the time of the current step
    //Serial.print("Step time updated: ");
    //Serial.println(currentStepTime);
}
