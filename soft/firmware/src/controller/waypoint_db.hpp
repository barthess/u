#ifndef WAYPOINT_DB_HPP_
#define WAYPOINT_DB_HPP_

#include "eeprom_file.hpp"

void save_waypoint_count(int i);
bool get_waypoint_from_eeprom(int a, mavlink_mission_item_t *b);
int get_waypoint_count(void);
void save_waypoint_to_eeprom(int a, mavlink_mission_item_t *b);

#define HEADER_SIZE       (sizeof(uint16_t))
#define WAYPOINT_SIZE     (sizeof(mavlink_mission_item_t))


/*
 * DB structure:
 * uint16_t                 waypoint count currently stored in DB
 * mavlink_mission_item_t[] array of fixed size chunks storing wp data.
 *                          Chunks must be stored subsequently in waypoints' order
 */
class WpDB{
public:
  WpDB(void);
  uint16_t connect(EepromFile *dbfile);
  bool get(mavlink_mission_item_t *wpp, uint16_t seq);
  bool massErase(void);
  bool deleteAll(void);
  bool write(const mavlink_mission_item_t *wpp, uint16_t seq);
  uint16_t len(void);

private:
  EepromFile *dbfile;
  bool validate(mavlink_mission_item_t *wpp);
  bool finalize(void);
  uint16_t count;
};

#endif /* WAYPOINT_DB_HPP_ */
