#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include "joystick.h"
#include "rc.h"

extern uint8_t button;

void checkButton();
void button_init();

#endif
