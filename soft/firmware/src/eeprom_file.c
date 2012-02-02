#include "ch.h"
#include "hal.h"

#include "eeprom.h"
#include "eeprom_file.h"


static fileoffset_t getsize(void *ip){
  (void)ip;
  return EEPROM_SIZE;
}

static fileoffset_t getposition(void *ip){
  return ((EepromFileStream*)ip)->position;
}

static fileoffset_t lseek(void *ip, fileoffset_t offset){
  if (offset > (EEPROM_SIZE - 1))
    offset = EEPROM_SIZE - 1;
  ((EepromFileStream*)ip)->position = offset;
  return offset;
}

/* determines how much data can be processed */
static size_t _check_size(void *ip, size_t n){
  if (getposition(ip) > getsize(ip))
    return 0;
  else if ((getposition(ip) + n) > getsize(ip))
    return getsize(ip) - getposition(ip);
  else
    return n;
}

/**
 * @brief     Write data to EEPROM.
 * @details   Only one EEPROM page can be written at once. So fucntion
 *            splits large data chunks in small EEPROM transactions if needed.
 * @note      To achieve the maximum effectivity use write operations
 *            aligned to EEPROM page boundaries.
 */
static size_t write(void *ip, const uint8_t *bp, size_t n){
  msg_t status = RDY_OK;

  uint32_t len = 0;     /* bytes to be write at one trasaction */
  uint32_t written = 0; /* total bytes written */
  uint32_t page = getposition(ip) / EEPROM_PAGE_SIZE; /* first page to be write */

  n = _check_size(ip, n);
  if (n == 0)
    return 0;

  do{
    len = ((page + 1) * EEPROM_PAGE_SIZE) - getposition(ip);
    status  = eeprom_write((uint16_t)(getposition(ip) & 0xFFFF), bp, (uint16_t)(len & 0xFFFF));
    if (status != RDY_OK)
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
 * Read some bytes from current position in file. After successful
 * read operation the position pointer will be increased by the number
 * of read bytes.
 */
static size_t read(void *ip, uint8_t *bp, size_t n){
  msg_t status = RDY_OK;

  n = _check_size(ip, n);
  if (n == 0)
    return 0;

  /* call low level function */
  uint32_t pos = ((EepromFileStream*)ip)->position;
  status  = eeprom_read((uint16_t)(pos & 0xFFFF), bp, (uint16_t)(n & 0xFFFF));
  if (status != RDY_OK)
    return 0;
  else{
    lseek(ip, (getposition(ip) + n));
    return n;
  }
}

static uint32_t close(void *ip) {
  ((EepromFileStream*)ip)->errors = FILE_OK;
  ((EepromFileStream*)ip)->position = 0;
  ((EepromFileStream*)ip)->vmt = NULL;
  return FILE_OK;
}

static int geterror(void *ip){
  return ((EepromFileStream*)ip)->errors;
}

static const struct EepromFilelStreamVMT vmt = {
    write,
    read,
    close,
    geterror,
    getsize,
    getposition,
    lseek,
};

static EepromFileStream efs;

/**
 * Open EEPROM IC as file and return pointer to the file object
 */
const EepromFileStream* EepromOpen(void){
  efs.errors = FILE_OK;
  efs.position = 0;
  efs.vmt = &vmt;
  return &efs;
}





