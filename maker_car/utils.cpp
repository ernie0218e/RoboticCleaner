#include "utils.h"

volatile char incomingByte;

void iic_init(){
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  incomingByte = 0;
}

void receiveEvent(int howMany)
{
  while(Wire.available(){
    incomingByte = Wire.read();
  }
  
}

void transformCoord(int orig_x,int orig_y, int* x, int* y){
	*x = orig_y;
	*y = orig_x;
}
