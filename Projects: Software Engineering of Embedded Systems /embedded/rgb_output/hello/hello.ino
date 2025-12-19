#include <ArduinoJson.h>
String g_serial_input; //Serial input buffer

//using pins D9-D7 I have the RGB A light plugged into those with corresponding cables
const int RGB_A_RED = D9;
const int RGB_A_GREEN = D8;
const int RGB_A_BLUE = D7;

//Same for these pins for RGB B light plugged into D4-D6 on the opposite side of the breadboard
const int RGB_B_RED = D4;
const int RGB_B_GREEN = D5;
const int RGB_B_BLUE = D6;

void setup() {
  //initializing the RGB pins to output when called
  pinMode(RGB_A_RED, OUTPUT);
  pinMode(RGB_A_GREEN, OUTPUT);
  pinMode(RGB_A_BLUE, OUTPUT);
  pinMode(RGB_B_RED, OUTPUT);
  pinMode(RGB_B_GREEN, OUTPUT);
  pinMode(RGB_B_BLUE, OUTPUT);
  //Start Serial
  Serial.begin(115200);
}

void loop() {
  //check if there is any serial input
  if(Serial.available() > 0){
    //save input to char c
    char c = Serial.read();
    //check if new  line or return
    if((c == '\n') || (c == '\r') && g_serial_input.length() > 1){
      //make a doc for error checking
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, g_serial_input);
      //error check
      if (error) {
        Serial.print("deserializeJson() returned ");
        Serial.println(error.c_str());
        return;
      }else{
      //if no error then print the json object
      deserializeJson(doc, g_serial_input);
      serializeJson(doc, Serial);
      }
    }else{
      //if not a new line or return then add the char to the string
      g_serial_input.concat(c);
    }
  }
  //run the color loop to flash lights (this will make it slow, so I'll make it function different later
  colorLoop();
}

void colorLoop(){
  //Should change to white
  light_Color_A(0,0,0);
  light_Color_B(0,0,0);
  delay(1000);
  //change A to red and B to green
  light_Color_A(255,0,0);
  light_Color_B(0,255,0);
  delay(1000);
  //change A to green and B to blue
  light_Color_A(0,255,0);
  light_Color_B(0,0,255);
  delay(1000);
  //change A to blue and B to red
  light_Color_A(0,0,255);
  light_Color_B(255,0,0);
  delay(1000);
  //change them to a random collection of colors
  light_Color_A(150,10,100);
  light_Color_B(100,150,10);
  delay(1000);
}

//These methods are how to determine the color of the RGB lights either A or B
void light_Color_A(unsigned char red, unsigned char green, unsigned char blue){
  //Takes chars as those act as bytes with only 0-255 when unsigned so no chance of error with values
  //Then write to each pin the specified value
  analogWrite(RGB_A_RED, red);
  analogWrite(RGB_A_GREEN, green);
  analogWrite(RGB_A_BLUE, blue);
}
void light_Color_B(unsigned char red, unsigned char green, unsigned char blue){
  analogWrite(RGB_B_RED, red);
  analogWrite(RGB_B_GREEN, green);
  analogWrite(RGB_B_BLUE, blue);
}