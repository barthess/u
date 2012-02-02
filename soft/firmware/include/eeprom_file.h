#ifndef EEPROM_FILE_H_
#define EEPROM_FILE_H_

#include "ch.h"
#include "hal.h"

#include "eeprom.h"

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


const EepromFileStream* EepromOpen(void);


#endif /* EEPROM_FILE_H_ */
