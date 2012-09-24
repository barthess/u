#ifndef DBG_MSG_H_
#define DBG_MSG_H_

void DbgPrintInit(void);
msg_t dbg_print(uint8_t severity, const char *text);


#endif /* DBG_MSG_H_ */
