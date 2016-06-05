#define LED_R A4
#define LED_G 4
#define LED_B A5

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

