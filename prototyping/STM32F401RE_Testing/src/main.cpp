#include <Arduino.h>


void setup() {
  pinMode(PA5, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB devices.
  }
  Serial.println("Serial monitor is working!");
}

void loop() {
  digitalWrite(PA5, HIGH);
  delay(1000);
  digitalWrite(PA5, LOW);
  delay(1000);
  Serial.println("Serial monitor is working!");
}

