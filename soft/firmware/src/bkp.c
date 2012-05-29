#include "ch.h"
#include "hal.h"

#include "bkp.h"


void bkpSaveGpsLongitude(uint32_t n){
  RTC->BKP0R = n;
}
uint32_t bkpLoadGpsLongitude(void){
  return RTC->BKP0R;
}

void bkpSaveGpsLatitude(uint32_t n){
  RTC->BKP1R = n;
}
uint32_t bkpLoadGpsLatitude(void){
  return RTC->BKP1R;
}

void bkpSaveGpsAltitude(uint32_t n){
  RTC->BKP2R = n;
}
uint32_t bkpLoadGpsAltitude(void){
  return RTC->BKP2R;
}

