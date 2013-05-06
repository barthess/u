#ifndef MAVCMD_LOCAL_H_
#define MAVCMD_LOCAL_H_

#include "message.hpp"

/**
 * @brief   State of ACS
 */
typedef enum {
  MAV_EXECUTOR_STATE_UNINIT,
  MAV_EXECUTOR_STATE_IDLE,
  MAV_EXECUTOR_STATE_MISSION,
}mav_executor_state_t;


class MissionPlanner : public BaseStaticThread<512>{
public:
  /**
   *
   */
  msg_t main(void);

private:
  void executeCmd(mavlink_command_long_t *clp);
  mavlink_mission_item_t mi;  // cached mission item to reduce loading delay
  mav_executor_state_t state;
};


#endif /* MAVCMD_LOCAL_H_ */
