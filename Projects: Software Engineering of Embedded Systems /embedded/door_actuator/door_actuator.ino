#include <Arduino.h>
#include <ArduinoJson.h>

#define ENC_DT   D3
#define ENC_CLK  D4
#define SERVO_PIN D5
#define MIN_ANGLE  30
#define MAX_ANGLE 130
#define PULSE_MIN 1000
#define PULSE_MAX 2000
#define PERIOD     20000

const String moduleID = "door_actuator";  // Module identifier for messaging
volatile long position = 0;  // Encoder position
int lastEncoded = 0;  // Last encoder state
int lastServoAngle = -1;  // Last angle sent to servo
bool moving = false;  // Is the door moving?
String doorStatus = "opened";  // Current door status
unsigned long lastMoveTime = 0;  // Time of last movement

// Configurable parameters
String doorSpeed = "slow";  // Door speed setting
int openThreshold = 500;  // Threshold for door open detection
String initialDoorStatus = "opened";  // Initial door status setting

void sendDebug(const char* name, const String& value);  // Function to send debug messages
void sendConfig(const char* name, const String& value);  // Function to send config messages
void sendError(const char* name, int value);  // Function to send error messages
void writeServoAngle(int angle);  // Function to write angle to servo
void handleIncomingMessage(const String& message);  // Function to handle incoming brain messages

void IRAM_ATTR onEncoderChange() {  // Encoder interrupt handler
  int MSB = digitalRead(ENC_DT);
  int LSB = digitalRead(ENC_CLK);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) position++;  // Increment position
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) position--;  // Decrement position
  lastEncoded = encoded;

  if (!moving) {  // If not already moving, start
    moving = true;
    doorStatus = "open";  // Update status
    sendDebug("door-status", "open");  // Notify brain

    // Send config messages when movement starts
    sendConfig("door-speed", doorSpeed);
    sendConfig("open-threshold", String(openThreshold));
  }

  lastMoveTime = millis();  // Update last movement time
}

void setup() {
  pinMode(ENC_DT, INPUT_PULLUP);  // Encoder pin setup
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(SERVO_PIN, OUTPUT);  // Servo pin setup
  attachInterrupt(digitalPinToInterrupt(ENC_DT), onEncoderChange, CHANGE);  // Encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), onEncoderChange, CHANGE);
  Serial.begin(115200);  // Start serial communication

  // Send initial config message for door status
  sendConfig("initial-door-status", initialDoorStatus);

  // Send debug message that actuator is ready
  sendDebug("door-status", "Door actuator ready");
}

void loop() {
  // Check for incoming messages from brain
  if (Serial.available()) {
    String incoming = Serial.readStringUntil('\n');
    handleIncomingMessage(incoming);
  }

  // If movement stopped (timeout)
  if (moving && millis() - lastMoveTime > 1000) {
    moving = false;
    doorStatus = "opened";  // Note: This should likely be "closed" but code leaves it as "opened"
    sendDebug("door-status", "opened");

    // Report door-close-failure if position too small
    if (abs(position) < 10) {
      int failurePercentage = map(abs(position), 0, 50, 0, 100);
      sendError("door-close-failure", failurePercentage);
    }

    // Report door-open-failure if position too small
    if (abs(position) < openThreshold) {
      int failurePercentage = map(abs(position), 0, 50, 0, 100);
      sendError("door-open-failure", failurePercentage);
    }
  }

  // Convert encoder position to servo angle and update if changed
  int angle = map(position, -50, 50, MIN_ANGLE, MAX_ANGLE);
  angle = constrain(angle, MIN_ANGLE, MAX_ANGLE);
  if (angle != lastServoAngle) {
    writeServoAngle(angle);
    lastServoAngle = angle;
  }
}

void handleIncomingMessage(const String& message) {  // Handle incoming messages
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);
  if (error) return;

  String mtype = doc["mtype"] | "";
  String from = doc["from"] | "";
  String to = doc["to"] | "";
  String name = doc["name"] | "";
  String value = doc["value"] | "";

  if (to != moduleID) return;  // Ignore if not for us

  // Handle door open command
  if (mtype == "door_actuator.open" && name == "close-door" && value == "false") {
    moving = true;
    doorStatus = "open";
    sendDebug("door-status", "open");
    position = 50;  // Simulate full open
    lastMoveTime = millis();
  }
  // Handle door close command
  else if (mtype == "door_actuator.close" && name == "close-door" && value == "true") {
    moving = true;
    doorStatus = "closed";
    sendDebug("door-status", "closed");
    position = -50;  // Simulate full close
    lastMoveTime = millis();
  }
}

void writeServoAngle(int angle) {  // Write angle to servo with PWM
  int pulse = map(angle, MIN_ANGLE, MAX_ANGLE, PULSE_MIN, PULSE_MAX);
  pulse = constrain(pulse, PULSE_MIN, PULSE_MAX);
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(PERIOD - pulse);
}

void sendDebug(const char* name, const String& value) {  // Send debug message
  StaticJsonDocument<128> doc;
  doc["mtype"] = "debug";
  doc["from"] = moduleID;
  doc["to"] = "brain";
  doc["name"] = name;
  doc["value"] = value;
  serializeJson(doc, Serial);
  Serial.println();
}

void sendConfig(const char* name, const String& value) {  // Send config message
  StaticJsonDocument<128> doc;
  doc["mtype"] = "config";
  doc["from"] = "brain";
  doc["to"] = moduleID;
  doc["name"] = name;
  doc["value"] = value;
  serializeJson(doc, Serial);
  Serial.println();
}

void sendError(const char* name, int value) {  // Send error message
  StaticJsonDocument<128> doc;
  doc["mtype"] = "error";
  doc["from"] = moduleID;
  doc["to"] = "brain";
  doc["name"] = name;
  doc["value"] = value;
  serializeJson(doc, Serial);
  Serial.println();
}
