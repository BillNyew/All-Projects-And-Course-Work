/*
 * buttonread.ino
 *
 * Reads the state of a pushbutton and turns on an LED when pressed.
 * Also reports if no state change has occurred for over 1000 ms.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-10
 * Modified: 2025-04-15
 */

// === Pin Definitions ===
const int PIN_BUTTON = D2;     // Digital input pin for button
const int PIN_LED = D7;        // Digital output pin for LED

// === Constants ===
const unsigned long STATE_CHANGE_TIMEOUT_MS = 1000;  // Time threshold for inactivity

// === Global Variables ===
// Stores the current and previous button state
int g_button_state = LOW;
int g_last_button_state = LOW;

// Stores the timestamp of the last button state change
unsigned long g_button_changed_at_ms = 0;

// Stores the timestamp of the last time we printed the timeout message
unsigned long g_last_print_time_ms = 0;

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, LOW);  // Ensure LED is off initially

  Serial.begin(9600);

  // Initialize timestamps
  g_button_changed_at_ms = millis();
  g_last_print_time_ms = millis();
}

void loop() {
  // Read current button state
  int button_reading = digitalRead(PIN_BUTTON);

  // Check if the state has changed
  if (button_reading != g_last_button_state) {
    g_button_changed_at_ms = millis();      // Update change timestamp
    g_last_button_state = button_reading;   // Store new state

    if (button_reading == HIGH) {
      digitalWrite(PIN_LED, HIGH);  // LED on
    } else {
      digitalWrite(PIN_LED, LOW);   // LED off
    }
  }

  // Track time since last state change
  unsigned long current_time_ms = millis();

  if ((current_time_ms - g_button_changed_at_ms > STATE_CHANGE_TIMEOUT_MS) &&
      (current_time_ms - g_last_print_time_ms > STATE_CHANGE_TIMEOUT_MS)) {
    Serial.print(F("no state change since "));
    Serial.println(g_button_changed_at_ms);
    g_last_print_time_ms = current_time_ms;  // Update last print time
  }
}