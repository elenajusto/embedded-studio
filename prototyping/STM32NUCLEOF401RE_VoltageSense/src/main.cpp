#include <Arduino.h>

int state = 1;

float PositiveMeasureZ;
float NegativeMeasureZ;
float measureY;
float measureX;
float ZG;

float R1 = 400;
float R2 = 400;

int Average = 0;

void setup() {
  // A0 to read battery voltage
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  // Serial output measurements
  Serial.begin(115200);
  Serial.println("Starting...");
}

void loop() 
{
  // Read voltage
  //float reading = analogRead(A0);
  //float voltage = (reading/1024) * (3.3);

  // Print out readings
  //Serial.print(">Voltage: ");
  //Serial.println(voltage);

  /* Accelerometer Readings */
 /* float readZ = analogRead(A0);
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
  Serial.println(readZ); */
  if(state == 1)
  {
    if (Average < 10)
    {
      float PositiveReadZ = analogRead(A0);
      PositiveMeasureZ = PositiveMeasureZ + PositiveReadZ;
    }
    PositiveMeasureZ = PositiveMeasureZ/10;

    Average = 0;
    delay(5000);

    if (Average < 10)
    {
      float NegativeReadZ = analogRead(A0);
      NegativeMeasureZ = NegativeMeasureZ + NegativeReadZ;
    }
    PositiveMeasureZ = NegativeMeasureZ/10;
    state = 2;
  }

  if (state == 2)
  {
    float OffsetZ = (PositiveMeasureZ + NegativeMeasureZ)/2;

    float ScaleZ = (PositiveMeasureZ - NegativeMeasureZ)/2;

    ZG = (analogRead(A0) - OffsetZ)/ScaleZ;     
    Serial.print(">Z: ");
    Serial.println(ZG);
  }
}