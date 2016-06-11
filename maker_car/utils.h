#ifndef UTILS
#define UTILS
#include <Wire.h>
#include <Arduino.h>
#include "mouse.h"

//i2c address
const int SLAVE_ADDRESS = 1;

//i2c buffer
extern volatile char incomingByte;

//Button info
extern volatile bool lButton;
extern volatile bool rButton;

void receiveEvent(int howMany);
void requestEvent();
void checkSpeed(int joy_x, int joy_y, int* fix_x, int* fix_y);
void transformCoord(int orig_x,int orig_y, int* x, int* y);
void fixSpeed(int vx, int vy, int* vw1, int* vw2, int* vw3, int* vw4);

#endif
