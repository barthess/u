#ifndef MAIN_H_
#define MAIN_H_

/* chibios includes */
#include "ch.h"
#include "hal.h"

/* mavlink includes */
#include "mavlink.h"

/* uav includes */
#include "adc_local.h"
#include "airspeed.h"
#include "bkp.h"
#include "bmp085.h"
#include "cli.h"
#include "cli_cal.h"
#include "cli_cmd.h"
#include "controller.h"
#include "dcm_cli.h"
#include "dsp.h"
#include "eeprom.h"
#include "eeprom_conf.h"
#include "exti_local.h"
#include "fixed_wing.h"
#include "geometry.h"
#include "gps.h"
#include "ground_rover.h"
#include "gyro_cal.h"
#include "i2c_local.h"
#include "imu.h"
#include "irq_storm.h"
#include "itg3200.h"
#include "linkmgr.h"
#include "link.h"
#include "logger.h"
#include "mag3110.h"
#include "mag_cal.h"
#include "mavcmd_local.h"
#include "mavlink_dbg.h"
#include "max1236.h"
#include "memfunc.h"
#include "message.h"
#include "microsd.h"
#include "misc_math.h"
#include "mma8451.h"
#include "param.h"
#include "param_cli.h"
#include "param_persistant.h"
#include "pid.h"
#include "planner.h"
#include "pwr_mgmt.h"
#include "sanity.h"
#include "sensors.h"
#include "sensors_cli.h"
#include "servo.h"
#include "servo_cli.h"
#include "speedometer.h"
#include "sphere.h"
#include "stab.h"
#include "timekeeping.h"
#include "tlm_sender.h"
#include "tmp75.h"
#include "wp.h"
#include "wp_global.h"
#include "wp_local.h"
#include "wps.h"
#include "wps_cli.h"
#include "wps_persistant.h"

#define PI          3.14159265f

/* Heap size for dynamic thread creation */
#define THREAD_HEAP_SIZE    (1024 * 5)

/*******************************************************************
 * humanreadable names of serial drivers */
#define LINKSD  SD2
#define GPSSD   SD1
#define SHELLSD LINKSD

/******************************************************************
 * Disarm halting on panic and changing it to soft reset after this amount of time */
#define HALT_DISARM_TMO_SEC     30

/******************************************************************
 * use hardcoded value instead of measured */
#define GYRO_UPDATE_PERIOD_HARDCODED     TRUE

/******************************************************************
 * приоритеты для потоков */
#define I2C_THREADS_PRIO          (NORMALPRIO + 5)
#define GYRO_THREADS_PRIO         (I2C_THREADS_PRIO + 2)
#define TIMEKEEPER_THREAD_PRIO    (I2C_THREADS_PRIO - 1)
#define LINK_THREADS_PRIO         (NORMALPRIO - 5)
#define CONTROLLER_THREADS_PRIO   (NORMALPRIO)
#define CMD_THREADS_PRIO          (LINK_THREADS_PRIO - 2)
#define GPS_THREAD_PRIO           (NORMALPRIO - 2)


/******************************************************************
 * global bool flags */
typedef struct GlobalFlags_t{
  //0
  uint32_t allow_softreset:1; /* system performs soft reset instead of halting in panic */
  uint32_t gyro_cal:1;
  uint32_t accel_cal:1;
  uint32_t mag_cal:1;
  //4
  uint32_t eeprom_failed:1;
  uint32_t tlm_link_ready:1;
  uint32_t modem_ready:1;
  uint32_t logger_ready:1;
  //8
  uint32_t sighalt:1;
  uint32_t mag_data_ready:1;
  uint32_t mission_takeoff:1;
  uint32_t mission_loiter:1;
  //12
  uint32_t mission_abort:1;
  uint32_t parameters_got:1;  /* parameters successfully retrieved from EEPROM */
  uint32_t i2c_ready:1;       /* i2c bus initialized */
  uint32_t messaging_ready:1;
  //16
  uint32_t stub4:1;
  uint32_t stub5:1;
  uint32_t stub6:1;
  uint32_t stub7:1;
  //20
  uint32_t stub8:1;
  uint32_t stub9:1;
  uint32_t stuba:1;
  uint32_t stubb:1;
  //24
  uint32_t stubc:1;
  uint32_t stubd:1;
  uint32_t stube:1;
  uint32_t stubf:1;
  //28
  uint32_t stubg:1;
  uint32_t stubh:1;
  uint32_t stubi:1;
  uint32_t stubj:1;
}GlobalFlags_t;

//
#define setGlobalFlagI(flag)    do{chDbgCheckClassI(); flag = 1;}while(0)
#define clearGlobalFlagI(flag)  do{chDbgCheckClassI(); flag = 0;}while(0)

#define setGlobalFlag(flag)     do{chSysLock(); setGlobalFlagI(flag);   chSysUnlock();}while(0)
#define clearGlobalFlag(flag)   do{chSysLock(); clearGlobalFlagI(flag); chSysUnlock();}while(0)

/******************************************************************/
/* "init daemon" events */
//#define MODEM_READY_EVID    1
//#define LOGGER_READY_EVID   2
//#define I2C_READY_EVID      3
//#define EEPROM_MOUNTED_EVID 4
//#define PARAMETERS_GOT_EVID 5
//#define SIGHALT_EVID        6   /* при наступлении данного события все подсистемы должны себя корректно остановить */
//#define POWERFAILE_EVID     7   /* означает критическую просадку напряжения */
//#define MODEM_FAILED        8
//#define LOGGER_FAILED       9
//#define TLM_LINK_UP_EVID    10
//#define TLM_LINK_DOWN_EVID  11
//#define INIT_FAKE_EVID      31


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

/* region for settings file */
#define EEPROM_SETTINGS_START         8192
#define EEPROM_SETTINGS_SIZE          4096
#define EEPROM_SETTINGS_END           (EEPROM_SETTINGS_START + EEPROM_SETTINGS_SIZE)

/* region for waypoints file */
#define EEPROM_MISSION_WP_CNT_OFFSET  EEPROM_SETTINGS_END
/* size in byte of waypoint count variable */
#define EEPROM_MISSION_WP_CNT_SIZE    2
/* actual waypoints offset */
#define EEPROM_MISSION_START          (EEPROM_MISSION_WP_CNT_OFFSET + EEPROM_MISSION_WP_CNT_SIZE)
#define EEPROM_MISSION_SIZE           (8192 - EEPROM_MISSION_WP_CNT_SIZE)
#define EEPROM_MISSION_END            (EEPROM_MISSION_START + EEPROM_MISSION_SIZE)

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
