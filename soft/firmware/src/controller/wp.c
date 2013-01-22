#include "uav.h"

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
extern uint16_t WpSeqNew;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
extern mavlink_mission_current_t        mavlink_mission_current_struct;
extern mavlink_mission_item_reached_t   mavlink_mission_item_reached_struct;

extern EventSource event_mavlink_out_mission_current;
extern EventSource event_mavlink_out_mission_item_reached;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void WpSeqOverwrite(uint16_t seq){
  if (WpSeqNew < get_waypoint_count()){
    chSysLock();
    WpSeqNew = seq;
    chSysUnlock();
  }
}

/**
 *
 */
void broadcast_mission_current(uint16_t seq){
  mavlink_mission_current_struct.seq = seq;

  chEvtBroadcastFlags(&event_mavlink_out_mission_current, EVMSK_MAVLINK_OUT_MISSION_CURRENT);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_CURRENT, NULL, 0);
}

/**
 *
 */
void broadcast_mission_item_reached(uint16_t seq){
  mavlink_mission_item_reached_struct.seq = seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_item_reached, EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL, 0);
}

/**
 * Get waypoint from EEPROM
 * determine its type and call specialized routine
 */
goto_wp_result_t goto_wp(uint16_t seq){
  mavlink_mission_item_t wp;
  bool_t status = WP_FAILED;

  /* get current waypoint */
  status = get_waypoint_from_eeprom(seq, &wp);
  if (status != WP_SUCCESS)
    return WP_GOTO_FAILED;
  else{
    switch (wp.frame){
    case MAV_FRAME_LOCAL_NED:
      return goto_wp_local_ned(&wp);
      break;

    case MAV_FRAME_GLOBAL:
      return goto_wp_global(&wp);
      break;

    default:
      chDbgPanic("Frame unsupported");
      break;
    }
  }

  return WP_GOTO_FAILED;
}
