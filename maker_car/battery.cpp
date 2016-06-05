#include <Arduino.h>
#include "battery.h"
/*
stBattCell battCell[2] = {
  {A6, 0, ENUM_BATT_VOLT_NORMAL},
  {A7, 0, ENUM_BATT_VOLT_NORMAL}
};

stBatt batt = {
  2,
  ENUM_BATT_VOLT_3_0_V,
  ENUM_BATT_VOLT_3_2_V,
  battCell
};
*/
void setup_batt(stBatt* pBatt) {
  uint8_t i = 0;
  
  for(i=0;i<pBatt->cellNum;i++) {
    pinMode(pBatt->pCell[i].adcPin, INPUT);
  }
}

enumBattAdcStatue get_batt(stBatt* pBatt) {
  uint8_t i = 0;
  uint8_t battStatus = 0;
  
  for(i=0;i<pBatt->cellNum;i++) {
    pBatt->pCell[i].adcValue = analogRead(pBatt->pCell[i].adcPin);
    //
    //if(i!=0) pBatt->pCell[i-1].adcValue = pBatt->pCell[i-1].adcValue - pBatt->pCell[i].adcValue;
    if(i!=0) pBatt->pCell[i].adcValue = pBatt->pCell[i].adcValue - pBatt->pCell[i-1].adcValue;
    // calculate voltage
    pBatt->pCell[i].volt = BattAdc2Volt(pBatt->pCell[i].adcValue);
    // determine battery status
    if(pBatt->pCell[i].volt < pBatt->voltError) {
      pBatt->pCell[i].voltStatus = ENUM_BATT_VOLT_ERROR;
      battStatus |= (uint8_t)ENUM_BATT_VOLT_ERROR;
    } else if(pBatt->pCell[i].volt < pBatt->voltWarn) {
      pBatt->pCell[i].voltStatus = ENUM_BATT_VOLT_WARN;
      battStatus |= (uint8_t)ENUM_BATT_VOLT_WARN;
    }
  }
  
  if(battStatus > ENUM_BATT_VOLT_ERROR) pBatt->Status = ENUM_BATT_VOLT_ERROR;
  else pBatt->Status = (enumBattAdcStatue)battStatus;
  

}
