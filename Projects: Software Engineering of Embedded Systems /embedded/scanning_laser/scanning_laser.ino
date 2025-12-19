#include <ArduinoJson.h>
#include "Wire.h"
#include "TFLI2C.h"
#include <ESP32Servo.h>

// Message types for communication
enum mtype
{
  UNK,
  ERROR,
  DEBUG,
  CONFIG,
  START,
  SET,
  STOP,
};

// Internal command states
enum cmd_state
{
  IDLE,
  MEASURING,
  SETANGLE
};

// I2C sensor and servo objects
TFLI2C sensor;
Servo g_servo;
const int PIN_SERVO = D7; // Servo control pin

// Configuration parameters (with defaults)
int g_angle_resolution_deg = 5; // Degrees per step
int g_sampling_rate_ms = 10;    // Delay between measurements
int g_threshold_cm = 10;        // Threshold for significant change
float g_smoothing_factor = 0.1; // Exponential smoothing factor

// Global state
String g_uniq_id = "scanning_laser_unique_id";
String g_cmd = "";
int g_servo_pos_deg = 0;
int g_servo_fixed_pos_deg = 0;
unsigned g_time = millis();
cmd_state g_cmd_state = IDLE;
JsonDocument g_input_json; // Holds the latest parsed JSON command

// -------- Measurement Helpers --------

// Applies exponential smoothing to a new measurement
int smooth(int val, int arr[], int idx)
{
  int prev = arr[idx];
  return val * g_smoothing_factor + prev * (1 - g_smoothing_factor);
}

// Maintains an array of distances and flags large changes
int set_measurement_array(int msr, int idx)
{
  static int distances[180]; // circular buffer sized for 1° resolution
  if (msr == -1)
  {
    // Initialize/reset all distances
    for (int i = 0; i < 180 / g_angle_resolution_deg; i++)
    {
      distances[i] = 0;
    }
    return 0;
  }
  int new_dist = smooth(msr, distances, idx);
  // If change exceeds threshold, log debug message
  if (abs(distances[idx] - new_dist) > g_threshold_cm)
  {
    char buf[64];
    snprintf(buf, sizeof(buf), "Large change in distance at %d", g_angle_resolution_deg * idx);
    send_message(DEBUG, buf, g_input_json["from"]);
  }
  distances[idx] = new_dist;
  return new_dist;
}

// ---------- Actuation Routines ----------

// Rotate servo and take distance readings at each step
void measuring()
{
  if (millis() - g_time < g_sampling_rate_ms)
    return;
  g_time = millis();
  g_servo.write(g_servo_pos_deg);

  int16_t dist;
  sensor.getData(dist, 0x10);

  // Reverse direction if out of [0,180]
  if (g_servo_pos_deg < 0 || g_servo_pos_deg > 180)
  {
    g_angle_resolution_deg = -g_angle_resolution_deg;
  }
  g_servo_pos_deg += g_angle_resolution_deg;

  int idx = g_servo_pos_deg / abs(g_angle_resolution_deg);
  if (idx >= 0 && idx <= 180)
  {
    set_measurement_array(dist, idx);
  }
}

// Measure distance at a specific angle and report average
void measure_deg_specific(JsonDocument &doc)
{
  String name = doc["name"];
  int value = doc["value"];

  if (name != "target_angle")
  {
    send_message(ERROR, "Expected name 'target_angle'", doc["from"]);
    g_cmd_state = IDLE;
    return;
  }

  if (value < 0 || value > 180)
  {
    send_message(ERROR, "Angle out of range (0–180)", doc["from"]);
    g_cmd_state = IDLE;
    return;
  }

  g_servo.write(value);
  long sum = 0;
  for (int i = 0; i < 10; i++)
  {
    int16_t dist;
    sensor.getData(dist, 0x10);
    sum += dist;
  }

  int avg = sum / 10;
  char buf[64];
  snprintf(buf, sizeof(buf), "Distance at degree %d is: %d", value, avg);
  send_message(DEBUG, buf, doc["from"]);
  g_cmd_state = IDLE;
}

// ---------- Configuration Handling ----------

