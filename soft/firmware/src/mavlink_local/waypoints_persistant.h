#ifndef WAYPOINTS_PERSISTANT_H_
#define WAYPOINTS_PERSISTANT_H_


uint16_t get_waypoint_count(void);
void save_waypoint_count(uint16_t cnt);

bool_t get_waypoint_from_eeprom(uint16_t seq, mavlink_mission_item_t *wp);
bool_t save_waypoint_to_eeprom(uint16_t seq, mavlink_mission_item_t *wp);


#endif /* WAYPOINTS_PERSISTANT_H_ */
