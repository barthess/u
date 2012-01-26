#include <time.h>

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#include "rtc_pns.h"
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
 * Настройка всяких параметров часов.
 */
void RtcPnsInit(void){
  ;
}
