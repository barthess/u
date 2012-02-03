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

  switch(cmd->command){
  /**
   * Команды для загрузки/вычитки параметров из EEPROM
   */
  case MAV_CMD_PREFLIGHT_STORAGE:
    if (mavlink_system.mode != MAV_MODE_PREFLIGHT)
      return RDY_RESET;
    if (command_mail.payload == NULL){
      command_mail.invoice = MAV_CMD_PREFLIGHT_STORAGE;
      command_mail.payload = cmd;
      status = chMBPost(&param_mb, (msg_t)&command_mail, TIME_IMMEDIATE);
    }
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















