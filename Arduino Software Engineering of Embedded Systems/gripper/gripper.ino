#include <Arduino.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#define SERVO_PIN D7
#define IR_PIN D6
#define BAUD_RATE 115200 // Serial communication speed
Servo gripperServo;
// Gripper state variables
int gripperPosition = 50; // Current gripper position (0 = closed, 50 = fully open)
bool gripperEngaged = false; // Whether gripper is considered "engaged" (closed tightly)
unsigned long lastEngagedMsg = 0; // Timestamp of last "engaged" status message sent
unsigned long engagedMsgInterval = 3000; // Minimum time between engaged updates (in ms)
// IR sensor configuration and state
int irThreshold = 300; // Minimum duration (ms) IR beam must be broken to trigger
unsigned long irBreakStart = 0; // Timestamp when IR beam was first detected as broken
bool irBroken = false; // Whether IR beam is currently broken
bool irTriggered = false; // Whether the broken IR state has already triggered a close
bool irInverted = true; // If true: LOW means beam is broken (active low sensor)
unsigned long irLastChange = 0; // Timestamp of last IR input state change (for debouncing)
bool irStableState = false; // Debounced state of IR input
// Servo movement configuration
const int DEFAULT_SERVO_SPEED = 10; // Default speed used after reset (degrees per update)
int servoSpeed = 5; // Configurable speed: how many degrees per step
int servoDelay = 15; // Delay (ms) between steps when moving gripper
// Function declarations
void setGripperPosition(int pos);
void moveGripperTo(int target);
void sendStatus();
void sendError(const char* msg);
void sendReset();
void sendEngagedUpdate();
void handleIRTripwire();
void handleSerialInput();
void processMessage(const String& msg);
void setup() {
  Serial.begin(BAUD_RATE); // Start serial communication
  gripperServo.attach(SERVO_PIN);
  pinMode(IR_PIN, INPUT);
  setGripperPosition(50); // Initialize gripper to open position
  Serial.println("Gripper initialized [50=open, 0=closed]");
}
void loop() {
  handleSerialInput();
  handleIRTripwire();
  sendEngagedUpdate();
}
// Reads serial input and buffers until newline, then processes full message
void handleSerialInput() {
  static String input = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processMessage(input);
      input = "";
    } else {
      input += c;
    }
  }
}
// Parses and processes a JSON-formatted message
void processMessage(const String& msg) {
  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, msg);
  if (err) {
    sendError("Invalid JSON");
    return;
  }
  String mtype = doc["mtype"] | "";
  if (mtype == "gripper.open") {
    moveGripperTo(50);
    sendStatus();
  } else if (mtype == "gripper.close") {
    moveGripperTo(0);
    sendStatus();
  } else if (mtype == "gripper.command") {
    // Command to move to specific position
    int value = doc["value"] | 50;
    value = constrain(value, 0, 50);
    moveGripperTo(value);
    sendStatus();
  } else if (mtype == "reset") {
    sendReset();
  } else if (mtype == "gripper.config") {
    // Handle runtime configuration changes
    String name = doc["name"] | "";
    String valueStr = doc["value"] | "";
    if (name == "speed-config") {
      servoSpeed = valueStr.toInt();
    } else if (name == "servo-delay") {
      servoDelay = valueStr.toInt();
    } else if (name == "ir-threshold") {
      irThreshold = valueStr.toInt();
    } else if (name == "ir-inverted") {
      irInverted = (valueStr == "true");
    } else if (name == "engaged-interval") {
      int interval = valueStr.toInt();
      if (interval >= 500) {
        engagedMsgInterval = interval;
      } else {
        sendError("Invalid engaged interval");
        return;
      }
    } else {
      sendError("Unknown config name");
      return;
    }
    sendStatus();
  }
}
// Immediately sets the gripper position (no animation)
void setGripperPosition(int pos) {
  pos = constrain(pos, 0, 50);
  gripperServo.write(pos);
  gripperPosition = pos;
  gripperEngaged = (pos <= 10); // Considered engaged if nearly closed
}
// Smoothly moves gripper to a target position
void moveGripperTo(int target) {
  target = constrain(target, 0, 50);
  if (target == gripperPosition) return;
  int step = (target > gripperPosition) ? servoSpeed : -servoSpeed;
  while (gripperPosition != target) {
    int newPos = gripperPosition + step;
    if ((step > 0 && newPos > target) || (step < 0 && newPos < target)) {
      newPos = target;
    }
    gripperServo.write(newPos);
    gripperPosition = newPos;
    delay(servoDelay);
  }
  gripperEngaged = (gripperPosition <= 10);
}
// Handles IR beam logic and triggers gripper close if threshold is exceeded
void handleIRTripwire() {
  // Interpret IR state based on inversion
  bool rawState = (digitalRead(IR_PIN) == (irInverted ? LOW : HIGH));
  // Debounce logic: Only change state if stable for >50ms
  if (rawState != irStableState && millis() - irLastChange > 50) {
    irStableState = rawState;
    irLastChange = millis();
    if (irStableState) {
      // Beam has just been broken
      irBreakStart = millis();
      irBroken = true;
      Serial.println("IR: Beam broken - timing...");
    } else {
      // Beam restored
      Serial.println("IR: Beam restored");
      irBroken = false;
      irTriggered = false;
    }
  }
  // If beam broken long enough and not yet triggered, trigger close
  if (irStableState && !irTriggered && millis() - irBreakStart > irThreshold) {
    irTriggered = true;
    Serial.println("IR: Triggered - closing gripper!");
    moveGripperTo(0);
    sendStatus();
  }
}
// Sends a JSON message with current gripper status
void sendStatus() {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "gripper.status";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["position"] = gripperPosition;
  doc["state"] = (gripperPosition == 50) ? "open" : "closed";
  doc["engaged"] = gripperEngaged;
  serializeJson(doc, Serial);
  Serial.println();
}
// Sends a JSON error message
void sendError(const char* msg) {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "error";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["message"] = msg;
  serializeJson(doc, Serial);
  Serial.println();
}
// Resets the gripper to default position and speed, sends confirmation
void sendReset() {
  servoSpeed = DEFAULT_SERVO_SPEED;
  irThreshold = 300;
  engagedMsgInterval = 3000;
  moveGripperTo(50);
  StaticJsonDocument<128> doc;
  doc["mtype"] = "reset";
  doc["from"] = "gripper";
  doc["to"] = "brain";
  doc["message"] = "reset to default (position 50, speed 10)";
  serializeJson(doc, Serial);
  Serial.println();
}
// Sends periodic status updates if gripper is engaged
void sendEngagedUpdate() {
  if (gripperEngaged && millis() - lastEngagedMsg > engagedMsgInterval) {
    sendStatus();
    lastEngagedMsg = millis();
  }
}