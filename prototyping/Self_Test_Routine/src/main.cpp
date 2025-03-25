#include <Arduino.h>
/*
void setup() 
{

}

void loop() 
{

}

float read_voltage(int pin)
{
  READ analog value from pin
  CONVERT to voltage using ADC formula
  RETURN voltage
}

void self_test()
{
Serial.println("Starting Self-Test...");

// Step 1: Read baseline acceleration values
x_baseline = read_voltage(X_PIN)
y_baseline = read_voltage(Y_PIN)
z_baseline = read_voltage(Z_PIN)

// Step 2: Enable self-test mode
SET ST_PIN HIGH
WAIT 100 milliseconds

// Step 3: Read new acceleration values
x_test = read_voltage(X_PIN)
y_test = read_voltage(Y_PIN)
z_test = read_voltage(Z_PIN)

// Step 4: Calculate changes
x_change = x_test - x_baseline
y_change = y_test - y_baseline
z_change = z_test - z_baseline

PRINT "X Change:", x_change
PRINT "Y Change:", y_change
PRINT "Z Change:", z_change

// Step 5: Compare with expected values
pass = TRUE
IF absolute(x_change - (-0.325)) > 0.1 THEN
    PRINT "X-axis test failed!"
    pass = FALSE
ENDIF

IF absolute(y_change - (0.325)) > 0.1 THEN
    PRINT "Y-axis test failed!"
    pass = FALSE
ENDIF

IF absolute(z_change - (0.550)) > 0.1 THEN
    PRINT "Z-axis test failed!"
    pass = FALSE
ENDIF

// Step 6: Disable self-test mode
SET ST_PIN LOW

// Step 7: Output result
}
*/


// === Pin Definitions ===
#define ST_PIN 2     // Self-Test control pin
#define X_PIN A2
#define Y_PIN A1
#define Z_PIN A0
// === Constants ===
const float SUPPLY_VOLTAGE = 3.3;   // Change if using a different supply voltage
const float TOLERANCE = 0.1;        // Allowable error in g-forces

// Expected self-test voltage changes for 3V (can scale cubically with Vs)
const float EXPECTED_X_CHANGE = -0.325;  // in volts
const float EXPECTED_Y_CHANGE =  0.325;
const float EXPECTED_Z_CHANGE =  0.550;

// === Read Analog Voltage ===
float readVoltage(int pin) {
    int analogVal = analogRead(pin);
    return (analogVal * SUPPLY_VOLTAGE) / 1023.0; //ADC_resolution value = 1023
}

// === Get Sensor Readings (X, Y, Z) ===
void getSensorReadings(float &x, float &y, float &z) {
    x = readVoltage(X_PIN);
    y = readVoltage(Y_PIN);
    z = readVoltage(Z_PIN);
}

// === Check Self-Test Response ===
bool checkSelfTest(float xChange, float yChange, float zChange) {
    bool pass = true;

    if (abs(xChange - EXPECTED_X_CHANGE) > TOLERANCE) {
        Serial.println("X-axis self-test failed.");
        pass = false;
    }
    if (abs(yChange - EXPECTED_Y_CHANGE) > TOLERANCE) {
        Serial.println("Y-axis self-test failed.");
        pass = false;
    }
    if (abs(zChange - EXPECTED_Z_CHANGE) > TOLERANCE) {
        Serial.println("Z-axis self-test failed.");
        pass = false;
    }

    return pass;
}

// === Self-Test Routine ===
void runSelfTest() {
    Serial.println("Running ADXL335 Self-Test...");

    // Step 1: Read baseline
    float xBase, yBase, zBase;
    getSensorReadings(xBase, yBase, zBase);

    // Step 2: Enable self-test mode
    digitalWrite(ST_PIN, HIGH);
    delay(100);  // Wait for sensor to respond

    // Step 3: Read test values
    float xTest, yTest, zTest;
    getSensorReadings(xTest, yTest, zTest);

    // Step 4: Disable self-test mode
    digitalWrite(ST_PIN, LOW);

    // Step 5: Calculate changes
    float xChange = xTest - xBase;
    float yChange = yTest - yBase;
    float zChange = zTest - zBase;

    // Step 6: Print results
    Serial.print("X Change: "); Serial.println(xChange, 3);
    Serial.print("Y Change: "); Serial.println(yChange, 3);
    Serial.print("Z Change: "); Serial.println(zChange, 3);

    // Step 7: Evaluate test
    bool passed = checkSelfTest(xChange, yChange, zChange);

    if (passed) {
        Serial.println(" Self-Test PASSED.");
    } else {
        Serial.println(" Self-Test FAILED.");
    }
}

// === Setup ===
void setup() {

    pinMode(A0, INPUT); // Z-axis
    pinMode(A1, INPUT); // Y-axis
    pinMode(A2, INPUT); // X-axis
  
    // Serial output for debugging
    Serial.begin(115200);
    pinMode(ST_PIN, OUTPUT);
    digitalWrite(ST_PIN, LOW);  // Ensure ST is LOW initially
    delay(500);

    

    runSelfTest();  // Call self-test at startup
}

// === Loop ===
void loop() {

}
