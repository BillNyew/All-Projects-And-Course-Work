/*
 * lab3part1.ino
 *
 * Serial interaction and LED control.
 * - Prints "waiting..." once per second using millis()
 * - Reads characters from Serial input
 * - Buffers input into g_cmd
 * - Executes "on" / "off" to control LED
 * - Handles line endings: CR, LF, CRLF
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-13
 * Modified: 2025-04-16
 */

// === Pin Definitions ===
const int PIN_LED = D7;  // Output pin for LED

// === Constants ===
const unsigned long WAITING_INTERVAL_MS = 1000;
const String CMD_ON = "on";
const String CMD_OFF = "off";

// === Global Variables ===
unsigned long g_last_waiting_print_time_ms = 0;
String g_cmd;

void setup() {
  Serial.begin(115200);
  // Wait for Serial to start before printing
  while (!Serial) {
    continue;
  }
  Serial.println(F("Serial has started"));
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  unsigned long current_time_ms = millis();
  // Print "waiting..." once per second
  if (current_time_ms - g_last_waiting_print_time_ms >= WAITING_INTERVAL_MS) {
    Serial.println(F("waiting..."));
    g_last_waiting_print_time_ms = current_time_ms;
  }

  // Read available characters
  while (Serial.available() > 0) {
    char c = Serial.read();
    Serial.printf("read '%c'\n", c);

    // If newline or carriage return, process command
    if (c == '\n' || c == '\r') {
      if (g_cmd.length() > 0) {
        Serial.printf("command: '%s'\n", g_cmd.c_str());

        if (g_cmd.equalsIgnoreCase(CMD_ON)) {
          digitalWrite(PIN_LED, HIGH);
        } else if (g_cmd.equalsIgnoreCase(CMD_OFF)) {
          digitalWrite(PIN_LED, LOW);
        } else {
          Serial.print(F("unrecognized command: '"));
          Serial.print(g_cmd);
          Serial.println(F("'"));
        }
        g_cmd = "";  // Reset command string
      }
    } else {
      g_cmd.concat(c);  // Append char to command buffer
    }
  }
}
