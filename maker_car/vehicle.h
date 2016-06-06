
#define WHEEL_DIR_GPIO_LEVEL_CW LOW
#define WHEEL_DIR_GPIO_LEVEL_CCW HIGH

typedef struct {
  boolean enable;
  boolean dir; // direction, 0: CW, 1: CCW
  unsigned int pin_enable; // GPIO pin used for wheel ratation PWM
  unsigned int pin_cw; // GPIO pin used for clockwise
  unsigned int pwm;
} we_wheels;

typedef enum {
 WHEEL_NUM_FRONT_LEFT,
 WHEEL_NUM_REAR_LEFT,
 WHEEL_NUM_FRONT_RIGHT,
 WHEEL_NUM_REAR_RIGHT,
 WHEEL_NUM_MAX
} we_wheel_num;


typedef enum {
  WHEEL_DIR_CW = 0,
  WHEEL_DIR_CCW,
  WHEEL_DIR_FREEZE
} we_wheel_dir;

// (FRONT_LEFT, REAR_LEFT, FRONT_RIGHT, REAT_RIGHT)
#define WHEEL_DIR_ARRAY_FORWARD {WHEEL_DIR_CCW, WHEEL_DIR_CCW, WHEEL_DIR_CW, WHEEL_DIR_CW}
#define WHEEL_DIR_ARRAY_FORWARD_LEFT {WHEEL_DIR_CCW, WHEEL_DIR_FREEZE, WHEEL_DIR_FREEZE, WHEEL_DIR_CW}
#define WHEEL_DIR_ARRAY_LEFT {WHEEL_DIR_CCW, WHEEL_DIR_CW, WHEEL_DIR_CCW, WHEEL_DIR_CW}
#define WHEEL_DIR_ARRAY_BACKWARD_LEFT {WHEEL_DIR_FREEZE, WHEEL_DIR_CW, WHEEL_DIR_CCW, WHEEL_DIR_FREEZE}
#define WHEEL_DIR_ARRAY_BACKWARD {WHEEL_DIR_CW, WHEEL_DIR_CW, WHEEL_DIR_CCW, WHEEL_DIR_CCW}
#define WHEEL_DIR_ARRAY_BACKWARD_RIGHT {WHEEL_DIR_CW, WHEEL_DIR_FREEZE, WHEEL_DIR_FREEZE, WHEEL_DIR_CCW}
#define WHEEL_DIR_ARRAY_RIGHT {WHEEL_DIR_CW, WHEEL_DIR_CCW, WHEEL_DIR_CW, WHEEL_DIR_CCW}
#define WHEEL_DIR_ARRAY_FORWARD_RIGHT {WHEEL_DIR_FREEZE, WHEEL_DIR_CCW, WHEEL_DIR_CW, WHEEL_DIR_FREEZE}

#define WHEEL_DIR_ARRAY_ROTATE_CW {WHEEL_DIR_CCW, WHEEL_DIR_CCW, WHEEL_DIR_CCW, WHEEL_DIR_CCW}
#define WHEEL_DIR_ARRAY_ROTATE_CCW {WHEEL_DIR_CW, WHEEL_DIR_CW, WHEEL_DIR_CW, WHEEL_DIR_CW}

typedef enum {
  VEHICLE_DIR_FORWARD = 0,
  VEHICLE_DIR_FORWARD_LEFT,
  VEHICLE_DIR_LEFT,
  VEHICLE_DIR_BACKWARD_LEFT,
  VEHICLE_DIR_BACKWARD, 
  VEHICLE_DIR_BACKWARD_RIGHT,
  VEHICLE_DIR_RIGHT,
  VEHICLE_DIR_FORWARD_RIGHT,
  VEHICLE_DIR_ROTATE_CW,
  VEHICLE_DIR_ROTATE_CCW,
  VEHICLE_DIR_MAX
} we_vehicle_dir;

typedef struct {
  we_wheels wheels[WHEEL_NUM_MAX];
} we_vehicle;

typedef struct {
  
} we_remote;

typedef struct {
  
} we_sensors;

typedef struct {
  we_vehicle vehicle;
  we_remote remote;
  we_sensors sensors;
} wallE;

void setup_vehicle();
bool vehicleMove(uint16_t x, uint16_t y);
bool vehicleRotate(uint16_t x);

// test interface
void vehicleTestWheelPWM(we_wheel_num wheel, we_wheel_dir dir, uint8_t pwm);
void vehicleTestMove(we_vehicle_dir dir, uint16_t x, uint16_t y);
void carMove(uint16_t x, uint16_t y);