#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "eeprom.h"
#include "message.h"
#include "i2c_pns.h"
#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define eepromaddr 0b1010000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// семафор для реализации задержек при записи в eeprom
static BinarySemaphore eeprom_sem;

// буфера под данные
static uint8_t rxbuf[EEPROM_RX_DEPTH];
static uint8_t txbuf[EEPROM_TX_DEPTH];

/**********************************************************************
Write cycle time (byte or page) — 5 ms

Note:
Page write operations are limited to writing
bytes within a single physical page,
regardless of the number of bytes
actually being written. Physical page
boundaries start at addresses that are
integer multiples of the page buffer size (or
‘page size’) and end at addresses that are
integer multiples of [page size – 1]. If a
Page Write command attempts to write
across a physical page boundary, the
result is that the data wraps around to the
beginning of the current page (overwriting
data previously stored there), instead of
being written to the next page as might be
expected.

ACKNOWLEDGE POLLING
Since the device will not acknowledge during a write
cycle, this can be used to determine when the cycle is
complete (this feature can be used to maximize bus
throughput). Once the Stop condition for a Write
command has been issued from the master, the device
initiates the internally timed write cycle. ACK polling
can be initiated immediately. This involves the master
sending a Start condition, followed by the control byte
for a Write command (R/W = 0). If the device is still
busy with the write cycle, then no ACK will be returned.
If no ACK is returned, then the Start bit and control byte
must be re-sent. If the cycle is complete, then the
device will return the ACK and the master can then
proceed with the next Read or Write command.
*********************************************************************/

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * @brief   Split one uint16_t address to two uint8_t.
 *
 * @param[in] txbuf pointer to driver transmit buffer
 * @param[in] addr  uint16_t address
 */
#define eeprom_split_addr(txbuf, addr){                       \
  (txbuf)[0] = ((uint8_t)((addr >> 8) & 0xFF));               \
  (txbuf)[1] = ((uint8_t)(addr & 0xFF));                      \
}

/**
 * @brief   EEPROM read routine.
 *
 * @param[in] addr      addres of 1-st byte to be read
 * @param[in] len       number of bytes to be write
 * @param[in] ext_rxbuf pointer to data buffer
 */
void eeprom_read(uint16_t addr, uint16_t len, uint8_t *ext_rxbuf){
  msg_t status = RDY_OK;

  chDbgCheck(((len + addr) < EEPROM_SIZE), "Addres is out of bounds");

  eeprom_split_addr(txbuf, addr);

  chBSemWait(&eeprom_sem); // если запись еще не закончилась -- микросхема не ответит. Будем ждать

  status = i2c_transmit(eepromaddr, txbuf, 2, ext_rxbuf, len);
  if (status  != RDY_OK){
    chSysLock();
    GlobalFlags |= EEPROM_FAILED;
    chSysUnlock();
  }

  chBSemSignal(&eeprom_sem);
}

/**
 * Читает байт по указанному адресу. Возвращает байт
 */
uint8_t eeprom_read_byte(uint16_t addr){
  eeprom_read(addr, 1, rxbuf);
  return rxbuf[0];
}

/**
 * читает 2 байта по указанному адресу. Возвращает полуслово
 */
uint16_t eeprom_read_halfword(uint16_t addr){
  eeprom_read(addr, 2, rxbuf);
  return (rxbuf[0] << 8) + rxbuf[1];
}

/**
 * читает 4 байта по указанному адресу. Возвращает слово
 */
uint32_t eeprom_read_word(uint16_t addr){
  eeprom_read(addr, 4, rxbuf);
  return (rxbuf[0] << 24) + (rxbuf[1] << 16) + (rxbuf[2] << 8) + rxbuf[3];
}

/**
 * @brief   EEPROM write routine.
 * @details Function writes data to EEPROM.
 * @pre     Data must be aligned to EEPROM pages.
 *
 * @param[in] addr  addres of 1-st byte to be write
 * @param[in] len   number of bytes to be write
 * @param[in] buf   pointer to data
 */
void eeprom_write(uint16_t addr, uint8_t len, uint8_t *buf){
  msg_t status = RDY_OK;
  uint8_t i = 0;

  chDbgCheck((len <= (128 - addr % 128)), "Data buffer is not alligned to one eeprom page");
  chDbgCheck(((len + addr) <= EEPROM_SIZE), "Addres is out of bounds");

  eeprom_split_addr(txbuf, addr);

  while (i < len){
    txbuf[i+2] = buf[i];
    i++;
  }

  chBSemWait(&eeprom_sem);

  status = i2c_transmit(eepromaddr, txbuf, (len + 2), rxbuf, 0);
  if (status  != RDY_OK){
    chSysLock();
    GlobalFlags |= EEPROM_FAILED;
    chSysUnlock();
  }

  chThdSleepMilliseconds(5); // задержка, необходимая для записи данных
  chBSemSignal(&eeprom_sem);
}

/**
 * Запускатор
 */
void init_eeprom(void){

#if CH_DBG_ENABLE_ASSERTS
  // clear bufers. Just to be safe.
  uint8_t i = 0;
  for (i = 0; i < EEPROM_TX_DEPTH; i++){txbuf[i] = 0x55;}
  for (i = 0; i < EEPROM_RX_DEPTH; i++){rxbuf[i] = 0x55;}
#endif

  chBSemInit(&eeprom_sem, FALSE);
}




