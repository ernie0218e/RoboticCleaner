#include "Auto.h"

#define FRONT	3
#define	BACK	2
#define LEFT	1
#define RIGHT	0

#define VEHICLE_X_MID 515
#define VEHICLE_Y_MID 517

int currentDir;

struct Command{
  int x;
  int y;
};

struct Command cmd[4];

void auto_init(){

  //commands initialize
  //front
  cmd[FRONT].x = 0;
  cmd[FRONT].y = VEHICLE_Y_MID;

  //back
  cmd[BACK].x = 1023;
  cmd[BACK].y = VEHICLE_Y_MID;

  //left
  cmd[LEFT].x = VEHICLE_X_MID;
  cmd[LEFT].y = 0;

  //right
  cmd[RIGHT].x = VEHICLE_X_MID;
  cmd[RIGHT].y = 1023;

  currentDir = FRONT;

}

void test(){
	if(rButton)
		carMove(cmd[currentDir].x, cmd[currentDir].y);
	else
		carMove(VEHICLE_X_MID, VEHICLE_Y_MID);
}