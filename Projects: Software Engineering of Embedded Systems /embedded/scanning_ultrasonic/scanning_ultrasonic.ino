#include <ESP32Servo.h>
#include <ArduinoJson.h>

const int TRIG_PIN = D1;
const int ECHO_PIN = D2;
const int MAX_JSON_SIZE = 256;

Servo myservo;

// Configurable scan parameters
int max_distance = 23200;
int scan_angle = 180;  // allowed: 90, 180, 360
int smoothing_level = 5; // range: 1–10
int sampling_rate = 15;
bool start = false;

float scan_averages[10]; // for smoothing_level max = 10
int current_index = 0;
int valid_entries = 0;
unsigned long last_move_time = 0;
int current_angle = 0;
bool scanning_forward = true;
float scan_total_cm = 0;
int scan_step_count = 0;

String json_buffer = "";
unsigned long lastPrintMillis = 0;

void applyConfig(const char* name, int value) {
  //Parses and sets json config messages
  if (strcmp(name, "max_distance") == 0) {
    max_distance = value;
    Serial.printf("Set max_distance = %d\n", max_distance);
  } else if (strcmp(name, "smoothing_level") == 0) {
    if (value >= 1 && value <= 10) {
      smoothing_level = value;
      Serial.printf("Set smoothing_level = %d\n", smoothing_level);
    } else {
      Serial.println("Error: smoothing_level must be 1-10.");
    }
  } else if (strcmp(name, "scan_angle") == 0) {
    if (value == 90 || value == 180 || value == 360) {
      scan_angle = value;
      Serial.printf("Set scan_angle = %d\n", scan_angle);
    } else {
      Serial.println("Error: scan_angle must be 90, 180, or 360.");
    }
  } else if (strcmp(name, "scan_pace_ms") == 0) {
    sampling_rate = value;
    Serial.printf("Set scan_pace_ms = %d\n", sampling_rate);
  } else {
    Serial.printf("Error: Unknown config parameter name: %s\n", name);
  }
}

void applyInput(const String& mtype) {
  //Parses and sets input messages
  if (mtype == "scanning_ultrasonic.start_scan") {
    start = true;
    Serial.println("Scan started.");
  } else if (mtype == "scanning_ultrasonic.stop_scan") {
    start = false;
    Serial.println("Scan stopped.");
  } else {
    Serial.printf("Unhandled command: %s\n", mtype.c_str());
  }
}

void parseJsonMessage(const String& input) {
  //Produces errors if runs into issues reading JSON
  //Depending on message, passes input to applyConfig or applyInput
  StaticJsonDocument<MAX_JSON_SIZE> doc;
  DeserializationError error = deserializeJson(doc, input);
  if (error) {
    Serial.print("Error: Failed to parse JSON: ");
    Serial.println(error.f_str());
    return;
  }

  if (!doc.containsKey("mtype") || !doc.containsKey("from") || !doc.containsKey("to")) {
    Serial.println("Error: Missing required keys (mtype, from, to).");
    return;
  }

  String mtype = doc["mtype"];
  String from = doc["from"];
  String to = doc["to"];

  if (from != "brain" || to != "scanning_ultrasonic") {
    Serial.println("Error: Invalid from/to fields.");
    return;
  }

  if (mtype =="config") {
    if (!doc.containsKey("name")||!doc.containsKey("value")) {
      Serial.println("Error: Config missing name or value.");
      return;
    }
    const char* name = doc["name"];
    int value = doc["value"];
    applyConfig(name, value);
  } else if (mtype.startsWith("scanning_ultrasonic.")) {
    applyInput(mtype);
  } else {
    Serial.println("Error: Unknown mtype.");
  }
}

void readSerialJson() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (json_buffer.length() > 0) {
        parseJsonMessage(json_buffer);
        json_buffer = "";
      }
    } else {
      json_buffer += c;
    }
  }
}
int ping_cm(){
  // Function to send a pulse from the ultrasonic sensor.
  unsigned long l_t1;
  unsigned long l_t2;
  unsigned long l_pulse_width_us;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Waits several secodns for pulse, if not one, returns -1
  //Indicates error output
  unsigned long timeout = micros();
  while (digitalRead(ECHO_PIN) == 0) {
    if (micros() - timeout > 30000) {return -1;}
  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  l_t1 = micros();}
  while ( digitalRead(ECHO_PIN) == 1);
  l_t2 = micros();
  l_pulse_width_us = l_t2 - l_t1;
  if (l_pulse_width_us > max_distance){
    return -1.0;
  }
  else {
  return l_pulse_width_us;
  }
}
void setup() {
  // Pin setup, and instantiates scan_averages array.
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(D6);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Setup complete. Awaiting config...");

  for (int i = 0; i < 10; i++) scan_averages[i] = 0.0;
}

void loop() {
  readSerialJson();

  if (!start) return;

  unsigned long current_time = millis();
  if (current_time-last_move_time >= sampling_rate) {
    // Move the servo to current_angle
    myservo.write(current_angle);

    // Trigger ultrasonic pulse and measure
    int pulse = ping_cm();
    if (pulse != -1) {
      float cm = pulse / 58.0;
      scan_total_cm += cm;
    } else {
      // Produces error JSON if ping_cm returns -1, indicating an error.
      StaticJsonDocument<128> errDoc;
      errDoc["mtype"] = "scanning_ultrasonic.distance_error";
      errDoc["from"] = "ultra_sonic_sensor";
      errDoc["to"] = "*";
      errDoc["message"] = "-1";
      serializeJson(errDoc, Serial);
      Serial.println();
      //Just to stop error from spamming in case of hardware issue.
      delay(1000);
    }

    scan_step_count++;

    // Sweep logic
    // Continuously increments or decrements current angle, based on "scanning_forward" variable.
    // Switches direction at reaching scan_angle or 0.
    if (scanning_forward) {
      current_angle++;
      if (current_angle >= scan_angle) {
        scanning_forward = false;
        current_angle = scan_angle;
      }
    } else {
      current_angle--;
      if (current_angle <= 0) {
        // Code to produce moving average of last x sweeps
        // Calculates scan_avg from the average of a sweep
        // Adds the result of a sweep into the scan_averages array.
        // Averages the scan_averages array, and outputs it as JSON.
        float scan_avg = scan_step_count > 0 ? scan_total_cm / scan_step_count : 0;

        scan_averages[current_index] = scan_avg;
        current_index = (current_index + 1) % smoothing_level;
        if (valid_entries < smoothing_level) valid_entries++;

        float smoothed = 0;
        for (int i = 0; i < valid_entries; i++) {
          smoothed += scan_averages[i];
        }
        smoothed /= valid_entries;
        StaticJsonDocument<128> doc;
        doc["mtype"] = "scanning_ultrasonicstatus";
        doc["from"] = "ultra_sonic_sensor";
        doc["to"] = "*";
        doc["distance_cm"] = smoothed;
        serializeJson(doc, Serial);
        Serial.println();

        Serial.print("Smoothed Distance: ");
        Serial.print(smoothed);
        Serial.println(" cm");

        // Reset for next sweep
        current_angle = 0;
        scanning_forward = true;
        scan_total_cm = 0;
        scan_step_count = 0;
      }
    }

    last_move_time = current_time;
  }
}