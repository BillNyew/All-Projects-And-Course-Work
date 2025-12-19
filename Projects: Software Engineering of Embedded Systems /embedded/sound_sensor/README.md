# Sound Sensor
## Configuration Parameters:
How many decibles above the normal volume threshold a given sound must be to warrent a report to the brain
- The 0-300 range is based on the hardware video provided in the user story, testing would need to be done to figure out the exact number that should go into the value
```json
{mtype:"config", from:"does_not_matter", to:"sound_sensor", name:"warning_threshold_decibles", value:"0-300"} 
```

How often the baseline should be sent to the brain (ms)
- This might not need to be included at all depending on what the brain actually requires, the actual number is up to the brain
```json
{mtype:"config", from:"does_not_matter", to:"sound_sensor", name:"baseline_broadcast_rate_ms", value:"some number of milliseconds"}
```

How often the sound sensor reads the volume in the room (ms)
- Anything outside of that range would probably be ineffective at actually finding sounds
```json
{mtype:"config", from:"does_not_matter", to:"sound_sensor", name:"listen_rate_ms",value:"20-100"} 
```

How long to listen for (how many hits to analog sensor in one sample)
- Need to decide how many samples to read in one burst since analog reads very fast, must average this
```json
{mtype:"config", from:"does_not_matter", to:"sound_sensor", name:"listen_time_ms",value:"5-10"} 
```

## Input Messages:
The only input messages the device needs to recieve are activation and deactivation requests. It should choose when it sends information to the brain so it is unecessary for the brain to request information.
```json
{ mtype:"<sound-sensor>.start", from:"...", to:"sound_sensor" }
{ mtype:"<sound-sensor>.stop", from:"...", to:"sound_sensor" }
```

## Output Messages:
The module might want to send baseline sound over regular intervals depending on what exactly the brain wants from the sensor. The sensor will be calculating its own baseline sound in real time so this may not be nesessary
```json
{ mtype:"sensor_output", from:"sound_sensor", to:"*", name:"sound_baseline_decibles", value:"sound baseline in decibles"}
```

This module must send decibel level of sound if the sound is a certain amount above the threshold (to alert the brain of a potential problem)
- alert level may not be necessary but it would be easy to add in case we want to specify different levels of concern the brain should have with the issue
```json
{ mtype:"sensor_output", from:"sound_sensor", to:"*", name:"sound_alert", value:"decibles_above_baseline", alert_level:"low, medium, or high"}
```

This module should send error messages if it gets weird readings (out of logical bounds, too low/high), can't activate
```json
{ mtype: "error", from: "sound_sensor", to: "*", message: "error: could not activate sound_sensor"}
{ mtype: "error", from: "sound_sensor", to: "*", message: "error: reading out of bounds (too low)"}
{ mtype: "error", from: "sound_sensor", to: "*", message: "error: reading out of bounds (too high)"}
```


## Hardware Connections:
The sound sensor itself will need a power connection, a ground connection, and an output connection to allow an Arduino chip to read the sound that the sensor picks up. It needs 3 to 5 volts of power. The connection to the chip must be on an analog pin because it will be reading variable values representing decibles. It will likely connect to the chip through a bread board of some sort. It is fairly simple as far as hardware goes.
- See the Image included in the assets folder. The microphone represents the sound sensor. It is at the top of the diagram. The chip represents the same Arduino chips we have been using until now in class. The microphone connects to the 5 volt pin, the ground pin, and the A0 analog pin.

## Software Design:
This module is going to be reading sounds at regular intervals. It will calculate a baseline sound in real time. It will do this at certain intervals and listen for a certain amount of time during those intervals depending on what configuration values it recieves. This will allow it to be reactive to subtle changes in environmental sound levels without triggering a lockdown. It will keep track of an average of the last 200 to 1000 sound level readings (depending on what provides a more accurate reading when testing). It might send this baseline to the brain if the brain requires it. It definitely will send alerts if any sounds are above the average calculated threshold by the configured amount. It must be able to accept config messages and change the comparison values. It must also accept the on and off commands as input messages. Note that the calculation to determine if a sound is significantly above the threshold should happen before the averaage is recalculated because we do not want sounds that cause alerts to be calculated into the average.
- See the attached UML diagram in the assets folder for a visual representation of this module's running loop

## User Story

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/12  

### Example Sketch Description  

If a sound is detected, the LED will turn on. Otherwise, it will remain off.  
The hardware components are the ESP32-C3 microcontroller, an LED, a 10kΩ resistor, and the sound sensor module.  

## Hardware

### LED

Connect 10kΩ resistor from microcontroller pin D6 to LED cathode  
Connect LED anode to GND  

### Sound Sensor

Connect red wire on sound sensor module to 5V  
Connect black wire on sound sensor module to GND  
Connect SIG pin to microcontroller pin D7  

### Challenges / Pitfalls / Issues

The sensor is very sensitive, and may turn on the LED with the slightest amount of sound in the room.  
It is also inaccurate at times, and may suddenly turn on or for seemingly no reason.    

### Test Cases 
See tests.txt for test cases
