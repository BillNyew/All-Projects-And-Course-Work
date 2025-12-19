/*
 * lab3part3.ino
 *
 * Implements a finite state machine with serial and button input.
 * Bringing together part 1 and part 2
 * Controls servo motion and LED blinking across three states:
 * STOPPED, RUN, STOPPING.
 *
 * Author: Bill Turbadrakh
 * Created: 2025-04-16
 * Modified: 2025-04-17
 */

#include "ESP32Servo.h"

// === Pin Assignments ===
const int PIN_LED = D7;
const int PIN_SERVO = D5;
const int PIN_BUTTON = D2;

// === Constants ===
const unsigned long BLINK_INTERVAL_RUN_MS = 500;      // 2Hz
const unsigned long BLINK_INTERVAL_STOPPING_MS = 100; // 10Hz
const unsigned long SERVO_UPDATE_INTERVAL_MS = 20;    // Speed for smooth motion
const int SERVO_MIN_DEG = 0;
const int SERVO_MAX_DEG = 180;

const String CMD_START = "start";
const String CMD_STOP = "stop";
const bool PRESSED_STATE = HIGH;

// === FSM State ===
enum State {
  STOPPED,
  RUN,
  STOPPING
};
State g_state = STOPPED;

// === Globals ===
Servo g_servo;
String g_cmd = "";

unsigned long g_last_blink_time_ms = 0;
unsigned long g_last_servo_time_ms = 0;
//This line can be removed since it's not used but I wasn't if you wanted it kept or not
unsigned long g_last_button_read_time_ms = 0;

bool g_led_on = false;
//Also this one is not really used
bool g_is_button_pressed = false;
bool g_button_was_pressed = false;

int g_servo_angle_deg = 0;
bool g_servo_increasing = true;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    continue;
  }
  Serial.println(F("Serial has started"));

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  g_servo.attach(PIN_SERVO);
  g_servo.write(SERVO_MIN_DEG);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  read_serial_command();
  check_button_press();
  update_led_blinking();
  update_servo();
}

void read_serial_command() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    Serial.printf("read '%c'\n", c);

    if (c == '\n' || c == '\r') {
      if (g_cmd.length() > 0) {
        Serial.printf("command: '%s'\n", g_cmd.c_str());
        process_command(g_cmd);
        g_cmd = "";
      }
    } else {
      g_cmd.concat(c);
    }
  }
}

void process_command(String cmd) {
  if (cmd.equalsIgnoreCase(CMD_START)) {
    if (g_state == STOPPED || g_state == STOPPING) {
      g_state = RUN;
      Serial.println(F("Transition to RUN"));
    }
  } else if (cmd.equalsIgnoreCase(CMD_STOP)) {
    if (g_state == RUN) {
      g_state = STOPPING;
      Serial.println(F("Transition to STOPPING"));
    }
  } else {
    Serial.print(F("unrecognized command: '"));
    Serial.print(cmd);
    Serial.println(F("'"));
  }
}

void check_button_press() {
  bool is_pressed = digitalRead(PIN_BUTTON) == PRESSED_STATE;

  if (is_pressed && !g_button_was_pressed) {
    // rising edge: button just pressed
    g_is_button_pressed = true;
  }

  if (!is_pressed && g_button_was_pressed) {
    // falling edge: button just released
    if (g_state == STOPPED || g_state == STOPPING) {
      g_state = RUN;
      Serial.println(F("[Button] Transition to RUN"));
    } else if (g_state == RUN) {
      g_state = STOPPING;
      Serial.println(F("[Button] Transition to STOPPING"));
    }
  }

  g_button_was_pressed = is_pressed;
}

void update_led_blinking() {
  unsigned long now_ms = millis();
  unsigned long interval = 0;

  if (g_state == RUN) {
    interval = BLINK_INTERVAL_RUN_MS;
  } else if (g_state == STOPPING) {
    interval = BLINK_INTERVAL_STOPPING_MS;
  } else {
    digitalWrite(PIN_LED, LOW);
    return;
  }

  if (now_ms - g_last_blink_time_ms >= interval) {
    g_led_on = !g_led_on;
    digitalWrite(PIN_LED, g_led_on ? HIGH : LOW);
    g_last_blink_time_ms = now_ms;
  }
}

void update_servo() {
  unsigned long now_ms = millis();
  if (now_ms - g_last_servo_time_ms < SERVO_UPDATE_INTERVAL_MS) return;

  if (g_state == RUN) {
    // Sweep between 0 and 180
    if (g_servo_increasing) {
      g_servo_angle_deg++;
      if (g_servo_angle_deg >= SERVO_MAX_DEG) {
        g_servo_angle_deg = SERVO_MAX_DEG;
        g_servo_increasing = false;
      }
    } else {
      g_servo_angle_deg--;
      if (g_servo_angle_deg <= SERVO_MIN_DEG) {
        g_servo_angle_deg = SERVO_MIN_DEG;
        g_servo_increasing = true;
      }
    }
    g_servo.write(g_servo_angle_deg);
  }
  else if (g_state == STOPPING) {
    // Move back toward 0
    if (g_servo_angle_deg > SERVO_MIN_DEG) {
      g_servo_angle_deg--;
      g_servo.write(g_servo_angle_deg);
    } else {
      // Reached zero
      g_state = STOPPED;
      Serial.println(F("Transition to STOPPED"));
    }
  }

  g_last_servo_time_ms = now_ms;
}
