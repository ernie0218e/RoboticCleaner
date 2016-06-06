#ifndef UTILS
#define UTILS
#include <Wire.h>
const int SLAVE_ADDRESS = 1;

extern volatile char incomingByte;
void receiveEvent(int howMany);
void checkSpeed(int joy_x, int joy_y, int* fix_x, int* fix_y);
void transformCoord(int orig_x,int orig_y, int* x, int* y);
void fixSpeed(int vx, int vy, int* vw1, int* vw2, int* vw3, int* vw4);
#endif
