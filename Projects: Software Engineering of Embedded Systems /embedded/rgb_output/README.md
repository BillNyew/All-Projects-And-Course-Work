# RGB Output Module

An RGB output module for the security system to allow employees to configure and trigger two RGB LEDs as a bright flashing deterrent on unauthorized vault-access attempts, with adjustable brightness, flash rate, and color—and with clear status reporting.

## Table of Contents:
- Configuration Parameters
- Input Messages
- Output Messages
- Hardware Connections
- Software Design
- User Story

# Configuration Parameters

The rgb_output module accepts the following configuration parameters via JSON config messages:

- Parameter Type Description
- Brightness percentage from 1-100 (for flashing only 90 at max, otherwise 100 makes the light stay on)
- Flash rate int Flash frequency in Hertz (1–10)
- light_color value, each 0–255 used in light_red, light_green, or light_blue commands as following

# Messages:
## Config:
Brightness:
<pre>{"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"brightness", "value":"80"}</pre>
Flash Frequency:
<pre>{"mtype":"config", "from":"*", "to":"rgb_output_module_id", "name":"flash_rate", "value":"5"}</pre>
Color Changing:
<pre>{"mtype":"config", "from":"*", "to":"rgb_output_module_id", "name":"light_red", "value":"255"}</pre>
<pre>{"mtype":"config", "from":"*", "to":"rgb_output_module_id", "name":"light_green", "value":"255"}</pre>
<pre>{"mtype":"config", "from":"*", "to":"rgb_output_module_id", "name":"light_blue", "value":"255"}</pre>

## Input Messages:
Start Flashing:
<pre>{"mtype":"start", "from":"*", "to":"rgb_output_module_id"}</pre>
Stop Flashing:
<pre>{"mtype": "stop", "from":"*", "to":"rgb_output_module_id"}</pre>
Status:
<pre>{ "mtype": "status", "from": "*", "to": "rgb_output_module_id" }</pre>

## Output Messages:
Flashing Started:
<pre>{"mtype":"started", "from":"rgb_output_module_id", "to":"*", "message":"Flashing started"}</pre>

Flashing Stopped:
<pre>{ "mtype":"stopped", "from":"rgb_output_module_id", "to":"*", "message":"Flashing stopped"}</pre>

Status:
<pre>{"mtype":"status", "from":"rgb_output_module_id", "to": "*", "message":"Brightness: XXX, Flashrate: XXX, Colors: XX, XX, XX"}</pre>

## Error messages: 
- If Json is improperly formatted:
<pre>{"mtype":".error", "from":"rgb_output_module_id", "to":"*", "message":"IncompleteInput"}</pre>
- If Json doesn't have rgb_output_module_id in the "to" field:
<pre>{"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"This message was not meant for me"}</pre>
- If Json has brightness set to something lower than 0 or higher than 100:
<pre>{"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Brightness value not recognized"}</pre>
- If Json has an invalid mtype:
<pre>{"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Type not recognized"}</pre>
- If Json has invalid flashrate:
<pre>{"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Flash rate not recognized"}</pre>

# Hardware Connections
Components:
- 2 RGB LEDs
- Microcontroller with 6 PWM-capable pins
- 1 connection cable

# Software Design
Initialization:
1. Configure PWM pins as outputs.
2. Apply defaults: brightness = 100%, flash_rate = 2Hz, light_color = 255,0,0

Main Loop:
1. Make time checks so we can make pulse width modulation and flash rate
2. Check for serial input
3. Deserialize input into a doc to parse the information
4. Store values from serial input or throw error if input is incorrect
5. Check if the message is for us
6. Check the type of message
- Handle the input based on the name and value fields
7. Throw an error if no type is found
8. Statements for if start command has been called
9. Check if the light should flash on or off based on frequency
10. PWM for the lights
11. Reset time and change flashing cycle variable
12. Turn off the light if stop command gets called

# User Story

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/6


 rgb_output Module Documentation

 Overview

The rgb_output module controls two RGB LEDs to create a bright flashing deterrent for unauthorized vault access attempts.
It calibrates brightness, flash rate, and color based on environmental needs, responds to commands (start/stop flashing), and reports operation status and errors.

## Hardware Section (Nick Pollak):
### Hardware Description:
- I have two RGB lights with 4 connection pins each
- The vcc pin gets plugged into a positive rail which is powered by the XIAOesp32c board
- The rest of the R, G, B pins get plugged into digital output pins on the breadboard
- The RGB lights will act independantly and the pins must recieve independant input for the color to change based on the value to each pin.

### Test Connections:
- For my first RGB I used D9 for red, D8 for green, and D7 for blue
- For my second RGB I used D4 for red, D5 for green, and D6 for blue
- The vcc pin on both gets plugged into the rail on the right hand side which is powered by the 3.3v port with a cable

### Test Description:
- I set up a test of the lights so they blink with a 1 second delay of various colors (White, Red, Green, Blue)
- I also put in some serialization and JsonDocuments, but they currently serve no purpose

### Pit Falls:
- Instead of using an int which I'd have to check from being 0 to 255 I instead used an unsigned char which acts similar to a byte
- Thus the values can only span from 0 to 255 based on the data type.
- Deserializing is slow sometimes still for me which is an issue I had in the past, I'll try to make changes to previously used code to make it faster.

As a firmware developer, I want an rgb_output module to control two RGB LEDs so that unauthorized vault-access attempts trigger a bright flashing deterrent, with adjustable brightness, flash rate, and color—and with clear status reporting.

# Test Cases:

### Configuration Tests:

All config messages do not return anything, however they do alter global variables which is reflected by sending the status input message. These all require no prior set up and can be run at any time to change their values.

1. T-Config-01

The first config message is for changing the brightness which takes a value from 0 to 100 and sets the brightness to that level. This should dim or brighten the light depending on the value requested.

Config input: ``` {"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"brightness", "value":"50"} ```

2. T-Config-02

The second config message is for changing the flash rate, or the times per second that the lights flash on an off. It takes values from 1 to 10 and adjusts the flashing to that rate. This will cause flashing to increase or decrease depending on how many times per second is requested.

Config input: ``` {"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"flash_rate", "value":"6"} ```

3. T-Config-03

The third config message is for changing the light color, which is possible for all colors using the same naming scheme as shown below. This will set the variables for red, green, and blue at request for each color. However, making the colors low values will cause dimming due to the nature of the hardware. The colors' brightness are still adjustable using the brightness message, but the maximum is lower due to the values.

Config input: ``` {"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"light_red", "value":"255"} ```

Config input: ``` {"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"light_green", "value":"255"} ```

Config input: ``` {"mtype":"config", "from": "*", "to":"rgb_output_module_id", "name":"light_blue", "value":"255"} ```

### Input Message Tests:
1. T-Input-01 

This input message is to start flashing the lights. This message is met with an instant response that your request has been recieved and the lights are starting. There are initial values hard coded in so this will run from the beginning without issue. However, you can still configure the lights to different colors, brightness, and flash rate before running to see different results.

Input Message: ``` {"mtype":"start", "from": "*", "to":"rgb_output_module_id"} ```

Output Message: ``` {"mtype":"started","from":"rgb_ouptput_module_id","to":"*","message":"Started Flashing"} ```

2. T-Input-02

This input message is to stop the flashing of the lights and turn them off. The message will be met with an instant response that the message has been recieved and the lights are stopping flashing. 

Input Message: ``` {"mtype":"stop", "from": "*", "to":"rgb_output_module_id"} ```

Output Message: ``` {"mtype":"stopped","from":"rgb_ouptput_module_id","to":"*","message":"Stopped Flashing"} ```

3. T-Input-03

This input message is to get a status report on the system of what the current values of all variables are. When run it will output the values of the brightness, flash rate, and all three color values. This can be run at anytime and when lights are on or off. This can be helpful as a diagnostic check or debugging for errors.

Input Message: ``` {"mtype":"status", "from": "*", "to":"rgb_output_module_id"} ```

Output Message: ``` {"mtype":"status","from":"rgb_ouptput_module_id","to":"*","message":"Brightness: 90.00 Flash Rate: 2.00 Colors: 255, 0, 0"} ```

### Error Handling Tests:
1. T-Error-01

This error test handles malformed json messages, so if it does not have values assigned to a key, missing parenthesis or colons, quotations are incorrect, this will throw an invalid input message. This is to ensure the messages are in the proper format to be parsed by the code and extract values neccessary. I left off the parenthesis in the first example which caused an error and I did not fill a value in the second. Both are met with the same error message.

Error with Json Format:
``` {"mtype":"start", "to":"rgb_output_module_id" ```

Error with Json Format:
``` {"mtype":"start", "to":} ```

Response: ``` {"mtype":"error","from":"rgb_output_module_id","to":"*","message":"IncompleteInput"} ```

2. T-Error-02

This error message is for invalid mtypes. The valid types are as follows: config, start, stop, and status. All other types fail and throw this error. As seen in the example, I only had conf as the mtype and thus received the error message that the type is not recognized.

Error with message type:
``` {"mtype":"conf","from":"*","to":"rgb_output_module_id","name":"light_blue","value":"266"} ```

Response: ``` {"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Type not recognized"} ```

3. T-Error-03

This error message is for when the "to" field is incorrect, which means that the message was not meant for us or misspelled. The only valid way to send commands to the rgb lights is using "rgb_output_module_id" in the "to" field. This is crucial to input being accepted. Without it we get the error that the message was not meant for it and thus no further changes will be made.

Error with who message is for:
``` {"mtype":"config","from":"*","to":"NotCorrect","name":"light_blue","value":"266"} ```

Response:
``` {"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"This message was not meant for me"} ```

4. T-Error-04

This error is with the brightness value being too high or too low. If everything is correct, but the brightness value isn't between 0 and 100 (inclusive) we will recieve an error. By putting in 8000 as in the example the error is thrown and the brightness is not changed. It tells us that the brightness value is not recognized and the level of brightness remains the same.

Error with Brightness value:
``` {"mtype":"config","from":"*","to":"rgb_output_module_id","name":"brightness","value":"8000"} ```

Response:
``` {"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Brightness value not recognized"} ```

One note about the brightness, if the value is over 90 it will just stay on and not flash. So I've set the max to 90 even when inputting 91-100 for the brightness level.

5. T-Error-05

This error is for an invalid flash rate value. The flash rate being how often the light blinks in one second, only accepts values from 1 to 10 so 8000 as in the example throws an error and will not update. 

Error with flash rate value:
``` {"mtype":"config","from":"*","to":"rgb_output_module_id","name":"flash_rate","value":"8000"} ```

Response:
``` {"mtype":"error","from":"rgb_ouptput_module_id","to":"*","message":"Flash rate not recognized"} ```

6. T-Error-06

This error is not technically a response to an error. If values are input to the light color message which are too high they are moded by 256 to handle out of bounds values. If the value is too low, such as negatives, they are reset to 0. This is because I use a char to store the values which are only capable of storing values from 0-255 as they are only having 8 bits to store values.

When given values that are not 0-255 for color:

Ex: ```{"mtype":"config","from":"*","to":"rgb_output_module_id","name":"light_blue","value":"2550"}```

The program knows to mod by 256 so the equivalent of 2550 mod 256 = 246. So when I run a status call I recieve:

```{"mtype":"status","from":"rgb_ouptput_module_id","to":"*","message":"Brightness: 90.00 Flash Rate: 2.00 Colors: 255, 0, 246"}```

As expected.
