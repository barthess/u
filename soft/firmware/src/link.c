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
#define LINKSD SD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;

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

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

// Define the system type, in this case an airplane
//static uint8_t system_type     = MAV_TYPE_GROUND_ROVER;
//static uint8_t autopilot_type  = MAV_AUTOPILOT_GENERIC;
//static uint8_t system_mode     = MAV_MODE_PREFLIGHT; ///< Booting up
//static uint32_t custom_mode    = 0;                 ///< Custom mode, can be defined by user/adopter
//static uint8_t system_state    = MAV_STATE_STANDBY; ///< System ready for flight


/**
 * Поток отправки сообещиний через канал связи на землю.
 */
static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *arg){
  chRegSetThreadName("MAVLinkOut");
  (void)arg;

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
    sdWrite(&LINKSD, sendbuf, len);
  }

  return 0;
}


/**
 * Поток разбора входящих данных.
 */
static WORKING_AREA(LinkInThreadWA, 1024);
static msg_t LinkInThread(void *arg){
  chRegSetThreadName("MAVLinkIn");
  (void)arg;

  mavlink_message_t msg;
  mavlink_status_t status;
  uint8_t c = 0;

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  while (TRUE) {
    // Try to get a new message
    c = sdGet(&LINKSD);
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      if (msg.sysid == GROUND_STATION_ID){ /* нас запрашивает наземная станция */
        sort_input_messages(&msg);
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
void LinkInit(void){

  /* запуск на дефолтной частоте */
  sdStart(&LINKSD, &xbee_ser_cfg);

  chThdCreateStatic(LinkOutThreadWA,
          sizeof(LinkOutThreadWA),
          LINK_THREADS_PRIO,
          LinkOutThread,
          NULL);

  chThdCreateStatic(LinkInThreadWA,
          sizeof(LinkInThreadWA),
          LINK_THREADS_PRIO,
          LinkInThread,
          NULL);

  LinkCmdParserInit();
}






