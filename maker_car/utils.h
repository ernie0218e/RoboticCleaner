#ifndef UTILS
#define UTILS
#include <Wire.h>
const int SLAVE_ADDRESS = 1;

extern volatile incomingByte;
void receiveEvent(int howMany);

void transformCoord(int orig_x,int orig_y, int* x, int* y);

#endif
