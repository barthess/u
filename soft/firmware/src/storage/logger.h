#ifndef LOGGER_H_
#define LOGGER_H_

#include "ff.h"

/* use mavlink log format or raw format */
#define MAVLINK_LOG_FORMAT  TRUE

/**
 *
 * @brief   Macro helper. Shedule writing specified message to log.
 *
 * @param[in] id      Mavlink message id.
 * @api
 */
#define log_write_schedule(id) {\
  if (GlobalFlags & LOGGER_READY_FLAG){\
    chMBPost((&logwriter_mb), id, TIME_IMMEDIATE);\
  }\
}


FRESULT WriteLog(FIL *Log, msg_t id, bool_t *fresh_data);


#endif /* LOGGER_H_ */
