#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>  

// -----------------------------------------------------------------------------
// Accelerometer Inputs
// -----------------------------------------------------------------------------
static const uint8_t PIN_SIGNAL_X = A0; 
static const uint8_t PIN_SIGNAL_Y = A1;  
static const uint8_t PIN_SIGNAL_Z = A2;  

// -----------------------------------------------------------------------------
 // Battery Voltage Sensing
// -----------------------------------------------------------------------------
static const uint8_t PIN_V_SENSE   = A3;  

// -----------------------------------------------------------------------------
// I2C Pins (for LCD or other I2C peripherals)
// -----------------------------------------------------------------------------
static const uint8_t PIN_I2C1_SCL  = D15; 
static const uint8_t PIN_I2C1_SDA  = D14; 

// -----------------------------------------------------------------------------
// UART Pins (reserved for future use)
// -----------------------------------------------------------------------------
static const uint8_t PIN_UART_TX   = D1;
static const uint8_t PIN_UART_RX   = D0;

// -----------------------------------------------------------------------------
// LEDs
// -----------------------------------------------------------------------------
static const uint8_t PIN_LED_1_Walk = D12;  
static const uint8_t PIN_LED_2_Jog  = D4;  
static const uint8_t PIN_LED_3_Run  = D13;  

// -----------------------------------------------------------------------------
// Buzzer
// -----------------------------------------------------------------------------
static const uint8_t PIN_BUZZER    = D6; 

// -----------------------------------------------------------------------------
// Self-Test Switch / Buttons
// -----------------------------------------------------------------------------
static const uint8_t PIN_ST_SWITCH = D7;  
static const uint8_t PIN_BUTTON_1  = D8;   
static const uint8_t PIN_BUTTON_2  = D9;
static const uint8_t PIN_BUTTON_3  = D10; 

#endif  // BOARD_CONFIG_H
