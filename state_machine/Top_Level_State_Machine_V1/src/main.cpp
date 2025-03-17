#include <Arduino.h>
#include <Wire.h>
#include "main.h"

void setup() {

    // Initialise LEDs
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);

    // Initialise Buttons
    
    // Initialise Buzzer
    pinMode(BUZZ, OUTPUT);

    // Initialise ST
    pinMode(ST_SWITCH, OUTPUT);

    // Initialise ADCs
    pinMode(SIGNAL_X, INPUT);
    pinMode(SIGNAL_Y, INPUT);
    pinMode(SIGNAL_Z, INPUT);

    // Initialise starting state
    State currentState = IDLE;

    // Initialise communications
    Serial.begin(115200);
}

void loop() {
    switch (currentState) {
        case IDLE:
            handleIdleState();
            break;
        case CALIBRATION:
            handleCalibrationState();
            break;
        case ACTIVE_TRACKING:
            handleTrackingState();
            break;
        case SELF_TEST:
            handleSelfTestState();
            break;
        case BATTERY_MONITOR:
            handleBatteryMonitor();
            break;
    }
}

void handleIdleState() {
    if (buttonPressed()) {
        currentState = CALIBRATION;
    }
}

void handleCalibrationState() {
    calibrateAccelerometer();
    currentState = IDLE;
}

void handleTrackingState() {
    int steps = detectSteps();
    displayStepCount(steps);
    if (userStopsTracking()) {
        currentState = IDLE;
    }
}

void handleSelfTestState() {
    runSelfTest();
    currentState = IDLE;
}

void handleBatteryMonitor() {
    checkBatteryLevel();
    currentState = IDLE;
}

bool buttonPressed() {
    return digitalRead(BUTTON_PIN) == HIGH;
}

void calibrateAccelerometer() {
    Serial.println("Calibrating...");
    // Implement calibration logic
}

int detectSteps() {
    // Implement step detection logic
    return 0; 
}

void displayStepCount(int steps) {
    Serial.print("Steps: ");
    Serial.println(steps);
}

void runSelfTest() {
    Serial.println("Running Self-Test...");
    // Implement self-test
}

void checkBatteryLevel() {
    Serial.println("Checking battery level...");
    // Implement battery monitoring
}