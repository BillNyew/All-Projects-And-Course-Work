#include <ArduinoJson.h>

/**
 * Represents the different mtype values for json messages (to
 * determine which MType a string should be associated with use 
 * get_input_mtype(const String&)). This includes a field for invalid values.
 */
enum InputMType
{
  /** Represents the mtype of a configuration input message. */
  CONFIG = 1,

  /** Represents the mtype of a start input message. */
  START = 2,

  /** Represents the mtype of a stop input message. */
  STOP = 3,

  /** Represents the mtype of an invalid message (may also be treated as false). */
  INVALID = 0
};

enum OutputMType
{
  /** Represents the mtype of a data output message. */
  DATA,

  /** Represents the mtype of an error output message. */
  ERROR,

  /** Represents the mtype of a debug output message. */
  DEBUG
};

/**
 * Represents the different states the weight sensor can be in.
 */
enum STATE
{
  /** Represents the setup state which occurs before configuration has succeeded. */
  SETUP,

  /** Represents the setup idle which occurs after configuration has succeeded
   *  but before recieving the start command, or after recieving the stop 
   *  command. */
  IDLE,

  /** Represents the setup which occurs after configuration has succeeded
   *  and when the last command recieved was the start command. */
  MEASURING
};

/**
 * Structure representing one Message.
 */
struct InputMessage
{
  /** The value associated with the "mtype" key of this input message. */
  InputMType mtype;

  /** The value associated with the "from" key of this input message. */
  String from;

  /** The value associated with the "to" key of this input message. */
  String to;

  /** Stores the value associated with the "name" key of this input message
   *  if there is one (should be ignored with non-configuration messages. */
  String name;

  /** Stores the value associated with the "value" key of this input message
   *  if there is one (should be ignored with non-configuration messages. */
  int value;
};

/** The unique identifier for this module. */
const String WEIGHT_SENSOR_UID = "weight_sensor1";
/** The name of the pin associated with button one. */
const int BUTTON_1 = A0;
/** The name of the pin associated with button two. */
const int BUTTON_2 = A1;
/** The name of the pin associated with button three. */
const int BUTTON_3 = A2;
/** The serial BAUD rate passed to Serial.begin(). */
const int BAUD_RATE = 115200;

/** Key that should appear in json messages containing the mtype. */
static const String MTYPE_KEY = "mtype";
/** Key that should appear in json messages containing the sender. */
static const String FROM_KEY = "from";
/** Key that should appear in json messages containing the intended recipient. */
static const String TO_KEY = "to";
/** Key that should appear in json messages containing the message name. */
static const String NAME_KEY = "name";
/** Key that should appear in json messages containing a numeric value associated
 *  with the message. */
static const String VALUE_KEY = "value";

/** The current overall state of the module. */
STATE g_state = SETUP;
/** The numer of times per second the program will sample the buttons. */
int g_sample_freq_hz = 0;
/** When the number of pressed buttons is detected at or below this value a
 *  message should be sent indiciating the number of buttons currenlty pressed. */
int g_pressed_threshold = 3;

/**
 * Blocks until configuration messages are recieved and sets the provided
 * fields accordingly, invalid values are rejected and this method only
 * returns after recieving valid values or all config parameters.
 */
static void config();

/**
 * Takes 5 samples without delay from each button, and returns the count of 
 * pressed buttons (a button is only considered pressed if all 5 reads were
 * high).BAUD_RATE
 * 
 * @return The count of pressed buttons.
 */
static int read_pressed_count();

/**
 * Reads a serial message character by character until reaching a terminating
 * character or their is no more serail input, then fills the provided Message
 * with the values read and returns true if successful and the contents of msg are
 * valid or returns false if an invalid message was recieved, there was no
 * Serial input to read, or Serial input ran out before an entire message was
 * read in which case the contents of msg are invalid. For 
 * messages where mtype is START or STOP, the value and name fields will not be 
 * valid and should be ignored.
 * 
 * @param msg The Message to fill with the information in the Message read from
 *            Serial.
 * @return True if input was successfully read and the contents of msg are valid,
 *         false if there was nothing to read or the input read was 
 *         invalid/incomplete and the contents of msg are invalid.
 */
static bool read_serial_msg(InputMessage& msg);

/**
 * Send a json message Serially with the values in the provided message and
 * returns true on success, and false if the msg.mtype was not valid for an
 * output message or if serialization failed.
 * 
 * 
 * @param mtype The mtype of the message  to be sent.
 * @param name The value to be sent with the name key.
 * @param value The value of the message to be sentwith the value key if there
 *              is one, defaults to 0.
 * @return Returns true on success and false otherwise.
 */
