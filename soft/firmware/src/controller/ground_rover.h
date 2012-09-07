#ifndef GROUND_ROVER_H_
#define GROUND_ROVER_H_

float calc_ground_rover_speed(uint32_t rtt);
enum MAV_RESULT cmd_nav_takeoff_handler(mavlink_command_long_t *cl);
Thread *ControllerGroundRoverInit(void);

#endif /* GROUND_ROVER_H_ */
