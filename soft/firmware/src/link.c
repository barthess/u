#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"

#include <mavlink.h>
#include <bart.h>
#include <common.h>

/* test string */

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
extern Mailbox toservo_mb;

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

// Define the system type, in this case an airplane
//static uint8_t system_type     = MAV_TYPE_GROUND_ROVER;
//static uint8_t autopilot_type  = MAV_AUTOPILOT_GENERIC;
//static uint8_t system_mode     = MAV_MODE_PREFLIGHT; ///< Booting up
//static uint32_t custom_mode    = 0;                 ///< Custom mode, can be defined by user/adopter
//static uint8_t system_state    = MAV_STATE_STANDBY; ///< System ready for flight


static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *arg){
  chRegSetThreadName("MAVLinkOut");
  (void)arg;

  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  mavlink_message_t *msgp = NULL;
  msg_t tmp = 0;

  while (TRUE) {
    chMBFetch(&tolink_mb, &tmp, TIME_INFINITE);
    msgp = (mavlink_message_t*)tmp;
    len = mavlink_msg_to_send_buffer(buf, msgp);
    sdWrite(&LINKSD, buf, len);
    msgp->magic = 0;/* данные обработаны */
  }

  return 0;
}




/**
 * Поток разбора входящих данных.
 * Мавлинк проводит парсинг и валидацию данных.
 * Мы рассылаем письма по почтовым ящикам.
 * Подтверждение факта приёма является обнуленное поле "magic" сообщения,
 * в стандарте - 0х55.
 */
#define MSG_BUF_LEN 4
static WORKING_AREA(LinkInThreadWA, 1024 + MSG_BUF_LEN * MAVLINK_MAX_PACKET_LEN);
static msg_t LinkInThread(void *arg){
  chRegSetThreadName("MAVLinkIn");
  (void)arg;

  mavlink_message_t msg[MSG_BUF_LEN];
  mavlink_status_t status;
  uint32_t n, i;

  /* зануляем поле magic, как знак того, что буфер пустой */
  for (i = 0; i < MSG_BUF_LEN; i++)
    msg[i].magic = 0;

  n = 0;
  i = 0;

  while (TRUE) {
    // Try to get a new message
    if (mavlink_parse_char(MAVLINK_COMM_0, sdGet(&LINKSD), &(msg[i]), &status)) {
      // Handle message
      switch(msg[i].msgid){
      case MAVLINK_MSG_ID_HEARTBEAT:
        break;
      case MAVLINK_MSG_ID_BART_SERVO_TUNING:
        chMBPost(&toservo_mb, (msg_t)(&msg[i]), TIME_IMMEDIATE);
        break;
      default:
        //Do nothing
        break;
      }

      /* Если попали сюда, значит пакет успешно выловлен и брошен в нужный ящик.
         Выбираем ближайший свободный буфер, в норме это должен быть следующий же. */
      do {
        n++;
        i = n & 3;
      }
      while (msg[i].magic != 0);

    }
  }
  return 0;
}











static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    USART_CR3_CTSE,
};



void LinkInit(void){

  /* запуск на дефолтной частоте */
  sdStart(&LINKSD, &xbee_ser_cfg);

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  chThdCreateStatic(LinkOutThreadWA,
          sizeof(LinkOutThreadWA),
          NORMALPRIO,
          LinkOutThread,
          NULL);

  chThdCreateStatic(LinkInThreadWA,
          sizeof(LinkInThreadWA),
          NORMALPRIO,
          LinkInThread,
          NULL);
}






