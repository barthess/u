#include <stdio.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DBG_PRINT_TMO       MS2ST(1000)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern mavlink_statustext_t mavlink_statustext_struct;
extern uint32_t GlobalFlags;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Mail statustext_mail = {NULL, MAVLINK_MSG_ID_STATUSTEXT, NULL};
static BinarySemaphore dbg_sem;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Send debug message.
 * NOTE. This functions blocks its caller untill message processed.
 *
 * severity[in]   severity of message
 * semp[in]       pointer to mail synchronization semaphore (set to NULL if unused)
 * text[in]       text to send
 *
 * return         message posting status
 */
msg_t dbg_print(uint8_t severity, const char *text){
  uint32_t n = sizeof(mavlink_statustext_struct.text);
  msg_t status = RDY_RESET;

  if (GlobalFlags & TLM_LINK_FLAG){
    status = chBSemWaitTimeout(&dbg_sem, DBG_PRINT_TMO);
    if (status != RDY_OK){
      chBSemSignal(&dbg_sem);
      return status;
    }

    mavlink_statustext_struct.severity = severity;
    memset(mavlink_statustext_struct.text, 0, n);
    memcpy(mavlink_statustext_struct.text, text, n);

    statustext_mail.payload = &mavlink_statustext_struct;
    statustext_mail.semp = &dbg_sem;
    status = chMBPostAhead(&tolink_mb, (msg_t)&statustext_mail, TIME_IMMEDIATE);
    if (status != RDY_OK){
      chBSemSignal(&dbg_sem);
      return status;
    }
  }
  return status;
}

/**
 *
 */
void DbgPrintInit(void){
  chBSemInit(&dbg_sem, FALSE);
}
