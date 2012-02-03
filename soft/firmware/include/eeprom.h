#ifndef EEPROM_H_
#define EEPROM_H_

/* page size in bytes. Consult datasheet. */
#define EEPROM_PAGE_SIZE  128

/* total amount of memory in bytes */
#define EEPROM_SIZE       65536

/* time to write one page in mS. Consult datasheet! */
#define EEPROM_WRITE_TIME 5

/* human readable status definitions */
#define EEPROM_SUCCESS   FALSE
#define EEPROM_FAILED    TRUE

/* data offsets in EEPROM "file" */
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

/**
 * @brief   Sequential Stream read.
 * @details The function reads data from a stream into a buffer.
 *
 * @param[in] ip        pointer to a @p BaseSequentialStream or derived class
 * @param[out] bp       pointer to the data buffer
 * @param[in] n         the maximum amount of data to be transferred
 * @return              The number of bytes transferred. The return value can
 *                      be less than the specified number of bytes if the
 *                      stream reaches the end of the available data.
 *
 * @api
 */
#define chFileStreamRead(ip, bp, n)  (chSequentialStreamRead(ip, bp, n))

/**
 * @brief   Sequential Stream write.
 * @details The function writes data from a buffer to a stream.
 *
 * @param[in] ip        pointer to a @p BaseSequentialStream or derived class
 * @param[in] bp        pointer to the data buffer
 * @param[in] n         the maximum amount of data to be transferred
 * @return              The number of bytes transferred. The return value can
 *                      be less than the specified number of bytes if the
 *                      stream reaches a physical end of file and cannot be
 *                      extended.
 *
 * @api
 */
#define chFileStreamWrite(ip, bp, n) (chSequentialStreamWrite(ip, bp, n))



EepromFileStream* EepromOpen(void);


#endif /* EEPROM_H_ */



