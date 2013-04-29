#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"
#include "ground_rover.hpp"
#include "imu.hpp"

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

extern mavlink_command_ack_t mavlink_out_command_ack_struct;
extern mavlink_command_long_t mavlink_in_command_long_struct;

extern EventSource event_mavlink_out_command_ack;
extern EventSource event_mavlink_in_command_long;

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
    result = ImuTrigCalibrateGyro();
    if (CH_SUCCESS == result)
      return MAV_RESULT_ACCEPTED;
    else
      return MAV_RESULT_FAILED;
  }
  /* Magnetometer */
  else if (cl->param2 == 1){
    result = ImuTrigCalibrateMag();
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
 * parsing and execution of commands from ground
 */
static void process_cmd(mavlink_command_long_t *mavlink_command_long_struct){
  enum MAV_RESULT result = MAV_RESULT_DENIED;

  /* all this flags defined in MAV_CMD enum */
  switch(mavlink_command_long_struct->command){
  case MAV_CMD_DO_SET_MODE:
    /* */
    result = cmd_do_set_mode_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case MAV_CMD_PREFLIGHT_CALIBRATION:
    /* (re)calibrate */
    result = cmd_calibration_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
    /* */
    result = cmd_reboot_shutdown_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case MAV_CMD_PREFLIGHT_STORAGE:
    /* Data (storing to)/(loding from) EEPROM */
    result = cmd_preflight_storage_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case (MAV_CMD_NAV_TAKEOFF):
    result = cmd_nav_takeoff_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case (MAV_CMD_NAV_RETURN_TO_LAUNCH):
    result = cmd_nav_return_to_launch_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case (MAV_CMD_NAV_LAND):
    result = cmd_nav_land_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case (MAV_CMD_NAV_LOITER_UNLIM):
    result = cmd_nav_loiter_unlim_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  case (MAV_CMD_OVERRIDE_GOTO):
    result = cmd_override_goto_handler(mavlink_command_long_struct);
    cmd_confirm(result, mavlink_command_long_struct->command);
    break;

  default:
    cmd_confirm(MAV_RESULT_UNSUPPORTED, mavlink_command_long_struct->command);
    break;
  }
}

/**
 * Command processing thread.
 */
static WORKING_AREA(CmdThreadWA, 512);
static msg_t CmdThread(void* arg){
  chRegSetThreadName("MAVCommand");
  (void)arg;
  eventmask_t evt = 0;

  struct EventListener el_command_long;
  chEvtRegisterMask(&event_mavlink_in_command_long, &el_command_long, EVMSK_MAVLINK_IN_COMMAND_LONG);

  while(!chThdShouldTerminate()){
    evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_IN_COMMAND_LONG, MS2ST(50));
    if (evt == EVMSK_MAVLINK_IN_COMMAND_LONG){
      process_cmd(&mavlink_in_command_long_struct);
    }
  }

  chEvtUnregister(&event_mavlink_in_command_long, &el_command_long);
  chThdExit(0);
  return 0;
}



/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void MavCmdInitLocal(void){

  chThdCreateStatic(CmdThreadWA,
        sizeof(CmdThreadWA),
        NORMALPRIO,
        CmdThread,
        NULL);
}
