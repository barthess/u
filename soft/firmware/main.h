#ifndef MAIN_H_
#define MAIN_H_


/******************************************************************
 * групповые приоритеты для потоков
 ******************************************************************/
#define I2C_THREADS_PRIO   (NORMALPRIO + 5)
#define LINK_THREADS_PRIO  (NORMALPRIO - 5)


/******************************************************************
 * глобальные битовые флаги
 ******************************************************************/
#define GYRO_CAL        (1UL << 0)  /* если установлен в единицу, значит идет выставка гироскопов */
#define ACCEL_CAL       (1UL << 1)  /* если установлен в единицу, значит идет выставка акселерометров */
#define MAG_CAL         (1UL << 2)  /* если установлен в единицу, значит идет выставка магнитометра */
#define EEPROM_FAILED   (1UL << 3)  /* единица означает сбой в EEPROM */
#define POSTAGE_FAILED  (1UL << 4)  /* Сбой в системе отправки сообщений */
#define I2C_RESTARTED   (1UL << 5)  /* I2C шина была перезапущена из-за проблем */

#define setGlobalFlag(flag)   {chSysLock(); GlobalFlags |= (flag); chSysUnlock();}
#define clearGlobalFlag(flag) {chSysLock(); GlobalFlags &= (~(flag)); chSysUnlock();}

/******************************************************************
 * глобальные дефайны
 ******************************************************************/

#define SUCCESS   FALSE
#define FAILED    TRUE

#define GROUND_STATION_ID   255

/* максимальная скорость модема даже слегка недостаточна - пакеты все равно не
 * все приходят из-за внутренних задержек */
#define BAUDRATE_XBEE 115200
#define xbee_reset_assert() {palClearPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_reset_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_sleep_assert() {palClearPad(GPIOE, GPIOE_XBEE_SLEEP);}
#define xbee_sleep_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}

/* включить стрессовое тестирование */
#define ENABLE_IRQ_STORM    FALSE

#define pwr5v_power_on()  {palSetPad(GPIOA, GPIOA_5V_DOMAIN_EN);}
#define pwr5v_power_off() {palClearPad(GPIOA, GPIOA_5V_DOMAIN_EN);}


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
