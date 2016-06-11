#ifndef AUTO_H
#define AUTO_H
#include "Timer.h"
#include "vehicle.h"
#include "mouse.h"
#include "utils.h"

extern volatile char incomingByte;
extern volatile bool lButton;
extern volatile bool rButton;

void auto_init();
void test();

#endif