#include <Arduino.h>
#include "vehicle.h"
//#define VEHICLE_BATT_VOLT_COMPENSATE
#ifdef VEHICLE_BATT_VOLT_COMPENSATE
#include "battery.h"
#endif
//#include "printf.h"

//#define VEHICLE_OCTAL_DIR_ENABLE

#define VEHICLE_DIR_DELTA_DEBOUNCE 60 // blue
#define VEHICLE_DIR_DELTA_TOLERANCE 60 // blue
//#define VEHICLE_DIR_DELTA_DEBOUNCE 40 // green
//#define VEHICLE_DIR_DELTA_TOLERANCE 40 // green


#ifdef VEHICLE_BATT_VOLT_COMPENSATE
extern stBatt batt;
#endif


static we_wheel_dir wheelDir[VEHICLE_DIR_MAX][WHEEL_NUM_MAX] = {
  WHEEL_DIR_ARRAY_FORWARD,
  WHEEL_DIR_ARRAY_FORWARD_LEFT,
  WHEEL_DIR_ARRAY_LEFT,
  WHEEL_DIR_ARRAY_BACKWARD_LEFT,
  WHEEL_DIR_ARRAY_BACKWARD,
  WHEEL_DIR_ARRAY_BACKWARD_RIGHT,
  WHEEL_DIR_ARRAY_RIGHT,
  WHEEL_DIR_ARRAY_FORWARD_RIGHT,
  WHEEL_DIR_ARRAY_ROTATE_CW,
  WHEEL_DIR_ARRAY_ROTATE_CCW
};

wallE myWallE = {
  {
    {
      // front left
      {false, false, 5, A0, 0},
      // rear left
      {false, false, 6, A1, 0},
      // fornt right
      {false, false, 9, A2, 0},
      // rear right
      {false, false, 10, A3, 0}
    }
  },
};

void setup_vehicle() {
  int i=0;

  for(i=0;i<WHEEL_NUM_MAX;i++)
  {
    analogWrite(myWallE.vehicle.wheels[i].pin_enable, 0);
    pinMode(myWallE.vehicle.wheels[i].pin_enable, OUTPUT);
    pinMode(myWallE.vehicle.wheels[i].pin_cw, OUTPUT);
  }

}

#define VEHICLE_X_MID 502
#define VEHICLE_Y_MID 508
#define VEHICLE_RC_TOLERANCE 10

#define Y_FORWARD(y) (y < VEHICLE_Y_MID)
#define X_LEFT(x) (x > VEHICLE_X_MID)



static void vehicleSetWheelDir(we_vehicle_dir dir, uint16_t delta_x, uint16_t delta_y) {
  int i=0;
  we_wheel_dir tempDir;
  
    
  tempDir = wheelDir[dir][i];
    
#ifndef VEHICLE_OCTAL_DIR_ENABLE    
    if(wheelDir[dir][i] == WHEEL_DIR_FREEZE) {
      // Compensate dir
      if((dir==VEHICLE_DIR_FORWARD_LEFT) || (dir==VEHICLE_DIR_BACKWARD_RIGHT)) {
        // compensate dir by x, y
        if((abs(delta_x-delta_y)) > VEHICLE_DIR_DELTA_DEBOUNCE) {
          if(delta_x > delta_y) {// forward compensate
            tempDir = wheelDir[dir+1][i];
          } else {
            tempDir = wheelDir[dir-1][i];
          }
        }
      } else if((dir==VEHICLE_DIR_BACKWARD_LEFT) || (dir==VEHICLE_DIR_FORWARD_RIGHT)) {
        // compensate dir by x, y
        if((abs(delta_x-delta_y)) > VEHICLE_DIR_DELTA_DEBOUNCE) {
          if(delta_x > delta_y) {// backward compensate
            tempDir = wheelDir[dir-1][i];
          } else {
            if(dir == VEHICLE_DIR_FORWARD_RIGHT) tempDir = wheelDir[VEHICLE_DIR_FORWARD][i];
            else tempDir = wheelDir[dir+1][i];
          }
        }
      } 
    }  
    
#endif

    if(tempDir == WHEEL_DIR_CW)
    {
      digitalWrite(myWallE.vehicle.wheels[i].pin_cw, WHEEL_DIR_GPIO_LEVEL_CW);
    }
    else if(tempDir == WHEEL_DIR_CCW)
    {
      digitalWrite(myWallE.vehicle.wheels[i].pin_cw, WHEEL_DIR_GPIO_LEVEL_CCW);
    }
}
 
