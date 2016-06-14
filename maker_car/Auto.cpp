#include "Auto.h"

//the direction
#define FRONT	3
#define	BACK	2
#define LEFT	1
#define RIGHT	0

#define VEHICLE_X_MID 515
#define VEHICLE_Y_MID 517

uint8_t currentDir;

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

boolean checkDirection(uint8_t dir){
  //檢查行走方向有沒有障礙物
  if(incomingByte & (1 << dir))
    return true;
  return false;
}

void automove(){
  static int times = 0;
  boolean flag = false;
  
  //如果有障礙物且已經遠離上次的障礙物
  if(checkDirection(currentDir) && (times == 0)){
    uint8_t dir = (currentDir + 1) % 4;  //turn 90 degrees
    while(checkDirection(dir)){
      dir = (dir + 1) % 4;  //turn 90 degrees
      if(dir == currentDir){  //if can't move
        carMove(VEHICLE_X_MID, VEHICLE_Y_MID);
        flag = true;
        break;
      }
    }
    currentDir = dir;
    times = 25;
  }
  
  if(times > 0)
    times--;  
  if(!flag)
    carMove(cmd[currentDir].x, cmd[currentDir].y);
  Serial.println(currentDir);
}

