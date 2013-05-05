#ifndef MAVCMD_LOCAL_H_
#define MAVCMD_LOCAL_H_

#include "message.hpp"

void ExecuteCommandLong(mavlink_command_long_t *clp);
void MavCommanderInit(void);

#endif /* MAVCMD_LOCAL_H_ */
