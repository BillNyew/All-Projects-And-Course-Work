/*
 * environment_sensor.ino
 *
 * Final Sprint 1 implementation for Environment Sensor
 * - Detects light presence using a photoresistor (D0)
 * - Detects fire-level heat using analog thermistor (D2)
 * - Communicates via JSON messages over Serial
 * - Prioritizes fire alarm for LED output
 * - Does not use pin D0 of the thermoster per instructions by instructor
 *
 * Author: Bill Turbadrakh
 * Created: 2025-05-19
 * Modified: 2025-06-04
 */

#include <ArduinoJson.h>

// === Pin Definitions ===
const int PIN_PHOTO = D0;
const int PIN_TEMP = D2;
const int PIN_LED = D7;

// === Constants ===
const int ADC_RESOLUTION = 4095;
int LIGHT_THRESHOLD = 800;
float FIRE_THRESHOLD_C = 55.0;

const float SERIES_RESISTOR_OHM = 10000.0;
const float NOMINAL_RESISTANCE_OHM = 10000.0;
const float NOMINAL_TEMP_K = 298.15;
const float BETA_COEFF = 3950.0;

const int LOOP_INTERVAL_MS = 1000; 
const size_t JSON_BUFFER_SIZE = 256;
const int BAUD_RATE = 115200;

// === States ===
enum SensorState { STATE_RUNNING, STATE_STOPPED, STATE_ALARM };
SensorState g_temp_state = STATE_STOPPED;
SensorState g_light_state = STATE_STOPPED;

// === Globals ===
String g_input_buffer;
unsigned long g_last_loop_ms = 0;
const char* MODULE_ID = "environment_sensor1";
bool g_waiting_for_start = true;

// === Setup ===
void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) continue;
  analogReadResolution(12);
  pinMode(PIN_PHOTO, INPUT);
  pinMode(PIN_TEMP, INPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);  // LED off initially

  send_waiting_for_start();
}

// === Loop ===
void loop() {
  unsigned long now = millis();
  if (!g_waiting_for_start && (now - g_last_loop_ms >= LOOP_INTERVAL_MS)) {
    g_last_loop_ms = now;

    if (g_light_state != STATE_STOPPED) read_light_sensor();
    if (g_temp_state != STATE_STOPPED) read_temp_sensor();

    // LED Priority Logic (LED ON if alarm, OFF otherwise)
    if (g_temp_state == STATE_ALARM || g_light_state == STATE_ALARM) {
      digitalWrite(PIN_LED, LOW);  // LED ON
    } else {
      digitalWrite(PIN_LED, HIGH); // LED OFF
    }
  }

  // Serial command buffer logic (unchanged)
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n' || ch == '\r') {
      if (g_input_buffer.length() > 0) {
        handle_json(g_input_buffer);
        g_input_buffer = "";
      }
    } else {
      g_input_buffer += ch;
    }
  }
}

// === Light Sensor ===
void read_light_sensor() {
  long sum = 0;
  for (int i = 0; i < 10; i++) sum += analogRead(PIN_PHOTO);
  int avg = sum / 10;
  Serial.print(F("Light Avg: "));
  Serial.println(avg);

  if (avg > LIGHT_THRESHOLD) {
    Serial.println(F("Light is ON"));
    if (g_light_state != STATE_ALARM) send_alarm("light");
    g_light_state = STATE_ALARM;
  } else {
    g_light_state = STATE_RUNNING;
  }
}

// === Temperature Sensor ===
void read_temp_sensor() {
  int raw = analogRead(PIN_TEMP);
  float v_ratio = raw / float(ADC_RESOLUTION);
  float r_ohm = (v_ratio / (1.0 - v_ratio)) * SERIES_RESISTOR_OHM;
  float temp_c = -999.0;
  if (r_ohm > 0.0) {
    float temp_k = 1.0 / (log(r_ohm / NOMINAL_RESISTANCE_OHM) / BETA_COEFF + (1.0 / NOMINAL_TEMP_K));
    temp_c = temp_k - 273.15;
  }
  Serial.print(F("Temp Raw: "));
  Serial.print(raw);
  Serial.print(F(" | Temp °C: "));
  Serial.println(temp_c, 2);

  if (temp_c >= FIRE_THRESHOLD_C) {
    Serial.println(F("FIRE ALERT: Temp exceeds threshold!"));
    if (g_temp_state != STATE_ALARM) send_alarm("temp");
    g_temp_state = STATE_ALARM;
  } else {
    g_temp_state = STATE_RUNNING;
  }
}

