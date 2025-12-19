/*
 * keypad.ino
 *
 * Keypad module for security system - handles user authentication
 * and system state control through 4x4 matrix keypad input.
 *
 * Author: Charles Jensen
 * Created: 2025-05-20
 * Modified: 2025-05-25
 */

#include <ArduinoJson.h>

// Constants
const int KEYPAD_ID = 1;
const unsigned long DEBOUNCE_TIME_MS = 50;
const unsigned long LED_BLINK_DURATION_MS = 250;
const int MAX_PASSCODE_LENGTH = 20;

// Pin assignments
const byte PIN_LED_GREEN = D0;
const byte PIN_LED_RED = D1;
const byte PIN_ROW[4] = {D3, D4, D5, D6};
const byte PIN_COL[4] = {D7, D8, D9, D10};

// Keypad configuration
const byte NUM_ROWS = 4;
const byte NUM_COLS = 4;
const char KEYPAD_KEYS[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Module States
enum keypad_state
{
  ARMED,
  DISARMED,
  RESET,
  REPORT_STATUS,
  LOCKDOWN,
  NONE
};

enum message_type
{
  M_ERROR,
  M_PASSCODE,
  M_STATE,
  M_STATUS,
  M_DEBUG
};

// Global Variables
keypad_state g_previous_state = NONE;
keypad_state g_current_state = ARMED;
String g_entered_code = "";
String g_passcode = "";
String g_master_code = "";
char g_last_key = 0;
int g_failed_attempts = 0;
int g_lockout_attempts = 3;
unsigned long g_passcode_timeout_time_ms = 30000; // 30 seconds default
unsigned long g_time_button_pressed_ms = 0;

// LED control variables
unsigned long g_led_last_toggle_ms = 0;
bool g_led_state = false;
byte g_led_blink_pin = 255;
int g_led_blinks_remaining = 0;
unsigned long g_led_blink_interval_ms = LED_BLINK_DURATION_MS;

// JSON processing
static String s_json_buffer = "";

// Function prototypes
void setup();
void loop();
void read_incoming_json();
void process_keypad_input();
char read_keypad();
void blink_led_non_blocking(byte pin, int times, unsigned long interval_ms);
void update_led_blinking();
void set_state(keypad_state new_state);
void emit_json(const char *mtype, const String &to, const char *name, const String &value);
void emit_serial_message(message_type type, const String &message, const String &string_value = "");
bool is_code_command(const String &suffix);
void handle_code_command(const String &suffix, keypad_state state, const String &label);
void handle_state_command(const String &label, keypad_state state, message_type type, const String &value);
bool is_valid_passcode(const String &code);
bool validate_json_message(const JsonDocument &doc);

void setup()
{
  Serial.begin(115200);

  // Configure row pins as inputs with pullup
  for (byte i = 0; i < NUM_ROWS; i++)
  {
    pinMode(PIN_ROW[i], INPUT_PULLUP);
  }

  // Configure column pins as outputs
  for (byte i = 0; i < NUM_COLS; i++)
  {
    pinMode(PIN_COL[i], OUTPUT);
    digitalWrite(PIN_COL[i], HIGH);
  }

  // Configure LED pins
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Initialize system state
  digitalWrite(PIN_LED_GREEN, HIGH); // Armed state

  emit_serial_message(M_DEBUG, "Keypad system initialized", "initialized");
}

void loop()
{
  read_incoming_json();
  update_led_blinking();

  switch (g_current_state)
  {
  case ARMED:
    process_keypad_input();
    if (g_led_blinks_remaining == 0)
    {
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_RED, LOW);
    }
    break;

  case DISARMED:
    process_keypad_input();
    // Blinking green handled by non-blocking LED function
    if (g_led_blinks_remaining == 0)
    {
      // Implement blinking for disarmed state
      if (millis() - g_led_last_toggle_ms >= 500)
      {
        g_led_state = !g_led_state;
        digitalWrite(PIN_LED_GREEN, g_led_state ? HIGH : LOW);
        digitalWrite(PIN_LED_RED, LOW);
        g_led_last_toggle_ms = millis();
      }
    }
    break;

  case REPORT_STATUS:
  {
    String status_message = "Current status: " + String(g_current_state) +
                            ", Entered Code: " + g_entered_code +
                            ", Failed Attempts: " + String(g_failed_attempts) +
                            ", Current Passcode: " + g_passcode +
                            ", Allowed Tries: " + String(g_lockout_attempts) +
                            ", Master Code: " + g_master_code +
                            ", Code Timeout: " + String(g_passcode_timeout_time_ms / 1000) +
                            ", Keypad ID: " + String(KEYPAD_ID) +
                            ", Previous status: " + String(g_previous_state);
    emit_serial_message(M_STATUS, status_message);
    set_state(g_previous_state);
    break;
  }

  case LOCKDOWN:
    process_keypad_input();
    if (g_led_blinks_remaining == 0)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      digitalWrite(PIN_LED_GREEN, LOW);
    }
    break;

  case RESET:
    g_failed_attempts = 0;
    set_state(ARMED);
    break;

  default:
    break;
  }
}

