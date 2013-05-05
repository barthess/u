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
  MissionPlanner(void){
    state = MAV_EXECUTOR_STATE_UNINIT;
    seq = 0;
    mission_load_status = CH_FAILED;
  };
  /**
   *
   */
  msg_t main(void);
  /**
   * This function must be called from ACS to load next mission item task.
   */
  bool nextMission(mavlink_command_long_t *cl);

private:
  void executeCmd(mavlink_command_long_t *clp);
  bool mission_load_status;
  mavlink_mission_item_t mi;  // cached mission item to reduce loading delay
  uint16_t seq;
  mav_executor_state_t state;
};


#endif /* MAVCMD_LOCAL_H_ */
