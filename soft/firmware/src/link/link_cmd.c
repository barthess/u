#include "ch.h"
#include "hal.h"

#include "link.h"
#include "message.h"
#include "main.h"
#include "param_persistant.h"

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
extern Mailbox mavlinkcmd_mb;
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
/**
 * @note    MAV_CMD_PREFLIGHT_xxxx commands only accepted in preflight mode
 */
msg_t _analize_cmd(mavlink_command_long_t *cmd){
  msg_t status = RDY_OK;

  switch(cmd->command){
  /**
   *  оманды дл€ загрузки/вычитки параметров из EEPROM
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

/**
 * ѕоток приема команд.
 */
static WORKING_AREA(LinkCmdParserThreadWA, 1024);
static msg_t LinkCmdParserThread(void *arg){
  chRegSetThreadName("MAVCmdParser");
  (void)arg;
  msg_t tmp;
  Mail *mailp = NULL;
  mavlink_command_long_t *cmdp;

  while (TRUE) {
    chMBFetch(&mavlinkcmd_mb, &tmp, TIME_INFINITE);
    mailp = (Mail *)tmp;
    cmdp = (mavlink_command_long_t *)(mailp->payload);
    _analize_cmd(cmdp);


    //TODO: анализ вЄрнутого значени€ и генераци€ ответа в tolink_mb


    mailp->payload = NULL;
  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void LinkCmdParserInit(void){

  chThdCreateStatic(LinkCmdParserThreadWA,
          sizeof(LinkCmdParserThreadWA),
          LINK_THREADS_PRIO - 1,
          LinkCmdParserThread,
          NULL);
}

