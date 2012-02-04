/*
 *  Works with persistant storage (EEPROM)
 */

#include <string.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "param.h"
#include "main.h"
#include "param_persistant.h"
#include "eeprom.h"


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
extern EepromFileStream* EepromFile_p;
extern GlobalParam_t global_data[];
extern const uint32_t ONBOARD_PARAM_COUNT;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t eeprombuf[PARAM_ID_SIZE + sizeof(global_data[0].value)];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */



/**
 * �������� �������� ���������� �� EEPROM
 * param[in]  ����� ���������� ���������� � ������
 */
bool_t load_params_from_eeprom(void){
  uint32_t i = 0;
  uint32_t index = -1;
  uint32_t status = 0;

  union{
    float f32;
    uint32_t u32;
  }u;
  u.f32 = 0;
  u.u32 = 0;

  chFileStreamSeek(EepromFile_p, EEPROM_SETTINGS_START);

  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){

    /* reade field from EEPROM and check number of read bytes */
    status = chFileStreamRead(EepromFile_p, eeprombuf, sizeof(eeprombuf));
    if (status < sizeof(eeprombuf))
      return FAILED;

    /* search value by key and set it if found */
    index = key_value_search((char *)eeprombuf);
      if (index != -1){
        u.u32 = eeprombuf[PARAM_ID_SIZE + 0] << 24 |
                eeprombuf[PARAM_ID_SIZE + 1] << 16 |
                eeprombuf[PARAM_ID_SIZE + 2] << 8 |
                eeprombuf[PARAM_ID_SIZE + 3];
      }

    /* check value acceptability */
    if (u.f32 < global_data[i].min)
      global_data[i].value = global_data[i].min;
    else if (u.f32 > global_data[i].max)
      (global_data[i].value = global_data[i].max);
    else
      global_data[i].value = u.f32;
  }
  return SUCCESS;
}

uint16_t eeprom_get_halfword(EepromFileStream *EepromFile_p){
  uint8_t buf[2];
  size_t status = chFileStreamRead(EepromFile_p, buf, sizeof(buf));
  if (status != sizeof(buf))
    chDbgPanic("read failed");
  return (buf[0] << 8) | buf[1];
}

uint32_t eeprom_get_word(EepromFileStream *EepromFile_p){
  uint8_t buf[4];
  size_t status = chFileStreamRead(EepromFile_p, buf, sizeof(buf));
  if (status != sizeof(buf))
    chDbgPanic("read failed");
  return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

/**
 * ���������� �������� ���������� � EEPROM
 * param[in]  ����� ���������� ���������� � ������
 */
bool_t save_params_to_eeprom(void){
  uint32_t i, j;
  uint32_t status = 0;

  union{
    float f32;
    uint32_t u32;
  }u;

  chFileStreamSeek(EepromFile_p, EEPROM_SETTINGS_START);
  if (chFileStreamGetPosition(EepromFile_p) != EEPROM_SETTINGS_START)
    chDbgPanic("seek failed");

  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){

    /* first copy parameter name in buffer */
    memcpy(eeprombuf, global_data[i].name, PARAM_ID_SIZE);

    /* now write data */
    u.f32 = global_data[i].value;
    eeprombuf[PARAM_ID_SIZE + 0] = (u.u32 >> 24) & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 1] = (u.u32 >> 16) & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 2] = (u.u32 >> 8)  & 0xFF;
    eeprombuf[PARAM_ID_SIZE + 3] = (u.u32 >> 0)  & 0xFF;

    status = chFileStreamWrite(EepromFile_p, eeprombuf, sizeof(eeprombuf));
    if (status < sizeof(eeprombuf))
      chDbgPanic("write failed");

    /* check written data */
    chFileStreamSeek(EepromFile_p, chFileStreamGetPosition(EepromFile_p) - sizeof(eeprombuf));
    uint8_t tmpbuf[sizeof(eeprombuf)];
    status = chFileStreamRead(EepromFile_p, tmpbuf, sizeof(tmpbuf));
    for (j = 0; j < (PARAM_ID_SIZE + sizeof(u.f32)); j++){
      if (tmpbuf[j] != eeprombuf[j])
        chDbgPanic("veryfication failed");
    }
  }
  return 0;
}

/**
 * �������� ������ �� EEPROM
 */
bool_t load_mission_from_eeprom(void){
  return 0;
}

/**
 * ���������� ������ � EEPROM
 */
bool_t save_mission_to_eeprom(void){
  return 0;
}

