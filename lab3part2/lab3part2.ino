/*
 * lab3part2.ino
 *
 * Demonstrates basic sweeping motion of a standard servo motor.
 * Servo moves from 0° to 180° and back continuously.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-14
 * Modified: 2025-04-16
 */

#include "ESP32Servo.h"  // Correct header for ESP32 boards

// === Constants ===
const int PIN_SERVO = D7;
const int SERVO_DELAY_MS = 15;
const int SERVO_MIN_DEG = 0;
const int SERVO_MAX_DEG = 180;
const int SERVO_STEP_DEG = 1;

// === Global Variables ===
Servo g_servo;               // Servo instance
int g_servo_pos_deg = 0;     // Current servo position in degrees

void setup() {
  g_servo.attach(PIN_SERVO);  // Attach servo to pin D7
}

void loop() {
  // Sweep from 0° to 180°
  for (g_servo_pos_deg = SERVO_MIN_DEG; g_servo_pos_deg <= SERVO_MAX_DEG; g_servo_pos_deg += SERVO_STEP_DEG) {
    g_servo.write(g_servo_pos_deg);
    delay(SERVO_DELAY_MS);
  }

  // Sweep back from 180° to 0°
  for (g_servo_pos_deg = SERVO_MAX_DEG; g_servo_pos_deg >= SERVO_MIN_DEG; g_servo_pos_deg -= SERVO_STEP_DEG) {
    g_servo.write(g_servo_pos_deg);
    delay(SERVO_DELAY_MS);
  }
}
