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

#include <string.h>

#include "ch.h"
#include "hal.h"

#include "eeprom.h"


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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* semaphore for mutual access to EEPROM */
static BinarySemaphore eeprom_sem;

/* temporal transmit buffer. One page + 2 address bytes */
static uint8_t txbuf[EEPROM_PAGE_SIZE + 2];

/* object representing eeprom file stream */
static EepromFileStream efs;

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
#define eeprom_split_addr(txbuf, addr){                                       \
  (txbuf)[0] = ((uint8_t)((addr >> 8) & 0xFF));                               \
  (txbuf)[1] = ((uint8_t)(addr & 0xFF));                                      \
}

/**
 * @brief   EEPROM read routine.
 *
 * @param[in] addr      addres of 1-st byte to be read
 * @param[in] len       number of bytes to be write
 * @param[in] ext_rxbuf pointer to data buffer
 */
static bool_t eeprom_read(uint16_t addr, uint8_t *rxbuf, uint16_t len){
  msg_t status = RDY_OK;

  eeprom_split_addr(txbuf, addr);

  chBSemWait(&eeprom_sem);

  i2cAcquireBus(&I2CD2);
  status = i2cMasterTransmitTimeout(&I2CD2, eepromaddr, txbuf, 2, rxbuf,
                                    len, MS2ST(6));
  i2cReleaseBus(&I2CD2);

  chBSemSignal(&eeprom_sem);
  if (status != RDY_OK)
    return EEPROM_FAILED;
  else
    return EEPROM_SUCCESS;
}

/**
 * @brief   EEPROM write routine.
 * @details Function writes data to EEPROM.
 * @pre     Data must be fit to EEPROM single pages.
 *
 * @param[in] addr  addres of 1-st byte to be write
 * @param[in] buf   pointer to data
 * @param[in] len   number of bytes to be written
 */
static bool_t eeprom_write(uint16_t addr, const uint8_t *buf, uint8_t len){
  msg_t status = RDY_OK;

  eeprom_split_addr(txbuf, addr);
  memcpy(&(txbuf[2]), buf, len);

  chBSemWait(&eeprom_sem);

  i2cAcquireBus(&I2CD2);
  status = i2cMasterTransmitTimeout(&I2CD2, eepromaddr, txbuf, (len + 2),
                                    NULL, 0, MS2ST(6));
  i2cReleaseBus(&I2CD2);

  /* wait until EEPROM process data */
  chThdSleepMilliseconds(EEPROM_WRITE_TIME);
  chBSemSignal(&eeprom_sem);
  if (status != RDY_OK)
    return EEPROM_FAILED;
  else
    return EEPROM_SUCCESS;
}

/**
 * @brief   Returns total size of EEPROM
 */
static fileoffset_t getsize(void *ip){
  (void)ip;
  return EEPROM_SIZE;
}

/**
 * @brief   Returns current position in file
 */
static fileoffset_t getposition(void *ip){
  return ((EepromFileStream*)ip)->position;
}

/**
 * @brief   Determines how much data can be processed
 * @note    Helper function
 */
static size_t _check_size(void *ip, size_t n){
  if (getposition(ip) > getsize(ip))
    return 0;
  else if ((getposition(ip) + n) > getsize(ip))
    return getsize(ip) - getposition(ip);
  else
    return n;
}

/**
 * @brief   Go to specified position in file
 */
static fileoffset_t lseek(void *ip, fileoffset_t offset){
  if (offset > (EEPROM_SIZE - 1))
    offset = EEPROM_SIZE - 1;
  ((EepromFileStream*)ip)->position = offset;
  return offset;
}

/**
 * @brief     Write data to EEPROM.
 * @details   Only one EEPROM page can be written at once. So fucntion
 *            splits large data chunks in small EEPROM transactions if needed.
 * @note      To achieve the maximum effectivity use write operations
 *            aligned to EEPROM page boundaries.
 */
static size_t write(void *ip, const uint8_t *bp, size_t n){
  bool_t status;

  uint32_t len = 0;     /* bytes to be written at one trasaction */
  uint32_t written = 0; /* total bytes written */
  uint32_t page = getposition(ip) / EEPROM_PAGE_SIZE; /* first page to be written */

  n = _check_size(ip, n);
  if (n == 0)
    return 0;

  do{
    len = ((page + 1) * EEPROM_PAGE_SIZE) - getposition(ip);
    status  = eeprom_write((uint16_t)(getposition(ip) & 0xFFFF),
                           bp,
                           (uint16_t)(len & 0xFFFF));
    if (status != EEPROM_SUCCESS)
      return written;
    page++;
    written += len;
    bp += len;
    lseek(ip, (getposition(ip) + len));
  }
  while (written < n);

  return written;
}

/**
 * @brief     Read some bytes from current position in file.
 * @detatils  After successful read operation the position pointer
 *            will be increased by the number of read bytes.
 */
static size_t read(void *ip, uint8_t *bp, size_t n){
  msg_t status = RDY_OK;

  n = _check_size(ip, n);
  if (n == 0)
    return 0;

  /* call low level function */
  uint32_t pos = ((EepromFileStream*)ip)->position;
  status  = eeprom_read((uint16_t)(pos & 0xFFFF), bp, (uint16_t)(n & 0xFFFF));
  if (status != EEPROM_SUCCESS)
    return 0;
  else{
    lseek(ip, (getposition(ip) + n));
    return n;
  }
}

/**
 * @brief     Close file.
 */
static uint32_t close(void *ip) {
  ((EepromFileStream*)ip)->errors = FILE_OK;
  ((EepromFileStream*)ip)->position = 0;
  ((EepromFileStream*)ip)->vmt = NULL;
  return FILE_OK;
}

/**
 * @brief     Returns error code.
 */
static int geterror(void *ip){
  return ((EepromFileStream*)ip)->errors;
}

/* Init virtual metod table */
static const struct EepromFilelStreamVMT vmt = {
    write,
    read,
    close,
    geterror,
    getsize,
    getposition,
    lseek,
};

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief     Opens EEPROM IC as file and return pointer to the file object.
 * @note      Fucntion allways successfully open file. All checking makes
 *            in read/write functions.
 */
EepromFileStream* EepromOpen(){

  /* clear bufer just to be safe */
  uint32_t i = 0;
  for (i = 0; i < sizeof(txbuf); i++){txbuf[i] = 0x5A;}

  chBSemInit(&eeprom_sem, FALSE);

  efs.errors = FILE_OK;
  efs.position = 0;
  efs.vmt = &vmt;
  return &efs;
}
