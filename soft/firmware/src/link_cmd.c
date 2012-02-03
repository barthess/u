#include "ch.h"
#include "hal.h"

#include "link.h"
#include "message.h"
#include "main.h"


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
extern Mailbox param_mb;
extern mavlink_system_t mavlink_system;
extern mavlink_command_long_t mavlink_command_long_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Mail command_mail = {NULL, MAVLINK_MSG_ID_COMMAND_LONG, NULL};

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @note    MAV_CMD_PREFLIGHT_xxxx commands only accepted in preflight mode
 */
msg_t analize_cmd(mavlink_command_long_t *cmd){
  msg_t status = RDY_OK;
  mavlink_command_long_t *command = NULL;

  switch(cmd->command){
  /**
   * Команды для загрузки/вычитки параметров из EEPROM
   */
  case MAV_CMD_PREFLIGHT_STORAGE:
    if (mavlink_system.mode != MAV_MODE_PREFLIGHT)
      return RDY_RESET;
    /*
     * команды загрузки/чтения EEPROM
     */
//    case MAV_CMD_PREFLIGHT_STORAGE:
//      command = (mavlink_command_long_t *)(input_mail->payload);
//      input_mail->payload = NULL;
//
//      if (command->param1 == 0)
//        load_params_from_eeprom();
//      else if (command->param1 == 1)
//        save_params_to_eeprom();
//
//      if (command->param2 == 0)
//        load_mission_from_eeprom();
//      else if (command->param2 == 1)
//        save_mission_to_eeprom();
//      break;
    break;

  /*
   * (пере)запуск калибровки
   */
  case MAV_CMD_PREFLIGHT_CALIBRATION:
    if (mavlink_system.mode != MAV_MODE_PREFLIGHT)
      return RDY_RESET;
    break;


  default:
    break;
  }
  return status;
}















