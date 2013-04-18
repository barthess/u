#ifndef EEPROM_FILE_TREE_HPP_
#define EEPROM_FILE_TREE_HPP_

#include "eeprom_fs_conf.h"

/* region for settings file */
#define EEPROM_SETTINGS_START         EEPROM_FS_TOC_SIZE
#define EEPROM_SETTINGS_SIZE          (4096 - EEPROM_FS_TOC_SIZE)
#define EEPROM_SETTINGS_END           (EEPROM_SETTINGS_START + EEPROM_SETTINGS_SIZE)

/* region for waypoints file */
#define EEPROM_MISSION_WP_CNT_OFFSET  EEPROM_SETTINGS_END
/* size in byte of waypoint count variable */
#define EEPROM_MISSION_WP_CNT_SIZE    2
/* actual waypoints offset */
#define EEPROM_MISSION_START          (EEPROM_MISSION_WP_CNT_OFFSET + EEPROM_MISSION_WP_CNT_SIZE)
#define EEPROM_MISSION_SIZE           (8192 - EEPROM_MISSION_WP_CNT_SIZE)
#define EEPROM_MISSION_END            (EEPROM_MISSION_START + EEPROM_MISSION_SIZE)


void EepromFileTreeInit(void);

#endif /* EEPROM_FILE_TREE_HPP_ */
