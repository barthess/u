/* 
!!! Atomatically generated by
src/link/gen_link_unpacker.py
Do not edit it manually. 
*/
#include "uav.h"

extern GlobalFlags_t GlobalFlags;

extern mavlink_system_t mavlink_system_struct;
extern mavlink_command_long_t mavlink_command_long_struct;
extern mavlink_param_request_read_t mavlink_param_request_read_struct;
extern mavlink_param_request_list_t mavlink_param_request_list_struct;
extern mavlink_param_set_t mavlink_param_set_struct;
extern mavlink_mission_item_t mavlink_mission_item_struct;
extern mavlink_mission_request_t mavlink_mission_request_struct;
extern mavlink_mission_clear_all_t mavlink_mission_clear_all_struct;
extern mavlink_mission_set_current_t mavlink_mission_set_current_struct;

extern EventSource event_mavlink_in_command_long;
extern EventSource event_mavlink_in_param_request_read;
extern EventSource event_mavlink_in_param_request_list;
extern EventSource event_mavlink_in_param_set;
extern EventSource event_mavlink_in_mission_item;
extern EventSource event_mavlink_in_mission_request;
extern EventSource event_mavlink_in_mission_clear_all;
extern EventSource event_mavlink_in_mission_set_current;



/**
 *
 */
void UnpackCycle(SerialDriver *sdp){
  mavlink_message_t msg;
  mavlink_status_t status;
  msg_t c = 0;

  while(GlobalFlags.messaging_ready == 0)
    chThdSleepMilliseconds(50);

  while (!chThdShouldTerminate()) {
    c = sdGetTimeout((SerialDriver *)sdp, MS2ST(50));
    if (c != Q_TIMEOUT){
      if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &status)) {
        switch(msg.msgid){
        case MAVLINK_MSG_ID_COMMAND_LONG:
          mavlink_msg_command_long_decode(&msg, &mavlink_command_long_struct);
          if (mavlink_command_long_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_command_long, EVMSK_MAVLINK_IN_COMMAND_LONG);
          break;

        case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
          mavlink_msg_param_request_read_decode(&msg, &mavlink_param_request_read_struct);
          if (mavlink_param_request_read_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_param_request_read, EVMSK_MAVLINK_IN_PARAM_REQUEST_READ);
          break;

        case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
          mavlink_msg_param_request_list_decode(&msg, &mavlink_param_request_list_struct);
          if (mavlink_param_request_list_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_param_request_list, EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST);
          break;

        case MAVLINK_MSG_ID_PARAM_SET:
          mavlink_msg_param_set_decode(&msg, &mavlink_param_set_struct);
          if (mavlink_param_set_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_param_set, EVMSK_MAVLINK_IN_PARAM_SET);
          break;

        case MAVLINK_MSG_ID_MISSION_ITEM:
          mavlink_msg_mission_item_decode(&msg, &mavlink_mission_item_struct);
          if (mavlink_mission_item_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_mission_item, EVMSK_MAVLINK_IN_MISSION_ITEM);
          break;

        case MAVLINK_MSG_ID_MISSION_REQUEST:
          mavlink_msg_mission_request_decode(&msg, &mavlink_mission_request_struct);
          if (mavlink_mission_request_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_mission_request, EVMSK_MAVLINK_IN_MISSION_REQUEST);
          break;

        case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
          mavlink_msg_mission_clear_all_decode(&msg, &mavlink_mission_clear_all_struct);
          if (mavlink_mission_clear_all_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_mission_clear_all, EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL);
          break;

        case MAVLINK_MSG_ID_MISSION_SET_CURRENT:
          mavlink_msg_mission_set_current_decode(&msg, &mavlink_mission_set_current_struct);
          if (mavlink_mission_set_current_struct.target_system == mavlink_system_struct.sysid)
            chEvtBroadcastFlags(&event_mavlink_in_mission_set_current, EVMSK_MAVLINK_IN_MISSION_SET_CURRENT);
          break;


        default:
          break;
        }
      }
    }
  }
}
