// #include "Wire.h"
// #include "TFLI2C.h"
// #include <ESP32Servo.h>

// // I2C sensor and servo objects
// TFLI2C sensor;
// Servo g_servo;

// // Servo control parameters
// int g_servo_pos_deg = 0;      // current angle (degrees)
// int angle_resolution = 5;     // movement step (degrees)
// const int PIN_SERVO = D7;     // servo signal pin

// // Sweep the servo back and forth and print distance readings
// void measuring() {
//   g_servo.write(g_servo_pos_deg);  // move to current position

//   int16_t dist;
//   if (sensor.getData(dist, 0x10)) {  // read from sensor at address 0x10
//     Serial.print("dist: ");
//     Serial.println(dist);
//   }

//   // Reverse direction at the limits (0° and 180°)
//   if (g_servo_pos_deg < 0 || g_servo_pos_deg > 180) {
//     angle_resolution = -angle_resolution;
//   }

//   g_servo_pos_deg += angle_resolution;  // update for next sweep
//   Serial.printf("deg: %d\n", g_servo_pos_deg  );
//   delay(100);  // brief pause
// }

// // Move servo to a specific angle and take several readings
// void measure_deg_specific(int deg) {
//   g_servo.write(deg);  // set target angle

//   for (int i = 0; i < 10; i++) {
//     int16_t dist;
//     if (sensor.getData(dist, 0x10)) {
//       Serial.print("dist: ");
//       Serial.println(dist);
//     }
//   }

//   Serial.printf("deg: %d\n", deg);
// }

// void setup() {
//   Serial.begin(115200);       // start serial for debug
//   g_servo.attach(PIN_SERVO);  // attach servo to its pin
//   Wire.begin();               // init I2C bus
// }

// void loop() {
//   // To test, uncomment one of these:
//   measuring();
//   // measure_deg_specific(50);
// }



#include <ESP32Servo.h> // Include the ESP32 Servo library

// Servo object
Servo g_servo;

// Servo control parameters
const int PIN_SERVO = D7; // servo signal pin (assuming D7 is a valid pin for your ESP32)

void setup() {
  Serial.begin(115200);      // Start serial for debugging
  g_servo.attach(PIN_SERVO); // Attach servo to its pin
  Serial.println("Servo program started.");
}

void loop() {
  // Rotate from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) { // Go from 0 to 180 degrees
    g_servo.write(pos);                     // Tell servo to go to position in variable 'pos'
    Serial.print("Servo position: ");
    Serial.println(pos);
    delay(15);                              // waits 15ms for the servo to reach the position
  }

  delay(1000); // Wait for 1 second at 180 degrees

  // Rotate from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) { // Go from 180 to 0 degrees
    g_servo.write(pos);                     // Tell servo to go to position in variable 'pos'
    Serial.print("Servo position: ");
    Serial.println(pos);
    delay(15);                              // waits 15ms for the servo to reach the position
  }

  delay(1000); // Wait for 1 second at 0 degrees
}
