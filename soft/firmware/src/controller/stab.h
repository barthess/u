#ifndef SPEED_CONTROL_H_
#define SPEED_CONTROL_H_

/**
 *
 */
typedef enum {
  WP_GOTO_REACHED = 0,
  WP_GOTO_ABORTED = 1,
  WP_GOTO_FAILED = 2,
  WP_GOTO_RESCHEDULED = 3,
} goto_wp_result_t;

void WpSeqOverwrite(uint16_t seq);
Thread* StabInit(void);

#endif /* SPEED_CONTROL_H_ */
