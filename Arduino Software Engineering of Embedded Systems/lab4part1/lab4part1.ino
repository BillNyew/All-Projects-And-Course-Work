/*
 * lab4part1.ino
 *
 * Manually simulates PWM by toggling an LED on/off at different frequencies and duty cycles.
 * Uses millis() for non-blocking timing.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-18
 * Modified: 2025-04-22
 */

// === Constants ===
const int PIN_LED = D7;
const unsigned long PWM_PERIOD_MS = 10;       // Total period of one PWM cycle
const float DUTY_CYCLE_PERCENT = 50.0;        // Change this value to test different brightness levels

// === Globals ===
bool g_led_on = false;

// Calculated HIGH/LOW durations based on duty cycle
unsigned long g_high_duration_ms = 0;
unsigned long g_low_duration_ms = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // Calculate HIGH/LOW durations
  g_high_duration_ms = (unsigned long)(PWM_PERIOD_MS * (DUTY_CYCLE_PERCENT / 100.0));
  g_low_duration_ms = PWM_PERIOD_MS - g_high_duration_ms;
}

void loop() {
  unsigned long current_time_ms = millis();
  static bool s_led_state = false;
  static unsigned long s_last_toggle_time_ms = millis();
  unsigned long duration_ms = s_led_state ? g_high_duration_ms : g_low_duration_ms;

  if (current_time_ms - s_last_toggle_time_ms >= duration_ms) {
    s_led_state = !s_led_state;
    digitalWrite(PIN_LED, s_led_state ? HIGH : LOW);
    s_last_toggle_time_ms = current_time_ms;
  }
} 