void read_incoming_json()
{
  if (Serial.available() <= 0)
    return;

  char c = Serial.read();

  if (c == '\n' || c == '\r')
  {
    String serial_message = s_json_buffer;
    s_json_buffer = "";

    if (serial_message.isEmpty())
      return;

    JsonDocument doc_input;
    DeserializationError error = deserializeJson(doc_input, serial_message);

    if (error)
    {
      emit_serial_message(M_ERROR, "JSON parse error: " + String(error.c_str()));
      return;
    }

    if (!validate_json_message(doc_input))
    {
      return; // Error message already sent by validation function
    }

    String to = doc_input["to"];
    if (to != "keypad" + String(KEYPAD_ID) && to != "*")
    {
      return; // Message not for this keypad
    }

    String from = doc_input["from"];
    if (from != "*")
    {
      emit_serial_message(M_ERROR, "Invalid 'from' field, must be '*'");
      return;
    }

    String mtype = doc_input["mtype"];
    String name = doc_input["name"];
    String value = doc_input["value"];

    // Handle different message types
    if (mtype == "keypad.status")
    {
      set_state(REPORT_STATUS);
      return;
    }

    if (mtype == "keypad.config")
    {
      if (name == "passcode")
      {
        if (!doc_input["value"].is<String>() || value.isEmpty() || !is_valid_passcode(value))
        {
          emit_serial_message(M_ERROR, "Value is not valid.");
          return;
        }
        g_passcode = value;
        emit_serial_message(M_PASSCODE, "Passcode successfully set", "Passcode successfully set: " + value);
      }
      else if (name == "master_code")
      {
        if (!doc_input["value"].is<String>() || value.isEmpty() || !is_valid_passcode(value))
        {
          emit_serial_message(M_ERROR, "Invalid master code format");
          return;
        }
        g_master_code = value;
        emit_serial_message(M_DEBUG, "Master code successfully set", "Master code successfully set: " + value);
      }
      else if (name == "lockout_attempts")
      {
        if (!doc_input["value"].is<int>() || value.toInt() < 1)
        {
          emit_serial_message(M_ERROR, "Lockout attempts must be a positive integer");
          return;
        }
        g_lockout_attempts = value.toInt();
        emit_serial_message(M_DEBUG, "Lockout attempts successfully set", "Lockout attempts successfully set: " + String(g_lockout_attempts));
      }
      else if (name == "passcode_timeout_time_s")
      {
        if (!doc_input["value"].is<int>() || value.toInt() < 1)
        {
          emit_serial_message(M_ERROR, "Passcode timeout must be a positive integer");
          return;
        }
        g_passcode_timeout_time_ms = value.toInt() * 1000;
        emit_serial_message(M_DEBUG, "Passcode timeout successfully set", "Passcode timeout successfully set: " + String(value.toInt()) + "s");
      }
      else
      {
        emit_serial_message(M_ERROR, "Unknown configuration parameter: " + name);
      }
    }
    else if (mtype == "keypad.state")
    {
      if (name == "state")
      {
        if (!doc_input["value"].is<String>())
        {
          emit_serial_message(M_ERROR, "State value must be a string");
          return;
        }

        if (value == "arm")
        {
          handle_state_command("ARMED", ARMED, M_STATE, "arm");
        }
        else if (value == "disarm")
        {
          handle_state_command("DISARMED", DISARMED, M_STATE, "disarm");
        }
        else if (value == "reset")
        {
          handle_state_command("RESET", RESET, M_STATE, "reset");
        }
        else
        {
          emit_serial_message(M_ERROR, "Invalid state value: " + value);
        }
      }
      else
      {
        emit_serial_message(M_ERROR, "Unknown state parameter: " + name);
      }
    }
    else
    {
      emit_serial_message(M_ERROR, "Unknown message type: " + mtype);
    }
  }
  else
  {
    s_json_buffer.concat(c);
  }
}

