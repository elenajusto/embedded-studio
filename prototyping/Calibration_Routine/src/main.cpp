#include <Arduino.h>

// State variables
int state = 1;  

// Calibration storage variables
float PositiveX = 0, NegativeX = 0;
float PositiveY = 0, NegativeY = 0;
float PositiveZ = 0, NegativeZ = 0;

float OffsetX, OffsetY, OffsetZ;
float ScaleX, ScaleY, ScaleZ;

float ZG, XG, YG;  // Calibrated acceleration values

void setup() {
  // Set analog pins for accelerometer inputs
  pinMode(A0, INPUT); // Z-axis
  pinMode(A1, INPUT); // Y-axis
  pinMode(A2, INPUT); // X-axis

  // Serial output for debugging
  Serial.begin(115200);
  Serial.println("Starting Accelerometer Calibration...");
}


// Function to get average sensor readings
float getAverageReading(int pin) {
    float sum = 0;
    for (int i = 0; i < 10; i++) {
      sum += analogRead(pin);
      delay(10);
    }
    return sum / 10;  // Return averaged reading
  }

void loop() {
  // Step 1: Collect +X Readings
  if (state == 1) {
    Serial.println("Step 1: Place sensor with +X facing UP");
    delay(5000);  // Wait for user positioning
    PositiveX = getAverageReading(A2);
    Serial.println("Positive X collected.");
    state = 2;
  }

  // Step 2: Collect -X Readings
  if (state == 2) {
    Serial.println("Step 2: Place sensor with -X facing UP");
    delay(5000);
    NegativeX = getAverageReading(A2);
    Serial.println("Negative X collected.");
    state = 3;
  }

  // Step 3: Collect +Y Readings
  if (state == 3) {
    Serial.println("Step 3: Place sensor with +Y facing UP");
    delay(5000);
    PositiveY = getAverageReading(A1);
    Serial.println("Positive Y collected.");
    state = 4;
  }

  // Step 4: Collect -Y Readings
  if (state == 4) {
    Serial.println("Step 4: Place sensor with -Y facing UP");
    delay(5000);
    NegativeY = getAverageReading(A1);
    Serial.println("Negative Y collected.");
    state = 5;
  }

  // Step 5: Collect +Z Readings
  if (state == 5) {
    Serial.println("Step 5: Place sensor with +Z facing UP");
    delay(5000);
    PositiveZ = getAverageReading(A0);
    Serial.println("Positive Z collected.");
    state = 6;
  }

  // Step 6: Collect -Z Readings and Compute Calibration
  if (state == 6) {
    Serial.println("Step 6: Place sensor with -Z facing UP");
    delay(5000);
    NegativeZ = getAverageReading(A0);
    Serial.println("Negative Z collected.");

    Serial.println("Computing Calibration Values...");
    
    // Compute offsets
    OffsetX = (PositiveX + NegativeX) / 2;
    OffsetY = (PositiveY + NegativeY) / 2;
    OffsetZ = (PositiveZ + NegativeZ) / 2;

    // Compute scale factors
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

    state = 7;  // Move to normal operation
    delay(2000);
  }

  // Normal Operation: Use Calibrated Values
  if (state == 7) {
    float rawX = analogRead(A2);
    float rawY = analogRead(A1);
    float rawZ = analogRead(A0);

    XG = (rawX - OffsetX) / ScaleX;
    YG = (rawY - OffsetY) / ScaleY;
    ZG = (rawZ - OffsetZ) / ScaleZ;

    Serial.print(">X: "); Serial.println(XG);
    Serial.print(">Y: "); Serial.println(YG);
    Serial.print(">Z: "); Serial.println(ZG);

    delay(500);  // Update rate
  }
}
