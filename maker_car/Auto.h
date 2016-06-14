#ifndef AUTO_H
#define AUTO_H
#include "Timer.h"
#include "vehicle.h"
#include "mouse.h"
#include "utils.h"

extern volatile char incomingByte;

//initialize the auto mode
void auto_init();

//call repeatedly
void automove();

#endif
