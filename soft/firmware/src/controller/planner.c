#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
//MAVLINK_WPM_PROTOCOL_TIMEOUT_DEFAULT
#define PLANNER_STANDBY_TMO   MS2ST(20) /* poll inbox period waiting message from ground */
#define PLANNER_RETRY_CNT     5
#define PLANNER_RETRY_TMO     MS2ST(1000)
#define PLANNER_POST_TMO      MS2ST(2000)

#define TARGET_RADIUS         param2  /* dirty fix to correspond QGC not mavlink lib */
#define MIN_TARGET_RADIUS     5       /* minimal allowed waypoint radius */
/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox                    tolink_mb;
extern Mailbox                    mission_mb;

extern mavlink_mission_count_t    mavlink_mission_count_struct;
extern mavlink_mission_item_t     mavlink_mission_item_struct;
extern mavlink_mission_request_t  mavlink_mission_request_struct;
extern mavlink_mission_ack_t      mavlink_mission_ack_struct;

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
static Mail mission_out_mail = {NULL, MAVLINK_MSG_ID_MISSION_COUNT, NULL};

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
  msg_t status = RDY_RESET;

  /* logically the target_component must be MAV_COMP_ID_MISSIONPLANNER,
   * but QGC does not accept them. */
  mavlink_mission_ack_struct.target_component = MAV_COMP_ID_ALL;
  mavlink_mission_ack_struct.target_system = GROUND_STATION_ID;
  mavlink_mission_ack_struct.type = type;
  mission_out_mail.payload = &mavlink_mission_ack_struct;
  mission_out_mail.invoice = MAVLINK_MSG_ID_MISSION_ACK;
  status = chMBPost(&tolink_mb, (msg_t)(&mission_out_mail), PLANNER_POST_TMO);
  if (status != RDY_OK)
    chDbgPanic("time is out");
}

/**
 * Fast clear all routine.
 */
static void mission_clear_all(void){
  save_waypoint_count(0);
  send_ack(MAV_MISSION_ACCEPTED);
}

/**
 *
 */
static Mail* send_with_tmo(Mail* outmailp, bool_t retry){
  msg_t status = RDY_RESET;
  msg_t msg = 0;
  uint32_t retry_cnt;

  if (retry)
    retry_cnt = PLANNER_RETRY_CNT;
  else
    retry_cnt = 1;

  while(retry_cnt > 0){
    status = chMBPost(&tolink_mb, (msg_t)outmailp, PLANNER_POST_TMO);
    if (status != RDY_OK)
      chDbgPanic("time is out");

    /* wait any data */
    status = chMBFetch(&mission_mb, &msg, PLANNER_RETRY_TMO);
    if (status == RDY_OK){
      return (Mail*)msg;
    }
    else
      retry_cnt--;
  }
  return NULL;
}

/**
 *
 */
static MAVLINK_WPM_STATES mission_item_request_handler(Mail* mailp){
  mavlink_mission_request_t *mr;

  do{
    if (mailp->invoice != MAVLINK_MSG_ID_MISSION_REQUEST)
      break;

    mr = mailp->payload;
    get_waypoint_from_eeprom(mr->seq, &mavlink_mission_item_struct);
    ReleaseMail(mailp);

    mavlink_mission_item_struct.target_system = GROUND_STATION_ID;
    mavlink_mission_item_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
    mission_out_mail.payload = &mavlink_mission_item_struct;
    mission_out_mail.invoice = MAVLINK_MSG_ID_MISSION_ITEM;

    mailp = send_with_tmo(&mission_out_mail, TRUE);
    if (mailp->invoice != MAVLINK_MSG_ID_MISSION_REQUEST)
      break;

  }while((mailp != NULL) && (mailp->invoice == MAVLINK_MSG_ID_MISSION_REQUEST));

  return MAVLINK_WPM_STATE_IDLE;
}

/**
 * Handle mission request list message.
 */
static MAVLINK_WPM_STATES mission_request_list_handler(Mail* mailp){
  mavlink_mission_count_struct.count = get_waypoint_count();
  mavlink_mission_count_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
  mavlink_mission_count_struct.target_system = GROUND_STATION_ID;
  mission_out_mail.payload = &mavlink_mission_count_struct;
  mission_out_mail.invoice = MAVLINK_MSG_ID_MISSION_COUNT;

  if (mavlink_mission_count_struct.count == 0)
    mailp = send_with_tmo(&mission_out_mail, FALSE);
  else
    mailp = send_with_tmo(&mission_out_mail, TRUE);

  if (mailp != NULL)
    return mission_item_request_handler(mailp);
  else
    return MAVLINK_WPM_STATE_IDLE;
}

