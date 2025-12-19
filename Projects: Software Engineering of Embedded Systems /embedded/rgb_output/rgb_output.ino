#include <ArduinoJson.h>
String g_serial_input; //Serial input buffer
unsigned long pwm_start_time_ms; //used for PWM
unsigned long flash_start_time_ms;//used for starting the flashing
bool g_lights_on = false; //Boolean for lights to be on or off
bool g_flash_cycle = true;//Boolean for the flashing to go on or off
const float CYCLE = 10; //Cycle for PWM
float g_led_brightness = 90; //PWM level
float g_flash_frequency = 2; //Used for how fast to strobe the lights
JsonDocument output_message;//global output message to serialize when there are errors or other output
char g_red_val = 255, g_green_val = 0, g_blue_val = 0;//global variables to store and adjust the color values

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
  Serial.begin(115200);
  pwm_start_time_ms = millis();//Set the start times
  flash_start_time_ms = millis();
}

void loop() {
  unsigned long pwm_end_time_ms = millis();//used to find elapsed time and PWM
  unsigned long pwm_elapsed_time = pwm_end_time_ms - pwm_start_time_ms;//PWM varaible
  unsigned long flash_end_time_ms = millis();//measure elapsed time for flashing
  unsigned long flash_elapsed_time = flash_end_time_ms - flash_start_time_ms;//strobe variable

  if(Serial.available() > 0){//basic reading of serial
    char c = Serial.read();
    if((c == '\n' || c == '\r') && g_serial_input.length() > 1){

      JsonDocument input_message;//used for all of the input from serial
      DeserializationError error = deserializeJson(input_message, g_serial_input);
      g_serial_input = "";
      if (error) {
        //Checks if mtype or other variables are set, otherwise error
        serializeJson(makeJsonDoc("error", "rgb_output_module_id", "*", error.c_str()), Serial);
        return;
      }else{
        //store all of the input neccesary
        String messageType = input_message["mtype"];
        String name = input_message["name"] | "no name";
        float value = input_message["value"].as<float>();
        String reciever = input_message["to"] | "not me";
        //Check the "to" field of the deserial and proceed if the receiver is me
        if(reciever == "rgb_output_module_id"){
          //makes sure the message type is either connfig or start or stop otherwise throw error
          if(messageType == "config"){
            handleInput(name, value);
          }else if(messageType == "start"){
            //change lights on and send message starting
            g_lights_on = true;
            serializeJson(makeJsonDoc("started","rgb_ouptput_module_id","*","Started Flashing"), Serial);
          }else if(messageType == "stop"){
            //change lights off and send message stoppping
            g_lights_on = false;
            serializeJson(makeJsonDoc("stopped","rgb_ouptput_module_id","*","Stopped Flashing"), Serial);
          }else if(messageType == "status"){
            //Status call, report the current levels of things
            String m = "Brightness: " + String(g_led_brightness * 100) + " Flash Rate: " + String(g_flash_frequency) + " Colors: " + (int)g_red_val + ", " + (int)g_green_val + ", " + (int)g_blue_val;
            serializeJson(makeJsonDoc("status","rgb_ouptput_module_id","*", m), Serial);
          }else{
            serializeJson(makeJsonDoc("error","rgb_ouptput_module_id","*","Type not recognized"), Serial);
          }
        }else{
          //if the message "to" field isn't rgb then throw error
          serializeJson(makeJsonDoc("error","rgb_ouptput_module_id","*","This message was not meant for me"), Serial);
        }
      }
    }else{
      g_serial_input.concat(c);
    }
  }
  //turn lights on and off with this variable
  if(g_lights_on){
    //this is how flash frequency goes back and forth based on flash rate
    if(flash_elapsed_time < 1000/g_flash_frequency){
      //this is how to switch if it's on or off
      if(g_flash_cycle){
        //simple pwm cycle
        if(pwm_elapsed_time < CYCLE * g_led_brightness){
          low_light_level();
        }else if(pwm_elapsed_time < CYCLE){
          high_light_level();
        }else{
          pwm_start_time_ms = pwm_end_time_ms;
        }
      }
    }else{
      //reset timer for the flashing frequency and change off and on for the light
      flash_start_time_ms = flash_end_time_ms;
      g_flash_cycle = !g_flash_cycle;
    }
  }else{
    //turn off the lights on stop
    high_light_level();
  }
}

