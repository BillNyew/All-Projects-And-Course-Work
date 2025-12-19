#include <ArduinoJson.h>
/*
 * Sound sensor module implementation
 * 
 * Vincent Perez
 * */

// Setters
void set_warning_threshold(int val_db);
void set_baseline_broadcast_rate(int val_ms);
void set_listen_rate(int val_ms);
void set_listen_time(int val_ms);
// Message creation
void create_error_msg(String receiver, String message);
void create_output_msg(String receiver, int val);
void create_alert_msg(String receiver, String alert_level);
// State management, message sending
void send_msg();
void start();
void stop();
// Hardware interactions
int read_sensor();
String get_alert_level();
// Hardware setup
const int SOUND_SENSOR_PIN = A0;
const int BAUD_RATE = 9600;


// Input and output buffers for JSON data
JsonDocument g_output_msg;
JsonDocument g_input_msg;
String json_msg = "";

// Baselines and thresholds
int g_warning_threshold_db = 0;
int g_baseline_db = 0;
int g_broadcast_rate_ms = 0;
int g_listen_rate_ms = 0;
int g_listen_time_ms = 0;
int g_sensor_reading = 0;
int g_sum_db = 0;
int g_low_alert = 1000;
int g_medium_alert = 3000;
int g_high_alert = 4000;
// Timers for different evens 
unsigned long g_current_time_ms = millis();
unsigned long g_prev_time_ms = 0;
unsigned long g_current_time_ms_lr = millis();
unsigned long g_prev_time_ms_lr = 0;
unsigned long g_current_time_ms_lt = millis();
unsigned long g_prev_time_ms_lt = 0;

// Set the reading state. If false, we are in the idle state
bool g_reading = false;
// Check if we should be sampling
bool g_sampling = false;

// Set after receiving config message
void set_warning_threshold(int val_db) {
  g_warning_threshold_db = val_db;
}

void set_baseline_broadcast_rate(int val_ms) {
  g_broadcast_rate_ms = val_ms;
}

void set_listen_rate(int val_ms) {
  g_listen_rate_ms = val_ms;
}

void set_listen_time(int val_ms) {
  g_listen_time_ms = val_ms;
}

// Create a new JSON message to send as an output or error message
void create_error_msg(String receiver, String message) {
  g_output_msg["mtype"] = "error";
  g_output_msg["from"] = "sound_sensor";
  g_output_msg["to"] = "*";
  g_output_msg["message"] = message;
}

void create_output_msg(String receiver, int val) {
  g_output_msg["mtype"] = "sensor_output";
  g_output_msg["from"] = "sound_sensor";
  g_output_msg["to"] = "*";
  g_output_msg["name"] = "sound_baseline_decibels";
  g_output_msg["value"] = val;
}

void create_alert_msg(String receiver, String alert_level) {
  g_output_msg["mtype"] = "sensor_output";
  g_output_msg["from"] = "sound_sensor";
  g_output_msg["to"] = "*";
  g_output_msg["name"] = "decibels_above_baseline";
  g_output_msg["alert_level"] = alert_level;
}

void handle_config() {
  if (g_input_msg["name"] == nullptr) {
    Serial.println("Missing name parameter");
    return;
  }
  if (g_input_msg["name"] == "warning_threshold_decibels") {
    set_warning_threshold(g_input_msg["value"]);
  }
  else if (g_input_msg["name"] == "baseline_broadcast_rate_ms") {
    set_baseline_broadcast_rate(g_input_msg["value"]);
  }
  else if (g_input_msg["name"] == "listen_rate_ms") {
    set_listen_rate(g_input_msg["value"]);
  }
  else if (g_input_msg["name"] == "listen_time_ms") {
    set_listen_time(g_input_msg["value"]);
  }
  else {
    Serial.println("Invalid name");
  }
}

bool validate_json_input() {
  if (g_input_msg["name"] == nullptr) {
      Serial.println("Missing mtype");
      return false;
  }
  if (g_input_msg["mtype"] == nullptr) {
      Serial.println("Missing mtype");
      return false;
  }
  if (g_input_msg["from"] == nullptr || g_input_msg["to"] != "sound_sensor") {
      Serial.println("Missing mtype");
      return false;
  }

  if (g_input_msg["name"] == nullptr) {
      Serial.println("Missing mtype");
      return false;
  }

  if (g_input_msg["value"] == nullptr) {
      Serial.println("Missing mtype");
      return false;
  }

  return true;
}

void handle_input_msg() {
  // If the json message is invalid, do nothing and report it within the function
  if (!validate_json_input()) {
    return;
  }

  if (g_input_msg["mtype"] == "config") {
    handle_config();
  }
  else if (g_input_msg["mtype"] == "sound-sensor.start") {
    start();
  }
  else if (g_input_msg["mtype"] == "sound-sensor.stop") {
    stop();
  }
  else {
    Serial.println("Invalid mtype from input");
  }
}

void send_msg() {
  serializeJson(g_output_msg, Serial);
}

void start() {
  g_reading = true;
}

void stop() {
  g_reading = false;
}

// Hardware operations

int read_sensor() {
  return analogRead(A0);
}

String get_alert_level(int val_db) {
  if (val_db < g_low_alert) {
    return "low";
  }
  else if (val_db > g_low_alert || val_db < g_high_alert) {
    return "medium";
  }
  else if (val_db > g_high_alert){
    return "high";
  }
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(SOUND_SENSOR_PIN, INPUT);
}

void loop() {
  // Read the message if there is one
  if (Serial.available()) {
    char c = Serial.read();
    DeserializationError json_error = deserializeJson(g_input_msg, json_msg);
    if (c == '\n' || c == '\r') {
      if (json_error) {
        Serial.println("Failed to deserialize JSON");
        Serial.println(json_error.c_str());
      } else {
        handle_input_msg();
      }
      json_msg = "";
      g_input_msg.clear();
    } else {
      json_msg.concat(c);
    }
  }
  // Read the sensor at specified intervals
  if (g_current_time_ms_lr - g_prev_time_ms_lr >= g_listen_rate_ms) {
    g_prev_time_ms_lr = g_current_time_ms_lr;
    g_sensor_reading = read_sensor();
  }

  // If we have not taken the amount of samples, 
  if (g_current_time_ms_lt - g_prev_time_ms_lt < g_listen_time_ms) {
    g_prev_time_ms_lt = g_current_time_ms_lt;
    g_sum_db += g_sensor_reading;
  }

  else {
    // Get the baseline 
    g_baseline_db = g_sum_db / g_listen_time_ms;
    // Reset once we have read the amount of samples necessary
    g_current_time_ms_lt = 0;
    g_sum_db = 0;
  }

  // Send a warning at any time if the sensor reading is above the threshold
  if (g_sensor_reading >= g_warning_threshold_db) {
    String alert_level = get_alert_level(g_sensor_reading);
    create_alert_msg("*", alert_level);
    send_msg();
    g_output_msg.clear();
  }

  // Send the baseline to all modules
  if (g_current_time_ms - g_prev_time_ms >= g_broadcast_rate_ms) {
    create_output_msg("*", g_baseline_db);
    send_msg();
    g_prev_time_ms = g_current_time_ms;
    g_output_msg.clear();
  }
}
