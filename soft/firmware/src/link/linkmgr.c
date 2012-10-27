#include "uav.h"

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
extern GlobalFlags_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    USART_CR3_CTSE | USART_CR3_RTSE,
};

static uint32_t const *sh_enable;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Track changes of sh_enable flag and fork appropriate threads
 */
static WORKING_AREA(LinkMgrThreadWA, 96);
static msg_t LinkMgrThread(void *arg){
  chRegSetThreadName("LinkManager");

  bool_t shell_active = FALSE;

  /* wait slowpoked modems */
  chThdSleepMilliseconds(4000);

  /* define what we need to run based on flag */
  if (*sh_enable == 0){
    SpawnMavlinkThreads((SerialDriver *)arg);
    shell_active = FALSE;
  }
  else{
    SpawnShellThreads((SerialDriver *)arg);
    shell_active = TRUE;
  }

  /* say to all that modem is ready */
  setGlobalFlag(GlobalFlags.modem_ready);

  /* now track changes of flag and fork appropriate threads */
  while (TRUE) {
    chThdSleepMilliseconds(100);
    if(shell_active == TRUE){
      if(*sh_enable == 0){
        KillShellThreads();
        SpawnMavlinkThreads((SerialDriver *)arg);
        shell_active = FALSE;
      }
    }
    else{
      if(*sh_enable == 1){
        KillMavlinkThreads();
        SpawnShellThreads((SerialDriver *)arg);
        shell_active = TRUE;
      }
    }
  }

  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void LinkMgrInit(void){

  sh_enable = ValueSearch("SH_enable");

  sdStart(&LINKSD, &xbee_ser_cfg);

  chThdCreateStatic(LinkMgrThreadWA,
          sizeof(LinkMgrThreadWA),
          LINK_THREADS_PRIO,
          LinkMgrThread,
          &LINKSD);
}
