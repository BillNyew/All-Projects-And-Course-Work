const int BUTTON_1 = A0;
const int BUTTON_2 = A1;
const int BUTTON_3 = A2;
const int BUTTON_READ_INTERVAL_MS = 500;
const int BAUD_RATE = 115200;

unsigned long g_last_read_ms;

/**
 * Starts serial communication, initializes globals, and configures pins.
 */
void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.println("Serial starting...");
  while (!Serial)
  {
    continue;
  }
  Serial.println("Serial started.");

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  g_last_read_ms = 0;
}

/**
 * Reads from the buttons and prints the results via serial communication at the interval
 * defined by BUTTON_READ_INTERVAL_MS.
 */
void loop() 
{
  if (millis() > g_last_read_ms + BUTTON_READ_INTERVAL_MS) 
  {
    int pressed_count = 0;
    if (digitalRead(BUTTON_1))
    {
      pressed_count++;
    }
    if (digitalRead(BUTTON_2))
    {
      pressed_count++;
    }
    if (digitalRead(BUTTON_3))
    {
      pressed_count++;
    }
    g_last_read_ms = millis();

    Serial.printf("%d buttons pressed.\n", pressed_count);
  }
}