void process_keypad_input()
{
  // Check for timeout
  if (g_passcode_timeout_time_ms > 0 &&
      !g_entered_code.isEmpty() &&
      (millis() - g_time_button_pressed_ms > g_passcode_timeout_time_ms))
  {
    g_entered_code = "";
    emit_serial_message(M_DEBUG, "Passcode entry timed out");
  }

  char key = read_keypad();

  // Debounce and ensure key is not repeating
  if (key != 0 && key != g_last_key)
  {
    g_time_button_pressed_ms = millis();
    g_last_key = key;

    if (g_passcode.isEmpty())
    {
      emit_serial_message(M_ERROR, "No passcode has been set yet");
      return;
    }

    if (g_failed_attempts >= g_lockout_attempts && g_current_state != LOCKDOWN)
    {
      set_state(LOCKDOWN);
      emit_serial_message(M_ERROR, "Too many failed attempts, contact an administrator to reset the system");
      return;
    }

    if (key != '#')
    {
      // Add character to entered code
      if (g_entered_code.length() < MAX_PASSCODE_LENGTH)
      {
        g_entered_code += key;
        digitalWrite(PIN_LED_GREEN, LOW);
        blink_led_non_blocking(PIN_LED_GREEN, 1, 100);
      }
    }
    else
    {
      // Process entered code
      if (g_entered_code.length() <= 0)
        return;

      bool is_correct_code = false;

      if (g_current_state != LOCKDOWN)
      {
        // Check for regular passcode
        if (g_entered_code == g_passcode)
        {
          emit_serial_message(M_PASSCODE, "Correct code", "correct");
          blink_led_non_blocking(PIN_LED_GREEN, 3, LED_BLINK_DURATION_MS);
          is_correct_code = true;
        }
        // Check for command codes
        else if (is_code_command("A"))
        {
          handle_code_command("A", ARMED, "ARMED");
          is_correct_code = true;
        }
        else if (is_code_command("B"))
        {
          handle_code_command("B", DISARMED, "DISARMED");
          is_correct_code = true;
        }
        else if (is_code_command("C"))
        {
          set_state(REPORT_STATUS);
          blink_led_non_blocking(PIN_LED_GREEN, 3, LED_BLINK_DURATION_MS);
          is_correct_code = true;
        }
        else
        {
          // Incorrect passcode
          emit_serial_message(M_PASSCODE, "Incorrect code", "incorrect");
          g_failed_attempts++;
          blink_led_non_blocking(PIN_LED_RED, 3, LED_BLINK_DURATION_MS);
        }
      }
      else
      {
        // In lockdown, only master code + D works
        if (g_entered_code == g_master_code + "D")
        {
          set_state(RESET);
          emit_serial_message(M_STATE, "Lockdown lifted", "reset");
          blink_led_non_blocking(PIN_LED_GREEN, 3, LED_BLINK_DURATION_MS);
          is_correct_code = true;
        }
        else
        {
          emit_serial_message(M_ERROR, "System is in lockdown. Use master code + D to reset");
          blink_led_non_blocking(PIN_LED_RED, 3, LED_BLINK_DURATION_MS);
        }
      }

      if (is_correct_code)
      {
        g_failed_attempts = 0;
      }

      // Reset entered code
      g_entered_code = "";
    }
  }

  // Reset last key on release
  if (key == 0)
  {
    g_last_key = 0;
  }
}

char read_keypad()
{
  for (byte c = 0; c < NUM_COLS; c++)
  {
    digitalWrite(PIN_COL[c], LOW);
    for (byte r = 0; r < NUM_ROWS; r++)
    {
      if (digitalRead(PIN_ROW[r]) == LOW)
      {
        delay(DEBOUNCE_TIME_MS); // Simple debounce
        if (digitalRead(PIN_ROW[r]) == LOW)
        { // Confirm key is still pressed
          digitalWrite(PIN_COL[c], HIGH);
          return KEYPAD_KEYS[r][c];
        }
      }
    }
    digitalWrite(PIN_COL[c], HIGH);
  }
  return 0;
}

