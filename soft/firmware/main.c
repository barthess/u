/*                      WARNINGS!
 *
 * при компиляции без -fomit-frame-pointer срывает стэк .
 */

// TODO: выставка нуля магнитометра и акселя
// TODO: парсер времени GPS
// TODO: переписать нахуй этот пиздец с приемом-отправкой сообщений
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


#include "ch.h"
#include "hal.h"

#include "main.h"
#include "param.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "timekeeping.h"
#include "linkmgr.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "sensors.h"
#include "autopilot.h"
#include "eeprom.h"
#include "exti_pns.h"
#include "storage.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
uint64_t TimeUsec;                    /* Timestamp (microseconds since UNIX epoch) */
uint32_t GlobalFlags = 0;             /* флаги на все случаи глобальной жизни */

/* примонтированный файл EEPROM */
EepromFileStream EepromFile;

/* heap for (link threads) OR (shell thread)*/
MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE + sizeof(stkalign_t)];

/* источник событий связанных с управлением питанием */
EventSource pwrmgmt_event;
EventSource modem_event;

/* указатель на Idle поток. Оттуда мы будем брать данные для расчета загрузки проца */
Thread *IdleThread_p = NULL;

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
  IdleThread_p = chSysInit();

  chEvtInit(&pwrmgmt_event);
  chEvtInit(&modem_event);

  chThdSleepMilliseconds(1);

  /* раздача питалова нуждающимся */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  /* инициализация кучи под потоки связи */
  chHeapInit(&LinkThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  EepromOpen(&EepromFile);

  LinkMgrInit();
  MsgInit();
  SanityControlInit();
  TimekeepingInit();
  I2CInit_pns(); /* also starts EEPROM and load global parameters from it */
  SensorsInit(); /* uses I2C */
  ServoInit();
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

