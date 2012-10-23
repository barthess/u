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
extern EepromFileStream EepromWaypointFile;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

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
 * Read waypoints count
 */
uint16_t get_waypoint_count(void){
  chFileStreamSeek(&EepromWaypointFile, 0);
  return EepromReadHalfword(&EepromWaypointFile);
}

/**
 * Write waypoints count
 */
void save_waypoint_count(uint16_t cnt){
  chFileStreamSeek(&EepromWaypointFile, 0);
  EepromWriteHalfword(&EepromWaypointFile, cnt);
}

/**
 * Read single waypoint in EEPROM
 *
 * @param[in] seq     sequence number of waypoint
 * @param[out] wp     pointer to waypoint structure
 */
bool_t get_waypoint_from_eeprom(uint16_t seq, mavlink_mission_item_t *wp){
  uint32_t status = 0;
  size_t wpsize = sizeof(mavlink_mission_item_t);
  fileoffset_t offset = EEPROM_MISSION_WP_CNT_SIZE + seq * wpsize;

  chFileStreamSeek(&EepromWaypointFile, offset);
  if (chFileStreamGetPosition(&EepromWaypointFile) != offset){
    chDbgPanic("seek failed");
    return WP_FAILED;
  }

  status = chFileStreamRead(&EepromWaypointFile, (uint8_t*)wp, wpsize);
  if (status != wpsize){
    chDbgPanic("read failed");
    return WP_FAILED;
  }

  return WP_SUCCESS;
}

/**
 * Save single waypoint in EEPROM
 *
 * @param[in] seq     sequence number of waypoint
 * @param[in] wp      pointer to waypoint structure
 */
bool_t save_waypoint_to_eeprom(uint16_t seq, mavlink_mission_item_t *wp){
  uint32_t status = 0;
  const size_t wpsize = sizeof(mavlink_mission_item_t);
  fileoffset_t offset = EEPROM_MISSION_WP_CNT_SIZE + seq * wpsize;

  chFileStreamSeek(&EepromWaypointFile, offset);
  if (chFileStreamGetPosition(&EepromWaypointFile) != offset)
    chDbgPanic("seek failed");

  /* indicate writing on */
  palClearPad(GPIOB, GPIOB_LED_R);

  /* write */
  status = chFileStreamWrite(&EepromWaypointFile, (uint8_t*)wp, wpsize);
  if (status < sizeof(mavlink_mission_item_t))
    chDbgPanic("write failed");

  /* check written data */
  uint8_t tmpbuf[wpsize];
  chFileStreamSeek(&EepromWaypointFile, chFileStreamGetPosition(&EepromWaypointFile) - wpsize);
  status = chFileStreamRead(&EepromWaypointFile, tmpbuf, sizeof(tmpbuf));
  if (status < wpsize)
    chDbgPanic("read failed");
  if (memcmp(tmpbuf, wp, wpsize) != 0)
    chDbgPanic("veryfication failed");

  /* indicate writing off */
  palSetPad(GPIOB, GPIOB_LED_R);
  return 0;
}

