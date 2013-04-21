#include "uav.h"
#include "message.hpp"
#include "waypoint_db.hpp"

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
bool WpDB::load(mavlink_mission_item_t *wpp, uint16_t seq){
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
bool WpDB::clear(void){
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
bool WpDB::save(const mavlink_mission_item_t *wpp, uint16_t seq){
  uint32_t offset = 0;
  size_t result = 0;

  chDbgCheck((NULL != this->dbfile), "DB unconnected");
  chDbgCheck((NULL != wpp), "");

  if (seq >= count)
    return CH_FAILED;
  else{
    offset = HEADER_SIZE + seq * WAYPOINT_SIZE;
    dbfile->setPosition(offset);
    result = dbfile->write((uint8_t *)wpp, WAYPOINT_SIZE);
    if (WAYPOINT_SIZE == result){
      count++;
      return CH_SUCCESS;
    }
    else
      return CH_FAILED;
  }
}

/**
 *
 */
uint16_t WpDB::len(void){
  return count;
}

/**
 *
 */
bool WpDB::validate(mavlink_mission_item_t *wpp){
  chDbgCheck((NULL != wpp), "");
  return CH_FAILED;
}

/**
 *
 */
bool WpDB::finalize(void){
  size_t result = 0;
  dbfile->setPosition(0);
  result = dbfile->writeHalfWord(count);
  if (HEADER_SIZE == result)
    return CH_SUCCESS;
  else
    return CH_FAILED;
}


