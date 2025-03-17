#ifndef MAIN_H_
#define MAIN_H_

#include "Arduino.h"

/* Pin Definitions 
*  As per Google Sheets Signal Map
* https://docs.google.com/spreadsheets/d/1ynZojJuQsPqQfRi-4qh6FZbistdDF11p9jDVUJKjde4/edit?usp=sharing
*
*/

#define SIGNAL_X A0
#define SIGNAL_Y A1
#define SIGNAL_Z A2

#define V_SENSE A3

#define LED_1 D3
#define LED_2 D4
#define LED_3 D5
#define BUZZ D6
#define ST_SWITCH D7

/* State Definitions */
enum State { 
    IDLE, 
    CALIBRATION, 
    ACTIVE_TRACKING, 
    SELF_TEST, 
    BATTERY_MONITOR 
};

/* Function Definitions */

// State Functions
void handleIdleState();
void handleCalibrationState();
void handleTrackingState();
void handleSelfTestState();
void handleBatteryMonitor();

// Other
bool buttonPressed();
void calibrateAccelerometer();
int detectSteps();
void displayStepCount(int steps);
void runSelfTest();
void checkBatteryLevel();

#endif /* MAIN_H_ */