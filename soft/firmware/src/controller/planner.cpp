#include <stdio.h>

#include "uav.h"
#include "global_flags.h"
#include "message.hpp"
#include "waypoint_db.hpp"
#include "wps.hpp"
#include "mavlink_dbg.hpp"
#include "eeprom_file_tree.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
//MAVLINK_WPM_PROTOCOL_TIMEOUT_DEFAULT
#define PLANNER_STANDBY_TMO   MS2ST(20) /* poll inbox period waiting message from ground */
#define PLANNER_RETRY_CNT     5
#define PLANNER_RETRY_TMO     MS2ST(1000)

#define TARGET_RADIUS         param2  /* dirty fix to correspond QGC not mavlink lib */
#define MIN_TARGET_RADIUS     5       /* minimal allowed waypoint radius */
/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
WpDB wpdb;

extern GlobalFlags_t  GlobalFlags;
extern EepromFile     MissionFile;

extern mavlink_mission_count_t        mavlink_in_mission_count_struct;
extern mavlink_mission_count_t        mavlink_out_mission_count_struct;

extern mavlink_mission_request_t      mavlink_in_mission_request_struct;
extern mavlink_mission_request_t      mavlink_out_mission_request_struct;

extern mavlink_mission_ack_t          mavlink_in_mission_ack_struct;
extern mavlink_mission_ack_t          mavlink_out_mission_ack_struct;

extern mavlink_mission_item_t         mavlink_in_mission_item_struct;
extern mavlink_mission_item_t         mavlink_out_mission_item_struct;

extern EventSource event_mavlink_in_mission_clear_all;
extern EventSource event_mavlink_in_mission_request_list;

extern EventSource event_mavlink_in_mission_item;
extern EventSource event_mavlink_out_mission_item;
extern EventSource event_mavlink_in_mission_request;
extern EventSource event_mavlink_out_mission_request;
extern EventSource event_mavlink_in_mission_count;
extern EventSource event_mavlink_out_mission_count;
extern EventSource event_mavlink_in_mission_ack;
extern EventSource event_mavlink_out_mission_ack;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Thread *planner_tp = NULL;
static uint16_t waypoint_cnt = 0;
static char dbg_str[64];

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 *
 */
static void send_ack(uint8_t type){
  /* logically the target_component must be MAV_COMP_ID_MISSIONPLANNER,
   * but QGC does not accept them. */
  mavlink_out_mission_ack_struct.target_component = MAV_COMP_ID_ALL;
  mavlink_out_mission_ack_struct.target_system = GROUND_STATION_ID;
  mavlink_out_mission_ack_struct.type = type;

  chEvtBroadcastFlags(&event_mavlink_out_mission_ack, EVMSK_MAVLINK_OUT_MISSION_ACK);
}

/**
 * Lazy clear all routine.
 */
static void mission_clear_all(void){
  wpdb.clear();
  send_ack(MAV_MISSION_ACCEPTED);
}

/**
 * helper functions
 */
static void __send(uint32_t out_evid){
  switch(out_evid){
  case EVMSK_MAVLINK_OUT_MISSION_COUNT:
    chEvtBroadcastFlags(&event_mavlink_out_mission_count, EVMSK_MAVLINK_OUT_MISSION_COUNT);
    break;
  case EVMSK_MAVLINK_OUT_MISSION_ITEM:
    chEvtBroadcastFlags(&event_mavlink_out_mission_item, EVMSK_MAVLINK_OUT_MISSION_ITEM);
    break;
  case EVMSK_MAVLINK_OUT_MISSION_REQUEST:
    chEvtBroadcastFlags(&event_mavlink_out_mission_request, EVMSK_MAVLINK_OUT_MISSION_REQUEST);
    break;
  }
}

/**
 * @brief   Broadcasts event for sending of data.
 * @details Do some tries and waits until confirm message got.
 *
 * @param[in] out_evid    event ID scheduled for broadcast.
 * @param[in] in_evid_msk event ID confirmation message. Can be mask
 *                        of some events at onece. Set it to 0 to disable
 *                        waiting of confirmation.
 *
 * @return              Catched confirmation message id.
 * @retval 0            if the operation has timed out, or no confirmation
 *                      needed.
 */
static eventmask_t send_with_confirm(uint32_t out_evid, uint32_t in_evid_msk, int32_t retry_cnt){
  eventmask_t evt = 0;

  do{
    __send(out_evid);
    if (in_evid_msk == 0) // no need of confirmation
      return 0;

    evt = chEvtWaitOneTimeout(in_evid_msk, PLANNER_RETRY_TMO);
    if (evt & in_evid_msk)
      return evt;
    else
      retry_cnt--;
  }while(retry_cnt > 0);

  return 0;
}

