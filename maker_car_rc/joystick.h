// Left joy stick (x, y)
#define JOY_STICK_LEFT_X_PIN A1
#define JOY_STICK_LEFT_Y_PIN A0
// Right joy stick (x, y)
#define JOY_STICK_RIGHT_X_PIN A3
#define JOY_STICK_RIGHT_Y_PIN A2
// buttons
#define JOY_STICK_BUTTON_PIN_0 3 // Left js button
#define JOY_STICK_BUTTON_PIN_1 2 // Right js button


typedef enum {
  E_JOY_STICK_CH_LEFT_X = 0,
  E_JOY_STICK_CH_LEFT_Y,
  E_JOY_STICK_CH_RIGHT_X,
  E_JOY_STICK_CH_RIGHT_Y
} E_JOY_STICK_CHANNEL;

typedef enum {
  E_JOY_STICK_BTN_0 = 0,
  E_JOY_STICK_BTN_1,
  E_JOY_STICK_BTN_2
} E_JOY_STICK_BUTTON;

void setup_joystick(void);
uint16_t read_joystick(E_JOY_STICK_CHANNEL ch);
bool read_button(E_JOY_STICK_BUTTON);

