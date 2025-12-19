# Lock Actuator

## User Story
As a Vault Actuator I want to respond to a command so that I can lock the trophy enclosure (display case?) to restrict access to a vault

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/9

## Configuration Messages/Parameters:
"some_angle" will be a numeric value (likely an integer) and this may only need
configuration depending on hardware in which case it could be hardcoded
This parameter represents how far the motor must move to lock
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "name":"degree_to_lock", "value":"some_angle" }
```
These were the original config parameters, they were redundant so I combined them into one
for the final implementation.
```json
{ "mtype":"config", "from":"does_not_matter", "to":"my_unique_id", 
  "name":"locked_position", "value":"some_angle" }
{ "mtype":"config", "from":"does_not_matter", "to":"my_unique_id", 
"name":"unlocked_position", "value":"some_angle" }
```

## Output/Debug/Error Messages:
```json
{ "mtype":"error", "from": "my_unique_id", "to":"*", "message":"failed to lock"}
{ "mtype":"lock_actuator1.state", "from": "my_unique_id", "to":"*", "message":"the current state is current_state"}
{ "mtype":"lock_actuator1.state_change", "from": "my_unique_id", "to":"*", "message":"state changed from prev_state to new_state"}
```

## Input Messages:
```json
{ "mtype":"lock_actuator1.lock", "from":"sender_unique_id", "to":"lock_actuator1" }
{ "mtype":"lock_actuator1.unlock", "from":"sender_unique_id", "to":"lock_actuator1" }
{ "mtype":"lock_actuator1.request_state", "from":"sender_unique_id", "to":"lock_actuator1" }
```

## Hardare Connections:
- power will come from a standard wall outlet connection directly into the motor controller
- the motor controller will connect to two digital output pins from the arduino chip, these are the DIR+ and PUL+. 
- the ENA-, ENA+, DIR-, and PUL- will all need to connect to ground on the arduino chip
- the motor controller Hight Voltage channels should be connected to the motor
- for the test, I connected DIR+ to pin D5 and PUL+ to pin D6, but any two different digital output pins would work
- IMPORTANT UPDATE: pin D6 does not work for this purpose as it is used on startup and effects the motor when the program is being downloaded. I switched DIR+ to pin D4 and PUL+ to pin D5
- the test sketch simply has the motor move in one direction at a constant speed, there are const variables that can be changed before compilation that will change the speed and direction
- the main challenges I faced while coding this mostly revolved around controlling the timing of the motor moving. It was a bit challenging to implement the state toggle since there had to be a delay in between every state change, but it was not too difficult to figure out.

## Software Design:
- needs to be able to set the position which is considered locked according to configuration messages
- needs to respond to commands which lock or unlock by performing the associated action, and should send a message with information about the changed state when done
- needs to take config parameter to change degree necessary to be considered locked
- if locking or unlocking fails, an error message should be sent indicating the failure

## limitations of current implementation:
- cannot set a specific coordinate or radian to rotate motor towards, it only rotates from where it starts when activated

## Test Cases:
T-CONFIG-01:
- Tests normal behavior of setting rotation
- json input for test, output should be nothing:
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "name":"degree_to_lock", "value":"360" }
```
- lock correctly turns 360 degrees when told to lock after this command is sent
T-CONFIG-02:
- Tests that lock position cannot be changed while locked
- json input for test, output should be error:
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "name":"degree_to_lock", "value":"180" }
```
- Output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"Error, lock_actuator1 config name does not match accepted name or device is locked"}
```
- correctly outputs an error
T-CONFIG-03:
- Tests that changing the lock position by an invalid value gives an error
- json input for test, output should be error:
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "name":"degree_to_lock", "value":"cat" }
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"Invalid Degree entered"}
```
- correctly outputs an error
T-CONFIG-04:
- tests to make sure config messages to other modules are ignored
- json input for test, output should be nothing:
```json
{ "mtype":"config", "from":"does_not_matter", "to":"not_the_lock_actuator", 
  "name":"degree_to_lock", "value":"cat" }
