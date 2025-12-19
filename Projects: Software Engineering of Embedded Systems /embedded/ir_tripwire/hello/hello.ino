const int irSensorPin = D6;     // signal pin from IR receiver
const int ledPin = 10;         // built-in LED for beam status
int lastBeamState = HIGH;      // previous state of the beam (HIGH = clear)
unsigned long lastReportTime = 0;
const unsigned long reportInterval = 1000; // in ms 


void setup() {

  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Serial.println("IR Tripwire Hello-World Initialized");
}

void loop() {
  //helps slow things down
  delay(250);
  int beamState = digitalRead(irSensorPin);  // HIGH = beam clear, LOW = tripped

  Serial.printf("beamState = %d\n", beamState);

  // Report on beam state change
  if (beamState != lastBeamState) {
    lastBeamState = beamState;

    if (beamState == LOW) {
      Serial.println("{ \"mtype\": \"IRBreakBeamSensor3mm.beam_state\", \"state\": \"tripped\" }");
      digitalWrite(ledPin, HIGH);  // turn on LED when tripped
    } else {
      Serial.println("{ \"mtype\": \"IRBreakBeamSensor3mm.beam_state\", \"state\": \"clear\" }");
      digitalWrite(ledPin, LOW);   // turn off LED when beam is clear
    }
  }

  // Periodic reporting
  unsigned long currentTime = millis();
  if (currentTime - lastReportTime >= reportInterval) {
    lastReportTime = currentTime;

    String stateStr = (beamState == LOW) ? "tripped" : "clear";
    Serial.println("{ \"mtype\": \"IRBreakBeamSensor3mm.beam_state\", \"state\": \"" + stateStr + "\" }");
  }
}
