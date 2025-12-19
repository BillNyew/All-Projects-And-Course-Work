#include <Arduino.h>
#include <ArduinoJson.h>

// this is sprint1
const int irSensorPin = D6; // Signal from IR receiver
const int ledPin = 10; // LED indicates beam state
int lastBeamState = HIGH; // Previous sensor state

// Module configuration
unsigned long reportInterval = 0; // ms
unsigned int sensitivity = 1; // number of detections before report
int tripCounter = 0;

unsigned long lastReportTime = 0;
String moduleID = "IRBreakBeamSensor3mm";

// Serial input handling
String inputBuffer = "";

// Function declarations
void sendAck(String cmd, String status, String to, String msg = "");
void sendError(String msg);
void sendBeamState(int beamState);
void handleSerialInput();
void handleBeamDetection();
void processMessage(String message);
void handleConfig(JsonDocument& doc, const String& sender);

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("IRBreakBeamSensor3mm Initialized");
}

void loop() {
  handleSerialInput();
  handleBeamDetection();
}

// this part does the beam detection logic

void handleBeamDetection() {
  delay(50);
  int currentState = digitalRead(irSensorPin);  // HIGH = clear, LOW = tripped

  // Report on beam state change
  if (currentState != lastBeamState) {
    lastBeamState = currentState;
    tripCounter++;

    if (tripCounter >= sensitivity) {
      tripCounter = 0;
      sendBeamState(currentState);
    }

    digitalWrite(ledPin, (currentState == LOW) ? HIGH : LOW);
  }

  // Periodic reporting
  if (reportInterval > 0 && (millis() - lastReportTime >= reportInterval)) {
    lastReportTime = millis();
    sendBeamState(currentState);
  }
}

void sendBeamState(int beamState) {
  StaticJsonDocument<128> doc;
  doc["mtype"] = "IRBreakBeamSensor3mm.beam_state";
  doc["from"] = moduleID;
  doc["to"] = "*";
  doc["state"] = (beamState == LOW) ? "tripped" : "clear";
  serializeJson(doc, Serial);
  Serial.println();
}

// message handling

void handleSerialInput() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processMessage(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

void processMessage(String message) {
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    sendError("Malformed JSON");
    return;
  }

  if (!doc.containsKey("mtype") || !doc.containsKey("from") || !doc.containsKey("to")) {
    sendError("Missing required fields");
    return;
  }

  String mtype = doc["mtype"];
  String sender = doc["from"];
  String recipient = doc["to"];

  if (!(recipient == "*" || recipient == moduleID)) return;

  if (mtype == "config") {
    handleConfig(doc, sender);
  } else if (mtype == "IRBreakBeamSensor3mm.start") {
    lastReportTime = millis();
    sendAck("start", "ok", sender);
  } else if (mtype == "IRBreakBeamSensor3mm.stop") {
    reportInterval = 0;
    sendAck("stop", "ok", sender);
  } else {
    sendError("Unsupported mtype: " + mtype);
  }
}

void handleConfig(JsonDocument& doc, const String& sender) {
  if (!doc.containsKey("name") || !doc.containsKey("value")) {
    sendAck("config", "error", sender, "Missing config fields");
    return;
  }

  String name = doc["name"];
  String value = doc["value"];

  if (name == "report_interval_ms") {
    reportInterval = value.toInt();
    sendAck("config", "ok", sender);
  } else if (name == "sensitivity") {
    sensitivity = value.toInt();
    if (sensitivity < 1) sensitivity = 1;
    sendAck("config", "ok", sender);
  } else {
    sendAck("config", "error", sender, "Unknown config parameter");
  }
}

// message senders

void sendAck(String cmd, String status, String to, String msg) {
  StaticJsonDocument<256> doc;
  doc["mtype"] = "IRBreakBeamSensor3mm.ack";
  doc["from"] = moduleID;
  doc["to"] = to;
  doc["command"] = cmd;
  doc["status"] = status;
  doc["message"] = msg;
  serializeJson(doc, Serial);
  Serial.println();
}

void sendError(String msg) {
  StaticJsonDocument<256> doc;
  doc["mtype"] = "error";
  doc["from"] = moduleID;
  doc["to"] = "*";
  doc["message"] = msg;
  serializeJson(doc, Serial);
  Serial.println();
}
