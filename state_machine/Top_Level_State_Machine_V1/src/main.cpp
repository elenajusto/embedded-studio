#include <Arduino.h>
#include <Wire.h>
#include "main.h"

/* Initialise state */
State currentState;

/* Program Setup */
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

    // Initialise communications
    Serial.begin(115200);

    // Initialise starting state
    currentState = IDLE;
}

/* Main Program */
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

/* Function Definitions */

// State Function Definitions
void handleIdleState(){
    Serial.println("[state-handle] Function triggered."); // Debug statement
};

void handleCalibrationState(){
    Serial.println("[state-calibration] Function triggered."); // Debug statement
};

void handleTrackingState(){
    Serial.println("[state-tracking] Function triggered."); // Debug statement
};

void handleSelfTestState(){
    Serial.println("[state-testing] Function triggered."); // Debug statement
};

void handleBatteryMonitor(){
    Serial.println("[state-battery] Function triggered."); // Debug statement
;}