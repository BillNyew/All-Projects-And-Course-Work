const int LED_PIN = D7;
const int BLINK_INTERVAL = 125;  // 4 blinks per second = 125ms per half cycle

bool ledState = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  ledState = !ledState;                 // Toggle LED state
  digitalWrite(LED_PIN, ledState);     // Apply new state to LED
  delay(BLINK_INTERVAL);               // Only one delay call
}