/**
 * Perform waypoint checking
 */
static uint8_t check_wp(mavlink_mission_item_t *wp, uint16_t seq){
  if ((wp->frame != MAV_FRAME_GLOBAL) && (wp->frame != MAV_FRAME_LOCAL_NED))
    return MAV_MISSION_UNSUPPORTED_FRAME;
  if (wp->seq != seq)
    return MAV_MISSION_INVALID_SEQUENCE;
  if (wp->TARGET_RADIUS < MIN_TARGET_RADIUS)
    return MAV_MISSION_INVALID_PARAM1;

  /* no errors found */
  return MAV_MISSION_ACCEPTED;
}

/**
 * Save waypoints in EEPROM
 */
static bool_t mission_count_handler(Mail* mailp){
  mavlink_mission_count_t *mc = mailp->payload;
  uint16_t waypoint_cnt = mc->count;
  mavlink_mission_request_struct.seq = 0;
  mavlink_mission_item_t *wp = NULL;
  uint8_t type = MAV_MISSION_ERROR;

  /* check available space */
  if (waypoint_cnt * sizeof(mavlink_mission_item_t) > EEPROM_MISSION_SIZE){
    send_ack(MAV_MISSION_NO_SPACE);
    return MAVLINK_WPM_STATE_IDLE;
  }

  /* start transaction from clean state to be safer */
  save_waypoint_count(0);

  /* save waypoints one by one */
  do{
    mavlink_mission_request_struct.target_component = MAV_COMP_ID_MISSIONPLANNER;
    mavlink_mission_request_struct.target_system = GROUND_STATION_ID;
    mission_out_mail.payload = &mavlink_mission_request_struct;
    mission_out_mail.invoice = MAVLINK_MSG_ID_MISSION_REQUEST;

    /* send request to ground */
    mailp = send_with_tmo(&mission_out_mail, TRUE);

    /* wait waypoint */
    if ((mailp != NULL) && (mailp->invoice == MAVLINK_MSG_ID_MISSION_ITEM)){
      wp = mailp->payload;
      type = check_wp(wp, mavlink_mission_request_struct.seq);
      if (type != MAV_MISSION_ACCEPTED)
        break;
      save_waypoint_to_eeprom(mavlink_mission_request_struct.seq, wp);
      mavlink_mission_request_struct.seq++;
    }
    else
      break;
  }while(mavlink_mission_request_struct.seq < waypoint_cnt);

  /* save waypoint count in eeprom only in the end of transaction */
  save_waypoint_count(mavlink_mission_request_struct.seq);
  send_ack(type);
  return MAVLINK_WPM_STATE_IDLE;
}

/**
 * Realize state machine idle state.
 */
static MAVLINK_WPM_STATES msg_handler(Mail* mailp){
  MAVLINK_WPM_STATES status = MAVLINK_WPM_STATE_IDLE;

  switch(mailp->invoice){
  case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
    /* ground want to know how many items we have */
    status = mission_request_list_handler(mailp);
    break;

  case MAVLINK_MSG_ID_MISSION_COUNT:
    /* ground says how many items it wants to send us */
    status = mission_count_handler(mailp);
    break;

  case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
    mission_clear_all();
    break;

  default:
    //chDbgPanic("unimplemented");
    break;
  }
  ReleaseMail(mailp);

  return status;
}

/**
 * Planner thread.
 * process mission commands from ground
 */
static WORKING_AREA(PlannerThreadWA, 512);
static msg_t PlannerThread(void* arg){
  chRegSetThreadName("Planner");
  (void)arg;
  msg_t status = RDY_RESET;
  msg_t msg = 0;

  while (TRUE) {
    /* wait any data */
    status = chMBFetch(&mission_mb, &msg, PLANNER_RETRY_TMO);
    if (status == RDY_OK)
      msg_handler((Mail*)msg);
  }
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* PlannerInit(void){

  MavlinkWpmInit();

  Thread *tp = NULL;

  tp = chThdCreateStatic(PlannerThreadWA,
                        sizeof(PlannerThreadWA),
                        CONTROLLER_THREADS_PRIO,
                        PlannerThread,
                        NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}
