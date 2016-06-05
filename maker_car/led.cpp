#include <Arduino.h>
#include "led.h"

static bool ledErrorState = false;

void setup_led(void) {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);     
}

void OnLedLowLevel(ENUM_LED_CH_t led) {
  switch(led) {
    case ENUM_LED_CH_R:
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    break;
    case ENUM_LED_CH_G:
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    break;
    case ENUM_LED_CH_B:
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    break;
    case ENUN_LED_CH_MAGENTA:
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    break;
    case ENUM_LED_CH_YELLOW:
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    break;
    case ENUM_LED_CH_CYAN:
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    break;
    case ENUM_LED_CH_WHITE:
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    break;
    case ENUM_LED_CH_OFF:
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    break;
    default:
    break;
  }
}

void onLed(ENUM_LED_CH_t led)
{
  if(!ledErrorState) OnLedLowLevel(led);
}

void onLedErrorState(bool error, ENUM_LED_CH_t led)
{
  if(error) ledErrorState = true;
  else ledErrorState = false;
  OnLedLowLevel(led);
  
}
