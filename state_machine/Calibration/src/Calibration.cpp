#include "Calibration.h"
#include "C:\Users\saket\OneDrive\Documents\GitHub\embedded-studio\state_machine\Step-tracker\include\BoardConfig.h"

// Calibration state
int state = 1;

// Raw calibration values
float PositiveX = 0, NegativeX = 0;
float PositiveY = 0, NegativeY = 0;
float PositiveZ = 0, NegativeZ = 0;

float OffsetX, OffsetY, OffsetZ;
float ScaleX, ScaleY, ScaleZ;

// Exported global g-values
float XG = 0, YG = 0, ZG = 0;

// Averaging function
float getAverageReading(int pin) {
  float sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(10);
  }
  return sum / 10;
}

void startCalibration() {
  Serial.begin(115200);
  Serial.println("Starting Accelerometer Calibration...");
}

void updateCalibratedValues() {
  if (state == 1) 
  {
    Serial.println("Step 1: Place sensor with +X facing UP");
    delay(5000);
    PositiveX = getAverageReading(A2);
    Serial.println("Positive X collected.");
    state = 2;
  } 
  else if (state == 2) 
  {
    Serial.println("Step 2: Place sensor with -X facing UP");
    delay(5000);
    NegativeX = getAverageReading(A2);
    Serial.println("Negative X collected.");
    state = 3;
  } 
  else if (state == 3) 
  {
    Serial.println("Step 3: Place sensor with +Y facing UP");
    delay(5000);
    PositiveY = getAverageReading(A1);
    Serial.println("Positive Y collected.");
    state = 4;
  } 
  else if (state == 4) 
  {
    Serial.println("Step 4: Place sensor with -Y facing UP");
    delay(5000);
    NegativeY = getAverageReading(A1);
    Serial.println("Negative Y collected.");
    state = 5;
  } 
  else if (state == 5) 
  {
    Serial.println("Step 5: Place sensor with +Z facing UP");
    delay(5000);
    PositiveZ = getAverageReading(A0);
    Serial.println("Positive Z collected.");
    state = 6;
  } 
  else if (state == 6) 
  {
    Serial.println("Step 6: Place sensor with -Z facing UP");
    delay(5000);
    NegativeZ = getAverageReading(A0);
    Serial.println("Negative Z collected.");

    OffsetX = (PositiveX + NegativeX) / 2;
    OffsetY = (PositiveY + NegativeY) / 2;
    OffsetZ = (PositiveZ + NegativeZ) / 2;

    ScaleX = (PositiveX - NegativeX) / 2;
    ScaleY = (PositiveY - NegativeY) / 2;
    ScaleZ = (PositiveZ - NegativeZ) / 2;

    Serial.println("Calibration Complete!");
    Serial.print("Offset X: "); Serial.println(OffsetX);
    Serial.print("Offset Y: "); Serial.println(OffsetY);
    Serial.print("Offset Z: "); Serial.println(OffsetZ);
    Serial.print("Scale X: "); Serial.println(ScaleX);
    Serial.print("Scale Y: "); Serial.println(ScaleY);
    Serial.print("Scale Z: "); Serial.println(ScaleZ);

    state = 7;
    delay(2000);
  } 
  else if (state == 7) 
  {
    float rawX = analogRead(A2);
    float rawY = analogRead(A1);
    float rawZ = analogRead(A0);

    XG = (rawX - OffsetX) / ScaleX;
    YG = (rawY - OffsetY) / ScaleY;
    ZG = (rawZ - OffsetZ) / ScaleZ;

    Serial.print(">X: "); Serial.println(XG);
    Serial.print(">Y: "); Serial.println(YG);
    Serial.print(">Z: "); Serial.println(ZG);
  }
}
