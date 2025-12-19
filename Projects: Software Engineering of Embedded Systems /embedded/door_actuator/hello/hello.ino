#include <Arduino.h>

// --- Rotary Encoder Pins ---
#define ENC_SW   D2  // Encoder button (switch) input
#define ENC_DT   D3  // Encoder data A input
#define ENC_CLK  D4  // Encoder data B input

// --- Servo Control Pin ---
#define SERVO_PIN D5 // Servo control signal output

// --- Servo Config ---
#define MIN_ANGLE  30    // Minimum servo angle (°)
#define MAX_ANGLE  130   // Maximum servo angle (°)
#define PULSE_MIN  1000  // Pulse width at MIN_ANGLE (µs)
#define PULSE_MAX  2000  // Pulse width at MAX_ANGLE (µs)
#define PERIOD     20000 // Total PWM period (µs)

// --- Encoder state tracking ---
volatile long position = 0;    // Encoder tick count
int lastEncoded      = 0;      // Last 2-bit encoded state
int lastServoAngle   = -1;     // Last angle written to servo

// --- Interrupt Handler for Rotary Encoder ---
// Triggered on any change on DT or CLK pins
void IRAM_ATTR onEncoderChange() {
  int MSB     = digitalRead(ENC_DT);   // Most significant bit
  int LSB     = digitalRead(ENC_CLK);  // Least significant bit
  int encoded = (MSB << 1) | LSB;      // Combine bits to 2-bit value
  int sum     = (lastEncoded << 2) | encoded;  
  // Detect rotation direction by bit patterns
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) position++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) position--;
  lastEncoded = encoded;  // Update state
}

// --- Servo Pulse Function ---
// Sends a single PWM pulse corresponding to desired angle
void writeServoAngle(int angle) {
  int pulse = map(angle, MIN_ANGLE, MAX_ANGLE, PULSE_MIN, PULSE_MAX);
  pulse = constrain(pulse, PULSE_MIN, PULSE_MAX);
  digitalWrite(SERVO_PIN, HIGH);          // Start pulse
  delayMicroseconds(pulse);               // Hold high for pulse width
  digitalWrite(SERVO_PIN, LOW);           // End pulse
  delayMicroseconds(PERIOD - pulse);      // Complete 20 ms period
}

void setup() {
  // Configure encoder pins with pull-ups
  pinMode(ENC_SW,  INPUT_PULLUP);
  pinMode(ENC_DT,  INPUT_PULLUP);
  pinMode(ENC_CLK, INPUT_PULLUP);
  // Configure servo control pin
  pinMode(SERVO_PIN, OUTPUT);
  // Attach interrupts for rotation detection
  attachInterrupt(digitalPinToInterrupt(ENC_DT),  onEncoderChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), onEncoderChange, CHANGE);
  Serial.begin(9600);  // Initialize serial for debugging
}

void loop() {
  static unsigned long lastPrint = 0;
  // Map encoder position to servo angle range
  int angle = map(position, -50, 50, MIN_ANGLE, MAX_ANGLE);
  angle = constrain(angle, MIN_ANGLE, MAX_ANGLE);

  // Only update servo if angle changed
  if (angle != lastServoAngle) {
    writeServoAngle(angle);
    Serial.print("Servo Angle: ");
    Serial.println(angle);
    lastServoAngle = angle;
  }

  // Every 200 ms, print button state
  if (millis() - lastPrint >= 200) {
    lastPrint = millis();
    Serial.print("Button: ");
    Serial.println(digitalRead(ENC_SW) == LOW ? "Pressed" : "Released");
  }
}
