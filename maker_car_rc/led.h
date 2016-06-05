#define LED_R 9
#define LED_G 5
#define LED_B 6

typedef enum {
  ENUM_LED_CH_R,
  ENUM_LED_CH_G,
  ENUM_LED_CH_B,
  ENUN_LED_CH_MAGENTA,
  ENUM_LED_CH_YELLOW,
  ENUM_LED_CH_CYAN,
  ENUM_LED_CH_WHITE,
  ENUM_LED_CH_OFF
} ENUM_LED_CH_t;

void setup_led(void);
void onLed(ENUM_LED_CH_t led);
void onLedErrorState(bool error, ENUM_LED_CH_t led);

