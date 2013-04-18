#ifndef LOGGER_MAVENCODER_H_
#define LOGGER_MAVENCODER_H_

#include "uav.h"
#include "message.hpp"

uint16_t mavencoder(uint8_t msg_id, uint8_t system_id, uint8_t *threadsafe_buf, mavlink_message_t* msg);

#endif /* LOGGER_MAVENCODER_H_ */
