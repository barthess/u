#include <time.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"
#include "chrtclib.h"

#include "timekeeping.h"
#include "main.h"

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

/* ����� ������� �������� ����� � ����� �������, �� ������ ����� �������
 * ����� ��� ������������, ������� ������� ��������� ���������� */
static int64_t Correction = 0;

/* ����� ��������� ��������� */
static int64_t LastCorrTimestamp = 0;

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
      LastCorrTimestamp = pnsGetTimeUnixUsec();

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
  /* ��������� ����������� ����� ������ ����������� �� ����� �� ����� ������� -
   * ������ ���������� */
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
  return BootTimestamp + (int64_t)(TIME_BOOT_MS) * 1000 + Correction;
}

/**
 * Command to handle real time.
 */
Thread* date_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  cli_print("unimplemented yet\r\n");
  return NULL;

//  rtcGetTime(&RTCD1, &timespec);

//  bcd2tm(&timp, timespec.tv_time, timespec.tv_date);

//  time = mktime(&timp);
//  chprintf(chp, "date: %U%s%U%s%U%s%U%s%U%s%U", (timp.tm_year + 1900), "/",
//      (timp.tm_mon + 1), "/", timp.tm_mday, " - ",
//      timp.tm_hour, ":", timp.tm_min, ":", timp.tm_sec);
//  chprintf(chp, "\r\n");
//  chprintf(chp, "time_t: %U", time);
//  chprintf(chp, "\r\n");
}
