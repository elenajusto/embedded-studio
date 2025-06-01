#include "LCD.h"


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void LCD_Setup()
{
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);    // full brightness

  // Initialize display
  tft.init(240, 240);            // 240×240 round panel
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);

  // Test text
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(20, 110);
  tft.print("Hello, round TFT!");    
}