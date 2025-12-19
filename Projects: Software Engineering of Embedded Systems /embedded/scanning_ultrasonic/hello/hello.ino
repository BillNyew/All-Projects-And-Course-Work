//Largely a fusion of labs 2 and 3. 
//Servo is functioning correctly, ultrasonic is having issues due to hardware.
//No syntax errors in Arduino IDE

#include <ESP32Servo.h>

const int TRIG_PIN = D2;
const int ECHO_PIN = D3;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(D6);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(115200);
  delay(1000);
  Serial.println("Test Setup");
}

int ping_cm(){
  unsigned long l_t1;
  unsigned long l_t2;
  unsigned long l_pulse_width_us;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  Serial.println("Test Function");
  // Waits several secodns for pulse, if not one, returns -1
  //Currently gets stuck here; this indicates error output. 
  unsigned long timeout = micros();
  while (digitalRead(ECHO_PIN) == 0) {
    if (micros() - timeout > 30000) {return -1;}
  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  l_t1 = micros();}
  while ( digitalRead(ECHO_PIN) == 1);
  l_t2 = micros();
  //Test that code arrived here
  Serial.println("Test Function 2");
  l_pulse_width_us = l_t2 - l_t1;
  if (l_pulse_width_us > MAX_DIST){
    return -1.0;
  }
  else {
  return l_pulse_width_us;
  }
}

void loop() {
  Serial.println("Test Loop");
  unsigned long pulse_width_us;
  float cm;
  
  pulse_width_us = ping_cm();
  Serial.println("Test CM");
  // Calculate distance in centimeters. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width_us / 58.0;
  
  // Print out results
  if (cm<0) {
    Serial.println("Out of range");
  } else {
    Serial.print(cm);
    Serial.print(" cm \t");
  }

  //Servo correctly swivels 180-0
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  //Add in depending on needed speed
  //delay(60);
}