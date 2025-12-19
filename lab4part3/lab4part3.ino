/*
 * lab4part3.ino
 *
 * Controls a DC motor using the TB6612FNG motor driver and PWM.
 * Ramps speed from 0% to 100% and back, then reverses direction.
 * Uses millis() for non-blocking timing.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-20
 * Modified: 2025-04-22
 */

// === Pin Assignments ===
const int PIN_PWMA = D5;     // PWM pin to control speed
const int PIN_AIN1 = D2;     // Direction control
const int PIN_AIN2 = D3;     // Direction control
const int PIN_STBY = D4;     // Standby control

// === PWM Constants ===
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const unsigned long PWM_UPDATE_INTERVAL_MS = 100;  // ~5s for full ramp

// === Globals ===
int g_duty_cycle = 0;
int g_duty_step = 5;  // Adjust to reach max in ~5s
unsigned long g_last_update_time_ms = 0;
bool g_forward = true;
bool g_ramping_up = true;

void setup() {
  pinMode(PIN_PWMA, OUTPUT);
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_STBY, OUTPUT);

  digitalWrite(PIN_STBY, HIGH); // Enable motor driver
  set_direction(g_forward);
  analogWrite(PIN_PWMA, g_duty_cycle);
}

void loop() {
  unsigned long current_time_ms = millis();

  if (current_time_ms - g_last_update_time_ms >= PWM_UPDATE_INTERVAL_MS) {
    g_last_update_time_ms = current_time_ms;

    if (g_ramping_up) {
      g_duty_cycle += g_duty_step;
      if (g_duty_cycle >= PWM_MAX) {
        g_duty_cycle = PWM_MAX;
        g_ramping_up = false;
      }
    } else {
      g_duty_cycle -= g_duty_step;
      if (g_duty_cycle <= PWM_MIN) {
        g_duty_cycle = PWM_MIN;
        g_ramping_up = true;
        g_forward = !g_forward;
        set_direction(g_forward);
      }
    }
    analogWrite(PIN_PWMA, g_duty_cycle);
  }
}

// === Helper: Set motor direction ===
void set_direction(bool forward) {
  if (forward) {
    digitalWrite(PIN_AIN1, HIGH);
    digitalWrite(PIN_AIN2, LOW);
  } else {
    digitalWrite(PIN_AIN1, LOW);
    digitalWrite(PIN_AIN2, HIGH);
  }
}
