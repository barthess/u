#include "ch.h"
#include "hal.h"

#include "bkp.h"




void bkpInit(void){
  RCC->APB1ENR |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
  PWR->CR |= PWR_CR_DBP;
}

