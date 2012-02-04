#ifndef EEPROM_FILE_H_
#define EEPROM_FILE_H_

#include "ch.h"
#include "hal.h"

#include "eeprom.h"

/* data offsets in "file" */
#define EEPROM_SETTINGS_START    8192
#define EEPROM_SETTINGS_SIZE     (EEPROM_PAGE_SIZE * 32)
#define EEPROM_SETTINGS_FINISH   (EEPROM_SETTINGS_START + EEPROM_SETTINGS_SIZE)

/**
 * @brief   @p EepromFileStream specific data.
 */
#define _eeprom_file_stream_data                                            \
  _base_file_stream_data                                                    \
  uint32_t    errors;                                                       \
  uint32_t    position;

/**
 * @brief   @p EepromFileStream virtual methods table.
 */
struct EepromFilelStreamVMT {
  _base_file_stream_methods
};

/**
 * @brief   EEPROM file stream driver class.
 * @details This class extends @p BaseFileStream by adding some fields.
 */
typedef struct EepromFileStream EepromFileStream;
struct EepromFileStream {
  /** @brief Virtual Methods Table.*/
  const struct EepromFilelStreamVMT *vmt;
  _eeprom_file_stream_data
};

#define chFileStreamRead(ip, bp, n)  (chSequentialStreamRead(ip, bp, n))
#define chFileStreamWrite(ip, bp, n) (chSequentialStreamWrite(ip, bp, n))

EepromFileStream* EepromOpen(void);


#endif /* EEPROM_FILE_H_ */
