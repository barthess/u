/**********************************************************************
Write cycle time (byte or page) Ч 5 ms

Note:
Page write operations are limited to writing
bytes within a single physical page,
regardless of the number of bytes
actually being written. Physical page
boundaries start at addresses that are
integer multiples of the page buffer size (or
Сpage sizeТ) and end at addresses that are
integer multiples of [page size Ц 1]. If a
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

#include <string.h>

#include "ch.h"
#include "hal.h"

#include "eepromio.h"
#include "message.h"
#include "i2c_pns.h"
#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define i2caddr 0b1010000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// семафор дл€ реализации задержек при записи в eeprom
static BinarySemaphore eeprom_sem;

// буфера под данные
static uint8_t localtxbuf[EEPROM_TX_DEPTH];

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */
/**
 * @brief   Split one uint16_t address to two uint8_t.
 *
 * @param[in] txbuf pointer to driver transmit buffer
 * @param[in] addr  uint16_t address
 */
#define eeprom_split_addr(txbuf, addr){                                       \
  (txbuf)[0] = ((uint8_t)((addr >> 8) & 0xFF));                               \
  (txbuf)[1] = ((uint8_t)(addr & 0xFF));                                      \
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief   EEPROM read routine.
 *
 * @param[in] addr      addres of 1-st byte to be read
 * @param[in] len       number of bytes to be write
 * @param[in] ext_rxbuf pointer to data buffer
 */
msg_t eeprom_read(uint32_t addr, uint8_t *buf, size_t len){
  msg_t status = RDY_OK;

  chBSemWait(&eeprom_sem);

  chDbgCheck(((len < EEPROM_SIZE) && ((addr+len) < EEPROM_SIZE)),
             "data can not be fitted in device");

  eeprom_split_addr(localtxbuf, addr);

  status = i2c_transmit(i2caddr, localtxbuf, 2, buf, len);

  chBSemSignal(&eeprom_sem);
  return status;
}

/**
 * @brief   EEPROM write routine.
 * @details Function writes data to EEPROM.
 * @pre     Data must be fit to single EEPROM page.
 *
 * @param[in] addr  addres of 1-st byte to be write
 * @param[in] buf   pointer to data
 * @param[in] len   number of bytes to be written
 */
msg_t eeprom_write(uint32_t addr, const uint8_t *buf, size_t len){
  msg_t status = RDY_OK;

  chBSemWait(&eeprom_sem);

  chDbgCheck(((len < EEPROM_SIZE) && ((addr+len) < EEPROM_SIZE)),
             "data can not be fitted in device");

  chDbgCheck(((addr / EEPROM_PAGE_SIZE) == ((addr + len - 1) / EEPROM_PAGE_SIZE)),
             "data can not be fitted in single page");

  /* write address bytes */
  eeprom_split_addr(localtxbuf, addr);

  /* write data bytes */
  memcpy(&(localtxbuf[2]), buf, len);
//  uint32_t i = 0;
//  while (i < len){
//    localtxbuf[i+2] = buf[i];
//    i++;
//  }

  status = i2c_transmit(i2caddr, localtxbuf, (len + 2), NULL, 0);

  /* wait until EEPROM process data */
  chThdSleepMilliseconds(EEPROM_WRITE_TIME);
  chBSemSignal(&eeprom_sem);
  return status;
}

/**
 * Starter
 */
void init_eeprom(void){

  /* clear bufer just to be safe. */
  memset(localtxbuf, 0x55, EEPROM_TX_DEPTH);

  chBSemInit(&eeprom_sem, FALSE);
}



