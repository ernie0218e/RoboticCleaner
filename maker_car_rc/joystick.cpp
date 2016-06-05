#include <Arduino.h>
#include "joystick.h"

#define JS_DEBUG(x,...)
void setup_joystick() {
  // put your setup code here, to run once:
  pinMode(JOY_STICK_LEFT_X_PIN, INPUT);
  pinMode(JOY_STICK_LEFT_Y_PIN, INPUT);
  pinMode(JOY_STICK_RIGHT_X_PIN, INPUT);
  pinMode(JOY_STICK_RIGHT_Y_PIN, INPUT);
  pinMode(JOY_STICK_BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(JOY_STICK_BUTTON_PIN_1, INPUT_PULLUP);
}

uint16_t read_joystick(E_JOY_STICK_CHANNEL ch)
{
  switch(ch)
  {
    case E_JOY_STICK_CH_LEFT_X:
	    return analogRead(JOY_STICK_LEFT_X_PIN);
    case E_JOY_STICK_CH_LEFT_Y:
	    return analogRead(JOY_STICK_LEFT_Y_PIN);
    case E_JOY_STICK_CH_RIGHT_X:
	    return analogRead(JOY_STICK_RIGHT_X_PIN);
    case E_JOY_STICK_CH_RIGHT_Y:
	    return analogRead(JOY_STICK_RIGHT_Y_PIN);
    default:
	    break;
 
  }
}

bool read_button(E_JOY_STICK_BUTTON btn)
{
  switch(btn)
  {
    case E_JOY_STICK_BTN_0:
        return digitalRead(JOY_STICK_BUTTON_PIN_0);
    case E_JOY_STICK_BTN_1:
        return digitalRead(JOY_STICK_BUTTON_PIN_1);    
    case E_JOY_STICK_BTN_2:
	break;
    default:
	break;
  }
}


