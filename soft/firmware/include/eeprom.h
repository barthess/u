#include <stdlib.h>
#include "ch.h"
#include "message.h"

#ifndef EEPROM_H_
#define EEPROM_H_

/*===========================================================================*/
/*  онфигураци€ EEPROM */
/*===========================================================================*/
#define EEPROM_PAGE_SIZE  128   // размер страницы пам€ти (байт)
#define EEPROM_SIZE       65536 // суммарный размер пам€ти (байт)


/*===========================================================================*/
/* настройки */
/*===========================================================================*/
/* смещени€ данных относительного нулевого адреса и их длины */
#define EEPROM_SETTINGS_OFFSET 0
#define EEPROM_SETTINGS_SIZE   (EEPROM_PAGE_SIZE * 2)
/** сервы */
#define EEPROM_SERVO_SIZE 8                         /* количество байт на каждую серву. ќдин байт свободен, возможно под CRC */
#define EEPROM_SERVO_CNT 8                          /* сколько серв хранить в настройках */
#define EEPROM_SERVO_OFFSET (EEPROM_SETTINGS_OFFSET)


/*===========================================================================*/
/* точки маршрута */
/*===========================================================================*/
/* одна точка - это 3 координаты + скорость, кажда€ 4 байта = 16 байт
 * 128 / 16 = 8 точек на 1 страницу */
#define EEPROM_ROUTE_OFFSET    (EEPROM_SETTINGS_OFFSET + EEPROM_SETTINGS_SIZE)
#define EEPROM_ROUTEPOINT_SIZE 16                                              /* размер одной точки */
#define EEPROM_ROUTE_PAGES_NR  8                                               /* страниц под хранение точек */
#define EEPROM_ROUTE_SIZE      (EEPROM_PAGE_SIZE * EEPROM_ROUTE_PAGES_NR)      /* байт под хранение точек */
#define EEPROM_ROUTE_POINT_MAX_NR     (EEPROM_ROUTE_PAGES_NR * 8)              /* максимальное количество точек */


/*===========================================================================*/
/* место дл€ схоронени€ данных черного €щика.  ольцевой буфер. */
/*===========================================================================*/
#define EEPROM_LOG_OFFSET (EEPROM_ROUTE_OFFSET + EEPROM_ROUTE_SIZE)
#define EEPROM_LOG_SIZE   (EEPROM_SIZE - EEPROM_LOG_OFFSET)

/* buffers depth */
#define EEPROM_RX_DEPTH EEPROM_PAGE_SIZE
#define EEPROM_TX_DEPTH (EEPROM_PAGE_SIZE + 2)


/**
 * ѕишет 1 байт по указанному адресу
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