//Helper functions section
void set_brightness(float level){
  //this is the max that it will flash at so I hard coded it
  if(level > 90 && level <= 100){
    level = 90;
  }
  else if(level >= 0 && level <= 90){
    //make different brightness
    g_led_brightness = level/100;
  }else{
    //throw error if brightness doesn't fit these two arguements
    serializeJson(makeJsonDoc("error","rgb_ouptput_module_id","*","Brightness value not recognized"), Serial);
  }
}
void set_flash_rate(float rate){
  //if the flash rate is in range set the variable
  if(rate >= 1 && rate <= 10){
    g_flash_frequency = rate;
  }else{
    //otherwise error
    serializeJson(makeJsonDoc("error","rgb_ouptput_module_id","*","Flash rate not recognized"), Serial);
  }
}
//handles all input from the value used above
void handleInput(String n, float v){
  if(n == "brightness"){
    set_brightness(v);
  }else if(n == "flash_rate"){
    set_flash_rate(v);
  }else if(n == "light_red"){
    g_red_val = v;
    set_Light_Color(g_red_val, g_green_val, g_blue_val);
  }else if(n == "light_green"){
    g_green_val = v;
    set_Light_Color(g_red_val, g_green_val, g_blue_val);
  }else if(n == "light_blue"){
    g_blue_val = v;
    set_Light_Color(g_red_val, g_green_val, g_blue_val);
  }
}
//simple function to make json doc quickly
JsonDocument makeJsonDoc(String messType, String sender, String reciever, String mess){
  JsonDocument out;
  out["mtype"] = messType;
  out["from"] = sender;
  out["to"] = reciever;
  out["message"] = mess;
  return out;
}
void low_light_level(){
  //setting rgb based on the brightness
  int red_scaled   = (int)(g_red_val * g_led_brightness);
  int green_scaled = (int)(g_green_val * g_led_brightness);
  int blue_scaled  = (int)(g_blue_val * g_led_brightness);

  analogWrite(RGB_A_RED, 255 - red_scaled);
  analogWrite(RGB_A_GREEN, 255 - green_scaled);
  analogWrite(RGB_A_BLUE, 255 - blue_scaled);
  analogWrite(RGB_B_RED, 255 - red_scaled);
  analogWrite(RGB_B_GREEN, 255 - green_scaled);
  analogWrite(RGB_B_BLUE, 255 - blue_scaled);
}
//High level of light which is actually low?? some things are backwards
void high_light_level(){
  analogWrite(RGB_A_RED, 255);
  analogWrite(RGB_A_GREEN, 255);
  analogWrite(RGB_A_BLUE, 255);
  analogWrite(RGB_B_RED, 255);
  analogWrite(RGB_B_GREEN, 255);
  analogWrite(RGB_B_BLUE, 255);
}
//set light colors
void set_Light_Color(unsigned char red, unsigned char green, unsigned char blue){
  g_red_val=red;
  g_green_val=green;
  g_blue_val=blue;
}
//These methods are how to determine the color of the RGB lights either A or B
void light_Color_A(unsigned char red, unsigned char green, unsigned char blue){
  //Takes chars as those act as bytes with only 0-255 when unsigned so no chance of error with values
  //Then write to each pin the specified value
  analogWrite(RGB_A_RED, 255 - red);
  analogWrite(RGB_A_GREEN, 255 - green);
  analogWrite(RGB_A_BLUE, 255 - blue);
}
void light_Color_B(unsigned char red, unsigned char green, unsigned char blue){
  analogWrite(RGB_B_RED, 255 - red);
  analogWrite(RGB_B_GREEN, 255 - green);
  analogWrite(RGB_B_BLUE, 255 - blue);
}