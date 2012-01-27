#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"

#include <mavlink.h>
#include <bart.h>
#include <common.h>

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

extern mavlink_system_t mavlink_system;

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


/**
 * Определяет, что пришло в почтовом ящике.
 * Пакует в содержимое ящика в мавлинковое сообщение.
 * ЗаNULLяет указатель на содержимое, как знак того, что данные обработаны.
 */
static uint16_t pack_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
  uint16_t len;

  switch(mailp->invoice){

  case MAVLINK_MSG_ID_HEARTBEAT:
    len = mavlink_msg_heartbeat_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_heartbeat_t*)(mailp->payload));
    mailp->payload = NULL;
    return len;
    break;

  case MAVLINK_MSG_ID_RAW_IMU:
    len = mavlink_msg_raw_imu_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_IMU,
        mavlink_msgbuf,
        (const mavlink_raw_imu_t*)(mailp->payload));
    mailp->payload = NULL;
    return len;
    break;

  case MAVLINK_MSG_ID_BART_RAW_PRESSURE:
      len = mavlink_msg_bart_raw_pressure_encode (
          mavlink_system.sysid,
          MAV_COMP_ID_IMU,
          mavlink_msgbuf,
          (const mavlink_bart_raw_pressure_t*)(mailp->payload));
      mailp->payload = NULL;
      return len;
      break;

  default:
    break;
  }
  return 0;
}

/**
 * Поток отправки сообещиний через канал связи.
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
    pack_mail(mailp, &mavlink_msgbuf);
    len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_msgbuf);
    sdWrite(&LINKSD, sendbuf, len);
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

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

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
          NORMALPRIO,
          LinkOutThread,
          NULL);

  chThdCreateStatic(LinkInThreadWA,
          sizeof(LinkInThreadWA),
          NORMALPRIO,
          LinkInThread,
          NULL);
}






