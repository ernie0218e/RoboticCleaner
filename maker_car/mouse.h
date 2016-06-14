#ifndef MOUSE_H
#define MOUSE_H
#include <ps2.h>
#include "Timer.h"

#define MOUSE_DATA_PIN 4
#define MOUSE_CLK_PIN 2

void mouse_init();

//get the data of the movement from the mouse
void checkMouse(char *mx, char *my);

#endif
