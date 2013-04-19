#include "uav.h"
#include "message.hpp"

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
