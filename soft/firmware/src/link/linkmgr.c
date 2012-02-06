#include "ch.h"
#include "hal.h"

#include "main.h"
#include "link.h"
#include "linkmgr.h"


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

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * ����� �������� �� �������� ����� � ������������� �� �� ���� ����������
 */
static WORKING_AREA(LinkMgrThreadWA, 256);
static msg_t LinkMgrThread(void *arg){
  chRegSetThreadName("LinkManager");

  /* ����, ���� ������ ������� � ����� */
  chThdSleepMilliseconds(3000);

  /* �� ��������� ��������� ����������� ������ */
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

  chThdCreateStatic(LinkMgrThreadWA,
          sizeof(LinkMgrThreadWA),
          LINK_THREADS_PRIO,
          LinkMgrThread,
          &LinkThdHeap);
}
