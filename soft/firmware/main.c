/*                      WARNINGS!
 *
 * при компиляции без -fomit-frame-pointer срывает стэк .
 */

// TODO: парсер времени GPS
// TODO: переписать нахуй этот пиздец с приемом-отправкой сообщений
// TODO: корректно погасить I2C датчики, присылающие данные без запросов
// TODO: последние удачные координаты в BKP
// TODO: обработчик прерывания по просадке питания (рассылка сообщения, возможно поток PwrHypervisor)
// TODO: добвить событий на сбои разных подсистем (gyro_failed, gps_failed, etc.)

// TODO: снять еще одну точку для датчика давления на 60 градусах цельсия и сделать табличную функцию термокомпенсации
// TODO: запись в лог делать из LinkOutThread ровно в 2 раза чаще, чем посылать телеметрию
// TODO: переделать модемный поток на DMA
// TODO: софтовыми часами тикать по секундному прерыванию от RTC
// TODO: синхронизация программных часов с аппаратными, аппаратных с GPS.
// TODO: сторожевой таймер с использованием памяти с батарейным питанием для расследования пиздецов

// Hardware
// TODO: один из таймеров использовать для тактирования гироскопа
// TODO: выход тахометра завести на один из таймеров

#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "param.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "adc_pns.h"
#include "timekeeping.h"
#include "linkmgr.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "autopilot.h"
#include "eeprom.h"
#include "eeprom_testsuit.h"
#include "exti_pns.h"
#include "storage.h"
#include "cli.h"
#include "imu.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
uint64_t TimeUsec;                    /* Timestamp (microseconds since UNIX epoch) */

uint32_t GlobalFlags = 0;             /* флаги на все случаи глобальной жизни */

RawData raw_data;                     /* структура с сырыми данными с датчиков */
CompensatedData comp_data;            /* обработанные данные */

uint32_t itg3200_period = 0;          /* время получения сэмплов с гироскопа (uS)*/
uint32_t imu_step = 0;                /* incremented on each call to imu_update */
float dcmEst[3][3] = {{1,0,0},{0,1,0},{0,0,1}};   /* estimated DCM matrix */

BinarySemaphore imu_sem;              /* семафор для синхронизации инерциалки и датчиков */
BinarySemaphore mag3110_sem;          /* синхронизация потока с прерыванием от датчика */
BinarySemaphore mma8451_sem;          /* синхронизация потока с прерыванием от датчика */
BinarySemaphore bmp085_sem;           /* синхронизация потока с прерыванием от датчика */
BinarySemaphore itg3200_sem;          /* синхронизация потока с прерыванием от датчика */

/* примонтированный файл EEPROM */
EepromFileStream EepromFile;

Mailbox autopilot_mb;                 /* сообщения для автопилота */
static msg_t autopilot_mb_buf[4];
Mailbox tolink_mb;                    /* сообщения для отправки через модем */
static msg_t tolink_mb_buf[10];
Mailbox toservo_mb;                   /* сообщения для обслуживателя серв */
static msg_t toservo_mb_buf[1];
Mailbox mavlink_param_set_mb;                     /* сообщения с параметрами */
static msg_t param_mb_buf[2];
Mailbox mavlink_command_long_mb;                /* сообщения с командами */
static msg_t mavlinkcmd_mb_buf[2];
Mailbox logwriter_mb;                 /* сообщения для писалки логов */
static msg_t logwriter_mb_buf[4];

/* переменные, касающиеся мавлинка */
mavlink_system_t            mavlink_system_struct;
mavlink_raw_pressure_t      mavlink_raw_pressure_struct;
mavlink_raw_imu_t           mavlink_raw_imu_struct;
mavlink_scaled_imu_t        mavlink_scaled_imu_struct;
mavlink_sys_status_t        mavlink_sys_status_struct;
mavlink_command_long_t      mavlink_command_long_struct;
mavlink_vfr_hud_t           mavlink_vfr_hud_struct; /* воздушная и земляная скорости */
mavlink_set_mode_t          mavlink_set_mode_struct;

/* heap for (link threads) OR (shell thread)*/
MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE + sizeof(stkalign_t)];

/* источник событий связанных с управлением питанием */
EventSource pwrmgmt_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */


int main(void) {
  halInit();
  chSysInit();
  chEvtInit(&pwrmgmt_event);

  chThdSleepMilliseconds(1);

  /* раздача питалова нуждающимся */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  // обнуление инкрементальных сумм
  comp_data.xgyro_angle = 0;
  comp_data.ygyro_angle = 0;
  comp_data.zgyro_angle = 0;

  /* примитивов синхронизации */
  chBSemInit(&imu_sem,      TRUE);
  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);

  /* инициализация почтовых ящиков */
  chMBInit(&autopilot_mb,     autopilot_mb_buf,       (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb,        tolink_mb_buf,          (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&toservo_mb,       toservo_mb_buf,         (sizeof(toservo_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_param_set_mb,         param_mb_buf,           (sizeof(param_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_command_long_mb,    mavlinkcmd_mb_buf,      (sizeof(mavlinkcmd_mb_buf)/sizeof(msg_t)));
  chMBInit(&logwriter_mb,     logwriter_mb_buf,       (sizeof(logwriter_mb_buf)/sizeof(msg_t)));

  /* инициализация кучи под потоки связи */
  chHeapInit(&LinkThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  /* первоначальная настройка мавлинка */
  mavlink_system_struct.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system_struct.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system_struct.type   = MAV_TYPE_FIXED_WING;
  mavlink_system_struct.state  = MAV_STATE_BOOT;
  mavlink_system_struct.mode   = MAV_MODE_PREFLIGHT;

  EepromOpen(&EepromFile);

  LinkMgrInit();
  SanityControlInit();
  ExtiInit(); /* I2C и RTC используют его */
  TimekeepingInit();
  I2CInit_pns();
//  eeprom_testsuit_run();
  ServoInit();
  ADCInit_pns();
  ImuInit();
  GPSInit();
  AutopilotInit();  /* автопилот должен стартовать только после установки связи */
  StorageInit();

  #if ENABLE_IRQ_STORM
    chThdSleepMilliseconds(5000);
    IRQStormInit();
  #endif /* ENABLE_IRQ_STORM */

  while (TRUE){
    chThdSleepMilliseconds(666);
    //chEvtBroadcastFlags(&pwrmgmt_event, EVENT_MASK(PWRMGMT_SIGHALT_EVID));
  }

  return 0;
}

