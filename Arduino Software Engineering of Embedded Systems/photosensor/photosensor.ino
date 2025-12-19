// === Constants ===
const int SENSOR = D0;        // Analog input from photoresistor
const int LED_PIN = D7;       // Output pin for the LED
const int THRESHOLD = 800;    // Adjust based on your observations

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(SENSOR, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Turn LED ON by default
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  int sum = 0;

  // Take 10 quick samples
  for (int i = 0; i < 10; i++) {
  sum += analogRead(SENSOR);
  }

  int avg = sum / 10; // Calculate average reading
  
  // Print to Serial Monitor
  Serial.print("Avg Sensor Value: ");
  Serial.println(avg);

  // Logic based on threshold
  if (avg > THRESHOLD) {
    Serial.println("Triggered");
    digitalWrite(LED_PIN, LOW);   // Too much light → turn LED off
  } else {
    digitalWrite(LED_PIN, HIGH);  // Dark → turn LED on
  }

  delay(500); // 2 Hz loop
}
