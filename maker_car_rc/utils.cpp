#include "utils.h"

long llastDebounceTime, rlastDebounceTime;  // the last time the output pin was toggled
const long debounceDelay = 50;    // the debounce time; increase if the output flickers
int lbuttonState, rbuttonState;
int llastButtonState,rlastButtonState;
int lreading, rreading;
uint8_t button;

void button_init(){
	llastDebounceTime = 0;
	rlastDebounceTime = 0;
	llastButtonState = HIGH;
	rlastButtonState = HIGH;
  button = 0;
}

//check the button
void checkButton(){

	lreading = read_button(E_JOY_STICK_BTN_1);
	rreading = read_button(E_JOY_STICK_BTN_0);

	if(lreading != llastButtonState){
		llastDebounceTime = millis();
	}

	if(rreading != rlastButtonState){
		rlastDebounceTime = millis();
	}

	if((millis() - llastDebounceTime) > debounceDelay){

		if(lreading != lbuttonState){
			lbuttonState = lreading;
		}

		if(!lbuttonState)
   			button |=  (1 << RC_RF24_BTN_LEFT);
		else
   			button &=  ~(1 << RC_RF24_BTN_LEFT);

	}

	if((millis() - rlastDebounceTime) > debounceDelay){

		if(rreading != rbuttonState){
			rbuttonState = rreading;
		}

		if(!rbuttonState)
   			button |=  (1 << RC_RF24_BTN_RIGHT);
 		else
   			button &=  ~(1 << RC_RF24_BTN_RIGHT);

	}

   	llastButtonState = lreading;
   	rlastButtonState = rreading;
}
