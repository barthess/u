#include "uav.h"

#include "link_sortin.h"
#include "link_sortout.h"

/**
 * This code performs:
 * - receiving and sending of packages via UART
 * - decoding and encoding of packages
 * - passing and receiving of decoded messages
 */

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
extern Mailbox tolink_mb;
extern MemoryHeap ThdHeap;
extern mavlink_status_t mavlink_status_struct;
extern uint32_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* pointers to spawned threads */
static Thread *linkout_tp = NULL;
static Thread *linkin_tp  = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 *
 */
static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *sdp){
  chRegSetThreadName("MAVLinkOut");

  /* Variable for storing message. One for all because messages processed
   * one by one. */
  mavlink_message_t mavlink_msgbuf;

  /* output buffer for sending data */
  uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  Mail *mailp;
  msg_t tmp = 0;

  while (TRUE) {
    if (chThdShouldTerminate()){
      /* try correctly stop thread */
      chThdSleepMilliseconds(200);
      PurgeUavMailbox(&tolink_mb);
      chThdExit(0);
    }

    if (chMBFetch(&tolink_mb, &tmp, MS2ST(200)) == RDY_OK){
      mailp = (Mail*)tmp;
      sort_output_mail(mailp, &mavlink_msgbuf);
      len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_msgbuf);
      sdWrite((SerialDriver *)sdp, sendbuf, len);
    }
  }

  return 0;
}


/**
 * Parse input data.
 */
static WORKING_AREA(LinkInThreadWA, 512);
static msg_t LinkInThread(void *sdp){
  chRegSetThreadName("MAVLinkIn");

  mavlink_message_t msg;
  msg_t c = 0;

  while (TRUE) {
    if (chThdShouldTerminate())
      chThdExit(0);

    // Try to get a new message
    c = sdGetTimeout((SerialDriver *)sdp, MS2ST(200));
    if (c != Q_TIMEOUT){
      if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &mavlink_status_struct)) {
        if (msg.sysid == GROUND_STATION_ID){ /* message from our ground station */
          sort_input_messages(&msg);
        }
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

/**
 * Purge message queue correctly notifying writer threads.
 * @note  Do not use it often because it can
 *        lock system during log period of time.
 */
void PurgeUavMailbox(Mailbox *mbp){
  msg_t tmp;
  Mail *mail;

  chSysLock();
  while (chMBGetUsedCountI(mbp) != 0){
    chMBFetch(mbp, &tmp, TIME_IMMEDIATE);
    mail = (Mail *)tmp;
    mail->payload = NULL;
    if (mail->semp != NULL)
      chBSemSignalI(mail->semp);
  }
  chSysUnlock();
}

/**
 * Kills previously spawned threads
 */
void KillMavlinkThreads(void){
  clearGlobalFlag(TLM_LINK_FLAG);

  chThdTerminate(linkout_tp);
  chThdTerminate(linkin_tp);

  chThdWait(linkout_tp);
  chThdWait(linkin_tp);
}

/**
 * Create telemetry link threads
 */
void SpawnMavlinkThreads(SerialDriver *sdp){

//  PurgeUavMailbox(&manual_control_mb);
//  PurgeUavMailbox(&autopilot_mb);
//  PurgeUavMailbox(&tolink_mb);
//  PurgeUavMailbox(&toservo_mb);
//  PurgeUavMailbox(&param_mb);
//  PurgeUavMailbox(&mavlinkcmd_mb);

  linkout_tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(LinkOutThreadWA),
                            LINK_THREADS_PRIO,
                            LinkOutThread,
                            sdp);
  if (linkout_tp == NULL)
    chDbgPanic("Can not allocate memory");

  linkin_tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(LinkInThreadWA),
                            LINK_THREADS_PRIO,
                            LinkInThread,
                            sdp);
  if (linkin_tp == NULL)
    chDbgPanic("Can not allocate memory");

  setGlobalFlag(TLM_LINK_FLAG);
}





