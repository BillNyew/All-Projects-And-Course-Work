/*
 * lab5part1.ino
 *
 * Generates and parses JSON over Serial using ArduinoJson v7.
 * Outputs JSON every 500ms. Responds to `{ "mtype": "ping", "value": X }` with `pong`.
 * Handles deserialization errors and malformed inputs.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-18
 * Modified: 2025-04-24
 */

#include <ArduinoJson.h>

// === Constants ===
const unsigned long JSON_SEND_INTERVAL_MS = 500;
const size_t JSON_BUFFER_SIZE = 256;

// === Globals ===
unsigned long g_last_send_time_ms = 0;
int g_value = 0;
String g_input_buffer;

void loop_serialize() {
  unsigned long now_ms = millis();
  if (now_ms - g_last_send_time_ms >= JSON_SEND_INTERVAL_MS) {
    StaticJsonDocument<JSON_BUFFER_SIZE> doc;
    doc["mtype"] = "pong";
    doc["millis"] = now_ms;
    doc["value"] = g_value++;

    serializeJson(doc, Serial);
    Serial.println(); // For delimiter
    g_last_send_time_ms = now_ms;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;
  Serial.println(F("lab5part1: Serial initialized"));
}

// === Helper function for handling incoming JSON ===
void handle_json_message(const String& json_input) {
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  DeserializationError error = deserializeJson(doc, json_input);

  if (error) {
    Serial.print(F("Deserialization error: "));
    Serial.println(error.c_str());
    return;
  }

  // Check if mtype exists and is "ping"
  const char* mtype = doc["mtype"] | "";
  if (strcmp(mtype, "ping") != 0) {
    Serial.println(F("Error: mtype is not 'ping' or is missing."));
    return;
  }

  // Check for valid integer value
  if (!doc["value"].is<int>()) {
    Serial.println(F("Error: value is missing or not an integer."));
    return;
  }

  int val = doc["value"];

  // Respond with pong message
  StaticJsonDocument<JSON_BUFFER_SIZE> response;
  response["mtype"] = "pong";
  response["value"] = val + 1;
  response["millis"] = millis();

  serializeJson(response, Serial);
  Serial.println();
}

void loop() {
  loop_serialize();  // continue periodic output

  // === Accumulate input from Serial ===
  while (Serial.available()) {
    char ch = Serial.read();

    if (ch == '\n' || ch == '\r') {
      if (g_input_buffer.length() > 0) {
        handle_json_message(g_input_buffer);
        g_input_buffer = "";
      }
    } else {
      g_input_buffer += ch;
    }
  }
}