static bool send_serial_msg(OutputMType mtype, const String name, int value = 0);

/**
 * Returns the appropriate InputMType for the provided string, or the INVALID
 * mtype if there was not a valid InputMType associated with the provided string.
 * 
 * @param mtype A string representing some mtype which needs to be identified
 *              and returned.
 * @return The InputMType associated with the provided string or InputMType::INVALID
 *         if no other (valid) InputMType values could be matched (InputMType::INVALID
 *         may be interpreted as false).
 */
static InputMType get_input_mtype(const String& mtype);

/**
 * Starts serial communication, configures pins, and waits for configuration
 * messages.
 */
void setup() 
{
  Serial.begin(BAUD_RATE);
  while (!Serial)
  {
    continue;
  }

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);

  config();
  g_state = IDLE;
  // TODO - add this and other debug messages to readme
  send_serial_msg(DEBUG, "configuration succeeded: entering IDLE state");
}

/**
 * In the idle state this makes calls to read_serial_msg() until a 
 * start message is recieved and then enters the measuring state. In the 
 * measuring state the buttons are sampled at the rate described by g_saple_freq_hz
 * until reading a number of pressed buttons at or below g_pressed_threashold
 * and then sends a data message indicating the number of buttons currently
 * pressed. While measuring json messages are also read and if a stop command
 * is recieved the idle state is entered again.
 */
void loop() 
{
  static int last_sample_ms = 0;
  // 1000 is hardcoded because there are 1000ms in a second 
  static float sample_interval_ms = 1000.0/g_sample_freq_hz;
  static InputMessage input_msg;

  if (g_state == IDLE)
  {
    if (read_serial_msg(input_msg))
    {
      if (input_msg.mtype == START)
      {
        send_serial_msg(DEBUG, "start message recieved: entering MEASURING state");
        g_state = MEASURING;
      }
    }
  }
  else if (g_state == MEASURING) // if g_state is not MEASURING or IDLE then config failed
  {
    if (millis() - last_sample_ms >= sample_interval_ms)
    {
      int pressed_count = read_pressed_count();
      if (pressed_count <= g_pressed_threshold)
      {
        send_serial_msg(DATA, "pressed_count", pressed_count);
      }
      last_sample_ms = millis();
    }
    if (read_serial_msg(input_msg))
    {
      if (input_msg.mtype == STOP)
      {
        send_serial_msg(DEBUG, "stop message recieved: entring IDLE state");
        g_state = IDLE;
      }
    }
  }
}

static int read_pressed_count()
{
  int button1_read = HIGH;
  int button2_read = HIGH;
  int button3_read = HIGH;
  for (int i = 0; i < 5; i++)
  {
    if (digitalRead(BUTTON_1) == LOW)
    {
      button1_read = LOW;
    }
    if (digitalRead(BUTTON_2) == LOW)
    {
      button2_read = LOW;
    }
    if (digitalRead(BUTTON_3) == LOW)
    {
      button3_read = LOW;
    }
  }
  int pressed_count = 0;
  if (button1_read == HIGH)
  {
    pressed_count++;
  }
  if (button2_read == HIGH)
  {
    pressed_count++;
  }
  if (button3_read == HIGH)
  {
    pressed_count++;
  }
  return pressed_count;
}

static void config()
{
  static const String FREQ_CONFIG_NAME = "sample_freq";
  static const String THREASHOLD_CONFIG_NAME = "pressed_threashold";
  bool freq_configured = false;
  bool threashold_configured = false;
  InputMessage msg;
  send_serial_msg(DEBUG, "waiting for configuration");
  while (!freq_configured || !threashold_configured)
  {
    if (read_serial_msg(msg))
    {
      if (msg.mtype == CONFIG)
      {
        if (!freq_configured && msg.name == FREQ_CONFIG_NAME)
        {
          if (msg.value <= 0)
          {
            send_serial_msg(ERROR, "configuration value for sample freq invalid: " + String(msg.value));
          }
          else
          {
            g_sample_freq_hz = msg.value;
            freq_configured = true;
            send_serial_msg(DEBUG, "sample frequency configured");
          }
        }
        if (!threashold_configured && msg.name == THREASHOLD_CONFIG_NAME)
        {
          if (msg.value > 2 || msg.value < 0)
          {
            send_serial_msg(ERROR, "configuration value for pressed threashold invalid: " + String(msg.value));
          }
          else
          {
            g_pressed_threshold = msg.value;
            threashold_configured = true;
            //send_serial_msg(DEBUG, "pressed threashold configured");
          }
        }
      }
    }
  }
}

