#ifndef GROUND_ROVER_H_
#define GROUND_ROVER_H_


enum MAV_RESULT cmd_nav_takeoff_handler(mavlink_command_long_t *cl);
enum MAV_RESULT cmd_nav_return_to_launch_handler(mavlink_command_long_t *cl);
enum MAV_RESULT cmd_nav_land_handler(mavlink_command_long_t *cl);
enum MAV_RESULT cmd_nav_loiter_unlim_handler(mavlink_command_long_t *cl);
enum MAV_RESULT cmd_override_goto_handler(mavlink_command_long_t *cl);

float calc_ground_rover_speed(uint32_t rtt);
Thread *ControllerGroundRoverInit(void);


#endif /* GROUND_ROVER_H_ */
