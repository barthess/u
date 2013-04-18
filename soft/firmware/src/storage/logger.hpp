#ifndef LOGGER_H_
#define LOGGER_H_

#include "ff.h"

/* use mavlink log format or raw format */
#define MAVLINK_LOG_FORMAT  TRUE

void log_write_schedule(uint8_t id, uint32_t *i, uint32_t decimator);
FRESULT WriteLog(FIL *Log, msg_t id, bool_t *fresh_data);


#endif /* LOGGER_H_ */
