# Weight Sensor

    Note: some of the latex does not render propely on github.com so it is best to view this in vscode.

## User Story

[https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/1](https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/1)

## Overview of measurements

This module expects all three buttons to be pressed. During configuration a
threashold and sample frequency are set. The buttons are read at the provided sample
frequency rate and when a button is read, it is read 5 times and considered
pressed only if all 5 readings indicate pressed. Then, if the number of presssed
buttons is below the threashold set at configuration, a `weight_sensor.data` 
message is sent via Serial communication indicating the number of pressed buttons.

## Configuration Parameters

### 1. Sample frequency

This config message setup the rate at which the weight sensor measures weight. The assumption here is the `sample_freq` is in `hz`

```json
{
  "mtype": "config",
  "from": "*",
  "to": "weight_sensor1",
  "name": "sample_freq",
  "value": 5
}
```

### 1. Pressed threashold

This config message sets the number of pressed buttons which for which a warning
message should be sent (when the number pressed for a sample is at or below this
threashold). `value` should be between 0 and 2.

```json
{
  "mtype": "config",
  "from": "*",
  "to": "weight_sensor1",
  "name": "pressed_threashold",
  "value": 2
}
```

## Input Messages

### 1. Start

Sends a command to begin sampling weight values.

```json
{
  "mtype": "weight_sensor.start",
  "from": "brain_unique_id",
  "to": "weight_sensor1"
}
```

### 2. Stop

Sends a command to stop sampling weight values.

```json
{
  "mtype": "weight_sensor.stop",
  "from": "brain_unique_id",
  "to": "weight_sensor1"
}
```

## Output Messages

### Broadcast of weight data

When reporting the current number of pressed buttons:

```json
{
  "mtype": "weight_sensor.data",
  "from": "weight_sensor1",
  "to": "*",
  "name": "pressed_count",
  "value": 2
}
```

### Debug Messages

Indicates serial input is being read.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "reading serial message"
}
```

Indicates a message addressed to another module was recieved.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved message intended for other module"
}
```

Indicates a json message was succesffully read.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "successfully read json msg"
}
```

Indicates the module has been successfully configured.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration succeeded: entering IDLE state"
}
```

Indicates a start message has been recieved triggering the measuring state.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "start message recieved: entering MEASURING state"
}
```

Indicates a stop message has been recieved triggering the idle state.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "stop message recieved: entring IDLE state"
}
```

Indicates the module has started and is ready to recieve configuration parameters.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "waiting for configuration"
}
```

Indicates the sample frequency has been configured.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "sample frequency configured"
}
```

Indicates the pressed threashold has been configured.
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "pressed threashold configured"
}
```

### Error Messages
Indicates a config message with an invalid sample freq value was recieved and 
ignored.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration value for sample freq invalid: value"
}
```

Indicates a config message with an invalid pressed threashold value was recieved and 
ignored.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration value for pressed threashold invalid: value"
}
```

Indicates a deserialization error and provides the error detials.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "deserialization() error: errror info"
}
```

Indicates some serial input was recieved which was either empty or missing a 
terminating character.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "invalid message: no terminating character or only terminating character"
}
```

Indicates some required field was missing from a json message.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved json message without essential field (mtype, to, or from)"
}
```

Indicates the provided mtype in a message was unknown.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved message with missing or invalid mtype"
}
```

Indicates the name field was not provided or was not the correct type.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved config message with missing or invalid name"
}
```

