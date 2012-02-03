#include "ch.h"
#include "hal.h"

#include "link.h"
#include "message.h"
#include "main.h"
#include "param.h"


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

/* some commands not allowed in preflight mode. This macro check that */
#define check_preflight() {                                                   \
  if (mavlink_system.mode != MAV_MODE_PREFLIGHT)                              \
  return RDY_RESET;                                                           \
}

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
    /*
     * команды загрузки/чтения EEPROM
     */
    check_preflight();

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
    check_preflight();
    break;


  default:
    break;
  }
  return status;
}















