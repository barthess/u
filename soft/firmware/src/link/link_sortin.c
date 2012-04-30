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
extern Mailbox param_mb;
extern Mailbox mavlinkcmd_mb;
extern mavlink_system_t mavlink_system;
extern mavlink_command_long_t mavlink_command_long_struct;
extern mavlink_set_mode_t mavlink_set_mode_struct;

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
static Mail command_mail = {NULL, MAVLINK_MSG_ID_COMMAND_LONG, NULL};

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */


/* определяет, кому пришло это сообщение и кидает в соотверствующий почтовый ящик */
bool_t sort_input_messages(mavlink_message_t *msg){
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
        return LINK_FAILED;
    }
    else
      return LINK_SUCCESS;
    break;

  case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
    mavlink_msg_param_request_read_decode(msg, &param_request_read);
    if (param_mail.payload == NULL){
      param_mail.invoice = MAVLINK_MSG_ID_PARAM_REQUEST_READ;
      param_mail.payload = &param_request_read;
      status = chMBPost(&param_mb, (msg_t)&param_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return LINK_FAILED;
    }
    else
      return LINK_SUCCESS;
    break;

  case MAVLINK_MSG_ID_PARAM_SET:
    mavlink_msg_param_set_decode(msg, &param_set);
    if (param_mail.payload == NULL){
      param_mail.invoice = MAVLINK_MSG_ID_PARAM_SET;
      param_mail.payload = &param_set;
      status = chMBPost(&param_mb, (msg_t)&param_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return LINK_FAILED;
    }
    else
      return LINK_SUCCESS;
    break;

  case MAVLINK_MSG_ID_COMMAND_LONG:
    mavlink_msg_command_long_decode(msg, &mavlink_command_long_struct);

    if (mavlink_command_long_struct.target_system != mavlink_system.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */

    if (command_mail.payload == NULL){
      command_mail.invoice = MAVLINK_MSG_ID_COMMAND_LONG;
      command_mail.payload = &mavlink_command_long_struct;
      status = chMBPost(&mavlinkcmd_mb, (msg_t)&command_mail, TIME_IMMEDIATE);
      if (status != RDY_OK)
        return LINK_FAILED;
    }
    else
      return LINK_SUCCESS;
    break;

  case MAVLINK_MSG_ID_SET_MODE:
    mavlink_msg_set_mode_decode(msg, &mavlink_set_mode_struct);
    if (mavlink_set_mode_struct.target_system == mavlink_system.sysid)
      mavlink_system.mode = mavlink_set_mode_struct.custom_mode | mavlink_set_mode_struct.base_mode;
    break;

  default:
    //Do nothing
    break;
  }

  return LINK_SUCCESS;
}




