#include <time.h>

#include "ch.h"
#include "hal.h"

#include "timekeeping.h"
#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SOFT_RTC_PERIOD 10

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint64_t TimeUsec;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static VirtualTimer timekeeping_vt;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Перевод из STM32 BCD в классическое представление
 */
void bcd2tm(struct tm *timp, uint32_t tv_time, uint32_t tv_date){
  timp->tm_isdst = -1;

  timp->tm_wday = ((tv_date >> 13) & 0x7);
  if(timp->tm_wday == 7)
    timp->tm_wday = 0;
  timp->tm_mday = (tv_date & 0xF) + ((tv_date >> 4) & 0x3) * 10;
  timp->tm_mon  = (((tv_date >> 8) & 0xF) + ((tv_date >> 12) & 0x1) * 10) - 1;
  timp->tm_year = (((tv_date >> 16)& 0xF) + ((tv_date >> 20) & 0xF) * 10) + 2000 - 1900;

  timp->tm_sec  = (tv_time & 0xF) + ((tv_time >> 4) & 0x7) * 10;
  timp->tm_min  = ((tv_time >> 8)& 0xF) + ((tv_time >> 12) & 0x7) * 10;
  timp->tm_hour = ((tv_time >> 16)& 0xF) + ((tv_time >> 20) & 0x3) * 10;
}

/**
 * Перевод из классического представления в STM32 BCD формат
 */
void tm2bcd(struct tm *timp, RTCTime *timespec){
  uint32_t p = 0; // вспомогательная переменная

  timespec->tv_date = 0;
  timespec->tv_time = 0;

  p = timp->tm_year - 100;
  timespec->tv_date |= (((p / 10) & 0xF) << 20) | ((p % 10) << 16);
  if (timp->tm_wday == 0)
    p = 7;
  else
    p = timp->tm_wday;
  timespec->tv_date |= (p & 7) << 13;
  p = timp->tm_mon + 1;
  timespec->tv_date |= (((p / 10) & 1) << 12) | ((p % 10) << 8);
  p = timp->tm_mday;
  timespec->tv_date |= (((p / 10) & 3) << 4) | (p % 10);
  p = timp->tm_hour;
  timespec->tv_time |= (((p / 10) & 3) << 20) | ((p % 10) << 16);
  p = timp->tm_min;
  timespec->tv_time |= (((p / 10) & 7) << 12) | ((p % 10) << 8);
  p = timp->tm_sec;
  timespec->tv_time |= (((p / 10) & 7) << 4) | (p % 10);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * Function incrementing global time value by TIMEKEEPING_VT_PERIOD_SEC
 */
static void vtcb(void *arg) {
  (void)arg;
  if (!chVTIsArmedI(&timekeeping_vt)){
    chVTSetI(&timekeeping_vt, MS2ST(SOFT_RTC_PERIOD), vtcb, NULL);
    TimeUsec += 1000 * SOFT_RTC_PERIOD;
  }
}

/**
 * Читает время из RTC
 * Конвертает в счетчик микросекунд
 */
void TimekeepingInit(void){
  RTCTime  timespec;
  struct tm timp;
  uint64_t t = 0;

  rtc_lld_get_time(&RTCD1, &timespec);
  bcd2tm(&timp, timespec.tv_time, timespec.tv_date);
  t = mktime(&timp);
  if (t != -1){
    TimeUsec = t * 1000000;
    chSysLock();
    chVTSetI(&timekeeping_vt, S2ST(SOFT_RTC_PERIOD), vtcb, NULL);
    chSysUnlock();
  }
  else
    chDbgPanic("time collapsed");
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
