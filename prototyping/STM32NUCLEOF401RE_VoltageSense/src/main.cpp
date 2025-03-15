#include <Arduino.h>

float R1 = 400;
float R2 = 400;

void setup() {
  // A0 to read battery voltage
  pinMode(A0, INPUT);

  // Serial output measurements
  Serial.begin(115200);
}

void loop() {
  // Read voltage
  float reading = analogRead(A0);
  float voltage = (reading/1024) * (3.3);

  // Print out readings
  Serial.print(">Voltage: ");
  Serial.println(voltage);
}

