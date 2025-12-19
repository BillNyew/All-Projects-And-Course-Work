/*
 * lab4part2.ino
 *
 * Demonstrates built-in PWM functionality using analogWrite() on ESP32-C3.
 * LED brightness is smoothly pulsed by ramping duty cycle 0 → 255 → 0.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-18
 * Modified: 2025-04-22
 */

// === Constants ===
const int PIN_LED = D7;
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const unsigned long PWM_UPDATE_INTERVAL_MS = 25;  // Adjust for pulsing speed

// === Globals ===
int g_duty_cycle = 0;
int g_duty_step = 1;
unsigned long g_last_update_time_ms = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  analogWrite(PIN_LED, g_duty_cycle);  // Start at 0 (fully off)
}

void loop() {
  unsigned long current_time_ms = millis();

  if (current_time_ms - g_last_update_time_ms >= PWM_UPDATE_INTERVAL_MS) {
    g_duty_cycle += g_duty_step;

    if (g_duty_cycle >= PWM_MAX || g_duty_cycle <= PWM_MIN) {
      g_duty_step = -g_duty_step;  // Reverse direction
    }
    g_duty_cycle = constrain(g_duty_cycle, PWM_MIN, PWM_MAX);
    analogWrite(PIN_LED, g_duty_cycle);
    g_last_update_time_ms = current_time_ms;
  }
}
