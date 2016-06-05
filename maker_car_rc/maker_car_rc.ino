#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "joystick.h"
#include "rc.h"
#include "led.h"
#include "battery.h"

#define printf(x, ...)

uint8_t testPattern = 0xFF;

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  setup_joystick();
  setup_rc(role_sender);
  setup_led();
  
}

void loop() {
 static uint32_t count = 0;
 static uint32_t i = 0;
 bool battNormal = false;
 uint8_t button = 0;

 if(read_button(E_JOY_STICK_BTN_0))
   button |=  (1 << RC_RF24_BTN_LEFT);
 else
   button &=  ~(1 << RC_RF24_BTN_LEFT);
   
 if(read_button(E_JOY_STICK_BTN_1))
   button |=  (1 << RC_RF24_BTN_RIGHT);
 else
   button &=  ~(1 << RC_RF24_BTN_RIGHT);

#if 0
printf("left js (x, y) = (%4d, %4d)\n",read_joystick(E_JOY_STICK_CH_LEFT_X),
            read_joystick(E_JOY_STICK_CH_LEFT_Y) );
printf("right js (x, y) = (%4d, %4d)\n",read_joystick(E_JOY_STICK_CH_RIGHT_X),
            read_joystick(E_JOY_STICK_CH_RIGHT_Y) );
printf("button: 0x%2x\n", button);
#else
 update_rc( read_joystick(E_JOY_STICK_CH_LEFT_X),
            read_joystick(E_JOY_STICK_CH_LEFT_Y),
            read_joystick(E_JOY_STICK_CH_RIGHT_X),
            read_joystick(E_JOY_STICK_CH_RIGHT_Y),
            button,
	    count%8);
#endif
//uint32_t time = 0x22222222;
//send_rc(sizeof(uint32_t), (uint8_t*)&time);
printf("i=%d\n", i);

i++;
if(i%20 == 0) count++;

delay(20);
}


