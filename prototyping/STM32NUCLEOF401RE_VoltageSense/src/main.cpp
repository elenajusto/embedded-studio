#include <Arduino.h>

float measureZ;
float measureY;
float measureX;

float R1 = 400;
float R2 = 400;

void setup() {
  // A0 to read battery voltage
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  // Serial output measurements
  Serial.begin(115200);
}

void loop() {
  // Read voltage
  //float reading = analogRead(A0);
  //float voltage = (reading/1024) * (3.3);

  // Print out readings
  //Serial.print(">Voltage: ");
  //Serial.println(voltage);

  /* Accelerometer Readings */
  float readZ = analogRead(A0);
  float readY = analogRead(A1);
  float readX = analogRead(A2);
 
  measureZ = (readZ/1024.0) * 3.3;
  measureY = (readY/1024.0) * 3.3;
  measureX = (readX/1024.0) * 3.3;

  Serial.print(">X: ");
  Serial.println(measureX);

  Serial.print(">Y: ");
  Serial.println(measureY);

  Serial.print(">Z: ");
  Serial.println(readZ);
}

