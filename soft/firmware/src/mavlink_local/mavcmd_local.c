#include "uav.h"

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
extern Mailbox mavlink_command_long_mb;
extern Mailbox tolink_mb;
extern mavlink_system_t mavlink_system_struct;

mavlink_command_ack_t mavlink_command_ack_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Mail command_ack_mail = {NULL, MAVLINK_MSG_ID_COMMAND_ACK, NULL};

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
static void cmd_confirm(enum MAV_RESULT result, enum MAV_CMD cmd){
  mavlink_command_ack_struct.result = result;
  mavlink_command_ack_struct.command = cmd;
  command_ack_mail.payload = &mavlink_command_ack_struct;
  chMBPost(&tolink_mb, (msg_t)&command_ack_mail, CONFIRM_TMO);
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

  if ((mavlink_system_struct.mode != MAV_MODE_PREFLIGHT) ||
                            (GlobalFlags.gyro_cal) || (GlobalFlags.mag_cal))
    return MAV_RESULT_TEMPORARILY_REJECTED;

  /* Gyro */
  if (cl->param1 == 1){
    setGlobalFlag(GlobalFlags.gyro_cal);
    return MAV_RESULT_ACCEPTED;
  }
  else if (cl->param2 == 1){ /* Magnetometer */
    setGlobalFlag(GlobalFlags.mag_cal);
    return MAV_RESULT_ACCEPTED;
  }
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

  /* currently only reboot supported */
  if (cl->param1 == 1.0){
    setGlobalFlag(GlobalFlags.sighalt);
    return MAV_RESULT_ACCEPTED;
  }
  else {
    return MAV_RESULT_UNSUPPORTED;
  }
}

/**
 *
 */
static enum MAV_RESULT cmd_preflight_storage_handler(mavlink_command_long_t *cl){
  bool_t status = CH_FAILED;

  if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
    return MAV_RESULT_TEMPORARILY_REJECTED;

  if (cl->param1 == 0)
    status = load_params_from_eeprom();
  else if (cl->param1 == 1)
    status = save_params_to_eeprom();

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
  msg_t tmp = 0;
  msg_t status = 0;
  Mail *input_mail = NULL;

  while (TRUE) {
    status = chMBFetch(&mavlink_command_long_mb, &tmp, TIME_INFINITE);
    (void)status;
    input_mail = (Mail*)tmp;
    process_cmd(input_mail->payload);
    ReleaseMail(input_mail);
  }

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
