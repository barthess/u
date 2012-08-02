#include "mavlink.h"
#include "common.h"


#ifndef LINK_H_
#define LINK_H_


void SpawnMavlinkThreads(SerialDriver *sdp);
void PurgeUavMailbox(Mailbox *mbp);
void KillMavlinkThreads(void);


#endif /* LINK_H_ */
