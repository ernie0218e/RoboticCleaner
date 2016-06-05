#ifndef MOUSE_H
#define MOUSE_H
#include <ps2.h>
#include "Timer.h"

#define MOUSE_DATA_PIN 4
#define MOUSE_CLK_PIN 2

extern volatile char mx, my;

void mouse_init();
void mouseTimerUpdate();
void checkMouse();

#endif
