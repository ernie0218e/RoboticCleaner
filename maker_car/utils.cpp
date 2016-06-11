#include "utils.h"

#define JOY_MID_X 515
#define JOY_MID_Y 517

volatile char incomingByte;
volatile int actual_x, actual_y;

void iic_init(){
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  incomingByte = 0;
}

void receiveEvent(int howMany)
{
  while(Wire.available()){
    incomingByte = Wire.read();
    //Serial.println(incomingByte, DEC);
  }
}


void checkSpeed(int joy_x, int joy_y, int* fix_x, int* fix_y){
	int tjoy_x = (joy_x - JOY_MID_X)/4;
	int tjoy_y = (joy_y - JOY_MID_Y)/4;
	int dx = 0, dy = 0;
  char mx, my;
  checkMouse(&mx, &my);
	if(my != 0 || mx != 0){
		dx = tjoy_x - my;
		dy = tjoy_y + mx;
		*fix_x = joy_x + dx;
		*fix_y = joy_y + dy;
		if(*fix_x > 1023)
			*fix_x = 1023;
		if(*fix_x < 0)
			*fix_x = 0;
		if(*fix_y > 1023)
			*fix_y = 1023;
		if(*fix_y < 0)
			*fix_y = 0;
	}else{
		*fix_x = joy_x;
		*fix_y = joy_y;
	}
}
void fixSpeed(int vx, int vy, int* vw1, int* vw2, int* vw3, int* vw4){
	int dx = 0, dy = 0;
  char mx, my;
  checkMouse(&mx, &my);
	if(my != 0 || mx != 0){
		dx = 0.2*(vx + mx);
		dy = 0.2*(vy + my) ;
		*vw1 = dy - dx;
		*vw2 = dy + dx;
		*vw3 = dy - dx;
		*vw4 = dy + dx;
   actual_x += mx;
   actual_y += my;
	}else{
		*vw1 = 0;
		*vw2 = 0;
		*vw3 = 0;
		*vw4 = 0;
	}
}

void transformCoord(int orig_x,int orig_y, int* x, int* y){
	*x = orig_y;
	*y = orig_x;
}
