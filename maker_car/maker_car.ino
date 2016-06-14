#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "rc.h"
#include "battery.h"
#include "vehicle.h"
#include "mouse.h"
#include "utils.h"
#include "Auto.h"


//recieve packet
extern stRcPkt_t rcPacket;

//uncomment to run square test
//#define SQUARETEST
#ifdef SQUARETEST
extern volatile int actual_x, actual_y;
Timer t, t2;

void check();
void change();


struct Pts{
  int x;
  int y;
  int time;
};
struct Pts pts[8];
int index, event;
#endif

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  
  setup_rc(role_receiver);
  setup_vehicle();
  mouse_init();
  iic_init();
  auto_init();
  
#ifdef SQUARETEST
  actual_x = 0;
  actual_y = 0;
  index = 0;

  pts[0].x = 0;
  pts[0].y = 517;
  pts[0].time = 3000;

  pts[1].x = 515;
  pts[1].y = 517;
  pts[1].time = 1000;

  pts[2].x = 515;
  pts[2].y = 0;
  pts[2].time = 2000;

  pts[3].x = 515;
  pts[3].y = 517;
  pts[3].time = 1000;

  pts[4].x = 1023;
  pts[4].y = 517;
  pts[4].time = 3000;

  pts[5].x = 515;
  pts[5].y = 517;
  pts[5].time = 1000;
  
  pts[6].x = 515;
  pts[6].y = 1023;
  pts[6].time = 2000;

  pts[7].x = 515;
  pts[7].y = 517;
  pts[7].time = 1000;
  
  t.every(20, check);
  event = t2.after(pts[index].time, change);
#endif

}

void loop() {

#ifdef SQUARETEST
  t.update();
  t2.update();
#else
  delay(10);
#endif

}

#ifdef SQUARETEST
void check(){
  carMove(pts[index].x, pts[index].y);
  Serial.println(actual_x);
  Serial.println(actual_y);
}

void change(){
  index = (index + 1) % 8;
  t2.after(pts[index].time, change);
}
#endif
