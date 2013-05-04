#include <stdio.h>

#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "waypoint_db.hpp"
#include "wps.hpp"
#include "mavdbg.hpp"
#include "eeprom_file_tree.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
//MAVLINK_WPM_PROTOCOL_TIMEOUT_DEFAULT
#define PLANNER_STANDBY_TMO     MS2ST(20) /* poll inbox period waiting message from ground */
#define PLANNER_RETRY_CNT       5
#define PLANNER_RETRY_TMO       MS2ST(1000)
#define PLANNER_ADDITIONAL_TMO  MS2ST(10)

#define TARGET_RADIUS         param2  /* dirty fix to correspond QGC not mavlink lib */
#define MIN_TARGET_RADIUS     5       /* minimal allowed waypoint radius */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern WpDB wpdb;

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
  //mavlink_out_mission_ack_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
  mavlink_out_mission_ack_struct.target_system = GROUND_STATION_ID;
  mavlink_out_mission_ack_struct.type = type;

  chEvtBroadcastFlags(&event_mavlink_out_mission_ack, EVMSK_MAVLINK_OUT_MISSION_ACK);
}

/**
 * Lazy clear all routine.
 */
static void mission_clear_all(void){
  if (CH_SUCCESS == wpdb.clear())
    send_ack(MAV_MISSION_ACCEPTED);
  else
    send_ack(MAV_MISSION_ERROR);
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
 *
 */
static bool gcs2mav(uint16_t N){
  uint32_t seq = 0;
  uint32_t retry_cnt = PLANNER_RETRY_CNT;
  eventmask_t evt = 0;
  mavlink_mission_item_t mi;        /* local copy */
  uint8_t status = MAV_MISSION_ERROR;

  /* check available space */
  if (N > wpdb.getCapacity()){
    send_ack(MAV_MISSION_NO_SPACE);
    return CH_FAILED;
  }

  /* prepare to harvest waypoints */
  struct EventListener el_mission_item;
  chEvtRegisterMask(&event_mavlink_in_mission_item, &el_mission_item, EVMSK_MAVLINK_IN_MISSION_ITEM);
  chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_ITEM, 1);/* fake wait to clear "queue" */
  if (CH_FAILED == wpdb.clear())
    chDbgPanic("");

  for (seq=0; seq<N; seq++){
    /* prepare request to ground */
    mavlink_out_mission_request_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
    mavlink_out_mission_request_struct.target_system = GROUND_STATION_ID;
    mavlink_out_mission_request_struct.seq = seq;
    retry_cnt = PLANNER_RETRY_CNT;
    chThdSleep(PLANNER_ADDITIONAL_TMO);

    do{
      /* drop message */
      chEvtBroadcastFlags(&event_mavlink_out_mission_request, EVMSK_MAVLINK_OUT_MISSION_REQUEST);

      /* wait answer */
      evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_ITEM, PLANNER_RETRY_TMO);
      if (EVMSK_MAVLINK_IN_MISSION_ITEM == evt){
        chSysLock();
        mi = mavlink_in_mission_item_struct;
        chSysUnlock();

        /* check waypoint cosherness and write it if cosher */
        status = check_wp(&mi, seq);
        if (status != MAV_MISSION_ACCEPTED)
          goto EXIT;
        else{
          if (CH_FAILED == wpdb.save(&mi, seq))
            chDbgPanic("");
          break; /* do-while */
        }
      }

      retry_cnt--;
      if(0 == retry_cnt)
        goto EXIT;

    }while(retry_cnt);
  }
  /* save waypoint count in eeprom only in the very end of transaction */
  if (CH_FAILED == wpdb.finalize())
    chDbgPanic("");

  /* final stuff */
