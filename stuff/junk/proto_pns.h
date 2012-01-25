#include "ch.h"
#include "hal.h"
#include "message.h"

#ifndef PROTO_PNS_H_
#define PROTO_PNS_H_



// проткольный уровень, т.е. состав кадра:
#define PROTO_ID_OFFSET 0
#define PROTO_ID_LEN 1

#define PROTO_DIRECTION_OFFSET (PROTO_ID_OFFSET + PROTO_ID_LEN)
#define PROTO_DIRECTION_LEN 1

#define PROTO_MSG_OFFSET (PROTO_DIRECTION_OFFSET + PROTO_DIRECTION_LEN)


uint8_t ProtoPnsParser(uint8_t *buf);
uint8_t unpack_routepoint(RoutePoint *rp, uint8_t *buf);


#endif /* PROTO_PNS_H_ */

