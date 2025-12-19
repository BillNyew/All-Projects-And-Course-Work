# Door Sensor

## User Story

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/14


### Configuration Parameters
Must process JSON messages with the configuration parameters such as: <br>
- ```{mtype:"config", from:"brain", to:"door_sensor_unique_id", name:"parameter-name", value:"parameter-value"}```<br>
- ``` int polling_rate_hz``` represents how often digitalRead() is called.<br>
- ``` int door_open_threshold``` represents many consecutive "open" readings of the sensor is considered an open door. <br>
- ```int broadcast_rate_hz``` how often to broadcast the state of the sensor. <br>

### Input messages 
Supports JSON messages such as:
  
- ```{"mtype": "<door-sensor>.start_alarm","from": "..","to": "door_sensor_unique_id"}```
- ```{"mtype": "<door-sensor>.stop","from": "..","to": "door_sensor_unique_id"}```
-  ```{"mtype": "<door-sensor>.start_continuous","from": "..","to": "door_sensor_unique_id"}```



### Output messages 
Should broadcast JSON message in the following format: <br>
- ```{mtype:"door_state", from:"door_sensor_unique_id", to:"*", name:"door-sensor-state" value:"is_door_open"}```<br>
Where ```is_door_open``` is a boolean.<br>
- ```{mtype: "debug", from: "door_sensor_unique_id", to: "*", message: "debug message no newlines."}```<br>
The debug message should give the current state of the sensor.<br>
- ```{mtype: "error", from: "door_sensor_unique_id", to: "*", message: "error message no newlines."}```<br>
If there is a huge variation in sensor readings indicating a disconnection between esp32 & reed switch sensor, output an error.

### Hardware Connections
A reed switch is a type of line switch component that realizes control by magnetic signals. It induces by a magnet. The “switch” here means dry reed pipe, which is a kind of contact passive electronic switch component with the advantage of simple structure, small size, and easy to control. When a magnetic substance approaches, the switch senses the magnetic force and is electrified; thus, the module outputs a low level. When there is not a magnet approach, the module is de-energized and will output high. The induction distance between the reed >switch and magnet should be less than 1.5cm; otherwise, the module won't be sufficiently sensitive to the magnet field and give no response. 
    
- Power Requirements: 3.3-5V, which will be supplied by the ESP32, assuming it's powered through its' USB-C port
- Output Type: digital 1-bit output, when a magnet approaches it will output HIGH, otherwise it outputs LOW
Connection: 3 pin (VCC, GND, SIG) - SIG is the digital output 
- Hardware Hookup Instructions: connect 5V and GND pins of the ESP32C3 to the power and ground rails on the breadboard. Connect the VCC and GND pins of the reed switch module to their respective rails on the breadboard. Connect the SIG pin to pin D7 on the ESP32.

- Refer to door_sensor_HW_diagram.png in the assets subfolder for diagram.

    Hello.ino Program:
    In the program I attached the vcc port to the 3v3 port for energy, as well as the ground pin of the ESP32. Then D6 was used as the digital input pin from the Reed sensor to the ESP32. The hello.ino program setup function begins the serial at a baud rate of 115200 and assigns the D6 pin as input. Then the loop simply reads the state of the sensor input (Low when magnet is close to the sensor) then it prints the state of the sensor before delaying for 500ms.
    Refer to reed_sensor_hardware_connections.png for the photo of the hardware setup.

Software Design:
    After setting up the input pin for the Reed Switch Module, the system should wait for a JSON message of mtype: "<door-sensor>.start". When it receives that message, it should call digitalRead() based on polling_rate_hz variable. It should constantly read JSON messages and process messages that are to:"door_sensor_unique_id". Based on what the message is, it should change configuration parameters (polling rate, door open threshold & broadcast rate) or a JSON with mtype: "<door-sensor>.stop" to signal it to stop reading from the sensor. It should regularly output a JSON message (at whatever broadcast_rate_hz) indicating whether the door is open or not. 

Refer to door_sensor_UML png.

### Tests
The following are test JSON strings to be pasted into Serial

{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.stop","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.start_continuous","from":"brain","to":"door_sensor1"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"polling_rate_hz","value":5}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"door_open_threshold","value":3}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"broadcast_rate_hz","value":2}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"other_sensor"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"polling_rate_hz","value":0}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"door_open_threshold","value":20}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"broadcast_rate_hz","value":10}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1","extra":"unexpected"}
{"mtype":"config","from":"brain","to":"door_sensor1","name":"unknown_param","value":123}
{"mtype":"door_sensor1.start_alarm","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.stop","from":"brain","to":"door_sensor1"}
{"mtype":"door_sensor1.start_continuous","from":"brain","to":"door_sensor1"}