// Update one of the config parameters
void set_config(JsonDocument &doc)
{
  String name = doc["name"];
  float value = doc["value"];

  if (name == "null" || value == 0.0)
  {
    send_message(ERROR,
                 "Invalid name and value pairs for config",
                 doc["from"]);
    return;
  }

  if (name == "angular_resolution")
  {
    g_angle_resolution_deg = (int)value;
  }
  else if (name == "sampling_rate")
  {
    g_sampling_rate_ms = (int)(1000.0 / value);
  }
  else if (name == "change_threshold")
  {
    g_threshold_cm = (int)value;
  }
  else if (name == "smoothing_factor")
  {
    g_smoothing_factor = value;
  }
  char buf[64];
  snprintf(buf, sizeof(buf), "Config %s has been set %g", name.c_str(), value);
  send_message(DEBUG, buf, doc["from"]);
}

// ---------- JSON & Messaging ----------

// Determine enum type from input string
mtype get_mtype(const String &input_mtype)
{
  if (input_mtype == "config")
    return CONFIG;
  if (input_mtype == "scanning_laser.start")
    return START;
  if (input_mtype == "scanning_laser.stop")
    return STOP;
  if (input_mtype == "scanning_laser.set_angle")
    return SET;
  send_message(ERROR, "Invalid mtype", g_input_json["from"]);
  return UNK;
}

// Send a JSON message back over Serial
void send_message(mtype t, const char *arr, String to)
{
  StaticJsonDocument<200> response;
  response["mtype"] = (t == ERROR ? "error" : "debug");
  response["to"] = to.length() ? to : "*";
  response["from"] = g_uniq_id;
  response["value"] = arr;
  serializeJson(response, Serial);
  Serial.println();
}

// Validate presence of required keys and correct 'to' field
bool validate_json(JsonDocument &doc, bool has_deserialize)
{
  if (!has_deserialize)
    return false;
  if (!doc.containsKey("mtype"))
  {
    send_message(ERROR, "Missing 'mtype' key", "*");
    return false;
  }
  if (!doc.containsKey("from"))
  {
    send_message(ERROR, "Missing 'from' key", "*");
    return false;
  }
  if (!doc.containsKey("to"))
  {
    send_message(ERROR, "Missing 'to' key", "*");
    return false;
  }
  if (doc["to"] != g_uniq_id)
  {
    send_message(ERROR, "Invalid unique id", doc["from"]);
    return false;
  }
  return true;
}

// Accumulate serial input until newline is detected
String handle_serial_input(char c)
{
  g_cmd += c;
  int len = g_cmd.length();
  if (len && (g_cmd.endsWith("\n") || g_cmd.endsWith("\r\n")))
  {
    return g_cmd;
  }
  return "";
}

// Deserialize a JSON string into a document
bool deserialize_input(const String &input, JsonDocument &doc)
{
  DeserializationError error = deserializeJson(doc, input);
  if (error)
  {
    send_message(ERROR, error.c_str(), "*");
    return false;
  }
  return true;
}

// ---------- Arduino Lifecycle ----------

void setup()
{
  Serial.begin(115200);         // Initialize Serial for communication
  g_servo.attach(PIN_SERVO);    // Attach servo motor
  Wire.begin();                 // Initialize I2C bus
  set_measurement_array(-1, 0); // Reset measurement buffer
}

void loop()
{
  bool has_deserialize = false;
  bool is_valid_json = true;

  // Read incoming serial data
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    String cmd = handle_serial_input(c);
    if (cmd.length())
    {
      has_deserialize = deserialize_input(cmd, g_input_json);
      g_cmd = "";
    }
  }

  // Process JSON if valid
  is_valid_json = validate_json(g_input_json, has_deserialize);
  if (is_valid_json && has_deserialize)
  {
    mtype mt = get_mtype(g_input_json["mtype"].as<String>());
    switch (mt)
    {
    case CONFIG:
      g_cmd_state = IDLE;
      set_config(g_input_json);
      break;
    case START:
      g_cmd_state = MEASURING;
      break;
    case STOP:
      g_cmd_state = IDLE;
      break;
    case SET:
      g_cmd_state = SETANGLE;
      break;
    default:
      break;
    }
  }

  // Execute current command state if all configs are set
  if (g_cmd_state == MEASURING)
  {
    measuring();
  }
  else if (g_cmd_state == SETANGLE)
  {
    measure_deg_specific(g_input_json);
  }
}
