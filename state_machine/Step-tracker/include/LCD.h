#ifndef LCD_H
#define LCD_H

#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Pin definitions for your ST7789 display
#define TFT_CS    D10
#define TFT_DC    D9
#define TFT_RST   D8   // or -1 if RST is tied to 3.3 V
#define TFT_BL    D7   // backlight control (PWM capable)

// Declare the display instance; define it in the corresponding .cpp
extern Adafruit_ST7789 tft;

// Initialize the LCD (call once in setup)
void LCD_Setup();

#endif // LCD_H
