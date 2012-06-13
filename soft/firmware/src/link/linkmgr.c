#include "ch.h"
#include "hal.h"

#include "main.h"
#include "link.h"
#include "cli.h"
#include "linkmgr.h"
#include "param.h"


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
extern GlobalParam_t global_data[];
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

static int32_t sh_enable_index = -1;

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
  if (global_data[sh_enable_index].value == 0){
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
      if(global_data[sh_enable_index].value == 0){
        KillShellThreads();
        SpawnMavlinkThreads((SerialDriver *)arg);
        shell_active = FALSE;
      }
    }
    else{
      if(global_data[sh_enable_index].value == 1){
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

  sdStart(&LINKSD, &xbee_ser_cfg);

  sh_enable_index = _key_index_search("SH_enable");
  if (sh_enable_index == -1)
    chDbgPanic("not found");

  chThdCreateStatic(LinkMgrThreadWA,
          sizeof(LinkMgrThreadWA),
          LINK_THREADS_PRIO,
          LinkMgrThread,
          &LINKSD);
}
