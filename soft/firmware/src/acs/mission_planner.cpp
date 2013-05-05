#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"
#include "ground_rover.hpp"
#include "imu.hpp"
#include "bmp085.hpp"
#include "acs.hpp"
#include "mission_planner.hpp"
#include "waypoint_db.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONFIRM_TMO           MS2ST(500)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern ParamRegistry param_registry;

extern mavlink_system_t mavlink_system_struct;

extern mavlink_manual_control_t mavlink_in_manual_control_struct;
extern mavlink_set_mode_t mavlink_in_set_mode_struct;
extern mavlink_mission_set_current_t mavlink_in_mission_set_current_struct;
extern mavlink_command_ack_t mavlink_out_command_ack_struct;
extern mavlink_command_long_t mavlink_in_command_long_struct;

extern EventSource event_mavlink_in_manual_control;
extern EventSource event_mavlink_in_set_mode;
extern EventSource event_mavlink_in_mission_set_current;
extern EventSource event_mavlink_out_command_ack;
extern EventSource event_mavlink_in_command_long;

extern IMU imu;
extern ACS acs;
extern WpDB wpdb;

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

/**
 * helper funcion
 */
static void cmd_confirm(uint8_t result, uint16_t cmd){
  mavlink_out_command_ack_struct.result = result;
  mavlink_out_command_ack_struct.command = cmd;

  chEvtBroadcastFlags(&event_mavlink_out_command_ack, EVMSK_MAVLINK_OUT_COMMAND_ACK);
}

/**
 * NOTE: Calibration of gyros and magnetometers can not be run simulatiously
 */
static enum MAV_RESULT cmd_calibration_handler(mavlink_command_long_t *cl){
  /* Trigger calibration. This command will be only accepted if in pre-flight mode.
  * | Gyro calibration: 0: no, 1: yes
  * | Magnetometer calibration: 0: no, 1: yes
  * | Ground pressure: 0: no, 1: yes
  * | Radio calibration: 0: no, 1: yes
  * | Empty| Empty| Empty|  */

  bool result;

  if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
    return MAV_RESULT_TEMPORARILY_REJECTED;

  /* Gyro */
  if (cl->param1 == 1){
    result = imu.trigCalibrateGyro();
    if (CH_SUCCESS == result)
      return MAV_RESULT_ACCEPTED;
    else
      return MAV_RESULT_FAILED;
  }

  /* Magnetometer */
  else if (cl->param2 == 1){
    result = imu.trigCalibrateMag();
    if (CH_SUCCESS == result)
      return MAV_RESULT_ACCEPTED;
    else
      return MAV_RESULT_FAILED;
  }

  /* Barometer */
  else if (cl->param3 == 1){
    result = TrigCalibrateBaro();
    if (CH_SUCCESS == result)
      return MAV_RESULT_ACCEPTED;
    else
      return MAV_RESULT_FAILED;
  }

  /* unknown */
  else
    return MAV_RESULT_DENIED;
}

/**
 *
 */
static enum MAV_RESULT cmd_reboot_shutdown_handler(mavlink_command_long_t *cl){
 /* Request the reboot or shutdown of system components.|
  * 0: Do nothing for autopilot, 1: Reboot autopilot, 2: Shutdown autopilot.|
  * 0: Do nothing for onboard computer, 1: Reboot onboard computer, 2: Shutdown onboard computer.
  * | Reserved| Reserved| Empty| Empty| Empty|  */

  if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
    return MAV_RESULT_TEMPORARILY_REJECTED;

  /* you can perform power operation on autopilot OR computer, not both at once */
  if (cl->param1 == 1.0f){/* reboot */
    NVIC_SystemReset();
    return MAV_RESULT_UNSUPPORTED;
  }
  else if (cl->param1 == 2.0f){/* shutdown */
    //setGlobalFlag(GlobalFlags.sighalt);
    return MAV_RESULT_UNSUPPORTED;
  }

  /**/
  if (cl->param2 == 1.0f){/* reboot */
    return MAV_RESULT_UNSUPPORTED;
  }
  else if (cl->param2 == 2.0f){/* shutdown */
    return MAV_RESULT_UNSUPPORTED;
  }

  /* default */
  return MAV_RESULT_UNSUPPORTED;
}

/**
 *
 */
static enum MAV_RESULT cmd_preflight_storage_handler(mavlink_command_long_t *cl){
  bool_t status = CH_FAILED;

  if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
    return MAV_RESULT_TEMPORARILY_REJECTED;

  if (cl->param1 == 0)
    status = param_registry.load();
  else if (cl->param1 == 1)
    status = param_registry.saveAll();

  if (status != CH_SUCCESS)
    return MAV_RESULT_FAILED;
  else
    return MAV_RESULT_ACCEPTED;
}

/**
 * Looks like duplicated functionality of SET_MODE message
 */
static enum MAV_RESULT cmd_do_set_mode_handler(mavlink_command_long_t *cl){
  /* Set system mode. |Mode, as defined by ENUM MAV_MODE| Empty| Empty| Empty| Empty| Empty| Empty|  */
  (void)cl;
  return MAV_RESULT_DENIED;
}


