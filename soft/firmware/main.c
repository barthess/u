/*                      WARNINGS!
 *
 * при компил€ции без -fomit-frame-pointer срывает стэк .
 */

// TODO: выставка нул€ магнитометра и аксел€
// TODO: парсер времени GPS
// TODO: переписать нахуй этот пиздец с приемом-отправкой сообщений
// TODO: последние удачные координаты в BKP
// TODO: обработчик прерывани€ по просадке питани€ (рассылка сообщени€, возможно поток PwrHypervisor)
// TODO: добвить событий на сбои разных подсистем (gyro_failed, gps_failed, etc.)

// TODO: сн€ть еще одну точку дл€ датчика давлени€ на 60 градусах цельси€ и сделать табличную функцию термокомпенсации
// TODO: запись в лог делать из LinkOutThread ровно в 2 раза чаще, чем посылать телеметрию
// TODO: переделать модемный поток на DMA
// TODO: софтовыми часами тикать по секундному прерыванию от RTC
// TODO: синхронизаци€ программных часов с аппаратными, аппаратных с GPS.
// TODO: сторожевой таймер с использованием пам€ти с батарейным питанием дл€ расследовани€ пиздецов

// Hardware
// TODO: один из таймеров использовать дл€ тактировани€ гироскопа


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

/* источник событий св€занных с управлением питанием */
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

  /* раздача питалова нуждающимс€ */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  /* инициализаци€ кучи под потоки св€зи */
  chHeapInit(&LinkThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  EepromOpen(&EepromFile);

  LinkMgrInit();
  MsgInit();
  SanityControlInit();
  TimekeepingInit();
  I2CInit_pns(); /* also starts EEPROM and load global parameters from it */
  SensorsInit(); /* uses I2C */
  ServoInit();
  AutopilotInit();  /* автопилот должен стартовать только после установки св€зи */
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

