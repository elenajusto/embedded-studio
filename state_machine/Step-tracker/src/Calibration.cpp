#include "Calibration.h"
#include "BoardConfig.h"

int state = 1;

float PositiveX = 0, NegativeX = 0;
float PositiveY = 0, NegativeY = 0;
float PositiveZ = 0, NegativeZ = 0;

float OffsetX, OffsetY, OffsetZ;
float ScaleX, ScaleY, ScaleZ;

float XG = 0, YG = 0, ZG = 0;

// Internal timer variables
unsigned long stateStartTime = 0;
bool waitingForPositioning = false;

float getAverageReading(int pin) {
  float sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(10);  // Still fine here for quick averaging (total ~100ms)
  }
  return sum / 10;
}

void startCalibration() {
  Serial.begin(115200);
  Serial.println("Starting Accelerometer Calibration...");
  state = 1;
  waitingForPositioning = true;
  stateStartTime = millis();
}

void updateCalibratedValues() {
  unsigned long currentTime = millis();

  if (state >= 1 && state <= 6) {
    if (waitingForPositioning && currentTime - stateStartTime >= 5000) {
      // Enough time has passed — take readings
      switch (state) 
      {
        case 1:
          Serial.println("Step 1: +X facing UP");
          PositiveX = getAverageReading(PIN_SIGNAL_X);
          Serial.println("Positive X collected.");
          break;
        case 2:
          Serial.println("Step 2: -X facing UP");
          NegativeX = getAverageReading(PIN_SIGNAL_X);
          Serial.println("Negative X collected.");
          break;
        case 3:
          Serial.println("Step 3: +Y facing UP");
          PositiveY = getAverageReading(PIN_SIGNAL_Y);
          Serial.println("Positive Y collected.");
          break;
        case 4:
          Serial.println("Step 4: -Y facing UP");
          NegativeY = getAverageReading(PIN_SIGNAL_Y);
          Serial.println("Negative Y collected.");
          break;
        case 5:
          Serial.println("Step 5: +Z facing UP");
          PositiveZ = getAverageReading(PIN_SIGNAL_Z);
          Serial.println("Positive Z collected.");
          break;
        case 6:
          Serial.println("Step 6: -Z facing UP");
          NegativeZ = getAverageReading(PIN_SIGNAL_Z);
          Serial.println("Negative Z collected.");

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

          // Add 2s pause before proceeding to runtime mode
          stateStartTime = currentTime;
          waitingForPositioning = true;
          state++;
          return;
      }

      // Go to next calibration step
      state++;
      stateStartTime = currentTime;
      waitingForPositioning = true;
    } else if (!waitingForPositioning) {
      // Prompt user once per state
      Serial.print("Place sensor for step ");
      Serial.println(state);
      waitingForPositioning = true;
      stateStartTime = currentTime;
    }
  }

  // Small 2s hold after step 6 before normal operation
  else if (state == 7 && currentTime - stateStartTime >= 2000) {
    state = 8;  // Final state: runtime tracking
  }

  else if (state == 8) {
    float rawX = analogRead(PIN_SIGNAL_X);
    float rawY = analogRead(PIN_SIGNAL_Y);
    float rawZ = analogRead(PIN_SIGNAL_Z);

    XG = (rawX - OffsetX) / ScaleX;
    YG = (rawY - OffsetY) / ScaleY;
    ZG = (rawZ - OffsetZ) / ScaleZ;

    Serial.print(">X: "); Serial.println(XG);
    Serial.print(">Y: "); Serial.println(YG);
    Serial.print(">Z: "); Serial.println(ZG);
  }
}

bool isCalibrationDone() {
  return state >= 8;
}
