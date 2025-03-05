#include <Arduino.h>

void setup() 
{
  pinMode(PA5, OUTPUT);
}

void loop() 
{
  digitalWrite(PA5, true);
  delay(1000);
  digitalWrite(PA5, false);
  delay(1000);
}