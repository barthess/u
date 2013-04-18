#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "uav.h"
#include "chrtclib.h"

#include "sensors.hpp"
#include "timekeeping.hpp"

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
extern RawData raw_data;
extern chibios_rt::BinarySemaphore rtc_sem;
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

/* variables for cpu utilization calculation */
static systime_t last_systick = 0;
static systime_t last_idletick = 0;

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
    sem_status = rtc_sem.waitTimeout(MS2ST(2000));
    if (sem_status == RDY_OK && raw_data.gps_valid){
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
 * Command to handle RTC.
 */
Thread* date_clicmd(int argc, const char * const * argv, SerialDriver *sdp){
  (void)sdp;

  struct tm timp;
  time_t tv_sec = 0;
  int sscanf_status;

  /* 1 argument */
  if (argc == 1){
    sscanf_status = sscanf(argv[0], "%i", (int*)&tv_sec);
    if (sscanf_status != 1)
      cli_println("ERROR. Date value inconsistent");
    else
      rtcSetTimeUnixSec(&RTCD1, tv_sec);
  }

  /* error handler */
  else{
    int n = 32;
    int nres = 0;
    char str[n];

    tv_sec = rtcGetTimeUnixSec(&RTCD1);
    rtcGetTimeTm(&RTCD1, &timp);

    cli_print("Current UTC time is: ");
    strftime(str, n, "%F %H:%M:%S", &timp);
    cli_println(str);

    nres = snprintf(str, n, "%d", (int)tv_sec);
    cli_print_long(str, n, nres);
    cli_println(" seconds since Unix epoch");
    cli_println("");

    cli_println("To set time run 'date N'");
    cli_println("    where 'N' is count of seconds (UTC) since Unix epoch.");
    cli_println("    you can obtain this value from Unix command line: 'date -u +%s'");
  }

  /* stub */
  return NULL;
}

/**
 * return tens of persents.
 */
uint16_t getCpuLoad(void){

  systime_t i, s;

  s = chTimeNow() - last_systick;
  i = chThdGetTicks(chSysGetIdleThread()) - last_idletick;

  last_systick = chTimeNow();
  last_idletick = chThdGetTicks(chSysGetIdleThread());

  return ((s - i) * 1000) / s;
}
