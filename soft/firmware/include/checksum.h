#include "ch.h"
#include "hal.h"

#ifndef CHECKSUM_H_
#define CHECKSUM_H_


uint8_t checksum_xor(uint8_t *buf, size_t len);
uint8_t checksum_xbee(uint8_t *buf, size_t len);
uint8_t checksum_crc8(uint8_t *buf, size_t len);
uint32_t checksum_crc32(uint8_t *buf, size_t len);

#endif /* CHECKSUM_H_ */