static bool read_serial_msg(InputMessage& msg)
{
  JsonDocument doc;
  InputMessage msgBuf;
  msg.mtype = INVALID;
  msg.from = "";
  msg.to = "";
  msg.name = "";
  msg.value = 0;

  if (Serial.available() <= 0)
  {
    // No input to read
    return false;
  }
  send_serial_msg(DEBUG, "reading serial message");

  char c;
  String msg_text = "";
  bool valid_msg = false;
  while (Serial.available() > 0)
  {
    c = Serial.read();
    if (c != '\n' && c != '\r')
    {
      msg_text.concat(c);
    }
    else if (msg_text.length() > 0)
    {
      DeserializationError err = deserializeJson(doc, msg_text);
      if (err)
      {
        send_serial_msg(ERROR, "deserialization() error: " + String(err.c_str()));
        return false;
      }
      valid_msg = true;
    }
  }

  if (!valid_msg)
  {
    send_serial_msg(ERROR, "invalid message: no terminating character or only terminating character");
    return false;
  }

  // Verifies essential fields for all json input messages
  if (!doc[MTYPE_KEY].is<String>() || !doc[FROM_KEY].is<String>() ||
      !doc[TO_KEY].is<String>())
  {
    // json message missing fields required for all input messages
    // TODO - specifcy which is missing?
    send_serial_msg(ERROR, "recieved json message without essential field (mtype, to, or from)");
    return false;
  }
  msgBuf.to = doc[TO_KEY].as<String>();
  // TODO - return the invalid string?
  if (msgBuf.to != WEIGHT_SENSOR_UID)
  {
    // message intended for different module
    send_serial_msg(DEBUG, "recieved message intended for other module");
    return false;
  }
  msgBuf.from = doc[FROM_KEY].as<String>();
  String mtype_text = doc[MTYPE_KEY].as<String>();
  msgBuf.mtype = get_input_mtype(mtype_text);
  if (msgBuf.mtype == INVALID)
  {
    // message had invalid mtype
    send_serial_msg(ERROR, "recieved message with missing or invalid mtype");
    return false;
  }

  // Handles additional fields for config messages
  if (msgBuf.mtype == CONFIG)
  {
    // Should this only accept config messages from the brain
    // if (msgBuf.from != unique_brain_id)
    // {
    //   // only accept config message from the brain
    //   return false;
    // }
    if (!doc[NAME_KEY].is<String>())
    {
      send_serial_msg(ERROR, "recieved config message with missing or invalid name");
      return false;
    }
    if (!doc[VALUE_KEY].is<int>())
    {
      send_serial_msg(ERROR, "recieved config message with missing or invalid value");
      return false;
    }
    msgBuf.name = doc[NAME_KEY].as<String>();
    msgBuf.value = doc[VALUE_KEY].as<int>();
  }

  msg = msgBuf;
  send_serial_msg(DEBUG, "successfully read json msg");
  return true;
}

static bool send_serial_msg(OutputMType mtype, const String name, int value)
{
  static const String DATA_MTYPE = "weight_sensor.data";
  static const String ERROR_MTYPE = "weight_sensor.error";
  static const String DEBUG_MTYPE = "weight_sensor.debug";
  
  JsonDocument doc;

  if (mtype == DATA)
  {
    doc[MTYPE_KEY] = DATA_MTYPE;
    doc[VALUE_KEY] = value;
  }
  else if (mtype == ERROR)
  {
    doc[MTYPE_KEY] = ERROR_MTYPE;
  }
  else if (mtype == DEBUG)
  {
    doc[MTYPE_KEY] = DEBUG_MTYPE;
  }
  else
  {
    return false;
  }
  doc[FROM_KEY] = WEIGHT_SENSOR_UID;
  doc[TO_KEY] = "*";
  doc[NAME_KEY] = name;

  serializeJson(doc, Serial);
  Serial.println();
  return true;
}

static InputMType get_input_mtype(const String& mtype)
{
  static const String CONFIG_MTYPE = "config";
  static const String START_MTYPE = "weight_sensor.start";
  static const String STOP_MTYPE = "weight_sensor.stop";
  if (mtype == CONFIG_MTYPE)
  {
    return CONFIG;
  }
  else if (mtype == START_MTYPE)
  {
    return START;
  }
  else if (mtype == STOP_MTYPE)
  {
    return STOP;
  }
  return INVALID;
}