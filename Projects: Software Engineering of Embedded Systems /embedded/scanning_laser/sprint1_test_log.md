# Scanning Laser Rangefinder

## Test Log

## Existing Tests

### Setup Command 1
This test was structured to allow me to configure angular resolution. It failed as the unique ID was set incorrectly. In the code all config json messages will fail if the unique ID in the "to" category is not set to "scaning_laser_unique_id". 

Here is the original test:
```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "brain_unique_id",
  "name": "angular_resolution",
  "value": 5
}
```

Here is the fixed test:
```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "scanning_laser_unique_id",
  "name": "angular_resolution",
  "value": 5
}
```

### Setup Command 2
This test was made to config the sample rate. It had the same error as the other test. (Invalid unique ID)
This is the original message.
```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "brain_unique_id",
  "name": "sampling_rate",
  "value": 10
}
```

Here is fixed message:

```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "scanning_laser_unique_id",
  "name": "sampling_rate",
  "value": 10
}
```

### Setup Command 3
This code is for changing threshold. It also has the same error as the two previous tests (Invalid unique ID).
```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "scanning_laser_unique_id",
  "name": "smoothing_factor",
  "value": 0.3
}
```

### Next steps
After trying these tests I then tried to start the sensor. I used this command:
```json
{
  "mtype": "scanning_laser.start",
  "from": "brain_unique_id",
  "to": "scanning_laser_unique_id"
}
```
Which seems to have worked correctly. After starting the sensor I got these errors repeating. 
```json
{
  "mtype": "scanning_laser.start",
  "from": "brain_unique_id",
  "to": "scanning_laser_unique_id"
}
```
E (1997185) i2c.master: s_i2c_synchronous_transaction(924): I2C transaction failed
E (1997187) i2c.master: i2c_master_multi_buffer_transmit(1186): I2C transaction failed
E (1997285) i2c.master: I2C transaction unexpected nack detected

Checking the hardware setup I had, the pins for i2c were set correctly. What ended up happeing is that I had one cable swapped which put 3.3v to the ground lead on the sensor. Swapping my jumper cable over every sprung to life. The hardware setup in the readme isn't the best (it's just a photo) I had a website that did a better job though but it wasn't for the exact configuration I had so it would have been nice to have a bit more instruction on what pin is supposed to connect where exactly.

At this point the code seems to be working and functioning no issues. The sensor gets a value and the servo motor moves.

## Tests

Starting with test  T-CONFIG-01. It worked as expected.
Test T-CONFIG-02 worked as expected as well.
Tests T-CONFIG-03 and -04 worked as well.

For the invalid tests
Tests T-INVALID-01, -02, -03, -04, -07 worked as expected. Errors that were expected were produced.
For tests T-INVALID-05 and -06 the tests executed and failed as expected but the error is slightly wrong. Error expected in the readme is : "Missing or invalid 'name' and/or 'value' field in config message". The actual error is: "Invalid name and value pairs for config".

T-INPUT-02 seems to be working perfectly. 

T-INPUT-01 input did not work. It was a simple syntax error where the mtype was spelled incorrectly. It was set to "scanning_laser.set" where the correct format is "scanning_laser.set_angle". I figured this out by looking through the code, it only took around 1 minute to debug.

Overall the tests are very through and tests all aspects of the device. Besides a few syntax errors and my incorrect setup everything went smoothly and worked as expected.

## Additional tests

A test with the invalid ID would be useful if anything to help someone debug the issue if they mistype something.
It could look something like this:
```json
{
  "mtype": "config",
  "from": "brain_unique_id",
  "to": "scanning_id",
  "name": "smoothing_factor",
  "value": 0.8
}
```
I have added this to the readme.

## Issues
After testing I don't believe there are any issues with the code. Besides the syntax errors in the readme which were not too bad to fix after troubleshooting the code seems to function correctly and is also easy to read.