static uint16_t vehicleCalculatePWM(uint16_t delta_x, uint16_t delta_y)
{

  if(delta_x > delta_y) 
    return delta_x*3/2;
  else 
    return delta_y*3/2;
}

static void vehicleSetWheelPWM(we_vehicle_dir dir, uint16_t delta_x, uint16_t delta_y) {
  int i=0;
  double tempSqrt = 0;
  uint16_t tempPWM = 0;
  
  switch(dir) {
    case VEHICLE_DIR_FORWARD:
    case VEHICLE_DIR_BACKWARD:
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = delta_y;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = delta_y;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = delta_y;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = delta_y;
    break;
    case VEHICLE_DIR_FORWARD_LEFT:
    case VEHICLE_DIR_BACKWARD_RIGHT:
     tempSqrt = vehicleCalculatePWM(delta_x, delta_y);//sqrt(delta_x^2 + delta_y^2);
     if(delta_x > delta_y) tempPWM = delta_x;
     else tempPWM = delta_y;
     tempPWM = abs(delta_x - delta_y);
     if(tempSqrt >= 512) tempSqrt = 511;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = (unsigned int)tempSqrt;
#ifndef VEHICLE_OCTAL_DIR_ENABLE
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = tempPWM;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = tempPWM;
#else
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = 0;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = 0;
#endif
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = (unsigned int)tempSqrt;
    break;
    case VEHICLE_DIR_LEFT:
    case VEHICLE_DIR_RIGHT:
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = delta_x;
    break;
    case VEHICLE_DIR_BACKWARD_LEFT:
    case VEHICLE_DIR_FORWARD_RIGHT:
     if(delta_x > delta_y) tempPWM = delta_x;
     else tempPWM = delta_y;
     tempPWM = abs(delta_x - delta_y);
     if(tempSqrt >= 512) tempSqrt = 511;
     tempSqrt = vehicleCalculatePWM(delta_x, delta_y);//sqrt(delta_x^2 + delta_y^2);
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = (unsigned int)tempSqrt;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = (unsigned int)tempSqrt;
#ifndef VEHICLE_OCTAL_DIR_ENABLE
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = tempPWM;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = tempPWM;
#else
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = 0;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = 0;
#endif
    break;
    case VEHICLE_DIR_ROTATE_CW:
    case VEHICLE_DIR_ROTATE_CCW:
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_LEFT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_LEFT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_FRONT_RIGHT].pwm = delta_x;
     myWallE.vehicle.wheels[WHEEL_NUM_REAR_RIGHT].pwm = delta_x;
    break;
    default:
    break;
  }
  
  for(i=0;i<WHEEL_NUM_MAX;i++)
  {
#ifdef VEHICLE_BATT_VOLT_COMPENSATE
    // battery volt compensate
    if(batt.pCell[0].volt < 3700 || batt.pCell[1].volt < 3700) myWallE.vehicle.wheels[i].pwm = myWallE.vehicle.wheels[i].pwm*3/2;
#endif
    if(myWallE.vehicle.wheels[i].pwm >= 512) 
      myWallE.vehicle.wheels[i].pwm = 511;
    analogWrite(myWallE.vehicle.wheels[i].pin_enable, myWallE.vehicle.wheels[i].pwm);
  }
}


