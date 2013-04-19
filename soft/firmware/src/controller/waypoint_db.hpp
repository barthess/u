#ifndef WAYPOINT_DB_HPP_
#define WAYPOINT_DB_HPP_

void save_waypoint_count(int i);
bool get_waypoint_from_eeprom(int a, mavlink_mission_item_t *b);
int get_waypoint_count(void);
void save_waypoint_to_eeprom(int a, mavlink_mission_item_t *b);

#endif /* WAYPOINT_DB_HPP_ */
