#include <time.h>
#include <stdlib.h>

#include "uav.h"
#include "chrtclib.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern int32_t *timezone;
extern BinarySemaphore rtc_sem;
extern struct tm gps_timp;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* Boot timestamp (microseconds since UNIX epoch). Inits in boot time. Latter
 * uses to calculate current time using TIME_BOOT_MS. Periodically synced with
 * GPS to correct systick drift */
static int64_t BootTimestamp = 0;

/* Можно вносить поправку прямо в метку времени, но точное время запуска
 * может понадобиться позднее, поэтому заведем отдельную переменную */
static int64_t Correction = 0;

/* количество переполнений системного таймера. Фактически для программного
 * расширения разрядности счетчика на 32 бита */
static uint32_t WrapCount = 0;

/* последнее значение счетчика для отлова момента переполнения */
static uint32_t LastTimeBootMs = 0;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static WORKING_AREA(TimekeeperThreadWA, 512);
static msg_t TimekeeperThread(void *arg){
  chRegSetThreadName("Timekeeper");
  (void)arg;

  int64_t  gps_time = 0;
  int64_t  pns_time = 0;

  msg_t sem_status = RDY_RESET;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&rtc_sem, MS2ST(2000));
    if (sem_status == RDY_OK){
      pns_time = pnsGetTimeUnixUsec();

      gps_time = (int64_t)mktime(&gps_timp) * 1000000;
      Correction += gps_time - pns_time;

      /* now correct time in internal RTC (if needed) */
      time_t t1 = pnsGetTimeUnixUsec() / 1000000;
      time_t t2 = rtcGetTimeUnixSec(&RTCD1);
      if (abs(t1 - t2) > 2)
        rtcSetTimeUnixSec(&RTCD1, t1);
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void TimekeepingInit(void){

  timezone = ValueSearch("TIME_zone");

  BootTimestamp = rtcGetTimeUnixUsec(&RTCD1);
  /* поскольку вычитывание метки можеть происходить не сразу же после запуска -
   * внесем коррективы */
  BootTimestamp -= (int64_t)TIME_BOOT_MS * 1000;

  chThdCreateStatic(TimekeeperThreadWA,
          sizeof(TimekeeperThreadWA),
          TIMEKEEPER_THREAD_PRIO,
          TimekeeperThread,
          NULL);
}

/**
 * Return current time using lightweight approximation to avoid calling
 * of heavy time conversion (from hardware RTC) functions.
 */
uint64_t pnsGetTimeUnixUsec(void){

  chSysLock();
  if (TIME_BOOT_MS < LastTimeBootMs)
    WrapCount++;

  LastTimeBootMs = TIME_BOOT_MS;
  chSysUnlock();
  return BootTimestamp
         + (int64_t)(TIME_BOOT_MS) * 1000
         + Correction
         + 0x100000000ull * WrapCount;
}

/**
 * @brief   Return number of system ticks since last call.
 * @note    Function modifies the last value itself.
 *
 * @param[in] last      pointer to the value containing last call time
 * @return              The number of ticks.
 *
 * @api
 */
systime_t GetTimeInterval(systime_t *last){
  systime_t t = 0;

  if (chTimeNow() >= *last)
    t = chTimeNow() - *last;
  else /* overflow happens */
    t = chTimeNow() + (0xFFFFFFFF - *last);
  /* refresh last value */
  *last = chTimeNow();
  return t;
}

/**
 * Command to tune RTC.
 */
Thread* date_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  cli_print("unimplemented yet\r\n");
  return NULL;

//  rtcGetTime(&RTCD1, &timespec);
//
//  bcd2tm(&timp, timespec.tv_time, timespec.tv_date);
//
//  time = mktime(&timp);
//  chprintf(chp, "date: %U%s%U%s%U%s%U%s%U%s%U", (timp.tm_year + 1900), "/",
//      (timp.tm_mon + 1), "/", timp.tm_mday, " - ",
//      timp.tm_hour, ":", timp.tm_min, ":", timp.tm_sec);
//  chprintf(chp, "\r\n");
//  chprintf(chp, "time_t: %U", time);
//  chprintf(chp, "\r\n");
}