```
- testing it shows that not output is created, it is ignored

T-INPUT-01:
- tests that lock is handled correctly
- when system is unlocked, lock should rotate it by specified degree in config
- json input for test: output should be lock_actuator1.state_change with new state
```json
{ "mtype":"lock_actuator1.lock", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output:
```json
{"mtype":"lock_actuator1.state_change","from":"lock_actuator1","to":"*","message":"State of lock changed, locked = 1"}
```
- correctly moves the motor the right amount and outputs the message it is supposed to
T-INPUT-02:
- tests to make sure that inputing lock while already locked produces error and does not move motor
- json input for test: output should be an error message:
```json
{"mtype":"lock_actuator1.state_change","from":"lock_actuator1","to":"*","message":"State of lock changed, locked = 1"}
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"lock_actuator1 is already locked"}
```
- correctly gives error message and does not move motor
T-INPUT-03:
- tests that unlock is handled correctly
- should unlock when the command is given and the device is in the locked state
- json input for test: output should be state change message:
```json
{ "mtype":"lock_actuator1.unlock", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output:
```json
{"mtype":"lock_actuator1.state_change","from":"lock_actuator1","to":"*","message":"State of lock changed, locked = 0"}
```
- correctly outputs new state and moves motor by right amount
T-INPUT-04:
- tests to make sure unlock does not work if already unlocked
- input for test: output should be error and motor should not move:
```json
{ "mtype":"lock_actuator1.unlock", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"lock_actuator1 is already unlocked"}
```
- correctly outputs an error and does not move
T-INPUT-05:
- tests to see if the request state input works
- should output whether the system is locked or unlocked
- json input for test: should return state message, testing from an unlocked state:
```json
{ "mtype":"lock_actuator1.request_state", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output
```json
{"mtype":"lock_actuator1.state","from":"lock_actuator1","to":"*","message":"State of lock, locked = 0"}
```
- correctly outputs the state of the lock
T-INPUT-06:
- tests to see if the request state input works
- should output whether the system is locked or unlocked
- json input for test: should return state message, testing from a locked state:
```json
{ "mtype":"lock_actuator1.request_state", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output
```json
{"mtype":"lock_actuator1.state","from":"lock_actuator1","to":"*","message":"State of lock, locked = 1"}
```
- correctly outputs the state of the lock
T-INPUT-07
- tests to make sure request state command is not executed if it is not sent to lock_actuator1
- input for test: should output nothing:
```json
{ "mtype":"lock_actuator1.request_state", "from":"sender_unique_id", "to":"lock" }
```
- output is nothing, works as intended

T-ERROR-01
- tests to make sure giving a non-viable mtype returns an error
- input for test: output should be error:
```json
{ "mtype":"say_hello", "from":"sender_unique_id", "to":"lock_actuator1" }
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"error, no mtype command matches given mtype"}
```
- correctly outputs that the mtype was incorrect
T-ERROR-02
- tests to make sure mtype is actually present in input
- input for test: output should be error:
```json
{ "mnothing":"lock-actuator1.lock", "from":"sender_unique_id", "to":"lock_actuator1" }
```
-output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"Error, mtype is missing in command"}
```
- output correctly states that mtype is missing
T-ERROR-03
- tests to make sure that a message with a missing "to" field is ignored
- input for test: output should be nothing:
```json
{ "mnothing":"lock-actuator1.lock", "from":"sender_unique_id", "wow":"lock_actuator1" }
```
- correctly outputs nothing
T-ERROR-04
- tests to make sure name was added to the config parameter
- input for test: should return error:
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "nombre":"degree_to_lock", "value":"360" }
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"error, name or value of config parameter was not provided"}
```
- correctly outputs an error
T-ERROR-05
- tests to make sure the name is a valid config parameter for the device
- input for test: should output error
```json
{ "mtype":"config", "from":"does_not_matter", "to":"lock_actuator1", 
  "name":"coolness", "value":"100000" }
```
- output:
```json
{"mtype":"error","from":"lock_actuator1","to":"*","message":"Error, lock_actuator1 config name does not match accepted name or device is locked"}
```
- correctly outputs an error message