/**
 * @details    When the last waypoint was successfully received
 *             the requesting component sends a WAYPOINT_ACK message
 *             to the targeted component. This finishes the transaction.
 *             Notice that the targeted component has to listen to
 *             WAYPOINT_REQUEST messages of the last waypoint until it
 *             gets the WAYPOINT_ACK or another message that starts
 *             a different transaction or a timeout happens.
 */
static MAVLINK_WPM_STATES mission_item_request_handler(void){
  eventmask_t status = 0;

  // NOTE: first mission request already received
  do{
    if (mavlink_in_mission_request_struct.seq >= waypoint_cnt) // prevent EEPROM overflow
      return MAVLINK_WPM_STATE_IDLE;

    wpdb.load(&mavlink_out_mission_item_struct, mavlink_in_mission_request_struct.seq);
    mavlink_out_mission_item_struct.target_system = GROUND_STATION_ID;
    mavlink_out_mission_item_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;

    status = send_with_confirm(EVMSK_MAVLINK_OUT_MISSION_ITEM,
                               EVMSK_MAVLINK_IN_MISSION_REQUEST | EVMSK_MAVLINK_IN_MISSION_ACK,
                               PLANNER_RETRY_CNT);

    if (status == 0) // time is out
      return MAVLINK_WPM_STATE_IDLE;

    if (status & EVMSK_MAVLINK_IN_MISSION_ACK)// the end
      return MAVLINK_WPM_STATE_IDLE;

    if (status & EVMSK_MAVLINK_IN_MISSION_REQUEST) // GCS wants next WP
      continue;
  }while(TRUE);

  return MAVLINK_WPM_STATE_IDLE;
}

/**
 * Handle mission request list message.
 */
static MAVLINK_WPM_STATES mission_request_list_handler(void){

  eventmask_t status = 0;

  waypoint_cnt = wpdb.len();
  mavlink_out_mission_count_struct.count = waypoint_cnt;
  mavlink_out_mission_count_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
  mavlink_out_mission_count_struct.target_system = GROUND_STATION_ID;

  if (mavlink_out_mission_count_struct.count == 0){
    send_with_confirm(EVMSK_MAVLINK_OUT_MISSION_COUNT, 0, 0);
    return MAVLINK_WPM_STATE_IDLE;
  }
  else{
    status = send_with_confirm(EVMSK_MAVLINK_OUT_MISSION_COUNT,
                               EVMSK_MAVLINK_IN_MISSION_REQUEST,
                               PLANNER_RETRY_CNT);
    if (status == EVMSK_MAVLINK_IN_MISSION_REQUEST){
      /* start long and slow receiving cycle */
      return mission_item_request_handler();
    }
    else
      return MAVLINK_WPM_STATE_IDLE;
  }
}

/**
 * Perform waypoint checking
 */
static uint8_t check_wp(mavlink_mission_item_t *wp, uint16_t seq){
  if ((wp->frame != MAV_FRAME_GLOBAL) && (wp->frame != MAV_FRAME_LOCAL_NED)){
    snprintf(dbg_str, sizeof(dbg_str), "%s%d",
                                 "PLANNER: Unsupported frame #", (int)wp->seq);
    mavlink_dbg_print(MAV_SEVERITY_WARNING, dbg_str);
    return MAV_MISSION_UNSUPPORTED_FRAME;
  }
  if (wp->seq != seq){
    snprintf(dbg_str, sizeof(dbg_str), "%s%d - %d",
                        "PLANNER: Invalid sequence #", (int)wp->seq, (int)seq);
    mavlink_dbg_print(MAV_SEVERITY_WARNING, dbg_str);
    return MAV_MISSION_INVALID_SEQUENCE;
  }
  if (wp->TARGET_RADIUS < MIN_TARGET_RADIUS){
    snprintf(dbg_str, sizeof(dbg_str), "%s%d",
                          "PLANNER: Not enough target radius #", (int)wp->seq);
    mavlink_dbg_print(MAV_SEVERITY_WARNING, dbg_str);
    return MAV_MISSION_INVALID_PARAM1;
  }

  /* no errors found */
  return MAV_MISSION_ACCEPTED;
}

/**
 * Save waypoints in EEPROM
 */
