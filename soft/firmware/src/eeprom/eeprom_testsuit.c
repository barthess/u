#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "eeprom_testsuit.h"

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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t referencebuf[EEPROM_TEST_AREA_SIZE];
static uint8_t checkbuf[EEPROM_TEST_AREA_SIZE];

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

/**
 * Fills eeprom area with pattern, than read it back and compare
 */
void suit_write(uint8_t pattern, uint32_t len, uint8_t misaligment){
  uint32_t i = 0;
  uint32_t status = 0;
  uint32_t pos = 0;

  /* fill buffer with pattern */
  for (i = 0; i < len; i++)
    referencebuf[i] = pattern;

  /* move to begin of test area */
  chFileStreamSeek(EepromFile_p, EEPROM_TEST_AREA_START + misaligment);
  pos = chFileStreamGetPosition(EepromFile_p);
  if (pos != EEPROM_TEST_AREA_START + misaligment)
    chDbgPanic("file seek error");

  /* write */
  status = chFileStreamWrite(EepromFile_p, referencebuf, len);
  if (status < len)
    chDbgPanic("write failed");

  /* check */
  pos = chFileStreamGetPosition(EepromFile_p);
  if (pos != len + EEPROM_TEST_AREA_START + misaligment)
    chDbgPanic("file seek error");

  chFileStreamSeek(EepromFile_p, pos - len);
  status = chFileStreamRead(EepromFile_p, checkbuf, len);
  if (status < len)
    chDbgPanic("veryfication failed");
  if (memcmp(referencebuf, checkbuf, len) != 0)
    chDbgPanic("veryfication failed");
}

void pat(uint32_t len, uint8_t misaligment){
  uint8_t r;
  chSysLock();
  r = rand() & 0xFF;
  chSysUnlock();

  suit_write(0x55, len, misaligment);
  suit_write(0xAA, len, misaligment);
  suit_write(0x00, len, misaligment);
  suit_write(0xFF, len, misaligment);
  suit_write(r,    len, misaligment);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void eeprom_testsuit_run(void){
  int8_t i = 0;
  int8_t j = 0;

  for (i = -2; i < 3; i++){
    for (j = 0; j < 3; j++){
      pat(128 + i,  j);
      pat(256 + i,  j);
      pat(512 + i,  j);
      pat(1024 + i, j);

      pat(128 + i,  EEPROM_PAGE_SIZE - 1 - j);
      pat(256 + i,  EEPROM_PAGE_SIZE - 1 - j);
      pat(512 + i,  EEPROM_PAGE_SIZE - 1 - j);
      pat(1024 + i, EEPROM_PAGE_SIZE - 1 - j);

      pat(4 + i, j);
      pat(4 + i, j);
      pat(4 + i, j);
      pat(4 + i, j);

      pat(4 + i, EEPROM_PAGE_SIZE - 1 - j);
      pat(4 + i, EEPROM_PAGE_SIZE - 1 - j);
      pat(4 + i, EEPROM_PAGE_SIZE - 1 - j);
      pat(4 + i, EEPROM_PAGE_SIZE - 1 - j);

      palTogglePad(GPIOB, GPIOB_LED_B);
    }
  }

  pat(20, EEPROM_PAGE_SIZE - 1);
  pat(30, EEPROM_PAGE_SIZE - 1);
  pat(40, EEPROM_PAGE_SIZE - 1);
  pat(50, EEPROM_PAGE_SIZE - 1);

  pat(20, EEPROM_PAGE_SIZE - 2);
  pat(30, EEPROM_PAGE_SIZE - 2);
  pat(40, EEPROM_PAGE_SIZE - 2);
  pat(50, EEPROM_PAGE_SIZE - 2);
}





