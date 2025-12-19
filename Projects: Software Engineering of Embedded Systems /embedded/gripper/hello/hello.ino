#include <Arduino.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
/*
 * Gripper Module Implementation
 *
 * Handles servo control for the gripper mechanism.
 * Processes JSON config and command messages via serial.
 *
 * Design notes:
 * - Servo moves smoothly with configurable speed and delay.
 * - JSON errors handled gracefully with error messages.
 * - Ignores unrelated messages.
 *
 * Limitations:
 * - Servo range fixed 0-180 degrees.
 * - Configurable parameters limited to speed, servo delay, IR threshold.
 */

// Pins defined
#define SERVO_PIN D7 // Digital pin D7 connected to servo signal line
#define IR_PIN D6 // Digital pin D6 connected to IR sensor output
#define BAUD_RATE 115200 // Serial communication baud rate

// Global State and Configuration
Servo gripperServo; // Servo object for controlling gripper

int gripperPosition = 50; // Current servo angle (50=open, 180=closed)
bool gripperEngaged = false; // True if gripper is currently holding an object
unsigned long lastEngagedMsg = 0;  // Time when last "engaged" message was sent
unsigned long engagedMsgInterval = 3000; // Interval between "engaged" messages (milliseconds)

// IR Tripwire Settings
int irThreshold = 100; // Required beam break duration (ms) to trigger closing
unsigned long irBreakStart = 0; // Timestamp when beam break started
bool irBroken = false; // Whether beam is currently broken
bool irTriggered = false; // Whether this break has already triggered a close

// Servo Motion Settings
int servoSpeed = 5; // Step size in degrees for each motion increment
int servoDelay = 10; // Delay in ms between servo steps for smooth motion

// Setup Function that initializes serial, servo, and IR sensor
void setup() {
  Serial.begin(BAUD_RATE); // Start serial communication
  gripperServo.attach(SERVO_PIN); // Attach servo to earlier defined pin
  pinMode(IR_PIN, INPUT); // Set IR pin as input
  setGripperPosition(50); // Default to open position
}

// Main Loop handles message processing and sensor updates
void loop() {
  handleSerialInput(); // Check for and process incoming serial commands
  handleIRTripwire(); // Monitor IR sensor for beam breaks
  sendEngagedUpdate(); // Periodically send engaged status if applicable
}

// Serial Input Buffering & Dispatch
 // Buffers input until newline, then processes JSON message
void handleSerialInput() {
  static String input = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processMessage(input); // Process full message
      input = "";
    } else {
      input += c; // Build input buffer
    }
  }
}

// JSON Command Handler
// Parses JSON messages and triggers appropriate actions
void processMessage(const String& msg) {
  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, msg);
  if (err) {
    sendError("Invalid JSON");
    return;
  }

  String mtype = doc["mtype"] | "";

  if (mtype == "gripper.open") {
    int value = doc["value"] | 50;
    moveGripperTo(value);
    sendStatus();
  } else if (mtype == "gripper.close") {
    int value = doc["value"] | 180;
    moveGripperTo(value);
    sendStatus();
  } else if (mtype == "gripper.command") {
    int value = doc["value"] | 0;
    moveGripperTo(value);
    sendStatus();
  } else if (mtype == "gripper.config") {
    String name = doc["name"] | "";
    String valueStr = doc["value"] | "";

    // Handle specific config updates
    if (name == "grip-config") {
      if (valueStr.startsWith("default")) {
        moveGripperTo(50); // Reset to open
      }
    } else if (name == "speed-config") {
      int speed = valueStr.toInt();
      if (speed > 0) servoSpeed = speed;
    } else if (name == "servo-delay") {
      int delayVal = valueStr.toInt();
      if (delayVal > 0) servoDelay = delayVal;
    } else if (name == "ir-threshold") {
      int threshold = valueStr.toInt();
      if (threshold > 0) irThreshold = threshold;
    } else if (name == "engaged-interval") {
      int interval = valueStr.toInt();
      if (interval > 0) engagedMsgInterval = interval;
    } else {
      sendError("Unknown config name");
    }

    sendStatus();
  } else if (mtype == "gripper.report") {
    sendStatus(); // Manual report request
  } else if (mtype == "reset") {
    moveGripperTo(0); // Fully open
    sendReset();
    sendStatus();
  } else {
    sendError("Unknown mtype");
  }
}

// Direct Servo Position Setter
// Immediately sets gripper angle (used for initialization or reset)
void setGripperPosition(int pos) {
  pos = constrain(pos, 50, 180); // Limit angle range
  gripperServo.write(pos);
  gripperPosition = pos;
  gripperEngaged = (pos > 50);
}

// Smooth Servo Motion
// Animates servo movement toward target in small steps
void moveGripperTo(int target) {
  target = constrain(target, 50, 180);
  if (target == gripperPosition) return;

  int step = (target > gripperPosition) ? servoSpeed : -servoSpeed;

  for (int pos = gripperPosition; pos != target; pos += step) {
    gripperServo.write(pos); // Move incrementally
    delay(servoDelay);       // Wait between steps

    // Avoid overshooting the final position
    if ((step > 0 && pos + step > target) || (step < 0 && pos + step < target)) break;
  }

  gripperServo.write(target); // Ensure exact final position
  gripperPosition = target;
  gripperEngaged = (target > 50);
}

// Send Current Gripper State
// Emits JSON status message to host
void sendStatus() {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "gripper.status";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["name"] = "grip-status";
  doc["value"] = (gripperPosition == 50) ? "open" : "closed";
  serializeJson(doc, Serial);
  Serial.println();
}

// Send Error Message
// Sends structured error response to host
void sendError(const char* msg) {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "error";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["message"] = msg;
  serializeJson(doc, Serial);
  Serial.println();
}

// Send Reset Confirmation
// Informs host that module has reset
void sendReset() {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "reset";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["message"] = "reset to default";
  serializeJson(doc, Serial);
  Serial.println();
}

// Periodic "Engaged" Notification
// Used when gripper is holding something
void sendEngagedUpdate() {
  if (gripperEngaged && millis() - lastEngagedMsg > engagedMsgInterval) {
    StaticJsonDocument<128> doc;
    doc["mtype"] = "update";
    doc["from"] = "gripper";
    doc["to"] = "brain";
    doc["message"] = "engaged";
    serializeJson(doc, Serial);
    Serial.println();
    lastEngagedMsg = millis(); // Reset timer
  }
}

// IR Tripwire Monitoring
// Closes gripper if beam is broken too long
void handleIRTripwire() {
  int irState = digitalRead(IR_PIN); // Read IR sensor (LOW = beam broken)

  if (irState == LOW) { // Beam is currently broken
    if (!irBroken) {
      irBreakStart = millis(); // Record start time
      irBroken = true;
    } else if (!irTriggered && (millis() - irBreakStart > irThreshold)) {
      // Beam has been broken long enough to trigger
      irTriggered = true;
      moveGripperTo(180); // Auto-close the gripper
      sendStatus(); // Notify host
    }
  } else {
    // Beam restored
    irBroken = false;
    irTriggered = false; // Reset trigger readiness
  }
}