EXIT:
  chEvtUnregister(&event_mavlink_in_mission_item, &el_mission_item);
  send_ack(status);
  if (0 == retry_cnt)
    return CH_FAILED;
  else
    return CH_SUCCESS;
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
static bool mav2gcs(void){
  eventmask_t evt = 0;
  bool status = CH_FAILED;
  uint32_t retry_cnt = PLANNER_RETRY_CNT;

  struct EventListener el_mission_request;
  struct EventListener el_mission_ack;
  struct EventListener el_mission_request_list;
  chEvtRegisterMask(&event_mavlink_in_mission_request_list, &el_mission_request_list, EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST);
  chEvtRegisterMask(&event_mavlink_in_mission_request,      &el_mission_request,      EVMSK_MAVLINK_IN_MISSION_REQUEST);
  chEvtRegisterMask(&event_mavlink_in_mission_ack,          &el_mission_ack,          EVMSK_MAVLINK_IN_MISSION_ACK);

START:
  mavlink_out_mission_count_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
  mavlink_out_mission_count_struct.target_system = GROUND_STATION_ID;
  mavlink_out_mission_count_struct.count = wpdb.getCount();

  chEvtBroadcastFlags(&event_mavlink_out_mission_count, EVMSK_MAVLINK_OUT_MISSION_COUNT);

  if (0 == mavlink_out_mission_count_struct.count){
    status = CH_SUCCESS;
    goto EXIT;
  }


  /* теперь нам надо понять, дошло сообщение с количеством вейпоинтов, или нет.
   * Если нет - земля пришле повторный запрос MISSION_REQUEST_LIST */
  evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST |
                            EVMSK_MAVLINK_IN_MISSION_REQUEST |
                            EVMSK_MAVLINK_IN_MISSION_ACK,
                            PLANNER_RETRY_TMO * PLANNER_RETRY_CNT);
  switch(evt){
  case EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST:
    /* надобно повторить */
    goto START;

  /* maint loooong loop */
  case EVMSK_MAVLINK_IN_MISSION_REQUEST:
    do{
      wpdb.load(&mavlink_out_mission_item_struct, mavlink_in_mission_request_struct.seq);
      mavlink_out_mission_item_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
      mavlink_out_mission_item_struct.target_system = GROUND_STATION_ID;
      chEvtBroadcastFlags(&event_mavlink_out_mission_item, EVMSK_MAVLINK_OUT_MISSION_ITEM);
      /* wait next request or ack */
      evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_REQUEST |
                                EVMSK_MAVLINK_IN_MISSION_ACK,
                                PLANNER_RETRY_TMO);
      switch(evt){
      case EVMSK_MAVLINK_IN_MISSION_REQUEST:
        continue;

      case EVMSK_MAVLINK_IN_MISSION_ACK:
        status = CH_SUCCESS;
        goto EXIT;
        break;

      default:
        retry_cnt--;
        status = CH_FAILED;
        break;
      }
    }while(retry_cnt);
    break; /* case EVMSK_MAVLINK_IN_MISSION_REQUEST */

  case EVMSK_MAVLINK_IN_MISSION_ACK:
    status = CH_SUCCESS;
    break;

  default:
    status = CH_FAILED;
    break;
  }

EXIT:
  chEvtUnregister(&event_mavlink_in_mission_request, &el_mission_request);
  chEvtUnregister(&event_mavlink_in_mission_ack,     &el_mission_ack);
  chEvtUnregister(&event_mavlink_in_mission_request_list, &el_mission_request_list);
  return status;
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

  struct EventListener el_mission_request_list;
  struct EventListener el_mission_count;
  struct EventListener el_mission_clear_all;
  struct EventListener el_mission_item;

  chEvtRegisterMask(&event_mavlink_in_mission_request_list, &el_mission_request_list, EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST);
  chEvtRegisterMask(&event_mavlink_in_mission_count,        &el_mission_count,        EVMSK_MAVLINK_IN_MISSION_COUNT);
  chEvtRegisterMask(&event_mavlink_in_mission_clear_all,    &el_mission_clear_all,    EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL);
  chEvtRegisterMask(&event_mavlink_in_mission_item,         &el_mission_item,         EVMSK_MAVLINK_IN_MISSION_ITEM);

  eventmask_t evt = 0;
  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST |
                              EVMSK_MAVLINK_IN_MISSION_COUNT |
                              EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL |
                              EVMSK_MAVLINK_IN_MISSION_ITEM,
                              MS2ST(100));
    switch (evt){

    /* ground want to know how many items we have */
    case EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST:
      chEvtUnregister(&event_mavlink_in_mission_request_list, &el_mission_request_list);
      mav2gcs();
      chEvtRegisterMask(&event_mavlink_in_mission_request_list, &el_mission_request_list, EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST);
      break;

    /* ground says how many items it wants to send here */
    case EVMSK_MAVLINK_IN_MISSION_COUNT:
      /* this event now will be handled inside write loop */
      chEvtUnregister(&event_mavlink_in_mission_item, &el_mission_item);
      gcs2mav(mavlink_in_mission_count_struct.count);
      /* register event back to main cycle */
      chEvtRegisterMask(&event_mavlink_in_mission_item, &el_mission_item, EVMSK_MAVLINK_IN_MISSION_ITEM);
      break;

    /* ground wants erase all wps */
    case EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL:
      mission_clear_all();
      break;

    case EVMSK_MAVLINK_IN_MISSION_ITEM:
      /* If a waypoint planner component receives WAYPOINT messages outside
       * of transactions it answers with a WAYPOINT_ACK message. */
      send_ack(MAV_MISSION_DENIED);
      break;

    default:
      //chDbgPanic("unimplemented");
      break;
    }
  }

  chEvtUnregister(&event_mavlink_in_mission_request_list, &el_mission_request_list);
  chEvtUnregister(&event_mavlink_in_mission_count,        &el_mission_count);
  chEvtUnregister(&event_mavlink_in_mission_clear_all,    &el_mission_clear_all);
  chEvtUnregister(&event_mavlink_in_mission_item,         &el_mission_item);

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
