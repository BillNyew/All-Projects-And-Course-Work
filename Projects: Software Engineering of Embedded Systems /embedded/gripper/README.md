# Gripper

## User Story

https://github.com/ComputerScienceUniversityofDenver/S25-EmbeddedSecuritySystem/issues/7


## Configuring: 
Accept Json message from brain of tripwire notification and or a reset to default positioning.

### Config message:
```{mtype:"gripper.config", from:"brain",to:"gripper", name:"grip-config", value:"default (0)"}```

### Report message:
```{mtype:"gripper.report", from:"brain",to:"gripper", name:"grip-report"}```

This should be followed up with a 
```{mtype:"gripper.status", from:"gripper",to:"brain", name:"grip-status", value:"open or closed based on previous input"}```

## Messages:
(I don't think it has capability to send feedback on if it hit something or not but if that is possible sure),
if not responsive serialize a message to the brain, 
### Error message:
```{mtype:"error", from:"gripper", to:"brain", message:"failed to respond"}```

### Reset message: 
```{mtype:"reset", from:"gripper", to:"brain", message:"reset to default"}```

### Gripper is engaged message: 

```{mtype:"update", from:"gripper", to:"brain", message:"engaged"} ```

sent every few seconds while grip is engaged

### Command message:
```{mtype:"gripper.open", from:"brain",to:"gripper", name:"grip-open", value:"VALUE TO OPEN GRIPPER BY OR 0"}```
### Command message:
```{mtype:"gripper.close", from:"brain",to:"gripper", name:"grip-close", value:"VALUE TO CLOSE GRIPPER BY OR 180"}```
### Positioning message:
```{mtype:"gripper.command", from:"brain", to:"gripper", name:"grip-position", value:"0-180"}```


## Deliverables: 
1. Fully engage gripper 
2. Take input to set gripper to default (0?) 
3. Send output messages on error or reset and status report 
4. Respond to tripwire notification 
5. Calibrate via brain messages and respond with appropriate messages

## Software set up:
 Be prepared for input Json messages to trigger the gripper on a wire trip or a brain declaration. When triggered fully close the gripper and remain in that state until further notified, thus remain listening for new messages that say reset. then return servos to default position 0 or whatever it may be. Then notify the brain of that reset of the servos.

## Parameters: 
- Speed constant varaible
- Infered digital pin varaible
- Servo position global(maybe static in a method)
- Gripper status varaible
- Light sensitivity variable
- Threshold for broken light time varaible
- Timing varaible initial
- Timing varaible to check against initial
- Timing threshold (for gripper message updates)

## Hardware design:
Hardware includes a gripper (claws) attached to a servo, along with a breadboard, ESP32-C3 and an external battery supporting the power. There are 2 claws on the gripper whom both have ground wires connected to the GND pin of the ESP32-C3 and power wires connected to the 5V pin of the ESCP32-C3. Additionally, one of the claws contains a signal wire connected to the D6 pin of the ESP32-C3. Next, the servo has 3 wires: a ground, power, and signal wire. The ground wire is connected to the negative terminal, the power wire is connected to the positive terminal, and the signal wire is connected to D7 of the ESP32-C3. Finally, the external battery contains a power wire and ground wire that are connected to their respective terminals to provide the needed current that the ESP32-C3 cannot provide on its own to support the high-usage gripper. 

## Software design: 
Senses wired inferred beams to sync at the top of their gripper position as position 0 and sensing for breaks in the light at a Hz rate high enough to sense quick movements through the beam. This should also include a time of 100 ms or so (play around with timing) for the light to be broken before the gripper closes. Then having a gripper closing at a speed that is fast enough to catch whatever broke the beam making the position go from 50 - 180 in approximately .5 - 1 seconds. recieve messages of input to manually change the position of the gripper. Recive input to reset the gripper (ie: release). While engaged serialize message output to the brain to tell it the gripper is engaged, every few seconds?. Standard error on malfunction or bad message input. 

### Miscelaneous notes from meeting:
some value that tells you: how far open or closed it is, how sensitive the light sensor need to be, so how long to break the light
mtype = "gripper.command" as: gripper.reset, gripper.open, gripper.closed
Current state= "gripper.status", message:"open" or "closed"
change speed to config that does speed

## Test Cases:

## Configuration Tests:
T-CONFIG-01: Set Servo Speed to 10 - Verify that the servo speed configuration parameter updates correctly.
{"mtype":"gripper.config","name":"speed-config","value":"10","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: Servo connected and gripper initially open.

T-CONFIG-02: Set IR Threshold to 500ms - Verify the IR beam break threshold is updated to 500 milliseconds.
{"mtype":"gripper.config","name":"ir-threshold","value":"500","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: IR sensor connected and operational.

T-CONFIG-03: Set Engaged Interval to 5s - Confirm that the engaged message interval is updated to 5000ms.
{"mtype":"gripper.config","name":"engaged-interval","value":"5000","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: Module powered on.

T-CONFIG-04: Invalid Configuration Name - Send an unknown config name and expect an error.
{"mtype":"gripper.config","name":"invalid-config","value":"123","from":"test","to":"gripper"}
{"mtype":"error","from":"gripper","to":"brain","message":"Unknown config name"}
Preconditions: Module powered on.

T-CONFIG-05: Set Servo Delay to 20ms - Verify that servo moves slower in subsequent commands
{"mtype":"gripper.config","name":"servo-delay","value":"20","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: Servo connected and idle



## Input Tests:
T-INPUT-01: Open Gripper to 50 Degrees (Normal Operation) - Command the gripper to open to 50 degrees.
{"mtype":"gripper.open","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: Gripper servo connected and ready.

T-INPUT-02: Close Gripper to 180 Degrees (Normal Operation) - Command the gripper to close fully.
{"mtype":"gripper.close","from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"closed","position":180}
Preconditions: Gripper servo connected and ready.

T-INPUT-03: Gripper Command with Mid-Range Position (120°) - Move gripper to a specific intermediate angle.
{"mtype":"gripper.command","value":120,"from":"test","to":"gripper"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"closed","position":120}
Preconditions: Gripper initialized.

T-INPUT-04: Reset Command - Send reset command to open gripper and reset state.
{"mtype":"reset","from":"test","to":"gripper"}
{"mtype":"reset","from":"gripper","to":"brain","message":"reset to default (50 degrees)"}
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"open","position":50}
Preconditions: Gripper closed.

## Error Tests:
T-ERROR-01: Malformed JSON Input - Send malformed JSON and verify error handling.
{mtype:gripper.open}
{"mtype":"error","from":"gripper","to":"brain","message":"Invalid JSON"}
Preconditions: Serial connection active.

T-ERROR-02: Missing Required Fields in Message - Send JSON missing required fields (mtype or to).
{"from":"test"}
{"mtype":"error","from":"gripper","to":"brain","message":"Missing required fields"}
Preconditions: Module powered on.

T-ERROR-03: Invalid Position (250°) - Send a gripper.command with an out-of-range servo angle.
{"mtype":"gripper.command","value":250,"from":"test","to":"gripper"}
{"mtype":"error","from":"gripper","to":"brain","message":"Invalid position value"}
Preconditions: Module powered on.

T-ERROR-04: Invalid Config Parameter Value - Send configuration with invalid negative speed.
{"mtype":"gripper.config","name":"speed-config","value":"-1","from":"test","to":"gripper"}
{"mtype":"error","from":"gripper","to":"brain","message":"Invalid speed value"}
Preconditions: Module powered on.

## IR Tripwire Test:
T-IR-01: Simulate Beam Break (600ms) - Simulate an IR beam break longer than the configured threshold.
Action: Set IR threshold to 500ms (see T-CONFIG-02). Then simulate digitalRead(IR_PIN) = LOW for 600ms.
{"mtype":"gripper.status","from":"gripper","to":"brain","name":"grip-status","value":"closed","position":180}
Recurring:
{"mtype":"update","from":"gripper","to":"brain","message":"engaged","position":180} (every 5s)
Preconditions: IR threshold configured to 500ms.