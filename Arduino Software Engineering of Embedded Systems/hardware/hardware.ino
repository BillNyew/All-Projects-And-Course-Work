/*
 * hardware.ino
 *
 * Monitors ambient light and temperature using:
 * - Photoresistor (D0)
 * - Analog thermistor (D1)
 * - Digital threshold pin from temperature sensor (D2)
 * Triggers alerts on fire-level temperature or light spike.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-05-13
 * Modified: 2025-05-13
 */


// === Pin Definitions ===
const int PIN_PHOTO = D0;
const int PIN_TEMP_ANALOG = D1;
const int PIN_TEMP_DIGITAL = D2;
const int PIN_LED = D7;

// === Constants ===
const float SERIES_RESISTOR_OHM = 10000.0;
const float NOMINAL_RESISTANCE_OHM = 10000.0;
const float NOMINAL_TEMP_K = 298.15;  // 25°C in Kelvin
const float BETA_COEFF = 3950.0;

const int LIGHT_THRESHOLD = 800;
const float TEMP_DELTA_THRESHOLD_C = 3.0;
const float FIRE_THRESHOLD_C = 25.0;

// === Globals ===
float g_baseline_temp_c = -100.0;  // Set after first reading

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;

  analogReadResolution(12);  // ESP32 ADC: 0–4095

  pinMode(PIN_PHOTO, INPUT);
  pinMode(PIN_TEMP_ANALOG, INPUT);
  pinMode(PIN_TEMP_DIGITAL, INPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);  // LED default ON

  Serial.println(F("[environment_sensor] System initialized."));
}

void loop() {
  // === Light Sensor Reading ===
  int light_sum = 0;
  for (int i = 0; i < 10; i++) {
    light_sum += analogRead(PIN_PHOTO);
  }
  int light_avg = light_sum / 10;

  Serial.print(F("Light Sensor Avg: "));
  Serial.println(light_avg);

  if (light_avg > LIGHT_THRESHOLD) {
    Serial.println(F("Light has Changed!"));
    digitalWrite(PIN_LED, LOW);
  } else {
    digitalWrite(PIN_LED, HIGH);
  }

  // === Temperature Sensor Reading (Analog) ===
  int temp_raw = analogRead(PIN_TEMP_ANALOG);
  float voltage_ratio = temp_raw / 4095.0;

  float resistance_ohm = (voltage_ratio / (1.0 - voltage_ratio)) * SERIES_RESISTOR_OHM;
  float temperature_c = -100.0;

  if (resistance_ohm > 0.0) {
    float temp_k = 1.0 / (log(resistance_ohm / NOMINAL_RESISTANCE_OHM) / BETA_COEFF + (1.0 / NOMINAL_TEMP_K));
    temperature_c = temp_k - 273.15;
  } else {
    Serial.println(F("ERROR: Invalid thermistor resistance"));
  }

  Serial.print(F("Temp Sensor Raw: "));
  Serial.print(temp_raw);
  Serial.print(F(" | Calculated °C: "));
  Serial.println(temperature_c, 2);


  // === Fire or Temperature Spike Detection ===
  if (g_baseline_temp_c <= 23.0) {
    g_baseline_temp_c = temperature_c;
    Serial.println(F("Baseline temperature established."));
  } else {
    if (temperature_c - g_baseline_temp_c > TEMP_DELTA_THRESHOLD_C) {
      Serial.println(F("Temperature spike detected!"));
    }

    if (temperature_c >= FIRE_THRESHOLD_C) {
      Serial.println(F("FIRE ALERT: Temperature exceeds fire threshold!"));
      digitalWrite(PIN_LED, LOW);
    }
  }

  Serial.println(F("------------------------"));
  delay(500);  // 2 Hz loop rate
}
