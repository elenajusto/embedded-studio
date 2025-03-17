#include <Arduino.h>
#include <Wire.h>
#include "main.h"

/* Initialise state */
State currentState;
unsigned long lastButtonPressTime = 0;

/* Program Setup */
void setup() {

    // Initialise LEDs
    pinMode(LED_1, INPUT);
    pinMode(LED_2, INPUT);
    pinMode(LED_3, INPUT);

    // Initialise Buttons
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);

    // Initialise Buzzer
    pinMode(BUZZ, OUTPUT);

    // Initialise ST
    pinMode(ST_SWITCH, OUTPUT);

    // Initialise ADCs
    pinMode(SIGNAL_X, INPUT);
    pinMode(SIGNAL_Y, INPUT);
    pinMode(SIGNAL_Z, INPUT);

    // Initialise communications
    Serial.begin(9600);

    // Initialise starting state
    currentState = IDLE;


    digitalWrite(LED_1, LOW); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
    digitalWrite(LED_2, LOW); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
    digitalWrite(LED_3, LOW); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY

    delay(1000);
    digitalWrite(LED_1, HIGH); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
    digitalWrite(LED_2, HIGH); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
    digitalWrite(LED_3, HIGH); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
    delay(1000);
}

/* Main Program */
void loop() {

    /* Listening for button presses */
  
    buttonListener(BUTTON_1, lastButtonPressTime);
    buttonListener(BUTTON_2, lastButtonPressTime);
    buttonListener(BUTTON_3, lastButtonPressTime);

    /* Determine State */
    /*
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
    */
}

/* Function Definitions */

// Low level
void buttonListener(int buttonPin, unsigned long &lastButtonPressTime) {

    if (digitalRead(buttonPin) == HIGH && millis() - lastButtonPressTime >= debounceDelay) {
        
        if (buttonPin == BUTTON_1) {
            Serial.println("Button 1");
            pinMode(LED_1, OUTPUT);
            digitalWrite(LED_1, HIGH); // Debug - Blink LED 1 - REMOVE WHEN INDICATOR LOGIC READY
            lastButtonPressTime = millis();
            return;
        }
        if (buttonPin == BUTTON_2) {
            Serial.println("Button 2");
            pinMode(LED_1, INPUT);
            digitalWrite(LED_2, HIGH); // Debug - Blink LED 2 - REMOVE WHEN INDICATOR LOGIC READY
            lastButtonPressTime = millis();
            return;
        }
        if (buttonPin == BUTTON_3) {
            Serial.println("Button 3");
            digitalWrite(LED_3, HIGH); // Debug - Blink LED 3 - REMOVE WHEN INDICATOR LOGIC READY
            lastButtonPressTime = millis();
            return;
        }
    }
}

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