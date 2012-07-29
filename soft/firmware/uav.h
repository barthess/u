#ifndef MAIN_H_
#define MAIN_H_

#include "ch.h"
#include "hal.h"

#include "airspeed.h"
#include "autopilot.h"
#include "bkp.h"
#include "bmp085.h"
#include "cli.h"
#include "cli_cmd.h"
#include "dsp.h"
#include "eeprom.h"
#include "exti_local.h"
#include "gnc.h"
#include "gps.h"
#include "i2c_local.h"
#include "irq_storm.h"
#include "itg3200.h"
#include "linkmgr.h"
#include "link.h"
#include "logger.h"
#include "mag3110.h"
#include "max1236.h"
#include "message.h"
#include "microsd.h"
#include "mma8451.h"
#include "param.h"
#include "param_cli.h"
#include "persistant.h"
#include "sanity.h"
#include "sensors.h"
#include "servo.h"
#include "timekeeping.h"
#include "tlm_sender.h"
#include "tmp75.h"
#include "utils.h"

#include "mavlink.h"
#include "common.h"

/******************************************************************
 * humanreadable names of serial drivers */
#define LINKSD  SD2
#define GPSSD   SD1
#define SHELLSD LINKSD


/******************************************************************
 * приоритеты для потоков */
#define I2C_THREADS_PRIO          (NORMALPRIO + 5)
#define TIMEKEEPER_THREAD_PRIO    (I2C_THREADS_PRIO - 1)
#define LINK_THREADS_PRIO         (NORMALPRIO - 5)
#define CMD_THREADS_PRIO          (LINK_THREADS_PRIO - 2)
#define GPS_THREAD_PRIO           (NORMALPRIO - 2)


/******************************************************************
 * глобальные битовые флаги */
#define GYRO_CAL_FLAG        (1UL << 0)  /* если установлен в единицу, значит идет выставка гироскопов */
#define ACCEL_CAL_FLAG       (1UL << 1)  /* если установлен в единицу, значит идет выставка акселерометров */
#define MAG_CAL_FLAG         (1UL << 2)  /* если установлен в единицу, значит идет выставка магнитометра */
#define EEPROM_FAILED_FLAG   (1UL << 3)  /* единица означает сбой в EEPROM */
#define POSTAGE_FAILED_FLAG  (1UL << 4)  /* Сбой в системе отправки сообщений */
#define I2C_RESTARTED_FLAG   (1UL << 5)  /* I2C шина была перезапущена из-за проблем */

#define setGlobalFlag(flag)   {chSysLock(); GlobalFlags |= (flag); chSysUnlock();}
#define clearGlobalFlag(flag) {chSysLock(); GlobalFlags &= (~(flag)); chSysUnlock();}


/******************************************************************/
/* "init daemon" events */
#define MODEM_READY_EVID    1
#define LOGGER_READY_EVID   2
#define I2C_READY_EVID      3
#define EEPROM_MOUNTED_EVID 4
#define PARAMETERS_GOT_EVID 5
/* при наступлении данного события все подсистемы должны себя корректно остановить */
#define SIGHALT_EVID        6
/* означает критическую просадку напряжения */
#define POWERFAILE_EVID     7
#define MODEM_FAILED        8
#define LOGGER_FAILED       9
#define INIT_FAKE_EVID      31

/******************************************************************
* статусы возвращаемые разными подсистемами */
#define PARAM_SUCCESS  CH_SUCCESS
#define PARAM_FAILED   CH_FAILED
#define LINK_SUCCESS   CH_SUCCESS
#define LINK_FAILED    CH_FAILED
#define TLM_SUCCESS    CH_SUCCESS
#define TLM_FAILED     CH_FAILED

/******************************************************************
* константы для мавлинка */
#define GROUND_STATION_ID   255


/* метка времени для пакетов */
#if (CH_FREQUENCY) >= 1000
#define TIME_BOOT_MS ((chTimeNow()) / ((CH_FREQUENCY) / 1000))
#endif


/******************************************************************
* data offsets in eeprom "file" */
#define EEPROM_SETTINGS_START    8192
#define EEPROM_SETTINGS_SIZE     4096
#define EEPROM_SETTINGS_FINISH   (EEPROM_SETTINGS_START + EEPROM_SETTINGS_SIZE)


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
* функции включения питания в 5-вольтовом домене */
#define pwr5v_power_on()  {palSetPad(GPIOA, GPIOA_5V_DOMAIN_EN);}
#define pwr5v_power_off() {palClearPad(GPIOA, GPIOA_5V_DOMAIN_EN);}


/* включить стрессовое тестирование */
#define ENABLE_IRQ_STORM    FALSE

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
