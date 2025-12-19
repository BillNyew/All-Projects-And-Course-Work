/*
 * ultrasonicread.ino
 *
 * Reads distance from an HC-SR04 ultrasonic sensor and prints distance in cm.
 * If the measured distance exceeds MAX_DIST_CM, it prints "Out of range".
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-10
 * Modified: 2025-04-15
 */

// === Pin Definitions ===
const int PIN_TRIG = D2;
const int PIN_ECHO = D3;

// === Constants ===
const unsigned int MAX_DIST_CM = 400;             // Maximum reliable range in cm
const unsigned int MAX_PULSE_WIDTH_US = 23200;    // Based on max range
const unsigned long MEASUREMENT_INTERVAL_MS = 60; // Minimum interval between pings

// === Global Timing Variable ===
unsigned long g_last_measurement_time_ms = 0;

// === Function Prototypes ===
float ping_cm();

void setup() {
  Serial.begin(115200);  // Updated baud rate as required
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void loop() {
  unsigned long current_time_ms = millis();

  if (current_time_ms - g_last_measurement_time_ms >= MEASUREMENT_INTERVAL_MS) {
    float distance_cm = ping_cm();

    if (distance_cm < 0) {
      Serial.println(F("Out of range"));
    } else {
      Serial.print(F("Distance: "));
      Serial.print(distance_cm);
      Serial.println(F(" cm"));
    }

    g_last_measurement_time_ms = current_time_ms;
  }
}

// === ping_cm()
// Triggers the sensor and returns distance in cm.
// Returns -1.0 if pulse width exceeds MAX_PULSE_WIDTH_US
float ping_cm() {
  // Send 10us pulse to trigger
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Wait for echo start
  while (digitalRead(PIN_ECHO) == LOW);

  unsigned long t1_us = micros();

  // Wait for echo end
  while (digitalRead(PIN_ECHO) == HIGH);

  unsigned long t2_us = micros();
  unsigned long pulse_width_us = t2_us - t1_us;

  if (pulse_width_us > MAX_PULSE_WIDTH_US) {
    return -1.0; // Out of range
  }

  float distance_cm = pulse_width_us / 58.0;
  return distance_cm;
}
