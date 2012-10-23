/*
 *  Works with persistant storage (EEPROM)
 */

#include <string.h>

#include "uav.h"

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
extern EepromFileStream EepromSettingsFile;
extern GlobalParam_t GlobalParam[];
extern int32_t OnboardParamCount;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t eeprombuf[PARAM_ID_SIZE + sizeof(*(GlobalParam[0].valuep))];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
bool_t load_params_from_eeprom(void){
  int32_t i = 0;
  int32_t  index = -1;
  uint32_t status = 0;
  uint32_t v = 0;

  chFileStreamSeek(&EepromSettingsFile, 0);

  for (i = 0; i < OnboardParamCount; i++){

    /* reade field from EEPROM and check number of red bytes */
    status = chFileStreamRead(&EepromSettingsFile, eeprombuf, sizeof(eeprombuf));
    if (status < sizeof(eeprombuf)){
      chDbgPanic("");
      return PARAM_FAILED;
    }

    /* search value by key and set it if found */
    index = key_index_search((char *)eeprombuf);
    if (index != -1){
      v = eeprombuf[PARAM_ID_SIZE + 0] << 24 |
          eeprombuf[PARAM_ID_SIZE + 1] << 16 |
          eeprombuf[PARAM_ID_SIZE + 2] << 8 |
          eeprombuf[PARAM_ID_SIZE + 3];
    }

    /* check value acceptability and set it */
    set_global_param(&v, &(GlobalParam[i]));
  }
  return PARAM_SUCCESS;
}

/**
 *
 */
bool_t save_params_to_eeprom(void){
  int32_t i;
  uint32_t status = 0;
  uint32_t v = 0;

  chFileStreamSeek(&EepromSettingsFile, 0);

  for (i = 0; i < OnboardParamCount; i++){

    palClearPad(GPIOB, GPIOB_LED_R);

    /* first copy parameter name in buffer */
    memcpy(eeprombuf, GlobalParam[i].name, PARAM_ID_SIZE);

    /* now write data */
    v = GlobalParam[i].valuep->u32;
    eeprombuf[PARAM_ID_SIZE + 0] = (v >> 24) & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 1] = (v >> 16) & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 2] = (v >> 8)  & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 3] = (v >> 0)  & 0xFF;

    status = chFileStreamWrite(&EepromSettingsFile, eeprombuf, sizeof(eeprombuf));
    if (status < sizeof(eeprombuf))
      chDbgPanic("write failed");

    /* check written data */
    chFileStreamSeek(&EepromSettingsFile, chFileStreamGetPosition(&EepromSettingsFile) - sizeof(eeprombuf));
    uint8_t tmpbuf[sizeof(eeprombuf)];
    status = chFileStreamRead(&EepromSettingsFile, tmpbuf, sizeof(tmpbuf));
    if (memcmp(tmpbuf, eeprombuf, (PARAM_ID_SIZE + sizeof(v))) != 0)
      chDbgPanic("veryfication failed");

    chThdSleepMilliseconds(10);
  }

  palSetPad(GPIOB, GPIOB_LED_R);
  return 0;
}


