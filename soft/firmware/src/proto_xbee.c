/*
 * proto_xbee.c
 *
 *  Created on: 09.05.2011
 *      Author: barthess
 */

#include "proto_xbee.h"
#include "checksum.h"


//-----------------------------------------------------------------------------
// ��������� � �����
//-----------------------------------------------------------------------------
#define USE_ACK FALSE // ������������ ������������� ���������� �������?


/* ����� ���������� � ���� ������� ������. ���� �������� �� 64 ���� ����������
 * ������������ �����*/
static const uint8_t dest64[8] = {0x00,0x13,0xA2,0x00,0x40,0x5D,0xF9,0xEA}; //GND
static const uint8_t self64[8] = {0x00,0x13,0xA2,0x00,0x40,0x5D,0xF9,0xE9}; //PNS


//-----------------------------------------------------------------------------
// �������
//-----------------------------------------------------------------------------

/**
 *  ������������ ������ � ����� ��� �������� ����� ����������
 * [in] *opacket ��������� �� �����, � ������� ���� ������� ������� �����
 * [in] *buf ��������� �� ���������, ������� ���� ���������
 * [in] len ������ ���������, ������� ���� �������
 * [in] id ������������� ������
 * [in] ack (xbee specific) �������������, �� ������� ����������� �������
 *      ��������� �������������, ���� ����� ���� - ������������� �� �����������
 * [out] ���������� ����, ������� ���� ���������� � UART �� ���� �����
 */

size_t xbee_wrap(uint8_t *opacket, uint8_t *buf, size_t len, uint8_t id, uint8_t ack){
	// ��������� ����� ��� ��������� ��������������� �����
	uint8_t raw_opacket[API_PACKET_LEN];
	uint8_t checksum_pos = 0;

	chDbgCheck((buf != NULL) && (opacket != NULL) && (len <= RF_DATA_LEN),
             "xbee_wrap");

  // ��������� ��������� ����
	fill_header(raw_opacket, len, ack);

  // ��������� ������ ��������, ����� ����������
  cpbuf(&raw_opacket[TX_RF_DATA_OFFSET + 1], buf, len);
  raw_opacket[TX_RF_DATA_OFFSET] = id;

  // ����� ����� ��� ���� ������� ���������� �����
  len = raw_opacket[LEN_OFFSET + 1] + (raw_opacket[LEN_OFFSET] << 8);
  // ������� ����������� ����� � ������
  checksum_pos = LEN_OFFSET + LEN_LEN + len;
  // ������� ����������� �����
  raw_opacket[checksum_pos] = checksum_xbee(&raw_opacket[LEN_OFFSET + LEN_LEN], len);

  // ��������� ������������
  return(escape_packet(raw_opacket, opacket));
}



/**
 * ������������ ������ �� ������, ��������� �� ������
 * [in] *clean_ipacket ��������� �� �����, � ������� ���� ������� ������������ �����
 * [in] *ipacket ��������� �� �����, � ������� ������� ����� �� ������
 * [in] len ���������� ������
 * [out] ��������� �� ������ �������� �������� � clean_ipacket
 */
uint8_t* xbee_extract(uint8_t *clean_ipacket, uint8_t *ipacket, size_t len){
  len = unescape_packet(clean_ipacket, ipacket, len);                         // ������ ������� � ������� ������
  /* � ������ ����� ����� � ����� ��������� */

  if (ipacket[0] != 0x7E){                                                    // �������� ���������
  	return NULL;
  }

  len = len - DELIM_LEN - LEN_LEN - XBEE_CHECKSUM_LEN;                        // �������� �����
  size_t api_len = 0;
  api_len = clean_ipacket[LEN_OFFSET + 1] + (clean_ipacket[LEN_OFFSET] << 8);
  if (len != api_len){
  	return NULL;
  }

  if (checksum_xbee(                                                          // �������� ����������� �����
      &clean_ipacket[LEN_OFFSET + LEN_LEN], api_len + XBEE_CHECKSUM_LEN) != 0){
  	return NULL;
  }

  // ������� �� ��������
	switch(clean_ipacket[API_ID_OFFSET]){
	case API_RX_PACK:
		return &(clean_ipacket[RX_RF_DATA_OFFSET]);
	case API_TX_STATUS:
		return NULL;
	default:
		return NULL;
		// TODO: ����� ��������� ����������
	}
}


