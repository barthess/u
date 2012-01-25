/*
 * proto_xbee.h
 *
 *  Created on: 09.05.2011
 *      Author: barthess
 *      Файл описывает струкруры данных для обмена поверх API-протокола xbee
 */

#include "ch.h"
#include "hal.h"


#ifndef PROTO_XBEE_H_
#define PROTO_XBEE_H_

// начало пакета фиксированное
#define DELIM 0x7E
#define DELIM_LEN 1
#define DELIM_OFFSET 0

// длина пакета
#define LEN_LEN 2
#define LEN_OFFSET 1

// API-идентификатор пакета

#define API_TX_REQ     0x10 // запрос передачи данных
#define API_TX_STATUS  0x8B // подтверждение о доставке
#define API_RX_PACK    0x90 // пришел пакет данных
#define API_ID_LEN 1
#define API_ID_OFFSET 3

// ID пакета для целей ACK. Если равен 0, то ACK не приходит
#define API_ACK 0
#define API_ACK_LEN 1
#define API_ACK_OFFSET 4

// адрес назначения 64 бита
#define DEST64_ADDR_GND 0x0013A200405DF9EA
#define DEST64_ADDR_PNS 0x0013A200405DF9E9
#define DEST64_ADDR_LEN 8
#define DEST64_ADDR_OFFSET 5

// сетевой адрес 16 бит
#define DEST16_ADDR 0xFFFE // будем использовать фиксированное значение
#define DEST16_ADDR_LEN 2
#define DEST16_ADDR_OFFSET 13

// максимальное количество прыжков между модемами
#define BCAST_RADIUS 0 // означает максимальное количество прыжков - 10
#define BCAST_RADIUS_LEN 1
#define BCAST_RADIUS_OFFSET 15

// переключатель multicast/unicast
#define OPTIONS 0 // 0 - означает unicast
#define OPTIONS_LEN 1
#define OPTIONS_OFFSET 16

// дальше идут данные, которые надо передать. Не более 72 байт на пакет.
#define RF_DATA_LEN 72
#define TX_RF_DATA_OFFSET 17
#define RX_RF_DATA_OFFSET 15

// после данных идет контрольная сумма
#define XBEE_CHECKSUM 0xFF
#define XBEE_CHECKSUM_LEN 1

// максимальная длинна пакета в режиме API вместе с заголовком и контрольной суммой
#define API_PACKET_LEN 90
 /* Поскольку каждый байт может теоретически
 * превратиться в 2 - умножаем длинну на 2
 * TODO: возможно есть смысл уменьшить множитель до 1.5 */
#define O_PACKET_LEN (API_PACKET_LEN * 2)
#define I_PACKET_LEN (API_PACKET_LEN * 2)

// количество служебных байт вместе с контрольной суммой
#define CONTROL_LEN (TX_RF_DATA_OFFSET + 1)


size_t xbee_wrap(uint8_t *opacket, uint8_t *buf, size_t len, uint8_t id, uint8_t ack);
uint8_t* xbee_extract(uint8_t *raw_ipacket, uint8_t *ipacket, size_t len);
void fill_header(uint8_t *buf, size_t len, uint8_t ack);
void cpbuf(uint8_t *out, uint8_t *in, size_t len);
size_t escape_packet(uint8_t *raw_buf, uint8_t *opacket);
size_t unescape_packet(uint8_t *raw_buf, uint8_t *ipacket, size_t len);



#endif /* PROTO_XBEE_H_ */
