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
  if (n > getsize(ip))
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

  size_t   len = 0;     /* bytes to be written at one trasaction */
  uint32_t written = 0; /* total bytes successfully written */
  uint32_t firstpage = getposition(ip) / EEPROM_PAGE_SIZE;
  uint32_t lastpage  = (getposition(ip) + n - 1) / EEPROM_PAGE_SIZE;

  n = _check_size(ip, n);
  if (n == 0)
    return 0;

  /* data fitted in single page */
  if (firstpage == lastpage){
    len = n;
    status  = eeprom_write(getposition(ip), bp, len);
    if (status != RDY_OK)
      return 0;
    else{
      lseek(ip, (getposition(ip) + len));
      return len;
    }
  }

  else{
    /* запишем кусок данных до ближайшей границы страницы */
    len = ((firstpage + 1) * EEPROM_PAGE_SIZE) - getposition(ip);
    status  = eeprom_write(getposition(ip), bp, len);
    if (status != RDY_OK)
      return 0;
    else{
      written += len;
      bp += written;
      lseek(ip, (getposition(ip) + written));
    }

    /* теперь пишем куски, занимающие целую странцу (их может вообще не быть)*/
    while ((n - written) > EEPROM_PAGE_SIZE){
      status  = eeprom_write(getposition(ip), bp, EEPROM_PAGE_SIZE);
      if (status != RDY_OK)
        return written;
      else{
        written += EEPROM_PAGE_SIZE;
        bp += written;
        lseek(ip, (getposition(ip) + written));
      }
    }

    /* а теперь оставшийся хвостик, если есть */
    len = n - written;
    if (len == 0)
      return written;
    else{
      status  = eeprom_write(getposition(ip), bp, len);
      if (status != RDY_OK)
        return written;
      else{
        written += len;
        lseek(ip, (getposition(ip) + written));
      }
    }
  }
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
  status  = eeprom_read(pos, bp, n);
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
 * @note      Fucntion allways successfully open file. All checking makes
 *            in read/write functions.
 */
EepromFileStream* EepromOpen(void){
  efs.errors = FILE_OK;
  efs.position = 0;
  efs.vmt = &vmt;
  return &efs;
}





