/*
 * hello.ino
 *
 * Monitors ambient light and temperature using:
 * - Photoresistor (D0)
 * - Analog thermistor (D1)
 * - Digital threshold pin from temperature sensor (D2)
 * Triggers alerts on fire-level temperature or light spike.
 * Triggers alert when there is a change in light.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-05-13
 * Modified: 2025-05-13
 */

// === Pin Definitions ===
const int PIN_PHOTO = D0;              // Analog input pin for photoresistor
const int PIN_TEMP_ANALOG = D1;        // Analog input pin for thermistor
const int PIN_TEMP_DIGITAL = D2;       // Digital pin for threshold alert (LM393)
const int PIN_LED = D7;                // LED output to signal alert

// === Constants for Thermistor Calculation ===
const float SERIES_RESISTOR_OHM = 10000.0;        // Fixed resistor value (10k) in series with thermistor
const float NOMINAL_RESISTANCE_OHM = 10000.0;     // Resistance of thermistor at 25°C
const float NOMINAL_TEMP_K = 298.15;              // 25°C in Kelvin
const float BETA_COEFF = 3950.0;                  // Beta coefficient of thermistor

// === Alert Thresholds ===
const int LIGHT_THRESHOLD = 800;                  // Photoresistor value above which light change is triggered
const float TEMP_DELTA_THRESHOLD_C = 3.0;         // Temp change above baseline that triggers spike alert
const float FIRE_THRESHOLD_C = 55.0;              // Temp threshold that signals possible fire

// === Globals ===
float g_baseline_temp_c = -100.0;  // Stores initial temperature for comparison (set on first loop)

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;  // Wait for Serial to initialize

  analogReadResolution(12);  // Use 12-bit ADC resolution (0–4095) on ESP32

  // Initialize pin modes
  pinMode(PIN_PHOTO, INPUT);
  pinMode(PIN_TEMP_ANALOG, INPUT);
  pinMode(PIN_TEMP_DIGITAL, INPUT);
  pinMode(PIN_LED, OUTPUT);

  // Turn LED on initially
  digitalWrite(PIN_LED, HIGH);

  Serial.println(F("[environment_sensor] System initialized."));
}

void loop() {
  // === 1. Read Light Sensor ===
  int light_sum = 0;
  for (int i = 0; i < 10; i++) {
    light_sum += analogRead(PIN_PHOTO);  // Sample 10 times to smooth noise
  }
  int light_avg = light_sum / 10;

  Serial.print(F("Light Sensor Avg: "));
  Serial.println(light_avg);

  // Trigger alert if light exceeds threshold
  if (light_avg > LIGHT_THRESHOLD) {
    Serial.println(F("Light has Changed!"));
    digitalWrite(PIN_LED, LOW);  // Turn off LED to indicate alert
  } else {
    digitalWrite(PIN_LED, HIGH); // Normal condition
  }

  // === 2. Read Temperature Sensor (Analog) ===
  int temp_raw = analogRead(PIN_TEMP_ANALOG);            // Raw ADC reading
  float voltage_ratio = temp_raw / 4095.0;                // Normalize to 0.0–1.0

  // Calculate thermistor resistance using voltage divider formula
  float resistance_ohm = (voltage_ratio / (1.0 - voltage_ratio)) * SERIES_RESISTOR_OHM;
  float temperature_c = -100.0;

  // Only calculate if resistance is valid
  if (resistance_ohm > 0.0) {
    float temp_k = 1.0 / (log(resistance_ohm / NOMINAL_RESISTANCE_OHM) / BETA_COEFF + (1.0 / NOMINAL_TEMP_K));
    temperature_c = temp_k - 273.15;  // Convert Kelvin to Celsius
  } else {
    Serial.println(F("ERROR: Invalid thermistor resistance"));
  }

  Serial.print(F("Temp Sensor Raw: "));
  Serial.print(temp_raw);
  Serial.print(F(" | Calculated °C: "));
  Serial.println(temperature_c, 2);

  // === 3. Read Digital Threshold Pin ===
  bool is_digital_triggered = digitalRead(PIN_TEMP_DIGITAL) == HIGH;

  if (is_digital_triggered) {
    Serial.println(F("Digital Threshold Triggered!"));
    digitalWrite(PIN_LED, LOW);  // Visual alert
  }

  // === 4. Spike and Fire Detection (Based on Analog Reading) ===
  if (g_baseline_temp_c == -100.0) {
    g_baseline_temp_c = temperature_c;  // First run sets the baseline
    Serial.println(F("Baseline temperature established."));
  } else {
    // Alert if spike above threshold
    if (temperature_c - g_baseline_temp_c > TEMP_DELTA_THRESHOLD_C) {
      Serial.println(F("Temperature spike detected!"));
    }

    // Alert if fire-level temperature detected
    if (temperature_c >= FIRE_THRESHOLD_C) {
      Serial.println(F("FIRE ALERT: Temperature exceeds fire threshold!"));
      digitalWrite(PIN_LED, LOW);
    }
  }

  Serial.println(F("------------------------"));
  delay(500);  // Loop runs at 2 Hz
}