/**
 * Parses and executes commands. Commands can be both from ground or
 * sent by ACS from mission list.
 */
void MissionPlanner::executeCmd(mavlink_command_long_t *clp){
  enum MAV_RESULT result = MAV_RESULT_DENIED;

  /* all this flags defined in MAV_CMD enum */
  switch(clp->command){
  case MAV_CMD_DO_SET_MODE:
    /* */
    result = cmd_do_set_mode_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case MAV_CMD_PREFLIGHT_CALIBRATION:
    /* (re)calibrate */
    result = cmd_calibration_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
    /* */
    result = cmd_reboot_shutdown_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case MAV_CMD_PREFLIGHT_STORAGE:
    /* Data (storing to)/(loding from) EEPROM */
    result = cmd_preflight_storage_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case (MAV_CMD_NAV_TAKEOFF):
    result = acs.takeoff(clp);
    cmd_confirm(result, clp->command);
    break;

  case (MAV_CMD_NAV_RETURN_TO_LAUNCH):
    result = cmd_nav_return_to_launch_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case (MAV_CMD_NAV_LAND):
    result = cmd_nav_land_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  case (MAV_CMD_NAV_LOITER_UNLIM):
    result = acs.loiter(clp);
    cmd_confirm(result, clp->command);
    break;

  case (MAV_CMD_OVERRIDE_GOTO):
    result = cmd_override_goto_handler(clp);
    cmd_confirm(result, clp->command);
    break;

  default:
    cmd_confirm(MAV_RESULT_UNSUPPORTED, clp->command);
    break;
  }
}


/**
 * Command processing thread.
 */
msg_t MissionPlanner::main(void){
  this->setName("MAVCommand");
  eventmask_t evt = 0;

  struct EventListener el_command_long;
  struct EventListener el_manual_control;
  struct EventListener el_set_mode;
  struct EventListener el_mission_set_current;

  chEvtRegisterMask(&event_mavlink_in_command_long,         &el_command_long, EVMSK_MAVLINK_IN_COMMAND_LONG);
  chEvtRegisterMask(&event_mavlink_in_manual_control,       &el_manual_control,     EVMSK_MAVLINK_IN_MANUAL_CONTROL);
  chEvtRegisterMask(&event_mavlink_in_set_mode,             &el_set_mode,           EVMSK_MAVLINK_IN_SET_MODE);
  chEvtRegisterMask(&event_mavlink_in_mission_set_current,  &el_mission_set_current,EVMSK_MAVLINK_IN_MISSION_SET_CURRENT);

  /* wait modems */
  while(GlobalFlags.messaging_ready == 0)
    chThdSleepMilliseconds(50);

  /* try to load 0-th mission item to RAM */
  if (0 != wpdb.getCount()){
    if (CH_SUCCESS != wpdb.load(&mi, 0))
      chDbgPanic("can not acquare waypoint");
    else
      mission_load_status = CH_SUCCESS;
  }

  /* main loop */
  while(!chThdShouldTerminate()){
    evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_COMMAND_LONG |
                              EVMSK_MAVLINK_IN_MANUAL_CONTROL |
                              EVMSK_MAVLINK_IN_SET_MODE |
                              EVMSK_MAVLINK_IN_MISSION_SET_CURRENT,
                              MS2ST(50));

    switch (evt){
    case EVMSK_MAVLINK_IN_COMMAND_LONG:
      executeCmd(&mavlink_in_command_long_struct);
      break;

    case EVMSK_MAVLINK_IN_MANUAL_CONTROL:
      acs.manualControl(&mavlink_in_manual_control_struct);
      break;

    case EVMSK_MAVLINK_IN_SET_MODE:
      acs.setMode(&mavlink_in_set_mode_struct);
      break;

    case EVMSK_MAVLINK_IN_MISSION_SET_CURRENT:
      acs.setCurrentMission(&mavlink_in_mission_set_current_struct);
      break;

    default:
      break;
    }
  }

  chEvtUnregister(&event_mavlink_in_manual_control,       &el_manual_control);
  chEvtUnregister(&event_mavlink_in_set_mode,             &el_set_mode);
  chEvtUnregister(&event_mavlink_in_mission_set_current,  &el_mission_set_current);
  chEvtUnregister(&event_mavlink_in_command_long,         &el_command_long);
  chThdExit(0);
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
bool MissionPlanner::nextMission(mavlink_command_long_t *cl){
  if (CH_SUCCESS != mission_load_status)
    return CH_FAILED;
  else{
    /* construct command from cached mission item */
    cl->command = mi.command;
    cl->param1  = mi.param1;
    cl->param2  = mi.param2;
    cl->param3  = mi.param3;
    cl->param4  = mi.param4;
    cl->param5  = mi.x;
    cl->param6  = mi.y;
    cl->param7  = mi.z;
    cl->confirmation = 0;
    cl->target_component = mi.target_component;
    cl->target_system = mi.target_system;

    /* 0-th item must be handled separately*/
//    if (0 != seq)
//      broadcast_mission_item_reached(seq - 1);
//    broadcast_mission_current(seq);

    return CH_SUCCESS;
  }
}

