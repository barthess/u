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
#define ADDITIONAL_WRITE_TMO    MS2ST(10)

#define acquire_settings_file() chBSemWait(&SettingsFile_sem)
#define release_settings_file() chBSemSignal(&SettingsFile_sem)

#define PARAM_VALUE_SIZE        (sizeof(*((GlobalParam[0]).valuep)))
#define PARAM_RECORD_SIZE       (PARAM_ID_SIZE + PARAM_VALUE_SIZE)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern EepromFileStream EepromSettingsFile;
extern BinarySemaphore SettingsFile_sem;

extern GlobalParam_t GlobalParam[];
extern int32_t OnboardParamCount;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t eeprombuf[PARAM_RECORD_SIZE];

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
  int32_t  i = 0;
  int32_t  index = -1;
  uint32_t status = 0;
  uint32_t v = 0;

  acquire_settings_file();
  chFileStreamSeek(&EepromSettingsFile, 0);

  for (i = 0; i < OnboardParamCount; i++){

    /* reade field from EEPROM and check number of red bytes */
    status = chFileStreamRead(&EepromSettingsFile, eeprombuf, PARAM_RECORD_SIZE);
    if (status < PARAM_RECORD_SIZE){
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

  release_settings_file();
  return PARAM_SUCCESS;
}

/**
 * Save all parameters to EEPROM.
 * Designed to easily exted or shrink parameters bulk in EEPROM.
 */
bool_t save_all_params_to_eeprom(void){
  int32_t  i;
  uint32_t status = 0;
  uint32_t v = 0;
  uint8_t tmpbuf[PARAM_RECORD_SIZE];

  acquire_settings_file();
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

    status = chFileStreamWrite(&EepromSettingsFile, eeprombuf, PARAM_RECORD_SIZE);
    chDbgCheck(status == PARAM_RECORD_SIZE, "write failed");

    /* check written data */
    chFileStreamSeek(&EepromSettingsFile,
                    chFileStreamGetPosition(&EepromSettingsFile) - PARAM_RECORD_SIZE);
    status = chFileStreamRead(&EepromSettingsFile, tmpbuf, sizeof(tmpbuf));
    if (memcmp(tmpbuf, eeprombuf, (PARAM_ID_SIZE + sizeof(v))) != 0)
      chDbgPanic("veryfication failed");

    chThdSleep(ADDITIONAL_WRITE_TMO);
  }

  release_settings_file();
  palSetPad(GPIOB, GPIOB_LED_R);
  return PARAM_SUCCESS;
}

/**
 * Flush specified parameter from global parameter structure to EEPROM.
 */
bool_t save_param_to_eeprom(const char* key){
  int32_t  i;
  uint32_t status = 0;
  uint32_t v = 0;
  uint8_t  tmpbuf[PARAM_RECORD_SIZE];

  i = key_index_search(key);
  chDbgCheck(i != -1, "Not found");

  acquire_settings_file();
  chFileStreamSeek(&EepromSettingsFile, i * PARAM_RECORD_SIZE);

  /* ensure we found exacly what needed */
  status = chFileStreamRead(&EepromSettingsFile, tmpbuf, sizeof(tmpbuf));
  chDbgCheck(status == sizeof(tmpbuf), "read failed");
  chDbgCheck(strcmp((char *)tmpbuf, key) == 0, "param not found in EEPROM");

  /* write only if value differ */
  chFileStreamSeek(&EepromSettingsFile,
            chFileStreamGetPosition(&EepromSettingsFile) - PARAM_VALUE_SIZE);
  v = EepromReadWord(&EepromSettingsFile);

  if (v != GlobalParam[i].valuep->u32){
    palClearPad(GPIOB, GPIOB_LED_R);
    chFileStreamSeek(&EepromSettingsFile,
            chFileStreamGetPosition(&EepromSettingsFile) - PARAM_VALUE_SIZE);
    status = EepromWriteWord(&EepromSettingsFile, GlobalParam[i].valuep->u32);
    chDbgCheck(status == sizeof(uint32_t), "read failed");
    chThdSleep(ADDITIONAL_WRITE_TMO);
    palSetPad(GPIOB, GPIOB_LED_R);
  }

  release_settings_file();

  return PARAM_SUCCESS;
}

