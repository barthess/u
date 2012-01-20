#include <stdlib.h>
#include "ch.h"
#include "message.h"

#ifndef EEPROM_H_
#define EEPROM_H_

/*===========================================================================*/
/* ������������ EEPROM */
/*===========================================================================*/
#define EEPROM_PAGE_SIZE  128   // ������ �������� ������ (����)
#define EEPROM_SIZE       65536 // ��������� ������ ������ (����)


/*===========================================================================*/
/* ��������� */
/*===========================================================================*/
/* �������� ������ �������������� �������� ������ � �� ����� */
#define EEPROM_SETTINGS_OFFSET 0
#define EEPROM_SETTINGS_SIZE   (EEPROM_PAGE_SIZE * 2)
/** ����� */
#define EEPROM_SERVO_SIZE 8                         /* ���������� ���� �� ������ �����. ���� ���� ��������, �������� ��� CRC */
#define EEPROM_SERVO_CNT 8                          /* ������� ���� ������� � ���������� */
#define EEPROM_SERVO_OFFSET (EEPROM_SETTINGS_OFFSET)


/*===========================================================================*/
/* ����� �������� */
/*===========================================================================*/
/* ���� ����� - ��� 3 ���������� + ��������, ������ 4 ����� = 16 ����
 * 128 / 16 = 8 ����� �� 1 �������� */
#define EEPROM_ROUTE_OFFSET    (EEPROM_SETTINGS_OFFSET + EEPROM_SETTINGS_SIZE)
#define EEPROM_ROUTEPOINT_SIZE 16                                              /* ������ ����� ����� */
#define EEPROM_ROUTE_PAGES_NR  8                                               /* ������� ��� �������� ����� */
#define EEPROM_ROUTE_SIZE      (EEPROM_PAGE_SIZE * EEPROM_ROUTE_PAGES_NR)      /* ���� ��� �������� ����� */
#define EEPROM_ROUTE_POINT_MAX_NR     (EEPROM_ROUTE_PAGES_NR * 8)              /* ������������ ���������� ����� */


/*===========================================================================*/
/* ����� ��� ���������� ������ ������� �����. ��������� �����. */
/*===========================================================================*/
#define EEPROM_LOG_OFFSET (EEPROM_ROUTE_OFFSET + EEPROM_ROUTE_SIZE)
#define EEPROM_LOG_SIZE   (EEPROM_SIZE - EEPROM_LOG_OFFSET)

/* buffers depth */
#define EEPROM_RX_DEPTH EEPROM_PAGE_SIZE
#define EEPROM_TX_DEPTH (EEPROM_PAGE_SIZE + 2)


/**
 * ����� 1 ���� �� ���������� ������
 */
#define eeprom_write_byte(addr, byte){                                      \
  eeprom_write(addr, 1, (&(byte)));                                         \
}


void init_eeprom(void);

uint8_t  eeprom_read_byte(uint16_t addr);
uint16_t eeprom_read_halfword(uint16_t addr);
uint32_t eeprom_read_word(uint16_t addr);

void eeprom_read(uint16_t addr, uint16_t len, uint8_t *ext_rxbuf);
void eeprom_write(uint16_t addr, uint16_t len, uint8_t *buf);

void eeprom_write_log(uint16_t nr, RawData *buf);


#endif /* EEPROM_H_ */
