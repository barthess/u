#ifndef SPEED_CONTROL_H_
#define SPEED_CONTROL_H_


///**
// *
// */
typedef enum {
  WP_GOTO_REACHED = 0,
  WP_GOTO_ABORTED = 1,
  WP_GOTO_FAILED = 2,
  WP_GOTO_RESCHEDULED = 3,
} goto_wp_result_t;
//
//
//void loiter_if_need(void);
//void pid_keep_heading(float current, float desired);
//void pid_keep_speed(float current, float desired);
//Thread* StabInit(void);


#endif /* SPEED_CONTROL_H_ */
