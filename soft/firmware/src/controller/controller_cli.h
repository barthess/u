#ifndef CONTROLLER_CLI_H_
#define CONTROLLER_CLI_H_

/**
 * target point for testing purpose
 */
typedef struct{
  float speed;
  uint32_t heading;
  uint32_t trip;
} test_point_t;

Thread* controller_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);

#endif /* CONTROLLER_CLI_H_ */
