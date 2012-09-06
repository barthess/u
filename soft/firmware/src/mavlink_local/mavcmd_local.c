#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONFIRM_TMO           MS2ST(500)

/* helper macros */
#define command_accepted()    (_confirm(MAV_RESULT_ACCEPTED, \
                                mavlink_command_long_struct->command))
#define command_denied()      (_confirm(MAV_RESULT_DENIED, \
                                mavlink_command_long_struct->command))
#define command_unsupported() (_confirm(MAV_RESULT_UNSUPPORTED, \
                                mavlink_command_long_struct->command))
#define command_failed()      (_confirm(MAV_RESULT_FAILED, \
                                mavlink_command_long_struct->command))

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern Mailbox mavlink_command_long_mb;
extern Mailbox tolink_mb;
extern Mailbox controller_mb;

extern mavlink_system_t mavlink_system_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
mavlink_command_ack_t mavlink_command_ack_struct;
Mail command_ack_mail = {NULL, MAVLINK_MSG_ID_COMMAND_ACK, NULL};

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
void _confirm(enum MAV_RESULT result, enum MAV_CMD cmd){
  mavlink_command_ack_struct.result = result;
  mavlink_command_ack_struct.command = cmd;
  command_ack_mail.payload = &mavlink_command_ack_struct;
  chMBPostAhead(&tolink_mb, (msg_t)&command_ack_mail, CONFIRM_TMO);
}

/**
 *
 */
void handle_cmd_calibration(mavlink_command_long_t *mavlink_command_long_struct){
  /* Trigger calibration. This command will be only accepted if in pre-flight mode.
  * | Gyro calibration: 0: no, 1: yes
  * | Magnetometer calibration: 0: no, 1: yes
  * | Ground pressure: 0: no, 1: yes
  * | Radio calibration: 0: no, 1: yes
  * | Empty| Empty| Empty|  */

  /* Gyro */
  if (mavlink_command_long_struct->param1 == 1){
    setGlobalFlag(GYRO_CAL_FLAG);
    mavlink_system_struct.state = MAV_STATE_CALIBRATING;
  }
  else{
    clearGlobalFlag(GYRO_CAL_FLAG);
    mavlink_system_struct.state = MAV_STATE_STANDBY;
  }

  /* Magnetometer */
  if (mavlink_command_long_struct->param2 == 1){
    setGlobalFlag(MAG_CAL_FLAG);
    mavlink_system_struct.state = MAV_STATE_CALIBRATING;
  }
  else{
    clearGlobalFlag(MAG_CAL_FLAG);
    mavlink_system_struct.state = MAV_STATE_STANDBY;
  }

  command_accepted();
}

/**
 *
 */
void handle_cmd_reboot_shutdown(mavlink_command_long_t *mavlink_command_long_struct){
 /* Request the reboot or shutdown of system components.|
  * 0: Do nothing for autopilot, 1: Reboot autopilot, 2: Shutdown autopilot.|
  * 0: Do nothing for onboard computer, 1: Reboot onboard computer, 2: Shutdown onboard computer.
  * | Reserved| Reserved| Empty| Empty| Empty|
  */

  /* currently only reboot supported */
  if (mavlink_command_long_struct->param1 == 1.0){
    command_accepted();
    setGlobalFlag(SIGHALT_FLAG);
    return;
  }
  else {
    command_unsupported();
    return;
  }
}

/**
 *
 */
void handle_cmd_preflight_storage(mavlink_command_long_t *mavlink_command_long_struct){

  bool_t status = CH_FAILED;

  if (mavlink_command_long_struct->param1 == 0)
    status = load_params_from_eeprom();
  else if (mavlink_command_long_struct->param1 == 1)
    status = save_params_to_eeprom();
  if (status != CH_SUCCESS)
    command_failed();
  else
    command_accepted();
}

/**
 * Looks like duplicated functionality of SET_MODE message
 */
void handle_cmd_do_set_mode(mavlink_command_long_t *mavlink_command_long_struct){
  /* all modes defined in MAV_MODE */
//  mavlink_system_struct.mode = mavlink_command_long_struct->param1;
//  command_accepted();
  command_denied();
}

/**
 * parsing and execution of commands from ground
 */
void process_cmd(mavlink_command_long_t *mavlink_command_long_struct){

  /* all this flags defined in MAV_CMD enum */
  switch(mavlink_command_long_struct->command){

  /* */
  case MAV_CMD_DO_SET_MODE:
    /* Set system mode. |Mode, as defined by ENUM MAV_MODE| Empty| Empty| Empty| Empty| Empty| Empty|  */
    handle_cmd_do_set_mode(mavlink_command_long_struct);
    break;

  /* (re)calibrate */
  case MAV_CMD_PREFLIGHT_CALIBRATION:
    if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
      command_denied();
    else
      handle_cmd_calibration(mavlink_command_long_struct);
    break;

  /* */
  case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
    if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
      command_denied();
    else
      handle_cmd_reboot_shutdown(mavlink_command_long_struct);
    break;

  /* Data (storing to)/(loding from) EEPROM */
  case MAV_CMD_PREFLIGHT_STORAGE:
    if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
      command_denied();
    else
      handle_cmd_preflight_storage(mavlink_command_long_struct);
    break;

  case (MAV_CMD_NAV_LOITER_UNLIM || MAV_CMD_NAV_RETURN_TO_LAUNCH ||
        MAV_CMD_NAV_LAND || MAV_CMD_NAV_TAKEOFF ||  MAV_CMD_OVERRIDE_GOTO):
    //chMBPost(&controller_mb);
    //(&tolink_mb, (msg_t)(&mission_out_mail), PLANNER_POST_TMO);
    break;

  /*
   *
   */
  default:
    break;
  }
}

/**
 * Поток, принимающий и обрабатывающий команды с земли.
 */
static WORKING_AREA(CmdThreadWA, 512);
static msg_t CmdThread(void* arg){
  chRegSetThreadName("MAV_cmd_exec");
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