bool vehicleMove(uint16_t x, uint16_t y) {
  int i=0;
  uint16_t delta_x = 0, delta_y = 0;
  we_vehicle_dir vehicleDir = VEHICLE_DIR_MAX;
  
  boolean dir = false;
  
  
  // debounce
  if(x > VEHICLE_X_MID) {
    delta_x = x - VEHICLE_X_MID;
  } else {
    delta_x = VEHICLE_X_MID - x; 
  }
  if(y > VEHICLE_Y_MID) {
    delta_y = y - VEHICLE_Y_MID;
  } else {
    delta_y = VEHICLE_Y_MID - y; 
  }
  
  if((delta_x < VEHICLE_DIR_DELTA_DEBOUNCE) && (delta_y < VEHICLE_DIR_DELTA_DEBOUNCE) ) {
    for(i=0;i<WHEEL_NUM_MAX;i++)
    {
      analogWrite(myWallE.vehicle.wheels[i].pin_enable, 0);
    }
    return false;
  } 
 
  // parse vehicle direction
  if(delta_y < VEHICLE_DIR_DELTA_TOLERANCE) {
    if(X_LEFT(x)) {
      vehicleDir = VEHICLE_DIR_LEFT;
    } else {
      vehicleDir = VEHICLE_DIR_RIGHT;
    }
  }else if( Y_FORWARD(y)) {
    if(delta_x < VEHICLE_DIR_DELTA_TOLERANCE) {
      vehicleDir = VEHICLE_DIR_FORWARD;
    } else if(X_LEFT(x)) {
      vehicleDir = VEHICLE_DIR_FORWARD_LEFT;
    } else {
      vehicleDir = VEHICLE_DIR_FORWARD_RIGHT;
    }
  } else {
    if(delta_x < VEHICLE_DIR_DELTA_TOLERANCE) {
      vehicleDir = VEHICLE_DIR_BACKWARD;
    } else if(X_LEFT(x)) {
      vehicleDir = VEHICLE_DIR_BACKWARD_LEFT;
    } else {
      vehicleDir = VEHICLE_DIR_BACKWARD_RIGHT;
    }
  }
    
  vehicleSetWheelDir(vehicleDir, delta_x, delta_y);
#if 1
  delta_x /= 4;
  delta_y /= 4;
  if(delta_x >= 256) delta_x = 255;
  if(delta_y >= 256) delta_y = 255;
#else
  if(delta_x >= 512) delta_x = 511;
  if(delta_y >= 512) delta_y = 511;
#endif
  vehicleSetWheelPWM(vehicleDir, delta_x, delta_y);
  
  return true;

/*  simeple test
  if(delta_x < 10) {
    for(i=0;i<WHEEL_NUM_MAX;i++)
    {
      analogWrite(myWallE.vehicle.wheels[i].pin_enable, 0);
    }
    return;
  }
  // CW
  if(x > VEHICLE_X_MID) {
    dir = true;
  } else {
    dir = false;
  }
  
  for(i=0;i<WHEEL_NUM_MAX;i++)
  {
    if(dir)
    {
      digitalWrite(myWallE.vehicle.wheels[i].pin_cw, HIGH);
    }
    else
    {
      digitalWrite(myWallE.vehicle.wheels[i].pin_cw, LOW);
    }
    if(delta_x >= 512) delta_x = 511;
    analogWrite(myWallE.vehicle.wheels[i].pin_enable, delta_x/2);
  } 
 */  
}

static uint16_t vehicleRotatePWMCompensation(uint16_t pwm)
{
  return pwm*1/4;
}

bool vehicleRotate(uint16_t x)
{
  int i=0;
  uint16_t delta_x = 0;
  we_vehicle_dir dir = VEHICLE_DIR_MAX;
  
  // debounce
  if(x > VEHICLE_X_MID) {
    delta_x = x - VEHICLE_X_MID;
    dir = VEHICLE_DIR_ROTATE_CCW;
  } else {
    delta_x = VEHICLE_X_MID - x;
    dir = VEHICLE_DIR_ROTATE_CW;
  }
  
  if((delta_x < VEHICLE_DIR_DELTA_DEBOUNCE)) return false;
  
  // PWM compensation
  delta_x = vehicleRotatePWMCompensation(delta_x);
  
  vehicleSetWheelDir(dir, delta_x, 0);
  if(delta_x >= 256) delta_x = 255;
  vehicleSetWheelPWM(dir, delta_x, 0);
  
  return true;
}

// test interface
void vehicleTestWheelPWM(we_wheel_num wheel, we_wheel_dir dir, uint8_t pwm) {
  if(dir == WHEEL_DIR_CW) {
    digitalWrite(myWallE.vehicle.wheels[wheel].pin_cw, WHEEL_DIR_GPIO_LEVEL_CW);
    analogWrite(myWallE.vehicle.wheels[wheel].pin_enable, pwm);
  } else if(dir == WHEEL_DIR_CCW){
    digitalWrite(myWallE.vehicle.wheels[wheel].pin_cw, WHEEL_DIR_GPIO_LEVEL_CCW);
    analogWrite(myWallE.vehicle.wheels[wheel].pin_enable, pwm);
  } else {
    // do nothing
  }
}


void vehicleTestMove(we_vehicle_dir dir, uint16_t x, uint16_t y)
{
  vehicleSetWheelDir(dir, x, y);
  vehicleSetWheelPWM(dir, x, y);
}

