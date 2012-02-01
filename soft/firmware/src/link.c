#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"
#include "main.h"
#include "parameters.h"

#include "mavlink.h"
#include "bart.h"
#include "common.h"

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
extern Mailbox param_mb;
extern Mailbox manual_control_mb;
extern mavlink_system_t mavlink_system;
extern mavlink_bart_manual_control_t mavlink_bart_manual_control_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* переменные для установки параметров присланных с земли */
static mavlink_param_set_t param_set;
static mavlink_param_request_list_t param_request_list;
static mavlink_param_request_read_t param_request_read;
static Mail param_mail = {NULL, MAVLINK_MSG_ID_PARAM_SET, NULL};
static Mail manual_control_mail = {NULL, MAVLINK_MSG_ID_BART_MANUAL_CONTROL, NULL};

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
 * @brief Helper function.
 *
 * Определяет тип сообщения, чтобы применить правильную функцию упаковки.
 * Пакует письмо из ящика в мавлинковое сообщение.
 * ЗаNULLяет указатель на содержимое, как знак того, что данные обработаны.
 * Возвращает длинну сообщения получившегося сообщения.
 */
#define finalize_receive() {                                                  \
  mailp->payload = NULL;                                                      \
  if (mailp->confirmbox != NULL){                                             \
    chMBPost(mailp->confirmbox, len, TIME_IMMEDIATE);                         \
  }                                                                           \
  return len;                                                                 \
}

static uint16_t receive_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
  uint16_t len;

  switch(mailp->invoice){

  case MAVLINK_MSG_ID_HEARTBEAT:
    len = mavlink_msg_heartbeat_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_heartbeat_t*)(mailp->payload));
    finalize_receive();
    break;

  case MAVLINK_MSG_ID_SYS_STATUS:
    len = mavlink_msg_sys_status_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_sys_status_t*)(mailp->payload));
    finalize_receive();
    break;

  case MAVLINK_MSG_ID_PARAM_VALUE:
    len = mavlink_msg_param_value_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_param_value_t*)(mailp->payload));
    finalize_receive();
    break;

  case MAVLINK_MSG_ID_RAW_IMU:
    len = mavlink_msg_raw_imu_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_IMU,
        mavlink_msgbuf,
        (const mavlink_raw_imu_t*)(mailp->payload));
    finalize_receive();
    break;

  case MAVLINK_MSG_ID_GPS_RAW_INT:
    len = mavlink_msg_gps_raw_int_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_GPS,
        mavlink_msgbuf,
        (const mavlink_gps_raw_int_t*)(mailp->payload));
    finalize_receive();
    break;

  case MAVLINK_MSG_ID_RAW_PRESSURE:
    len = mavlink_msg_raw_pressure_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_IMU,
        mavlink_msgbuf,
        (const mavlink_raw_pressure_t*)(mailp->payload));
    finalize_receive();
    break;

  default:
    break;
  }
  return 0;
}
#undef finalize_receive

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
    receive_mail(mailp, &mavlink_msgbuf);
    len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_msgbuf);
    sdWrite(&LINKSD, sendbuf, len);
  }

  return 0;
}



/* определяет, кому пришло это сообщение и кидает в соотверствующий почтовый ящик */
static bool_t handle_message(mavlink_message_t *msg){
  msg_t status = RDY_OK;

  switch(msg->msgid){
  case MAVLINK_MSG_ID_HEARTBEAT:
    break;

  case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
    mavlink_msg_param_request_list_decode(msg, &param_request_list);
    if (param_mail.payload == NULL){
      param_mail.invoice = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;
      param_mail.payload = &param_request_list;
      status = chMBPost(&param_mb, (msg_t)&param_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return FAILED;
    }
    else
      return FAILED;
    break;

  case MAVLINK_MSG_ID_BART_MANUAL_CONTROL:
    mavlink_msg_bart_manual_control_decode(msg, &mavlink_bart_manual_control_struct);
    /* if this message not for us than just silently ignore it */
    if (mavlink_bart_manual_control_struct.target_id != mavlink_system.sysid)
      return SUCCESS;
    if (manual_control_mail.payload == NULL){
      manual_control_mail.invoice = MAVLINK_MSG_ID_BART_MANUAL_CONTROL;
      manual_control_mail.payload = &param_set;
      status = chMBPost(&manual_control_mb, (msg_t)&manual_control_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return FAILED;
    }
    else
      return FAILED;
    break;

  case MAVLINK_MSG_ID_PARAM_SET:
    mavlink_msg_param_set_decode(msg, &param_set);
    if (param_mail.payload == NULL){
      param_mail.invoice = MAVLINK_MSG_ID_PARAM_SET;
      param_mail.payload = &param_set;
      status = chMBPost(&param_mb, (msg_t)&param_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return FAILED;
    }
    else
      return FAILED;
    break;

  default:
    //Do nothing
    break;
  }

  return SUCCESS;
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
        handle_message(&msg);
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
}






