#ifndef EEPROM_H_
#define EEPROM_H_

/* page size in bytes. Consult datasheet. */
#define EEPROM_PAGE_SIZE  128

/* total amount of memory in bytes */
#define EEPROM_SIZE       65536

/* time to write one page in mS. Consult datasheet! */
#define EEPROM_WRITE_TIME 5

/* temporal transmit buffer depth for eeprom driver */
#define EEPROM_TX_DEPTH (EEPROM_PAGE_SIZE + 2)

void init_eeprom(void);
msg_t eeprom_read(uint16_t addr, uint8_t *rxbuf, uint16_t len);
msg_t eeprom_write(uint16_t addr, const uint8_t *buf, uint8_t len);

#endif /* EEPROM_H_ */