// === Command Logic ===
void handle_json(const String& input) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  DeserializationError err = deserializeJson(doc, input);
  if (err) { send_error("Deserialization failed"); return; }
  JsonObject obj = doc.as<JsonObject>();
  const char* to = obj["to"];
  if (!(strcmp(to, MODULE_ID) == 0 || strcmp(to, "*") == 0)) return;

  const char* mtype = obj["mtype"];
  if (!mtype) { send_error("Missing mtype or command"); return; }

  if (strcmp(mtype, "config") == 0) {
    handle_config(obj);
    return;
  }

  const char* cmd = obj["command"];
  if (!cmd) { send_error("Missing command"); return; }

  if (strcmp(cmd, "start") == 0) {
    g_temp_state = g_light_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("start");
  } else if (strcmp(cmd, "stop") == 0) {
    g_temp_state = g_light_state = STATE_STOPPED;
    digitalWrite(PIN_LED, HIGH); // Ensure LED OFF
    g_waiting_for_start = true;
    send_ack("stop");
    send_waiting_for_start();
  } else if (strcmp(cmd, "start_temp") == 0) {
    g_temp_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("start_temp");
  } else if (strcmp(cmd, "stop_temp") == 0) {
    g_temp_state = STATE_STOPPED;
    send_ack("stop_temp");
  } else if (strcmp(cmd, "start_light") == 0) {
    g_light_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("start_light");
  } else if (strcmp(cmd, "stop_light") == 0) {
    g_light_state = STATE_STOPPED;
    send_ack("stop_light");
  } else if (strcmp(cmd, "temp_status") == 0) {
    send_status("temp", read_current_temp());
    send_ack("temp_status");
  } else if (strcmp(cmd, "light_status") == 0) {
    send_status("light", analogRead(PIN_PHOTO));
    send_ack("light_status");
  } else {
    send_error("Unknown command");
  }
}

void handle_config(const JsonObject& obj) {
  const char* name = obj["name"];
  if (!name) { send_error("Missing config name"); return; }

  if (strcmp(name, "start") == 0) {
    g_temp_state = g_light_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("config_start");
  } else if (strcmp(name, "start_temp") == 0) {
    g_temp_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("config_start_temp");
  } else if (strcmp(name, "start_light") == 0) {
    g_light_state = STATE_RUNNING;
    g_waiting_for_start = false;
    send_ack("config_start_light");
  } else if (strcmp(name, "temp_threshold") == 0) {
    float value = obj["value"] | -1.0;
    if (value > 0.0) {
      FIRE_THRESHOLD_C = value;
      Serial.print(F("Updated FIRE_THRESHOLD_C to: "));
      Serial.println(FIRE_THRESHOLD_C);
      send_ack("temp_threshold");
    } else {
      send_error("Invalid threshold value");
    }
  } else if (strcmp(name, "light_threshold") == 0) {
    int value = obj["value"] | -1;
    if (value > 0) {
      LIGHT_THRESHOLD = value;
      Serial.print(F("Updated LIGHT_THRESHOLD to: "));
      Serial.println(LIGHT_THRESHOLD);
      send_ack("light_threshold");
    } else {
      send_error("Invalid threshold value");
    }
  } else {
    send_error("Unknown config name");
  }
}

// === Read Current Temperature ===
float read_current_temp() {
  int raw = analogRead(PIN_TEMP);
  float v_ratio = raw / float(ADC_RESOLUTION);
  float r_ohm = (v_ratio / (1.0 - v_ratio)) * SERIES_RESISTOR_OHM;
  if (r_ohm <= 0.0) return -999.0;
  float temp_k = 1.0 / (log(r_ohm / NOMINAL_RESISTANCE_OHM) / BETA_COEFF + (1.0 / NOMINAL_TEMP_K));
  return temp_k - 273.15;
}

// === Message Helpers ===
void send_alarm(const char* type) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["mtype"] = String(type) + "_sensor.alarm";
  doc["from"] = MODULE_ID;
  doc["to"] = "*";
  doc["name"] = "alarm";
  doc["value"] = type;
  serializeJson(doc, Serial);
  Serial.println();
}

void send_status(const char* type, float value) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["mtype"] = String("environment_sensor.") + type + "_status";
  doc["from"] = MODULE_ID;
  doc["to"] = "*";
  doc["name"] = String(type) + "_status";
  doc["value"] = value;
  serializeJson(doc, Serial);
  Serial.println();
}

void send_error(const char* msg) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["mtype"] = "environment_sensor.error";
  doc["from"] = MODULE_ID;
  doc["to"] = "*";
  doc["name"] = "error";
  doc["value"] = msg;
  serializeJson(doc, Serial);
  Serial.println();
}

void send_ack(const char* cmd) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["mtype"] = "environment_sensor.ack";
  doc["from"] = MODULE_ID;
  doc["to"] = "*";
  doc["name"] = "ack";
  doc["value"] = cmd;
  serializeJson(doc, Serial);
  Serial.println();
}

void send_waiting_for_start() {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["mtype"] = "environment_sensor.status";
  doc["from"] = MODULE_ID;
  doc["to"] = "*";
  doc["name"] = "waiting";
  doc["value"] = "waiting for start command";
  serializeJson(doc, Serial);
  Serial.println();
}
