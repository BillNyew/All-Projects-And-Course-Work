// By Jonathan Brouillette
// This code is for a door sensor that can be controlled via serial commands.
// It uses a digital pin to read the state of the door sensor and can be configured to operate in different modes.
#include <ArduinoJson.h> // Include the ArduinoJson library for JSON parsing
//constant variables
const int STOPPED = 0; // no polling or broadcasting
const int CONTINUOUS = 1;// send current state continuously at broadcast rate in Hz
const int ALARM = 2; // send state when door is open
const int REED_PIN = D7;
const String UNIQUE_ID = "door_sensor1"; // Unique ID for the door sensor
//config options (DEFAULT VALUES)
int g_door_open_threshold = 5; // # of consecutive readings to consider door open
int g_polling_rate_hz = 1;
int g_broadcast_rate_hz = 1;
//state variables
int g_door_sensor_state = STOPPED;
bool g_is_door_open = false;
//threshold helper variables
//stores the last readings to determine if the threshold of consecutive readings has been reached
int door_readings[20]; // max threshold, or use dynamic allocation if needed
int door_readings_count = 0;
//command variables
String g_json = "";//command string

void read_from_serial();
void parse_command(JsonDocument& doc);
//function prototypes

void setup() {
  Serial.begin(115200);
  pinMode(REED_PIN, INPUT);
}


void loop() {
  static unsigned long last_poll_time_ms = 0;
  static unsigned long last_broadcast_time_ms = 0;
  unsigned long current_time_ms = millis();

  if (g_door_sensor_state == STOPPED) {
    return; // Do nothing if stopped
  } else {
    if (current_time_ms - last_poll_time_ms >= (1000 / g_polling_rate_hz)) {
      last_poll_time_ms = current_time_ms;
      int door_sensor_value = digitalRead(REED_PIN);

      // Store the reading
      if (door_readings_count < g_door_open_threshold) {
        door_readings[door_readings_count++] = door_sensor_value;
      }

      // If we've collected enough readings, make a decision
      if (door_readings_count == g_door_open_threshold) {
        bool all_high = true;
        for (int i = 0; i < g_door_open_threshold; i++) {
          if (door_readings[i] == 0) {
            all_high = false;
            break;
          }
        }
        g_is_door_open = all_high;

        // Wipe the array for the next decision
        door_readings_count = 0;
      }
    }
    if ((g_door_sensor_state == ALARM && g_is_door_open) || g_door_sensor_state == CONTINUOUS) {
      // Broadcast the state if in ALARM mode and door is open or in CONTINUOUS mode
      if (current_time_ms - last_broadcast_time_ms >= (1000 / g_broadcast_rate_hz)) {
        last_broadcast_time_ms = current_time_ms;
        //broadcast door sensor state
        StaticJsonDocument<256> doc;
        doc["mtype"] = "door_sensor.state";
        doc["state"] = g_is_door_open;
        doc["from"] = UNIQUE_ID;
        doc["to"] = "*"; // Broadcast to all
        // Serialize and send the JSON document
        serializeJson(doc, Serial);
      }
    }
  }//end of else

  read_from_serial();// Read and process incoming serial commands
}

void read_from_serial() {
  // Accumulate incoming characters into g_json until a newline or closing brace
  while (Serial.available() > 0) {
    char c = Serial.read();
    g_json += c;
    // End of JSON object (assuming each message is one line)
    if (c == '\n' || c == '}') {
      // Parse JSON
      StaticJsonDocument<256> doc;
      DeserializationError error = deserializeJson(doc, g_json);
      if (error) {
        g_json = "";
        return;
      }else {
        // Successfully parsed JSON, now handle the command
        parse_command(doc);
      }
      g_json = ""; // Clear the buffer for the next message
    }
  }
}

void parse_command(JsonDocument& doc) {
  // Check if message is for this sensor
  const char* to = doc["to"];
  if (to && String(to) != UNIQUE_ID) {
    g_json = "";
    return; // Not for us
  }

  // Handle config messages
  const char* mtype = doc["mtype"];
  if (mtype) {
    String mtypeStr = String(mtype);

    if (mtypeStr.endsWith(".stop")) {
      g_door_sensor_state = STOPPED;
    } else if (mtypeStr.endsWith(".start_continuous")) {
      g_door_sensor_state = CONTINUOUS;
    } else if (mtypeStr.endsWith(".start_alarm")) {
      g_door_sensor_state = ALARM;
    } else if (mtypeStr == "config") {
      // Handle config parameter changes
      const char* name = doc["name"];
      int value = doc["value"];
      if (name) {
        String nameStr = String(name);
        if (nameStr == "polling_rate_hz") {
          g_polling_rate_hz = value;
        } else if (nameStr == "door_open_threshold") {
          g_door_open_threshold = value;
          door_readings_count = 0; // reset readings
        } else if (nameStr == "broadcast_rate_hz") {
          g_broadcast_rate_hz = value;
        }
      }
    }//unknown message type
  }
}

//testing for door sensor 