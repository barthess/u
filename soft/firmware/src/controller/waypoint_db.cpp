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


bool WpDB::get(uint16_t seq, mavlink_mission_item_t *wpp){
  chDbgCheck((NULL != this->dbfile), "DB unconnected");
  chDbgCheck((NULL != wpp), "");
  if (seq > count)
    return CH_FAILED;
  else{

  }
}



bool WpDB::massErase(void){
  return CH_FAILED;
}



bool WpDB::deleteAll(void){
  return CH_FAILED;
}



bool WpDB::write(uint16_t n, mavlink_mission_item_t *wpp){
return CH_FAILED;
}



uint16_t WpDB::len(void){
  return 0;
}



bool WpDB::validate(mavlink_mission_item_t *wpp){
  return CH_FAILED;
}



bool WpDB::finalize(void){
  return CH_FAILED;
}


