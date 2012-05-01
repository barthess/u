#include "mavlink.h"
#include "common.h"

#include "main.h"
#include "autopilot.h"
#include "servo.h"
#include "message.h"
#include "eeprom.h"
#include "persistant.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox mavlink_command_long_mb;
extern Mailbox tolink_mb;

extern mavlink_system_t mavlink_system_struct;
extern EventSource pwrmgmt_event;

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

/* helper funcion */
void confirmation(enum MAV_RESULT result, enum MAV_CMD cmd){
  mavlink_command_ack_struct.result = result;
  mavlink_command_ack_struct.command = cmd;
  command_ack_mail.payload = &mavlink_command_ack_struct;
  chMBPostAhead(&tolink_mb, (msg_t)&command_ack_mail, TIME_IMMEDIATE);
}

#define command_accepted() (confirmation(MAV_RESULT_ACCEPTED, mavlink_command_long_struct->command))
#define command_denied() (confirmation(MAV_RESULT_DENIED, mavlink_command_long_struct->command))







void process_cmd(mavlink_command_long_t *mavlink_command_long_struct){

  /* all this flags defined in MAV_CMD enum */
  switch(mavlink_command_long_struct->command){
  case MAV_CMD_DO_SET_MODE:
    /* Set system mode. |Mode, as defined by ENUM MAV_MODE| Empty| Empty| Empty| Empty| Empty| Empty|  */
    mavlink_system_struct.mode = mavlink_command_long_struct->param1;
    command_accepted();
    break;

  /*
   * (пере)запуск калибровки
   */
  case MAV_CMD_PREFLIGHT_CALIBRATION:
    /* Trigger calibration. This command will be only accepted if in pre-flight mode. |Gyro calibration: 0: no, 1: yes| Magnetometer calibration: 0: no, 1: yes| Ground pressure: 0: no, 1: yes| Radio calibration: 0: no, 1: yes| Empty| Empty| Empty|  */
    if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT){
      command_denied();
      return;
    }
    else{

    }
    break;

  case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
    /* Request the reboot or shutdown of system components. |0: Do nothing for autopilot, 1: Reboot autopilot, 2: Shutdown autopilot.| 0: Do nothing for onboard computer, 1: Reboot onboard computer, 2: Shutdown onboard computer.| Reserved| Reserved| Empty| Empty| Empty|  */
    if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT){
      command_denied();
      return;
    }
    else{
      chEvtBroadcastFlags(&pwrmgmt_event, PWRMGMT_SIGHALT_EVID);
      command_accepted();
    }
    break;
    /**
     * Команды для загрузки/вычитки параметров из EEPROM
     */
    case MAV_CMD_PREFLIGHT_STORAGE:
      if (mavlink_system_struct.mode != MAV_MODE_PREFLIGHT)
        return;

      if (mavlink_command_long_struct->param1 == 0)
        load_params_from_eeprom();
      else if (mavlink_command_long_struct->param1 == 1)
        save_params_to_eeprom();

      if (mavlink_command_long_struct->param2 == 0)
        load_mission_from_eeprom();
      else if (mavlink_command_long_struct->param2 == 1)
        save_mission_to_eeprom();

      break;

  default:
    return;
    break;
  }
}












/**
 *
 */
static WORKING_AREA(AutopilotThreadWA, 512);
Thread *autopilot_tp = NULL;
static msg_t AutopilotThread(void* arg){
  chRegSetThreadName("Autopilot");
  (void)arg;

  while (TRUE) {
    chThdSleepMilliseconds(10);
  }

  return 0;
}



/**
 * Поток, принимающий и обрабатывающий команды с земли.
 */
static WORKING_AREA(CmdThreadWA, 512);
static msg_t CmdThread(void* arg){
  chRegSetThreadName("CMD_excutor");
  (void)arg;
  msg_t tmp = 0;
  msg_t status = 0;
  Mail *input_mail = NULL;

  while (TRUE) {
    status = chMBFetch(&mavlink_command_long_mb, &tmp, TIME_INFINITE);
    (void)status;
    input_mail = (Mail*)tmp;
    process_cmd((mavlink_command_long_t *)input_mail->payload);
    input_mail->payload = NULL;
  }

  return 0;
}



/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void AutopilotInit(void){

  chThdCreateStatic(CmdThreadWA,
        sizeof(CmdThreadWA),
        NORMALPRIO,
        CmdThread,
        NULL);

  chThdCreateStatic(AutopilotThreadWA,
        sizeof(AutopilotThreadWA),
        NORMALPRIO,
        AutopilotThread,
        NULL);
}
