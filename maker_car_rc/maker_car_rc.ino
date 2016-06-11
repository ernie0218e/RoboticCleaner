#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "joystick.h"
#include "rc.h"
#include "utils.h"
#include "battery.h"

uint8_t testPattern = 0xFF;

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  setup_joystick();
  setup_rc(role_sender);
  button_init();  
}

void loop() {
 bool battNormal = false;

 checkButton();

 update_rc( read_joystick(E_JOY_STICK_CH_LEFT_X),
            read_joystick(E_JOY_STICK_CH_LEFT_Y),
            read_joystick(E_JOY_STICK_CH_RIGHT_X),
            read_joystick(E_JOY_STICK_CH_RIGHT_Y),
            button
            );

  Serial.println(read_joystick(E_JOY_STICK_CH_LEFT_X));
  Serial.println(read_joystick(E_JOY_STICK_CH_LEFT_Y));

delay(20);
}


