/*
 * proto_xbee.h
 *
 *  Created on: 09.05.2011
 *      Author: barthess
 *      ���� ��������� ��������� ������ ��� ������ ������ API-��������� xbee
 */

#include "ch.h"
#include "hal.h"


#ifndef PROTO_XBEE_H_
#define PROTO_XBEE_H_

// ������ ������ �������������
#define DELIM 0x7E
#define DELIM_LEN 1
#define DELIM_OFFSET 0

// ����� ������
#define LEN_LEN 2
#define LEN_OFFSET 1

// API-������������� ������

#define API_TX_REQ     0x10 // ������ �������� ������
#define API_TX_STATUS  0x8B // ������������� � ��������
#define API_RX_PACK    0x90 // ������ ����� ������
#define API_ID_LEN 1
#define API_ID_OFFSET 3

// ID ������ ��� ����� ACK. ���� ����� 0, �� ACK �� ��������
#define API_ACK 0
#define API_ACK_LEN 1
#define API_ACK_OFFSET 4

// ����� ���������� 64 ����
#define DEST64_ADDR_GND 0x0013A200405DF9EA
#define DEST64_ADDR_PNS 0x0013A200405DF9E9
#define DEST64_ADDR_LEN 8
#define DEST64_ADDR_OFFSET 5

// ������� ����� 16 ���
#define DEST16_ADDR 0xFFFE // ����� ������������ ������������� ��������
#define DEST16_ADDR_LEN 2
#define DEST16_ADDR_OFFSET 13

// ������������ ���������� ������� ����� ��������
#define BCAST_RADIUS 0 // �������� ������������ ���������� ������� - 10
#define BCAST_RADIUS_LEN 1
#define BCAST_RADIUS_OFFSET 15

// ������������� multicast/unicast
#define OPTIONS 0 // 0 - �������� unicast
#define OPTIONS_LEN 1
#define OPTIONS_OFFSET 16

// ������ ���� ������, ������� ���� ��������. �� ����� 72 ���� �� �����.
#define RF_DATA_LEN 72
#define TX_RF_DATA_OFFSET 17
#define RX_RF_DATA_OFFSET 15

// ����� ������ ���� ����������� �����
#define XBEE_CHECKSUM 0xFF
#define XBEE_CHECKSUM_LEN 1

// ������������ ������ ������ � ������ API ������ � ���������� � ����������� ������
#define API_PACKET_LEN 90
 /* ��������� ������ ���� ����� ������������
 * ������������ � 2 - �������� ������ �� 2
 * TODO: �������� ���� ����� ��������� ��������� �� 1.5 */
#define O_PACKET_LEN (API_PACKET_LEN * 2)
#define I_PACKET_LEN (API_PACKET_LEN * 2)

// ���������� ��������� ���� ������ � ����������� ������
#define CONTROL_LEN (TX_RF_DATA_OFFSET + 1)


size_t xbee_wrap(uint8_t *opacket, uint8_t *buf, size_t len, uint8_t id, uint8_t ack);
uint8_t* xbee_extract(uint8_t *raw_ipacket, uint8_t *ipacket, size_t len);
void fill_header(uint8_t *buf, size_t len, uint8_t ack);
void cpbuf(uint8_t *out, uint8_t *in, size_t len);
size_t escape_packet(uint8_t *raw_buf, uint8_t *opacket);
size_t unescape_packet(uint8_t *raw_buf, uint8_t *ipacket, size_t len);



#endif /* PROTO_XBEE_H_ */
