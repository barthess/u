#ifndef MAIN_H_
#define MAIN_H_

/******************************************************************
 * глобальные битовые флаги
 ******************************************************************/
#define GYRO_CAL  (1UL << 0)  /* если установлен в единицу, значит идет выставка гироскопов */
#define ACCEL_CAL (1UL << 1)  /* если установлен в единицу, значит идет выставка акселерометров */

/******************************************************************
 * глобальные дефайны
 ******************************************************************/
/* надо ли фильтровать данные с датчиков */
#define GET_FILTERED_DATA   TRUE

/* включить стрессовое тестирование */
#define ENABLE_IRQ_STORM    FALSE

/* тут можно отключить обработку GPS, чтобы освободить один SERIAL для консоли */
#define ENABLE_GPS          FALSE

/* использовать xbee API вместо MAVLink */
#define LINK_USE_XBEE_API   TRUE

#define pwr5v_power_on()  {palSetPad(GPIOA, GPIOA_5V_DOMAIN_EN);}
#define pwr5v_power_off() {palClearPad(GPIOA, GPIOA_5V_DOMAIN_EN);}

// usefull macros

/* stop watchdog timer in debugging mode */
/*unlock PR register*/
/*set 1.6384s timeout*/
/*start watchdog*/
#define WATCHDOG_INIT {\
    DBGMCU->CR |= DBGMCU_CR_DBG_IWDG_STOP;\
    IWDG->KR = 0x5555;\
    IWDG->PR = 16;\
    IWDG->KR = 0xCCCC;}

#define WATCHDOG_RELOAD {IWDG->KR = 0xAAAA;}


#endif /* MAIN_H_ */
