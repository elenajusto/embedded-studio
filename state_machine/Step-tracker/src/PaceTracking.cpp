#include "PaceTracking.h"
#include "Calibration.h"  // For XG, YG
#include "BoardConfig.h"

// Constants for pace classification based on time between steps (in ms)
const int WALKING_THRESHOLD_TIME = 850;  // Time in milliseconds for walking (e.g., 800 ms between steps)
const int JOGGING_THRESHOLD_TIME = 450;  // Time for jogging (e.g., 400 ms between steps)
const int RUNNING_THRESHOLD_TIME = 320;  // Time for running (e.g., 200 ms between steps)

String previousPace = "";  // Variable to store previous pace

unsigned long lastPaceTime = 0;  // Time of the previous step
unsigned long currentStepTime = 0;  // Time of the current step

void classifyPace() 
{
    // Calculate the time difference between two steps (in milliseconds)
    unsigned long timeDiff = currentStepTime - lastPaceTime;

    String currentPace = previousPace;

    // Classify pace based on the time difference between steps
    if (timeDiff >= WALKING_THRESHOLD_TIME) 
    {
        currentPace = "Walking";
        digitalWrite(PIN_LED_1_Walk, HIGH);
    } 
    else if (timeDiff >= JOGGING_THRESHOLD_TIME && timeDiff < WALKING_THRESHOLD_TIME) 
    {
        currentPace = "Jogging";
        digitalWrite(PIN_LED_2_Jog, HIGH);
    } 
    else if (timeDiff <= RUNNING_THRESHOLD_TIME && timeDiff > 0) {
        currentPace = "Running";
        digitalWrite(PIN_LED_3_Run, HIGH);
    }

    // Print only if the pace has changed
    if (currentPace != previousPace) {
        Serial.print("Pace: ");
        Serial.println(currentPace);
        previousPace = currentPace;  // Update the previous pace to current pace
        digitalWrite(PIN_LED_1_Walk, LOW);
        digitalWrite(PIN_LED_2_Jog, LOW);
        digitalWrite(PIN_LED_3_Run, LOW);
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
