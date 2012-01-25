/*                      WARNINGS!
 *
 * при компиляции без -fomit-frame-pointer срывает стэк .
 */

// TODO: сохранение и вычитка калибровочных коэффициетов для АЦП и ПВД
// TODO: загрузка/чтение точек маршрута
// TODO: сторожевой таймер с использованием памяти с батарейным питанием для расследования пиздецов
// TODO: менеджер в main(), который регулярно опрашивает все процессы на предмет жизнеспособности

#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "adc_pns.h"
#include "rtc_pns.h"
#include "link.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "autopilot.h"
#include "bkp.h"
#include "eeprom.h"
#include "exti_pns.h"
#include "storage.h"
#include "cli.h"
#include "imu.h"

#include <mavlink.h>
#include <common.h>
#include <bart.h>

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

//RTCTime  timespec;                    /* тут будет храниться время. Обновлять вручную. */

uint32_t GlobalFlags = 0;             /* флаги на все случаи глобальной жизни */

RawData raw_data;                     /* структура с сырыми данными с датчиков */
LogItem log_item;                     /* структура, содержащая запись для лога */

BinarySemaphore link_thd_sem;         /* семафор для синхронизации сеансов связи */
BinarySemaphore imu_sem;              /* семафор для синхронизации инерциалки и АЦП */

BinarySemaphore mag3110_sem;
BinarySemaphore mma8451_sem;
BinarySemaphore bmp085_sem;
BinarySemaphore itg3200_sem;

Mailbox autopilot_mb;                 /* сообщения для автопилота */
static msg_t autopilot_mb_buf[4];

Mailbox tolink_mb;                    /* сообщения для отправки через модем */
static msg_t tolink_mb_buf[8];

/** Переменные для хранения калибровочных данных */
volatile uint16_t cal_CurrentCoeff;   /* коэффициент пересчета из условных единиц в амперы. Для саломёта -- 37, для машинки  -- 1912 */
volatile uint8_t  cal_CurrentOffset;  /* смещение нуля датчика тока в единицах АЦП */
volatile uint16_t cal_VoltageCoeff;   /* коэффициент пересчета из условных единиц в децывольты */

mavlink_system_t mavlink_system;

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

/* Red LEDs blinker thread. */
//static WORKING_AREA(waBlink, 128);
//static msg_t Blink(void *arg) {
//  chRegSetThreadName("Blink");
//  (void)arg;
//  while (TRUE) {
//    palClearPad(IOPORT3, GPIOC_LED);
//    chThdSleepMilliseconds(500);
//    palSetPad(IOPORT3, GPIOC_LED);
//    chThdSleepMilliseconds(500);
//  }
//  return 0;
//}


int main(void) {
  halInit();
  chSysInit();

  // обнуление инкрементальных сумм
  raw_data.gyro_xI = 0;
  raw_data.gyro_yI = 0;
  raw_data.gyro_zI = 0;

  // Creates the blinker thread.
  //chThdCreateStatic(waBlink, sizeof(waBlink), LOWPRIO, Blink, NULL);

  /* примитивов синхронизации */
  chBSemInit(&link_thd_sem, TRUE);
  chBSemInit(&imu_sem,      TRUE);
  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);

  /* очереди сообщений */
  chMBInit(&autopilot_mb, autopilot_mb_buf, (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb, tolink_mb_buf, (sizeof(tolink_mb_buf)/sizeof(msg_t)));

  /* первоначальная настройка мавлинка */
  mavlink_system.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system.compid = MAV_COMP_ID_IMU;     ///< The component sending the message is the IMU, it could be also a Linux process
  mavlink_system.type   = MAV_TYPE_FIXED_WING;   ///< This system is an airplane / fixed wing

  /* раздача питалова нуждающимся */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();
  chThdSleepMilliseconds(50);

  ExtiInit(); /* I2C датчики используют его */
  I2CInit_pns();    /* Должно идти пораньше, т.к. через него читаются настройки из EEPROM */
//  RtcPnsInit();
  ServoInit();
  CliInit();
  ADCInit_pns();
//  ImuInit();
  GPSInit();
  LinkInit();
//  AutopilotInit();  /* автопилот должен стартовать только после установки связи */
  StorageInit();

  #if ENABLE_IRQ_STORM
    chThdSleepMilliseconds(5000);
    IRQStormInit();
  #endif /* ENABLE_IRQ_STORM */

  while (TRUE){
    chThdSleepMilliseconds(200);
    palTogglePad(GPIOB, GPIOB_LED_R);
  }

  return 0;
}

