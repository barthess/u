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
extern EventSource init_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    USART_CR3_CTSE,
};

static uint32_t *sh_enable;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * Поток следящий за потоками связи и переключающий их по мере надобности
 */
static WORKING_AREA(LinkMgrThreadWA, 128);
static msg_t LinkMgrThread(void *arg){
  chRegSetThreadName("LinkManager");

  bool_t shell_active = FALSE;

  /* ждем, пока модемы встанут в ружьё */
  chThdSleepMilliseconds(4000);

  /* по значению флага определяем, что надо изначально запустить */
  if (*sh_enable == 0){
    SpawnMavlinkThreads((SerialDriver *)arg);
    shell_active = FALSE;
  }
  else{
    SpawnShellThreads((SerialDriver *)arg);
    shell_active = TRUE;
  }

  /* say to all that modem is ready */
  chEvtBroadcastFlags(&init_event, EVENT_MASK(MODEM_READY_EVID));

  /* а теперь в цикле следим за изменениями и запускаем нужные потоки */
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
