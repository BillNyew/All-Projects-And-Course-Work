/*
 * lab2.ino
 *
 * Combines button input and ultrasonic sensor. Samples sensor at 50Hz
 * while button is pressed and reports distance, duration, average velocity
 * and acceleration when released.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-10
 * Modified: 2025-04-15
 */

// === Pin Assignments ===
const int PIN_BUTTON = D2;
const int PIN_TRIG = D3;
const int PIN_ECHO = D4;

// === Constants ===
const unsigned long SAMPLE_INTERVAL_MS = 20;           // 50Hz
const unsigned long MAX_PULSE_WIDTH_US = 23200;        // Based on 400cm max
const float MAX_DIST_CM = 400.0;

const bool PRESSED_STATE = HIGH; // Button reads HIGH when pressed using pull-down

// === Global Variables ===
bool g_is_button_pressed = false;
unsigned long g_press_start_time_ms = 0;
unsigned long g_last_sample_time_ms = 0;

// Distance tracking
float g_total_distance_cm = 0;
int g_sample_count = 0;

// Motion tracking
float g_prev_distance_cm = -1.0;
float g_prev_velocity_cms = 0.0;
float g_total_velocity_cms = 0.0;
float g_total_acceleration_cmss = 0.0;
int g_velocity_sample_count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT);  // No pullup — we use external pull-down resistor
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void loop() {
  bool is_pressed = (digitalRead(PIN_BUTTON) == PRESSED_STATE);
  unsigned long now_ms = millis();
 
  // === Handle Press Start ===
  if (is_pressed && !g_is_button_pressed) {
    g_is_button_pressed = true;
    g_press_start_time_ms = now_ms;
    g_last_sample_time_ms = now_ms;

    // Reset accumulators
    g_total_distance_cm = 0;
    g_sample_count = 0;
    g_total_velocity_cms = 0.0;
    g_velocity_sample_count = 0;
    g_total_acceleration_cmss = 0.0;
    g_prev_distance_cm = -1.0;
    g_prev_velocity_cms = 0.0;
  }

  // === While Pressed: Sample Sensor ===
  if (g_is_button_pressed && is_pressed && now_ms - g_last_sample_time_ms >= SAMPLE_INTERVAL_MS) {
    float distance_cm = ping_cm();

    if (distance_cm > 0) {
      g_total_distance_cm += distance_cm;
      g_sample_count++;

      // Velocity
      if (g_prev_distance_cm >= 0) {
        float delta_cm = distance_cm - g_prev_distance_cm;
        float velocity_cms = delta_cm / (SAMPLE_INTERVAL_MS / 1000.0); // cm/s
        g_total_velocity_cms += velocity_cms;

        // Acceleration
        float acceleration_cmss = (velocity_cms - g_prev_velocity_cms) / (SAMPLE_INTERVAL_MS / 1000.0); // cm/s²
        g_total_acceleration_cmss += acceleration_cmss;
        g_prev_velocity_cms = velocity_cms;
        g_velocity_sample_count++;
      }

      g_prev_distance_cm = distance_cm;
    }

    g_last_sample_time_ms = now_ms;
  }

  // === Handle Button Release ===
  if (g_is_button_pressed && !is_pressed) {
    g_is_button_pressed = false;

    unsigned long duration_ms = now_ms - g_press_start_time_ms;

    if (g_sample_count > 0) {
      float avg_distance_cm = g_total_distance_cm / g_sample_count;
      float avg_velocity_cms = (g_velocity_sample_count > 0) ? g_total_velocity_cms / g_velocity_sample_count : 0.0;
      float avg_acceleration_cmss = (g_velocity_sample_count > 0) ? g_total_acceleration_cmss / g_velocity_sample_count : 0.0;

      Serial.println(F("=== Measurement Summary ==="));
      Serial.print(F("Average Distance: "));
      Serial.print(avg_distance_cm);
      Serial.println(F(" cm"));

      Serial.print(F("Press Duration: "));
      Serial.print(duration_ms);
      Serial.println(F(" ms"));

      Serial.print(F("Average Velocity: "));
      Serial.print(avg_velocity_cms);
      Serial.println(F(" cm/s"));

      Serial.print(F("Average Acceleration: "));
      Serial.print(avg_acceleration_cmss);
      Serial.println(F(" cm/s²"));
      Serial.println();
    } else {
      Serial.println(F("No valid samples collected."));
    }
  }
}

// === ping_cm() ===
// Triggers ultrasonic sensor and returns distance in cm, or -1.0 if out of range.
float ping_cm() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  while (digitalRead(PIN_ECHO) == LOW);
  unsigned long t1_us = micros();

  while (digitalRead(PIN_ECHO) == HIGH);
  unsigned long t2_us = micros();

  unsigned long pulse_width_us = t2_us - t1_us;
  if (pulse_width_us > MAX_PULSE_WIDTH_US) {
    return -1.0;
  }

  float distance_cm = pulse_width_us / 58.0;
  return distance_cm;
}
