#ifndef MISSION_PLANNER_H_
#define MISSION_PLANNER_H_

#include "message.hpp"

class MissionPlanner : public BaseStaticThread<512>{
public:
  /**
   *
   */
  msg_t main(void);

private:
  void executeCmd(mavlink_command_long_t *clp);
  mavlink_mission_item_t mi;  // cached mission item to reduce loading delay
};


#endif /* MISSION_PLANNER_H_ */