Indicates the value field was not provided or was not the correct type.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved config message with missing or invalid value"
}
```

## Hardware Connections

TODO - update hardware diagram

The weight_sensor supports three buttons with pull-down resistors so that each
button reads LOW when unpressed, and high when pressed. All buttons recieve
power from the Arduino, and each is connected to one of its analog pins.

Implementation:

  Hello World:
    The arduinos 5v output is used connected to one of the (+) rails on the
    breadboard and that is used to power each of the buttons. The arduino's ground
    connection is also connected to a (-) rail on the breadboard, and each
    button's pull-down resistor (all 1k OHM resistors) is also connected to the
    same (-) rail as well as the button. Each button is connected to the arduino
    by one of its analog pins: A0, A1, A2 (which are also labled D0, D1, D2 on the arduino). 
    
    The pin connections used by the arduino are A0, A1, and A2, which are used to
    connect the buttons to the arduino so it can read their state (pressed/not
    pressed).

    The test sketch allows the user to press the buttons and see the number of 
    pressed buttons detected by the arduino printed via Serial communication.

## Software Design

# Functionality

The Weight Sensor Module provides continuous monitoring of weight measurements with automated reporting of significant changes. The module operates through a defined state machine that manages the complete lifecycle from initialization to active measurement:

- The system starts in the **Setup** state when powered on
- It transitions to **ReceiveConfig** to get configuration values
- After receiving configuration, it moves to **Calibrate** state
- Once calibration is complete, it enters an **Idle** state
- When a start command is received, it transitions to **Measuring** state
- While measuring, it continuously monitors weight
- When the number of buttons pressed is detected below the configured threashold,
  a `weight_sensor.data` message is sent with the current pressed count
- If a stop command is received while measuring, it returns to **Idle**

### Diagram

TODO - update state diagram
![diagram](statediagram.png)

# Testing

## Configuration Tests
These tests verify correct configuration behavior, to see how error handling is 
verified see the Error Handling Tests.

1) Once the module has been started you should see the following message. Before
   performing any other tests ensure you see this message which indicates the
   module is ready to be configured:
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "waiting for configuration"
}
```
2) Provide the json configuration message to set the pressed threashold (see
   Configuration Parameters section) with a valid value. You shuold see the 
   following debug message:
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "pressed threashold configured",
  "value": 2
}
```
3) Provide the json configuration message (see
   Configuration Parameters section) to verify the pressed threashold can 
   be set via configuration message with a valid value. You shuold see the 
   following debug message:
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "pressed threashold configured",
  "value": 2
}
```
4) Once you have provided valid values for both configuration parameters you
   should see the following mesage:
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration succeeded: entering IDLE state"
}
```

## Input Message Tests

The following tests relate to seeing input related debug messages which are not
considered errors. Theses tests verify general message handling behavior, to
see how error handling is verified see the Error Handling Tests section:

1) Anytime you provide any serial input you should see the following debug message:
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "reading serial message"
}
```
2) Anytime you provide a well formed json message with a known mtype and valid
   values for all fields associated with that mtype which is not addressed to
   this module you should see the following debug message (even if that message 
   does not change functionality in the modules current state):
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved message intended for other module"
}
```
3) Anytime you provide a well formed json message with a known mtype and valid
   values for all fields associated with that mtype which is also addressed to
   this module (i.e., to is `weight_sensor1`) you should see the following
   debug message (even if that message does not change functionality in the modules
   current state):
```json
{
  "mtype": "weight_sensor.debug",
  "from": "weight_sensor1",
  "to": "*",
  "name": "successfully read json msg"
}
```
4) Provide the start message as described in the Input Messages section. If
   this is at any point while the module is in the idle state you should see
   the following message (otherwise you should only see the standard input
   debug messages described above)
``` json
{
"mtype": "weight_sensor.debug",
"from": "weight_sensor1",
"to": "*",
"name": "start message recieved: entering MEASURING state"
}
```
5) Provide the stop message as described in the Input Messages section. If
   this is at any point while the module is in the measuring state you should see
   the following message (otherwise you should only see the standard input
   debug messages described above)
``` json
{
"mtype": "weight_sensor.debug",
"from": "weight_sensor1",
"to": "*",
"name": "stop message recieved: entring IDLE state"
}
```

## Error Handling Tests

### Configuration Errors

1) To verify invalid configuration parameters are correctly rejected provide an
   otherwise valid configuration message to configure either sample frequency
   or pressed threashold, but with an invalid value. You should see the
   following debug messages respectively for each case:
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration value for sample freq invalid: value"
}
```
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "configuration value for pressed threashold invalid: value"
}
```
### Deserialization Errors

1) At any point provide some serial input which cannot be deserialized by
   deserializeJson (non-json input)
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "deserialization() error: errror info"
}
```

2) Provide an empty message with only a '\r' or '\n', or provide any message which
   has neither.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "invalid message: no terminating character or only terminating character"
}
```

3) Provode any json message which does not have mtype, to, or from fields.
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved json message without essential field (mtype, to, or from)"
}
```

4) Provode a json message which has all required fields and an mtype which is
   not known by the module (see message descriptions for valid mtypes).
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved message with missing or invalid mtype"
}
```

5) Provode an otherwise valid json message with config mtype, but provide a name
   which does not describe a known configuration parameter (see message descriptions
   for known configuration parameters).
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved config message with missing or invalid name"
}
```

6) Provode a json message which requires a value (only configuration messages
   require values for this module) and provide a value which cannot be cast to
   the correct type, or do not include a value field (including a value field field
   with a correct type but a dissallowed value will result in a different error
   message).
```json
{
  "mtype": "weight_sensor.error",
  "from": "weight_sensor1",
  "to": "*",
  "name": "recieved config message with missing or invalid value"
}
```
