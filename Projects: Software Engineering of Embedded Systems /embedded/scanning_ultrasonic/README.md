# Scanning Ultrasonic Sensor
Configuration Parameters:
+ { "mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "max_distance", "value": (some positive integer) }
Max valid range in centimeters. Beyond this triggers an error.
+ { "mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "smoothing_level", "value": (int; 1-10) }
Level of data smoothing; higher = more smoothing
+ { "mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_pace_ms", "value": int (milliseconds) }
Time between scan steps.
+ { "mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_angle", "value":(90, 180, 360) }
Sweep angle range.

Input Messages / Commands
+ { "mtype": "scanning_ultrasonic.start_scan", "from": "brain", "to": "scanning_ultrasonic" }
Begin scanning loop
+ { "mtype": "scanning_ultrasonic.stop_scan", "from": "brain", "to": "scanning_ultrasonic" }
Stop scanning loop
+ { "mtype": "scanning_ultrasonic.set_sampling_rate", "from": "brain", "to": "scanning_ultrasonic" }
Set time between pings
+ { "mtype": "scanning_ultrasonic.set_smoothing", "from": "brain", "to": "scanning_ultrasonic" }
Set level of smoothing

Output Messages / Status Updates

+ { "mtype": "scanning_ultrasonicstatus", "from": "ultra_sonic_sensor", "to": "*", "distance_cm": (whatever max distance set}

+ { "mtype": "scanning_ultrasonic.distance_error", "from": "ultra_sonic_sensor", "to": "*", "message": "-1"}

+ { "mtype": "scanning_ultrasonic.non_functioning_error", "from": "ultra_sonic_sensor", "to": "*", "message": "not scanning anything

Hardware Design
This hardware setup includes an Arduino Uno, an ultrasonic sensor (HC-SR04), a servo motor, and a breadboard for power distribution. The ultrasonic sensor is physically mounted on the servo motor to rotate and perform scans across a range of angles. The Trig and Echo pins of the ultrasonic sensor are connected to digital pins on the Arduino to send and receive ultrasonic pulses. The servo motor is connected to another digital PWM pin on the Arduino, allowing it to rotate to specific angles as directed by software. The breadboard distributes 5V power and ground to both the servo and the ultrasonic sensor from the Arduino. 

Ground connects to Gnd on the ultrasonic and brown on the servo. 5V connects to Vcc on the ultrasonic and red on the servo. Ultrasonic echo pin connects to D2 analog pin, and Trig connects to D1. Servo connects to D7.

Hardware setup follows diagram below, images attached. All devices function as intended.

![Daring Maimu-Hango](https://github.com/user-attachments/assets/9f9ad9f8-21d6-4391-af08-d92dc0092764)

Software Design
The software system is structured around a messaging protocol between a control unit (brain), an intermediate controller (scanning_ultrasonic module), and a hardware sensor (ultrasonic sensor). The brain includes parameters like max_distance, which sets the maximum distance the sensor should consider valid, and smoothing_level, which controls how much the data is filtered to reduce noise (on a scale from 1 to 10). The scan_pace_ms field sets how often scans are performed, while scan_angle determines the physical rotation range of the scan (90, 180, or 360 degrees). The controller also provides methods to start and stop scanning and to update these settings dynamically. The Scanning Ultrasonic Module (Worker) receives these parameters and carries out the scanning logic. It stores the current distance reading in current_distance, the scan status in scan_status, and any error messages in error_message. It also includes methods for adjusting the same parameters as the Brain, along with methods to display errors or status updates. At the lowest level, the Ultrasonic Sensor, which is the hardware interface, controls the sensor through fields like trig_pin and echo_pin to manage the hardware signal lines.

Functions: 
applyConfig() - Takes in JSON message as a string, and modifies the config values according to the message content.
applyInput() - Takes in JSON message as a string, and modifies the global variables, "start", namely, according to input.
parseJsonMessage() - Takes in JSON message as a string, parses the content, and determines which functions to call to handle the information, erroring out if formatting is incorrect.
ping_cm() - convert the time duration of the echo pulse into a distance in centimeters.
setup() - Main setup function
loop() - Main loop function, repeatedly queries for Serial input.

Smoothing was implemented through averaging the results of each completed 90/180/360 degree sweep, then adding those averages to the list, and averaging the last x averages, where x is the smoothing_level. Comprehensive JSON input, output, and config functionality was added, largely allowing the brain to manually start, stop, and set the variables utilized throughout the code.

Known Issues/Todo:
Config seems to be entirely functional and cohesive. Both input and output JSON messages need some expansion, namely, in what actually gets passed back to the brain, and allowing for additional control over the code function with input. Past that, additional test cases still need to be added for more comprehensive testing, particularly for the parseJsonInput() function.

Currently, the only input messages supported are start/stop. Scanning pace and smoothing level can be set with config, but not through the input messages. Can be added if necessary.

![Specification_Design_and_Documentation drawio](https://github.com/user-attachments/assets/4baef071-d9dc-42b8-9cad-7d861d14858d)

## User Story

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/5

# Test Cases
## Configuration Tests
Correct Demo Messages:

+ T-CONFIG-01 - Set the max distance of the ultrasonic scanner.
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "max_distance", "value": 20000}
    + Intended Output: Set max_distance = 20000
+ T-CONFIG-02 - Set the level of smoothing being done.
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "smoothing_level", "value": 5}
    + Intended Output: Set smoothing_level = 5
+ T-CONFIG-03 -  Set the scanning angle (90, 180, or 360)
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_angle", "value": 90}
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_angle", "value": 180}
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_angle", "value": 360}
    + Intended Outputs: Set scan_angle = 90/180/360
+ T-CONFIG-04 - Set the sampling rate of the ultrasonic sensor. 
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_pace_ms", "value": 15}
    + Intended Output: Set scan_pace_ms = 15

Invalid Values Messages:
+ T-CONFIG-05 - Attempt to input smoothing outside of the 1-10 range.
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "smoothing_level", "value": 11}
    + Intended Output: Error: smoothing_level must be 1-10.
+ T-CONFIG-06 -  Attempt to input scan angle outside of 90, 180, or 360
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "scan_angle", "value": 50}
    + Intended Outputs: Error: scan_angle must be 90, 180, or 360.
+ T-CONFIG-07 - Attempt to alter parameter outside of recognized config messages
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic", "name": "error", "value": 99}
    + Intended Output: Error: Unknown config parameter name: error

## Input Message Tests
+ T-INPUT-01 - Start scanning and moving the servo
    + Input: {"mtype": "scanning_ultrasonic.start_scan", "from": "brain", "to": "scanning_ultrasonic"}
    + Intended Output: Scan Started
+ T-INPUT-02 - Stop scanning
    + Input: {"mtype": "scanning_ultrasonic.stop_scan", "from": "brain", "to": "scanning_ultrasonic"}
    + Intended Output: Scan Stopped
+ T-INPUT-03 - Command not recognized.
    + Input: {"mtype": "scanning_ultrasonic.errortest", "from": "brain", "to": "scanning_ultrasonic"}
    + Intended Output: Unhandled command: scanning_ultrasonic.errortest
 
## Error Handling Tests
+ T-ERROR-01 - Outputs error if the ultrasonic scanner isn't scanner, for whatever reason.
    + Input: Physically disconnect ultrasonic sensor
    + Intended Output: {"mtype":"scanning_ultrasonic.distance_error","from":"ultra_sonic_sensor","to":"*","message":"-1"}
+ T-ERROR-02
    + Input: {"message":"-1"}
    + Intended Output: Error: Missing required keys (mtype, from, to)
+ T-ERROR-03
    + Input: {"mtype":"scanning_ultrasonic.distance_error","from":"incorrect","to":"error","message":"-1"}
    + Intended Output: Error: Invalid from/to fields.
+ T-ERROR-04
    + Input: {"mtype": "config", "from": "brain", "to": "scanning_ultrasonic",: "scan_pace_ms", "value": 15}
    + Intended Output: Error: Config missing name or value.
+ T-ERROR-05
    + Input: "error": "scanning_ultrasonic.start_scan", "from": "brain", "to": "scanning_ultrasonic"}
    + Intended Output: Error: Unknown mtype