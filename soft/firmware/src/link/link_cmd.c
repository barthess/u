#include "ch.h"
#include "hal.h"

#include "link.h"
#include "message.h"
#include "main.h"
#include "persistant.h"

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

extern mavlink_system_t mavlink_system;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

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
msg_t analize_mavlink_cmd(mavlink_command_long_t *cmd){
  msg_t status = RDY_OK;

  switch(cmd->command){
  /**
   * Команды для загрузки/вычитки параметров из EEPROM
   */
  case MAV_CMD_PREFLIGHT_STORAGE:
    if (mavlink_system.mode != MAV_MODE_PREFLIGHT)
      return RDY_RESET;

    if (cmd->param1 == 0)
      load_params_from_eeprom();
    else if (cmd->param1 == 1)
      save_params_to_eeprom();

    if (cmd->param2 == 0)
      load_mission_from_eeprom();
    else if (cmd->param2 == 1)
      save_mission_to_eeprom();

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
