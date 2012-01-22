#include <time.h>

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#include "message.h"
#include "cli.h"
#include "storage.h"
#include "rtc_pns.h"
#include "main.h"

#if !ENABLE_GPS

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SDCLI SD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
//extern RTCTime timespec;

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/
static struct tm timp;



static void cmd_dateget(BaseChannel *chp, int argc, char *argv[]){
  time_t time = 0;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: dateget\r\n");
    return;
  }
//  rtcGetTime(&RTCD1, &timespec);

//  bcd2tm(&timp, timespec.tv_time, timespec.tv_date);

  time = mktime(&timp);
  chprintf(chp, "date: %U%s%U%s%U%s%U%s%U%s%U", (timp.tm_year + 1900), "/",
      (timp.tm_mon + 1), "/", timp.tm_mday, " - ",
      timp.tm_hour, ":", timp.tm_min, ":", timp.tm_sec);
  chprintf(chp, "\r\n");
  chprintf(chp, "time_t: %U", time);
  chprintf(chp, "\r\n");
}

static void cmd_dateset(BaseChannel *chp, int argc, char *argv[]){
//  RTCTime timespec;
  time_t gmt = 1500000000;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: dateset\r\n");
    return;
  }

//  tm2bcd(gmtime(&gmt), &timespec);

//  rtcSetTime(&RTCD1, &timespec);
  chprintf(chp, "date set");
  chprintf(chp, "\r\n");
}



static void cmd_reboot(BaseChannel *chp, int argc, char *argv[]){
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: reboot\r\n");
    return;
  }
  chprintf(chp, "rebooting...\r\n");
  NVIC_SystemReset();
}

static void cmd_sleep(BaseChannel *chp, int argc, char *argv[]){
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: sleep\r\n");
    return;
  }
  chprintf(chp, "going to sleep\r\n");

  chSysLock();
  PWR->CR |= (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}

static void cmd_mem(BaseChannel *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
}


static void cmd_test(BaseChannel *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: test\r\n");
    return;
  }
  chprintf(chp, "GPS - OK\r\nModem - OK\r\nEEPROM - OK\r\nStorage - OK\r\nServos - OK\r\n");
}

static void cmd_temp(BaseChannel *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Get onboard temperature.\r\nUsage: temp\r\n");
    return;
  }
  chprintf(chp, "temp: %d", raw_data.temp_tmp75);
}

static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"test", cmd_test},
  {"reboot", cmd_reboot},
  {"sleep", cmd_sleep},
  {"dateset", cmd_dateset},
  {"dateget", cmd_dateget},
  {"temp", cmd_temp},
  {"tree", cmd_tree},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseChannel *)&SDCLI,
  commands
};

static SerialConfig cli_ser_cfg = {
    115200,
    0,
    0,
    USART_CR3_CTSE,
};

static WORKING_AREA(waShell, 8192);

void CliInit(void){
  sdStart(&SDCLI, &cli_ser_cfg);

  shellInit();
  shellCreateStatic(&shell_cfg1, waShell, sizeof(waShell), NORMALPRIO);
}
#else
void CliInit(void){;}
#endif /* !ENABLE_GPS */


