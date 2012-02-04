#ifndef EEPROM_TESTSUIT_H_
#define EEPROM_TESTSUIT_H_

#include "eeprom.h"


#define EEPROM_TEST_AREA_START      EEPROM_SETTINGS_FINISH + 8192
#define EEPROM_TEST_AREA_SIZE       2048
#define EEPROM_TEST_AREA_FINISH     (EEPROM_TEST_AREA_START + EEPROM_TEST_AREA_SIZE)


void eeprom_testsuit_run(void);

#endif /* EEPROM_TESTSUIT_H_ */
