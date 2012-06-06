#ifndef LINK_SORTOUT_H_
#define LINK_SORTOUT_H_

#include "link.h"
#include "message.h"

uint16_t sort_output_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf);
uint16_t mavencoder(uint8_t msg_id, uint8_t system_id, mavlink_message_t* msg);

#endif /* LINK_SORTOUT_H_ */
