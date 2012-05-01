#include "ch.h"
#include "hal.h"

#include "link.h"
#include "link_sortin.h"
#include "message.h"
#include "main.h"

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
extern Mailbox mavlink_param_set_mb;
extern Mailbox mavlink_command_long_mb;

extern mavlink_system_t mavlink_system_struct;
extern mavlink_command_long_t mavlink_command_long_struct;
extern mavlink_set_mode_t mavlink_set_mode_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static mavlink_param_set_t mavlink_param_set_struct;
static mavlink_param_request_list_t mavlink_param_request_list_struct;
static mavlink_param_request_read_t mavlink_param_request_read_struct;

static Mail param_set_mail = {NULL, MAVLINK_MSG_ID_PARAM_SET, NULL};
static Mail command_long_mail = {NULL, MAVLINK_MSG_ID_COMMAND_LONG, NULL};

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

//  case MAVLINK_MSG_ID_PARAM_SET:
//    mavlink_msg_param_set_decode(msg, &mavlink_param_set_struct);
//    if (param_set_mail.payload == NULL){
//      param_set_mail.invoice = MAVLINK_MSG_ID_PARAM_SET;
//      param_set_mail.payload = &mavlink_param_set_struct;
//      status = chMBPost(&mavlink_param_set_mb, (msg_t)&param_set_mail, TIME_IMMEDIATE);
//      if (status != RDY_OK)
//        return LINK_FAILED;
//    }
//    else
//      return LINK_SUCCESS;
//    break;

/* m - part of mail name */
#define SORTINCASE(lowercase, UPPERCASE, m){                                          \
    case MAVLINK_MSG_ID_##UPPERCASE:                                                  \
      mavlink_msg_##lowercase##_decode(msg, &mavlink_##lowercase##_struct);           \
      if (mavlink_##lowercase##_struct.target_system != mavlink_system_struct.sysid)  \
        return LINK_SUCCESS; /* silently ignore messages not for this system */       \
      if (m##_mail.payload == NULL){                                                  \
        m##_mail.invoice = MAVLINK_MSG_ID_##UPPERCASE ;                               \
        m##_mail.payload = &mavlink_##lowercase##_struct;                             \
        status = chMBPost(&mavlink_##m##_mb, (msg_t)&m##_mail, TIME_IMMEDIATE);       \
        if (status != RDY_OK)                                                         \
          return LINK_FAILED;                                                         \
      }                                                                               \
      else                                                                            \
        return LINK_SUCCESS;                                                          \
      break;                                                                          \
}


/* определяет, кому пришло это сообщение и кидает в соотверствующий почтовый ящик */
bool_t sort_input_messages(mavlink_message_t *msg){
  msg_t status = RDY_OK;

  switch(msg->msgid){
    SORTINCASE(param_request_list, PARAM_REQUEST_LIST,  param_set)
    SORTINCASE(param_request_read, PARAM_REQUEST_READ,  param_set)
    SORTINCASE(param_set, PARAM_SET,                    param_set)

    SORTINCASE(command_long, COMMAND_LONG,              command_long)





  case MAVLINK_MSG_ID_SET_MODE:
    mavlink_msg_set_mode_decode(msg, &mavlink_set_mode_struct);
    if (mavlink_set_mode_struct.target_system == mavlink_system_struct.sysid)
      mavlink_system_struct.mode = mavlink_set_mode_struct.custom_mode | mavlink_set_mode_struct.base_mode;
    break;

  case MAVLINK_MSG_ID_HEARTBEAT:
    break;
  default:
    //Do nothing
    break;
  }

  return LINK_SUCCESS;
}




