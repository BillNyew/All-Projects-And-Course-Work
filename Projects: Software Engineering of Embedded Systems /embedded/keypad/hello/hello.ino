/*
 * hello.ino
 *
 * Demonstrates keypad + LED functionality for embedded hardware hello-world.
 * Users enter a passcode via a 4x4 keypad. Green LED blinks on each key press.
 * '#' validates the code: green LED blinks if correct, red LED if not.
 *
 * Author: Charles Jensen
 * Created: 2025-05-07
 * Last Modified: 2025-05-07
 */

// Constants
// Pin assignments
const byte PIN_LED_GREEN = D0;
const byte PIN_LED_RED = D1;
const byte PIN_ROW[4] = {D3, D4, D5, D6};
const byte PIN_COL[4] = {D7, D8, D9, D10};

// Keypad layout
const byte NUM_ROWS = 4;
const byte NUM_COLS = 4;

const char KEYPAD_KEYS[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Timing constants
const unsigned int LED_BLINK_DURATION_MS = 250;

// Target passcode
const String CORRECT_CODE = "95987123";

// Global Variables

String g_entered_code = ""; // Stores the current input code
char g_last_key = 0;        // Stores the last pressed key

// Function Declarations

void blink_led(byte pin, int times, unsigned int delay_ms);
char read_keypad();

// Setup Function

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println(F("Keypad Hello-World Starting..."));

  // Configure row pins as inputs with pull-up
  for (byte i = 0; i < NUM_ROWS; i++)
  {
    pinMode(PIN_ROW[i], INPUT_PULLUP);
  }

  // Configure column pins as outputs
  for (byte i = 0; i < NUM_COLS; i++)
  {
    pinMode(PIN_COL[i], OUTPUT);
    digitalWrite(PIN_COL[i], HIGH);
  }

  // Configure LED pins
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
}

// Main Loop

void loop()
{
  char key = read_keypad();

  // Debounce and ensure key is not repeating
  if (key != 0 && key != g_last_key)
  {
    g_last_key = key;

    if (key != '#')
    {
      g_entered_code += key;
      Serial.print(F("Current code: "));
      Serial.println(g_entered_code);
      blink_led(PIN_LED_GREEN, 1, 100);
    }
    else
    {
      if (g_entered_code.length() > 0)
      {
        if (g_entered_code == CORRECT_CODE)
        {
          Serial.println(F("Correct code entered"));
          blink_led(PIN_LED_GREEN, 3, LED_BLINK_DURATION_MS);
        }
        else
        {
          Serial.println(F("Incorrect code"));
          blink_led(PIN_LED_RED, 3, LED_BLINK_DURATION_MS);
        }
        g_entered_code = "";
      }
    }
  }

  // Reset last key on release
  if (key == 0)
  {
    g_last_key = 0;
  }
}

// Helper Functions
// Reads the keypad and returns the character of the pressed key
char read_keypad()
{
  for (byte c = 0; c < NUM_COLS; c++)
  {
    digitalWrite(PIN_COL[c], LOW);
    for (byte r = 0; r < NUM_ROWS; r++)
    {
      if (digitalRead(PIN_ROW[r]) == LOW)
      {
        delay(50); // Debounce delay
        digitalWrite(PIN_COL[c], HIGH);
        return KEYPAD_KEYS[r][c];
      }
    }
    digitalWrite(PIN_COL[c], HIGH);
  }
  return 0;
}

// Blinks the specified LED a given number of times
void blink_led(byte pin, int times, unsigned int delay_ms)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}
