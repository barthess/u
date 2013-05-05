#ifndef MAIN_H_
#define MAIN_H_

/* chibios includes */
#include "ch.hpp"
#include "hal.h"

using namespace chibios_rt;

/* Heap size for dynamic thread creation */
#define THREAD_HEAP_SIZE    (1024 * 4)

/*******************************************************************
 * humanreadable names of serial drivers */
#define XBEESD    SD2
#define GPSSD     SD1

/******************************************************************
 * Disarm halting on panic and changing it to soft reset after this amount of time */
#define HALT_DISARM_TMO_SEC     30

/******************************************************************
 * use hardcoded value instead of measured */
#define GYRO_UPDATE_PERIOD_HARDCODED     TRUE

/******************************************************************
 * приоритеты для потоков */
#define I2C_THREADS_PRIO          (NORMALPRIO - 5)
#define TIMEKEEPER_THREAD_PRIO    (I2C_THREADS_PRIO - 1)
#define LINK_THREADS_PRIO         (NORMALPRIO - 5)
#define CONTROLLER_THREADS_PRIO   (NORMALPRIO)
#define CMD_THREADS_PRIO          (LINK_THREADS_PRIO - 2)
#define GPS_THREAD_PRIO           (NORMALPRIO - 2)

/******************************************************************
* статусы возвращаемые разными подсистемами */
#define PARAM_SUCCESS     CH_SUCCESS
#define PARAM_FAILED      CH_FAILED
#define MISSION_SUCCESS   CH_SUCCESS
#define MISSION_FAILED    CH_FAILED
#define LINK_SUCCESS      CH_SUCCESS
#define LINK_FAILED       CH_FAILED
#define TLM_SUCCESS       CH_SUCCESS
#define TLM_FAILED        CH_FAILED
#define WP_SUCCESS        CH_SUCCESS
#define WP_FAILED         CH_FAILED

/******************************************************************
* константы для мавлинка */
#define GROUND_STATION_ID   255


/* метка времени для пакетов */
#if (CH_FREQUENCY) >= 1000
#define TIME_BOOT_MS ((chTimeNow()) / ((CH_FREQUENCY) / 1000))
#endif

/******************************************************************
* дефайны для модема */
#define BAUDRATE_XBEE 115200
#define xbee_reset_assert() {palClearPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_reset_clear()  {palClearPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_sleep_assert() {palSetPad(GPIOE, GPIOE_XBEE_SLEEP);}
#define xbee_sleep_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}

/******************************************************************
* DCM helpers */
/*
 *       | Rxx Rxy Rxz |
 * DCM = | Ryx Ryy Ryz |
 *       | Rzx Rzy Rzz |
 */
#define DCM dcmEst /* our pseudonim */

#define Rxx (DCM[0][0])
#define Rxy (DCM[1][0])
#define Rxz (DCM[2][0])

#define Ryx (DCM[0][1])
#define Ryy (DCM[1][1])
#define Ryz (DCM[2][1])

#define Rzx (DCM[0][2])
#define Rzy (DCM[1][2])
#define Rzz (DCM[2][2])


/******************************************************************
* powering of 5 volt domain */
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
