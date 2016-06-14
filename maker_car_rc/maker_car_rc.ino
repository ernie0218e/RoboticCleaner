#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "joystick.h"
#include "rc.h"
#include "utils.h"
#include "battery.h"

#define VEHICLE_X_MID 515
#define VEHICLE_Y_MID 517

uint8_t testPattern = 0xFF;
char cmd;

struct Command{
  int x;
  int y;
};

struct Command dir[4];

void control_init(){

  //commands initialize
  //front
  dir[3].x = 0;
  dir[3].y = VEHICLE_Y_MID;

  //back
  dir[2].x = 1023;
  dir[2].y = VEHICLE_Y_MID;

  //left
  dir[1].x = VEHICLE_X_MID;
  dir[1].y = 0;

  //right
  dir[0].x = VEHICLE_X_MID;
  dir[0].y = 1023;

  cmd = 0;
}

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  setup_joystick();
  setup_rc(role_sender);
  button_init(); 
  control_init();
}

void loop() {
// bool battNormal = false;
  
  checkButton();

  if (Serial.available() > 0) {
    int inByte = Serial.read();   
    //check the command from the serial port
    Serial.println(inByte,DEC);
    switch (inByte) {
    case '3':    
      cmd = 4;
      break;
    case '2':    
      cmd = 3;
      break;
    case '1':    
      cmd = 2;
      break;
    case '0':    
      cmd = 1;
      break;
    default:
      cmd = 0;
      break;
    } 
  }

  
  if(cmd != 0){
    update_rc(dir[cmd - 1].x,
              dir[cmd - 1].y,
              read_joystick(E_JOY_STICK_CH_RIGHT_X),
              read_joystick(E_JOY_STICK_CH_RIGHT_Y),
              button
              );
  }else{

   //Update info of Joystick
   update_rc( read_joystick(E_JOY_STICK_CH_LEFT_X),
              read_joystick(E_JOY_STICK_CH_LEFT_Y),
              read_joystick(E_JOY_STICK_CH_RIGHT_X),
              read_joystick(E_JOY_STICK_CH_RIGHT_Y),
              button
              );

    //Serial.println(read_joystick(E_JOY_STICK_CH_LEFT_X));
    //Serial.println(read_joystick(E_JOY_STICK_CH_LEFT_Y));

  }


  delay(20);
}


