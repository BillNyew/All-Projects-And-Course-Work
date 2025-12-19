const int PIN = D6;//digital input pin the reed switch is connected to
// The reed switch is a magnetic switch that closes when a magnet is near it.
// When the magnet is removed, the switch opens and the pin goes high.
// This is a simple example to read the state of the reed switch and print it to the serial monitor.
// The reed switch is connected to the pin D6, another side is connected to ground and the vcc pin is connected to 3v3 or 5 volts.

void setup() {
  Serial.begin(115200);
  pinMode(PIN,INPUT);//set up pin
}

void loop() {
  int s_sensor_state = digitalRead(PIN);//read state (low when mmagnet is close, high otherwise)
  Serial.printf("Read: %d\n",s_sensor_state);//print the sensor state
  delay(500);//delay to not overload  with prints
}