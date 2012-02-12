#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"
#include "main.h"
#include "param.h"

#include "link_cmd.h"
#include "link_sortin.h"
#include "link_sortout.h"


/*
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
extern Mailbox mavlinkcmd_mb;
//extern Mailbox autopilot_mb;
//extern Mailbox toservo_mb;
//extern Mailbox param_mb;
//extern Mailbox manual_control_mb;

extern MemoryHeap LinkThdHeap;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* pointers to spawned threads */
static Thread *linkout_tp = NULL;
static Thread *linkin_tp = NULL;
static Thread *linkcmdparser_tp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * ѕоток отправки сообещиний через канал св€зи на землю.
 */
static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *sdp){
  chRegSetThreadName("MAVLinkOut");

  /* ѕеременна€ дл€ формировани€ сообщени€. »спользуетс€ всеми,
     поскольку сообещин€ обрабатываютс€ по одному. */
  mavlink_message_t mavlink_msgbuf;
  /* выходной буфер дл€ отправки данных */
  uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  Mail *mailp;
  msg_t tmp = 0;

  while (TRUE) {
    if (chThdShouldTerminate())
      chThdExit(0);

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
 * ѕоток разбора вход€щих данных.
 */
static WORKING_AREA(LinkInThreadWA, 1024);
static msg_t LinkInThread(void *sdp){
  chRegSetThreadName("MAVLinkIn");

  mavlink_message_t msg;
  mavlink_status_t status;
  msg_t c = 0;

  while (TRUE) {
    if (chThdShouldTerminate())
      chThdExit(0);

    // Try to get a new message
    c = sdGetTimeout((SerialDriver *)sdp, MS2ST(200));
    if (c != Q_TIMEOUT){
      if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &status)) {
        if (msg.sysid == GROUND_STATION_ID){ /* нас запрашивает наземна€ станци€ */
          sort_input_messages(&msg);
        }
      }
    }
  }
  return 0;
}

/**
 * ѕоток приема команд.
 */
static WORKING_AREA(LinkCmdParserThreadWA, 1024);
static msg_t LinkCmdParserThread(void *arg){
  chRegSetThreadName("MAVCmdParser");
  (void)arg;
  msg_t tmp;
  Mail *mailp = NULL;
  mavlink_command_long_t *cmdp;

  while (TRUE) {
    if (chThdShouldTerminate())
      chThdExit(0);

    if (chMBFetch(&mavlinkcmd_mb, &tmp, MS2ST(200)) == RDY_OK){
      mailp = (Mail *)tmp;
      cmdp = (mavlink_command_long_t *)(mailp->payload);
      analize_mavlink_cmd(cmdp);
      //TODO: анализ вЄрнутого значени€ и генераци€ ответа в tolink_mb
      mailp->payload = NULL;
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
 * Kills previously spawned threads
 */
void KillMavlinkThreads(void){
  chThdTerminate(linkout_tp);
  chThdTerminate(linkin_tp);
  chThdTerminate(linkcmdparser_tp);

  chThdWait(linkout_tp);
  chThdWait(linkin_tp);
  chThdWait(linkcmdparser_tp);
}

/**
 * порождает потоки сортировки\парсинга сообщений
 * принимает указатель на пул пам€ти, из которго надо порождать треды
 */
void SpawnMavlinkThreads(SerialDriver *sdp){

//  chMBReset(&manual_control_mb);
//  chMBReset(&autopilot_mb);
//  chMBReset(&tolink_mb);
//  chMBReset(&toservo_mb);
//  chMBReset(&param_mb);
//  chMBReset(&mavlinkcmd_mb);

  linkout_tp = chThdCreateFromHeap(&LinkThdHeap,
                            sizeof(LinkOutThreadWA),
                            LINK_THREADS_PRIO,
                            LinkOutThread,
                            sdp);

  linkin_tp = chThdCreateFromHeap(&LinkThdHeap,
                            sizeof(LinkInThreadWA),
                            LINK_THREADS_PRIO,
                            LinkInThread,
                            sdp);

  linkcmdparser_tp = chThdCreateFromHeap(&LinkThdHeap,
                            sizeof(LinkCmdParserThreadWA),
                            LINK_THREADS_PRIO - 1,
                            LinkCmdParserThread,
                            sdp);
}





