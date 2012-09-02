#include "uav.h"
#include "link_sortin.h"

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
extern mavlink_system_t mavlink_system_struct;

extern Mailbox mavlink_param_set_mb;
extern Mailbox mavlink_command_long_mb;
extern Mailbox controller_mb;
extern Mailbox mission_mb;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static mavlink_param_set_t              mavlink_param_set_struct;
static mavlink_param_request_list_t     mavlink_param_request_list_struct;
static mavlink_param_request_read_t     mavlink_param_request_read_struct;
static mavlink_command_long_t           mavlink_command_long_struct;
static mavlink_manual_control_t         mavlink_manual_control_struct;
static mavlink_set_mode_t               mavlink_set_mode_struct;
static mavlink_mission_request_list_t   mavlink_mission_request_list_struct;
static mavlink_mission_request_t        mavlink_mission_request_struct;
static mavlink_mission_item_t           mavlink_mission_item_struct;
static mavlink_mission_clear_all_t      mavlink_mission_clear_all_struct;
static mavlink_mission_set_current_t    mavlink_mission_set_current_struct;
static mavlink_mission_count_t          mavlink_mission_count_struct;
static mavlink_mission_ack_t            mavlink_mission_ack_struct;

static Mail param_set_mail      = {NULL, MAVLINK_MSG_ID_PARAM_SET,      NULL};
static Mail command_long_mail   = {NULL, MAVLINK_MSG_ID_COMMAND_LONG,   NULL};
static Mail manual_control_mail = {NULL, MAVLINK_MSG_ID_MANUAL_CONTROL, NULL};
static Mail set_mode_mail       = {NULL, MAVLINK_MSG_ID_SET_MODE,       NULL};
static Mail mission_mail        = {NULL, MAVLINK_MSG_ID_MISSION_REQUEST,NULL};

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

/* определяет, кому пришло это сообщение и кидает в соотверствующий почтовый ящик */
bool_t sort_input_messages(mavlink_message_t *msg){
  msg_t status = RDY_OK;

  switch(msg->msgid){

  /* automatically generated handler */
  case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
    mavlink_msg_param_request_list_decode(msg, &mavlink_param_request_list_struct);
    if (mavlink_param_request_list_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    param_set_mail.invoice = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;
    param_set_mail.payload = &mavlink_param_request_list_struct;
    status = chMBPost(&mavlink_param_set_mb, (msg_t)&param_set_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
    mavlink_msg_param_request_read_decode(msg, &mavlink_param_request_read_struct);
    if (mavlink_param_request_read_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    param_set_mail.invoice = MAVLINK_MSG_ID_PARAM_REQUEST_READ;
    param_set_mail.payload = &mavlink_param_request_read_struct;
    status = chMBPost(&mavlink_param_set_mb, (msg_t)&param_set_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_PARAM_SET:
    mavlink_msg_param_set_decode(msg, &mavlink_param_set_struct);
    if (mavlink_param_set_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    param_set_mail.invoice = MAVLINK_MSG_ID_PARAM_SET;
    param_set_mail.payload = &mavlink_param_set_struct;
    status = chMBPost(&mavlink_param_set_mb, (msg_t)&param_set_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_COMMAND_LONG:
    mavlink_msg_command_long_decode(msg, &mavlink_command_long_struct);
    if (mavlink_command_long_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    command_long_mail.invoice = MAVLINK_MSG_ID_COMMAND_LONG;
    command_long_mail.payload = &mavlink_command_long_struct;
    status = chMBPost(&mavlink_command_long_mb, (msg_t)&command_long_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MANUAL_CONTROL:
    mavlink_msg_manual_control_decode(msg, &mavlink_manual_control_struct);
    if (mavlink_manual_control_struct.target != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    manual_control_mail.invoice = MAVLINK_MSG_ID_MANUAL_CONTROL;
    manual_control_mail.payload = &mavlink_manual_control_struct;
    status = chMBPost(&controller_mb, (msg_t)&manual_control_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_SET_MODE:
    mavlink_msg_set_mode_decode(msg, &mavlink_set_mode_struct);
    if (mavlink_set_mode_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    set_mode_mail.invoice = MAVLINK_MSG_ID_SET_MODE;
    set_mode_mail.payload = &mavlink_set_mode_struct;
    status = chMBPost(&controller_mb, (msg_t)&set_mode_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;










     /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
    mavlink_msg_mission_request_list_decode(msg, &mavlink_mission_request_list_struct);
    if (mavlink_mission_request_list_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_REQUEST_LIST;
    mission_mail.payload = &mavlink_mission_request_list_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_REQUEST:
    mavlink_msg_mission_request_decode(msg, &mavlink_mission_request_struct);
    if (mavlink_mission_request_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_REQUEST;
    mission_mail.payload = &mavlink_mission_request_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_ITEM:
    mavlink_msg_mission_item_decode(msg, &mavlink_mission_item_struct);
    if (mavlink_mission_item_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_ITEM;
    mission_mail.payload = &mavlink_mission_item_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_COUNT:
    mavlink_msg_mission_count_decode(msg, &mavlink_mission_count_struct);
    if (mavlink_mission_count_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_COUNT;
    mission_mail.payload = &mavlink_mission_count_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_ACK:
    mavlink_msg_mission_ack_decode(msg, &mavlink_mission_ack_struct);
    if (mavlink_mission_ack_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_ACK;
    mission_mail.payload = &mavlink_mission_ack_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
    mavlink_msg_mission_clear_all_decode(msg, &mavlink_mission_clear_all_struct);
    if (mavlink_mission_clear_all_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_CLEAR_ALL;
    mission_mail.payload = &mavlink_mission_clear_all_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;

  /* automatically generated handler */
  case MAVLINK_MSG_ID_MISSION_SET_CURRENT:
    mavlink_msg_mission_set_current_decode(msg, &mavlink_mission_set_current_struct);
    if (mavlink_mission_set_current_struct.target_system != mavlink_system_struct.sysid)
      return LINK_SUCCESS; /* silently ignore messages not for this system */
    mission_mail.invoice = MAVLINK_MSG_ID_MISSION_SET_CURRENT;
    mission_mail.payload = &mavlink_mission_set_current_struct;
    status = chMBPost(&mission_mb, (msg_t)&mission_mail, TIME_IMMEDIATE);
    if (status != RDY_OK)
      return LINK_FAILED;
    else
      return LINK_SUCCESS;
    break;













  case MAVLINK_MSG_ID_HEARTBEAT:
    break;

  default:
    //Do nothing
    break;
  }

  return LINK_SUCCESS;
}


/*
 *******************************************************************************
 * Old junk for hystorical purpose
 *******************************************************************************
 */
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
