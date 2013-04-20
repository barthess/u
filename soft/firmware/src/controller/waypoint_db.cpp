#include "uav.h"
#include "message.hpp"
#include "waypoint_db.hpp"


void save_waypoint_count(int i){
  (void)i;
  chDbgPanic("temporal stub");
}
bool get_waypoint_from_eeprom(int a, mavlink_mission_item_t *b){
  (void)a;
  (void)b;
  chDbgPanic("temporal stub");
  return false;
}
int get_waypoint_count(void){
  chDbgPanic("temporal stub");
  return 0;
}
void save_waypoint_to_eeprom(int a, mavlink_mission_item_t *b){
    (void)a;
  (void)b;
  chDbgPanic("temporal stub");
}

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

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
WpDB::WpDB(void){
  this->dbfile = NULL;
}

/**
 * file must be allready opened
 */
uint16_t WpDB::connect(EepromFile *dbfile){
  this->dbfile = dbfile;
  dbfile->setPosition(0);
  count = dbfile->readHalfWord();
  return count;
}

/**
 *
 */
bool WpDB::get(mavlink_mission_item_t *wpp, uint16_t seq){
  uint32_t offset = HEADER_SIZE;
  size_t result = 0;

  chDbgCheck((NULL != this->dbfile), "DB unconnected");
  chDbgCheck((NULL != wpp), "");

  if (seq >= count)
    return CH_FAILED;
  else{
    offset += seq * WAYPOINT_SIZE;
    dbfile->setPosition(offset);
    result = dbfile->read((uint8_t *)wpp, WAYPOINT_SIZE);
    if (WAYPOINT_SIZE == result)
      return CH_SUCCESS;
    else
      return CH_FAILED;
  }
}

/**
 * overwrite all data in db file by pattern
 */
bool WpDB::massErase(void){
  chDbgPanic("unrealized");
  return CH_FAILED;
}

/**
 * Just clear header without erasing of data
 */
bool WpDB::deleteAll(void){
  size_t result = 0;
  dbfile->setPosition(0);
  result = dbfile->writeHalfWord(0);
  if (HEADER_SIZE == result)
    return CH_SUCCESS;
  else
    return CH_FAILED;
}

/**
 *
 */
bool WpDB::write(const mavlink_mission_item_t *wpp, uint16_t seq){
  uint32_t offset = HEADER_SIZE;
  size_t result = 0;

  chDbgCheck((NULL != this->dbfile), "DB unconnected");
  chDbgCheck((NULL != wpp), "");

  if (seq >= count)
    return CH_FAILED;
  else{
    offset += seq * WAYPOINT_SIZE;
    dbfile->setPosition(offset);
    result = dbfile->read((uint8_t *)wpp, WAYPOINT_SIZE);
    if (WAYPOINT_SIZE == result)
      return CH_SUCCESS;
    else
      return CH_FAILED;
  }
}





uint16_t WpDB::len(void){
  return count;
}



bool WpDB::validate(mavlink_mission_item_t *wpp){
  return CH_FAILED;
}



bool WpDB::finalize(void){
  return CH_FAILED;
}