/* ��������� ��������� ���� */
void fill_header(uint8_t *buf, size_t len, uint8_t ack){
  uint8_t i = 0;

  chDbgCheck((len + 1 < RF_DATA_LEN), "Too much data");
  if (len + 1 > RF_DATA_LEN)
    len = RF_DATA_LEN - 1;

  // TODO: ���������� ��������� ���������� ���-������
  // �����������
  buf[DELIM_OFFSET] = DELIM;
  // �����
  buf[LEN_OFFSET] = 0; // ������� ���� ������ ���������� ����� 0
  /* ��������� ����� + (����� + ID) - ��������� - ����� ����� - ����� ����������� �����*/
  buf[LEN_OFFSET + 1] = CONTROL_LEN + (len + 1) - DELIM_LEN - LEN_LEN - XBEE_CHECKSUM_LEN;
  // ��� ������ ��������
  buf[API_ID_OFFSET] = API_TX_REQ;
  // ����� �� ������������� � ��������
  buf[API_ACK_OFFSET] = ack;
  // ���������� ������
  i = 8;
  while (i--){
    buf[DEST64_ADDR_OFFSET + i] = dest64[i];
  }
  buf[DEST16_ADDR_OFFSET] = 0xFF;
  buf[DEST16_ADDR_OFFSET + 1] = 0xFE;
  buf[BCAST_RADIUS_OFFSET] = 1;
  buf[OPTIONS_OFFSET] = 0;
}

/*
 * �������� ���������� ��������� �� ��������� �����
 */
inline void cpbuf(uint8_t *out, uint8_t *in, size_t len){
  // ������� ��������� �� ���������� ��������� � uint8_t*
  uint8_t *casted_in = in;
  while(len--){
    out[len] = casted_in[len];
  }
}


/*
 * �������� ��� ����������� ������� esc-��������������������
 * ��������� �������� ��, ����� ���������
 * [in] *raw_buf ��������� �� �������� ����� � ����������� ������
 * [in] *packet ��������� �� ����� ��� ������������� �����
 * [out] ���������� ���� �� ���� �����
 */
size_t escape_packet(uint8_t *raw_buf, uint8_t *packet){
  uint8_t len = 0;
  uint8_t i = 0; // ������ ��� ������������� �������
  uint8_t j = 0; // ������ ��� �������� �������
  // ������ ��� ����� ���������
  len = DELIM_LEN + raw_buf[LEN_OFFSET + 1] + (raw_buf[LEN_OFFSET] << 8) + LEN_LEN + XBEE_CHECKSUM_LEN;

  // �������� ��������� �������� ������
  packet[0] = raw_buf[0]; // ��������� ��� ���������
  j = 1;
  i = 1;

  for (j=1; j<len; j++){
    switch(raw_buf[j]){
    case 0x11:
      packet[i] = 0x7D;
      packet[i+1] = 0x11 ^ 0x20;
      i += 2;
      break;
    case 0x13:
      packet[i] = 0x7D;
      packet[i+1] = 0x13 ^ 0x20;
      i += 2;
      break;
    case 0x7D:
      packet[i] = 0x7D;
      packet[i+1] = 0x7D ^ 0x20;
      i += 2;
      break;
    case 0x7E:
      packet[i] = 0x7D;
      packet[i+1] = 0x7E ^ 0x20;
      i += 2;
      break;
    default:
      packet[i] = raw_buf[j];
      i++;
      break;
    }
  }
  return i; // ����� ������, � ������ ���������
}


/*
 * �������� ��� esc-������������������ ���������
 * ��������� �������� ��, ����� ���������
 * [in] *raw_buf ��������� �� �������� ����� � ����������� ������
 * [in] *ipacket ��������� �� ����� ��� ������������� �����
 * [out] ���������� ���� �� ���� �����
 */
size_t unescape_packet(uint8_t *raw_buf, uint8_t *ipacket, size_t len){
  uint8_t i = 1; // ������ ��� ������������� �������
  uint8_t j = 1; // ������ ��� �������� �������

  raw_buf[0] = ipacket[0]; // ��������� ��� ���������

  for (j=1; j<len; j++){
    if (ipacket[j] == 0x7D){
      raw_buf[i] = ipacket[j + 1] ^ 0x20;
      i++;
      j++; // ��������, �.�. ������� 2 �����
    }
    else{
      raw_buf[i] = ipacket[j];
      i++;
    }
  }
  // ������ ���������� ���� ����� �������� ��������
  return(i);
}




