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
extern MemoryHeap LinkThdHeap;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Поток отправки сообещиний через канал связи на землю.
 */
static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *sdp){
  chRegSetThreadName("MAVLinkOut");

  /* Переменная для формирования сообщения. Используется всеми,
     поскольку сообещиня обрабатываются по одному. */
  mavlink_message_t mavlink_msgbuf;
  /* выходной буфер для отправки данных */
  uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  Mail *mailp;
  msg_t tmp = 0;

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  while (TRUE) {
    chMBFetch(&tolink_mb, &tmp, TIME_INFINITE);
    mailp = (Mail*)tmp;
    sort_output_mail(mailp, &mavlink_msgbuf);
    len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_msgbuf);
    sdWrite((SerialDriver *)sdp, sendbuf, len);
  }

  return 0;
}


/**
 * Поток разбора входящих данных.
 */
static WORKING_AREA(LinkInThreadWA, 1024);
static msg_t LinkInThread(void *sdp){
  chRegSetThreadName("MAVLinkIn");

  mavlink_message_t msg;
  mavlink_status_t status;
  uint8_t c = 0;

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  while (TRUE) {
    // Try to get a new message
    c = sdGet((SerialDriver *)sdp);
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      if (msg.sysid == GROUND_STATION_ID){ /* нас запрашивает наземная станция */
        sort_input_messages(&msg);
      }
    }
  }
  return 0;
}

/**
 * Поток приема команд.
 */
static WORKING_AREA(LinkCmdParserThreadWA, 1024);
static msg_t LinkCmdParserThread(void *arg){
  chRegSetThreadName("MAVCmdParser");
  (void)arg;
  msg_t tmp;
  Mail *mailp = NULL;
  mavlink_command_long_t *cmdp;

  while (TRUE) {
    chMBFetch(&mavlinkcmd_mb, &tmp, TIME_INFINITE);
    mailp = (Mail *)tmp;
    cmdp = (mavlink_command_long_t *)(mailp->payload);
    analize_mavlink_cmd(cmdp);


    //TODO: анализ вёрнутого значения и генерация ответа в tolink_mb


    mailp->payload = NULL;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 * порождает потоки сортировки\парсинга сообщений
 * принимает указатель на пул памяти, из которго надо порождать треды
 */
void SpawnMavlinkThreads(SerialDriver *sdp){

  chThdCreateFromHeap(&LinkThdHeap,
          sizeof(LinkOutThreadWA),
          LINK_THREADS_PRIO,
          LinkOutThread,
          sdp);

  chThdCreateFromHeap(&LinkThdHeap,
          sizeof(LinkInThreadWA),
          LINK_THREADS_PRIO,
          LinkInThread,
          sdp);

  chThdCreateFromHeap(&LinkThdHeap,
          sizeof(LinkCmdParserThreadWA),
          LINK_THREADS_PRIO - 1,
          LinkCmdParserThread,
          sdp);
}





