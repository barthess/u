#ifndef PLANNER_H_
#define PLANNER_H_

enum mav_planner_state{
  MAV_PLANNER_STATE_IDLE,
  MAV_PLANNER_STATE_READ,
  MAV_PLANNER_STATE_WRITE,
};


Thread* PlannerInit(void);


#endif /* PLANNER_H_ */