void blink_led_non_blocking(byte pin, int times, unsigned long interval_ms)
{
  g_led_blink_pin = pin;
  g_led_blinks_remaining = times * 2; // On and off for each blink
  g_led_blink_interval_ms = interval_ms;
  g_led_last_toggle_ms = millis();
  g_led_state = false;
}

void update_led_blinking()
{
  if (g_led_blinks_remaining > 0 && (millis() - g_led_last_toggle_ms >= g_led_blink_interval_ms))
  {
    g_led_state = !g_led_state;
    digitalWrite(g_led_blink_pin, g_led_state ? HIGH : LOW);

    // Turn off the other LED
    if (g_led_blink_pin == PIN_LED_GREEN)
    {
      digitalWrite(PIN_LED_RED, LOW);
    }
    else
    {
      digitalWrite(PIN_LED_GREEN, LOW);
    }

    g_led_blinks_remaining--;
    g_led_last_toggle_ms = millis();

    if (g_led_blinks_remaining == 0)
    {
      digitalWrite(g_led_blink_pin, LOW);
    }
  }
}

void set_state(keypad_state new_state)
{
  if (g_current_state == RESET || g_current_state == g_previous_state)
  {
    g_current_state = new_state;
    g_previous_state = NONE;
    return;
  }

  if (new_state == NONE)
  {
    g_previous_state = NONE;
    g_current_state = NONE;
    return;
  }

  g_previous_state = g_current_state;
  g_current_state = new_state;
}

void emit_json(const char *mtype, const String &to, const char *name, const String &value)
{
  JsonDocument doc;
  doc["mtype"] = mtype;
  doc["from"] = "keypad" + String(KEYPAD_ID);
  doc["to"] = to;
  doc["name"] = name;
  doc["value"] = value;
  serializeJsonPretty(doc, Serial);
  Serial.println();
}

void emit_serial_message(message_type type, const String &message, const String &string_value)
{
  String output_value = string_value.isEmpty() ? message : string_value;

  Serial.println(message);

  switch (type)
  {
  case M_PASSCODE:
    emit_json("keypad.passcode", "*", "passcode", output_value);
    break;
  case M_STATE:
    emit_json("keypad.state", "*", "state", output_value);
    break;
  case M_STATUS:
    emit_json("keypad.output", "*", "status", output_value);
    break;
  case M_DEBUG:
    emit_json("keypad.output", "*", "debug", output_value);
    break;
  case M_ERROR:
    emit_json("keypad.output", "*", "error", "ERROR: " + message);
    break;
  default:
    break;
  }
}

bool is_code_command(const String &suffix)
{
  return g_entered_code == g_passcode + suffix;
}

void handle_code_command(const String &suffix, keypad_state state, const String &label)
{
  set_state(state);
  String suffix_lower = suffix;
  suffix_lower.toLowerCase();
  emit_serial_message(M_STATE, "Status changed to " + label, suffix_lower);
  blink_led_non_blocking(PIN_LED_GREEN, 3, LED_BLINK_DURATION_MS);
}

void handle_state_command(const String &label, keypad_state state, message_type type, const String &value)
{
  set_state(state);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  emit_serial_message(type, "Keypad state set to " + label, value);
}

bool is_valid_passcode(const String &code)
{
  if (code.length() == 0)
    return false;

  for (unsigned int i = 0; i < code.length(); i++)
  {
    char c = code.charAt(i);
    if (!(isDigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '*'))
    {
      return false;
    }
  }
  return true;
}

bool validate_json_message(const JsonDocument &doc)
{
  if (!(doc.containsKey("mtype") && doc.containsKey("from") && doc.containsKey("to")))
  {
    emit_serial_message(M_ERROR, "JSON message is missing required keys (mtype, from, to)");
    return false;
  }

  String mtype = doc["mtype"];
  if (mtype != "keypad.state" && mtype != "keypad.status" && mtype != "keypad.config")
  {
    emit_serial_message(M_ERROR, "Invalid message type: " + mtype);
    return false;
  }

  // For config and state messages, name and value are required
  if ((mtype == "keypad.config" || mtype == "keypad.state") &&
      !(doc.containsKey("name") && doc.containsKey("value")))
  {
    emit_serial_message(M_ERROR, "JSON message is missing required keys (name, value)");
    return false;
  }

  if (doc.containsKey("value") && doc["value"].is<bool>())
  {
    emit_serial_message(M_ERROR, "Value cannot be a boolean");
    return false;
  }

  return true;
}