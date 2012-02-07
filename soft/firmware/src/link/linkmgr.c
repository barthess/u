#include "ch.h"
#include "hal.h"

#include "main.h"
#include "link.h"
#include "linkmgr.h"
#include "param.h"


/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define LINKSD SD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalParam_t global_data[];

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

/* heap for (link threads) OR (shell thread)*/
static MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE];

static uint32_t sh_enable_index = -1;

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
static WORKING_AREA(LinkMgrThreadWA, 256);
static msg_t LinkMgrThread(void *arg){
  chRegSetThreadName("LinkManager");

  /* ждем, пока модемы встанут в ружьё */
  chThdSleepMilliseconds(3000);

  /* по значению флага определяем, что запускать */
//  if (global_data[sh_enable_index].value == 0)
//    SpawnMavlinkThreads((MemoryHeap *)arg);
//  else
//    SpawnShellThread((MemoryHeap *)arg);
  SpawnMavlinkThreads((MemoryHeap *)arg);

  while (TRUE) {
    chThdSleepMilliseconds(3000);
  }

  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void LinkMgrInit(void){

  chHeapInit(&LinkThdHeap, link_thd_buf, LINK_THD_HEAP_SIZE);

  sdStart(&LINKSD, &xbee_ser_cfg);

  sh_enable_index = key_value_search("SH_enable");
  if (sh_enable_index == -1)
    chDbgPanic("not found");

  chThdCreateStatic(LinkMgrThreadWA,
          sizeof(LinkMgrThreadWA),
          LINK_THREADS_PRIO,
          LinkMgrThread,
          &LinkThdHeap);
}