static bool_t mission_count_handler(void){
  eventmask_t status = 0;

  waypoint_cnt = mavlink_in_mission_count_struct.count;

  mavlink_out_mission_request_struct.seq = 0;
  uint8_t type = MAV_MISSION_ERROR;

  /* check available space */
  if (waypoint_cnt * sizeof(mavlink_mission_item_t) > EEPROM_MISSION_SIZE){
    send_ack(MAV_MISSION_NO_SPACE);
    return MAVLINK_WPM_STATE_IDLE;
  }

  /* start transaction from clean state to be safer */
  wpdb.clear();

  /* delete from "queue" probably stored old message */
  chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_ITEM, MS2ST(1));

  /* save waypoints one by one */
  do{
    mavlink_out_mission_request_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
    mavlink_out_mission_request_struct.target_system = GROUND_STATION_ID;

    /* send request to ground */
    status = send_with_confirm(EVMSK_MAVLINK_OUT_MISSION_REQUEST,
                               EVMSK_MAVLINK_IN_MISSION_ITEM,
                               PLANNER_RETRY_CNT);
    /* handle answer */
    if (status == EVMSK_MAVLINK_IN_MISSION_ITEM){
      type = check_wp(&mavlink_in_mission_item_struct, mavlink_out_mission_request_struct.seq);
      if (type != MAV_MISSION_ACCEPTED)
        goto EXIT;
      else{
        wpdb.save(&mavlink_in_mission_item_struct, mavlink_out_mission_request_struct.seq);
        mavlink_out_mission_request_struct.seq++;
      }
    }
    else
      goto EXIT;
  }while(mavlink_out_mission_request_struct.seq < waypoint_cnt);

  /* save waypoint count in eeprom only in the very end of transaction */
  wpdb.finalize();
EXIT:
  send_ack(type);
  return MAVLINK_WPM_STATE_IDLE;
}

/**
 * Planner thread.
 * process mission commands from ground
 */
static WORKING_AREA(PlannerThreadWA, 768);
static msg_t PlannerThread(void* arg){
  chRegSetThreadName("Planner");
  (void)arg;

  while(GlobalFlags.messaging_ready == 0)
    chThdSleepMilliseconds(50);

  /* register here _all_ events used by planner. Some of them will be
   * handled in subroutines called in thread context. */
  struct EventListener el_mission_request_list;
  struct EventListener el_mission_count;
  struct EventListener el_mission_clear_all;
  struct EventListener el_mission_item;
  struct EventListener el_mission_request;
  struct EventListener el_mission_ack;

  chEvtRegisterMask(&event_mavlink_in_mission_request,      &el_mission_request,      EVMSK_MAVLINK_IN_MISSION_REQUEST);
  chEvtRegisterMask(&event_mavlink_in_mission_request_list, &el_mission_request_list, EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST);
  chEvtRegisterMask(&event_mavlink_in_mission_count,        &el_mission_count,        EVMSK_MAVLINK_IN_MISSION_COUNT);
  chEvtRegisterMask(&event_mavlink_in_mission_clear_all,    &el_mission_clear_all,    EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL);
  chEvtRegisterMask(&event_mavlink_in_mission_item,         &el_mission_item,         EVMSK_MAVLINK_IN_MISSION_ITEM);
  chEvtRegisterMask(&event_mavlink_in_mission_ack,          &el_mission_ack,          EVMSK_MAVLINK_IN_MISSION_ACK);

  eventmask_t evt = 0;
  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST |
                              EVMSK_MAVLINK_IN_MISSION_COUNT |
                              EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL,
                              MS2ST(100));
    switch (evt){
    case EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST:
      /* ground want to know how many items we have */
      mission_request_list_handler();
      break;

    case EVMSK_MAVLINK_IN_MISSION_COUNT:
      /* ground says how many items it wants to send here */
      mission_count_handler();
      break;

    case EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL:
      /* ground wants erase all wps */
      mission_clear_all();
      break;

    default:
      //chDbgPanic("unimplemented");
      break;
    }
  }

  chEvtUnregister(&event_mavlink_in_mission_request_list, &el_mission_request_list);
  chEvtUnregister(&event_mavlink_in_mission_count,        &el_mission_count);
  chEvtUnregister(&event_mavlink_in_mission_clear_all,    &el_mission_clear_all);
  chEvtUnregister(&event_mavlink_in_mission_request,      &el_mission_request);
  chEvtUnregister(&event_mavlink_in_mission_item,         &el_mission_item);
  chEvtUnregister(&event_mavlink_in_mission_ack,          &el_mission_ack);

  chThdExit(0);
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* PlannerInit(void){

  MavlinkWpmInit();

  wpdb.connect(&MissionFile);

  planner_tp = chThdCreateStatic(PlannerThreadWA,
                        sizeof(PlannerThreadWA),
                        CONTROLLER_THREADS_PRIO,
                        PlannerThread,
                        NULL);

  if (planner_tp == NULL)
    chDbgPanic("can not allocate memory");

  return planner_tp;
}
