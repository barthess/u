/*                      WARNINGS!
 *
 * cmpilation without -fomit-frame-pointer cause stack overflows.
 */

// TODO: PID
// TODO: combine barometer and accelerometer in one filter.
// TODO: Magnetometer fusion with DCM, not accelerometer.
// TODO: (semi)automated zeroing of magnetometer and accelerometer.
// TODO: Rewrite messaging holy crap.
// TODO: Power brown out handler for sync/umout SDC.
// TODO: Events on differnt subsystems failures (gyro_failed, gps_failed, etc.)
// TODO: One more point in dynamic pressure thermal compensation algorith (at 60 celsius)
// TODO: Rewrite XBee code for use DMA.
// TODO: WDT with backup domain for fuckups investigation.

#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
/* RTC-GPS sync */
BinarySemaphore rtc_sem;

/* store here time from GPS */
struct tm gps_timp;

/* pointer to "timezone" value. Initialized in timekeeping.c */
int32_t *timezone = NULL;

/* some global flags */
uint32_t GlobalFlags = 0;

/* EEPROM "file" */
EepromFileStream EepromFile;

/* heap for link threads OR shell thread */
MemoryHeap ThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE + sizeof(stkalign_t)];

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

  chBSemInit(&rtc_sem, TRUE);

  chThdSleepMilliseconds(200);

  /* give power to all needys */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  chHeapInit(&ThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  EepromOpen(&EepromFile);

  MsgInit();
  SanityControlInit();
  I2CInitLocal(); /* also starts EEPROM and load global parameters from it */
  LinkMgrInit();
  TimekeepingInit();
  MavInit();      /* mavlink constants initialization must be called after I2C init */
  SensorsInit();  /* sensors use I2C */
  GncInit();
  TlmSenderInit();
  ServoInit();
  AutopilotInit();  /* autopilot must be started only after servos */
  StorageInit();

  while (TRUE){
    chThdSleepMilliseconds(666);
  }

  return 0;
}

