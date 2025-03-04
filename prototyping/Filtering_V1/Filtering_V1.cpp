#include <Arduino.h>

float filteredX = 0.0;
float filteredY = 0.0;
float filteredZ = 0.0;

// Smoothing factor (0 < alpha < 1)
// Smaller alpha = more smoothing, slower response
float alpha = 0.1;

void setup() {
  Serial.begin(9600);
  filteredX = analogRead(A0);
  filteredY = analogRead(A1);
  filteredZ = analogRead(A2);
}

void loop() {
  // 1) Read the raw ADC values from your accelerometer pins
  int rawX = analogRead(A0);  
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);

  // 2) Apply the single-pole IIR low-pass filter
  //    filteredValue = filteredValue + alpha * (rawValue - filteredValue)
  filteredX = filteredX + alpha * (rawX - filteredX);
  filteredY = filteredY + alpha * (rawY - filteredY);
  filteredZ = filteredZ + alpha * (rawZ - filteredZ);

  Serial.print("Filtered X = ");
  Serial.print(filteredX);
  Serial.print("\tFiltered Y = ");
  Serial.print(filteredY);
  Serial.print("\tFiltered Z = ");
  Serial.println(filteredZ);
}