#ifndef LOGGER_H_
#define LOGGER_H_

#include "message.h"
#include "ff.h"

FRESULT WriteLog(FIL *Log, msg_t id, bool_t *fresh_data);

#endif /* LOGGER_H_ */
