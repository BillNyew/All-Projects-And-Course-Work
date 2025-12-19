// Sound module testing program. LED will light up if a sound is detected.

// SIG pin on the sound sensor module
const int SOUND_SENSOR_PIN = D7;
// Pin to light up LED when sound is detected
const int LED_PIN = D6;

void setup() {
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Check if a sound has been detected 
  int status = digitalRead(SOUND_SENSOR_PIN);
  // If there was a sound detected, light up the LED
  if (status) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    // Otherwise, leave it off 
    digitalWrite(LED_PIN, LOW);
  }
}
