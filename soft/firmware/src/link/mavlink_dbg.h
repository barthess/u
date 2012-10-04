#ifndef MAVLINK_DBG_H_
#define MAVLINK_DBG_H_


void MavlinkDbgPrintInit(void);
msg_t mavlink_dbg_print(uint8_t severity, const char *text);


#endif /* MAVLINK_DBG_H_ */
