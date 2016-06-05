#define BATT_CELL_NUM 2

#define BATT_CELL_VOLT_MAX 5000 // 5V, 5000mV
#define BATT_CELL_VOLT_ADC_MAX 1023

#define BattAdc2Volt(adc) (((uint32_t)adc*2*5000)/1023)

#define BATT_CELL_VOLT_3_7_V 379 // 4.7V
#define BATT_CELL_VOLT_3_0_V 307  // 3.0V
#define BATT_CELL_VOLT_0_1_V 2
/*
typedef enum {
  ENUM_BATT_VOLT_3_0_V = 0,
  ENUM_BATT_VOLT_3_1_V,
  ENUM_BATT_VOLT_3_2_V,
  ENUM_BATT_VOLT_3_3_V,
  ENUM_BATT_VOLT_3_4_V,  
  ENUM_BATT_VOLT_3_5_V,
  ENUM_BATT_VOLT_3_6_V,
  ENUM_BATT_VOLT_3_7_V,
  ENUM_BATT_VOLT_3_8_V,
  ENUM_BATT_VOLT_3_9_V,
  ENUM_BATT_VOLT_4_0_V,
  ENUM_BATT_VOLT_4_1_V,
  ENUM_BATT_VOLT_4_2_V
} enumBattVolLevel;
*/
typedef enum {
  ENUM_BATT_VOLT_NORMAL = 0,
  ENUM_BATT_VOLT_WARN, 
  ENUM_BATT_VOLT_ERROR
} enumBattAdcStatue;

typedef struct {
  uint8_t adcPin;
  uint16_t adcValue;
  uint16_t volt;
  enumBattAdcStatue voltStatus;
} stBattCell;

typedef struct {
  uint8_t cellNum;
//  enumBattVolLevel adcValueWarn;
//  enumBattVolLevel adcValueError;  
  uint16_t voltWarn;
  uint16_t voltError;
  enumBattAdcStatue Status;
  stBattCell* pCell;
} stBatt;

void setup_batt(stBatt* pBatt);
enumBattAdcStatue get_batt(stBatt* pBatt);
