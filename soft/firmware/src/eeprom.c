#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "eeprom.h"
#include "rtc.h"
#include "bkp.h"
#include "message.h"


#define I2CD_eeprom I2CD2
#define eeprom_addr 0b1010000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern LogItem log_item;
extern Mailbox eeprommanager_mb;
//extern RTCTime timespec;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// семафор для реализации задержек при записи в eeprom
static Semaphore eeprom_sem;

// буфера под данные
static uint8_t eeprom_rxbuf[EEPROM_RX_DEPTH];
static uint8_t eeprom_txbuf[EEPROM_TX_DEPTH];

static i2cflags_t errors = 0;

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
  chDbgCheck(((len + addr) < EEPROM_SIZE), "Addres is out of bounds");

  eeprom_split_addr(eeprom_txbuf, addr);

  chSemWait(&eeprom_sem); // если запись еще не закончилась -- микросхема не ответит. Будем ждать
  i2cAcquireBus(&I2CD_eeprom);
  i2cMasterTransmit(&I2CD_eeprom, eeprom_addr, eeprom_txbuf, 2, ext_rxbuf, len);
  i2cReleaseBus(&I2CD_eeprom);
  chSemSignal(&eeprom_sem);
}

/**
 * Читает байт по указанному адресу. Возвращает байт
 */
inline uint8_t eeprom_read_byte(uint16_t addr){
  eeprom_read(addr, 1, eeprom_rxbuf);
  return eeprom_rxbuf[0];
}

/**
 * читает 2 байта по указанному адресу. Возвращает полуслово
 */
inline uint16_t eeprom_read_halfword(uint16_t addr){
  eeprom_read(addr, 2, eeprom_rxbuf);
  return (eeprom_rxbuf[0] << 8) + eeprom_rxbuf[1];
}

/**
 * читает 4 байта по указанному адресу. Возвращает слово
 */
inline uint32_t eeprom_read_word(uint16_t addr){
  eeprom_read(addr, 4, eeprom_rxbuf);
  return (eeprom_rxbuf[0] << 24) + (eeprom_rxbuf[1] << 16) + (eeprom_rxbuf[2] << 8) + eeprom_rxbuf[3];
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
void eeprom_write(uint16_t addr, uint16_t len, uint8_t *buf){
  uint8_t i = 0;

  chDbgCheck((len <= (128 - addr % 128)), "Data buffer is not alligned to one eeprom page");
  chDbgCheck(((len + addr) <= EEPROM_SIZE), "Addres is out of bounds");

  eeprom_split_addr(eeprom_txbuf, addr);

  while (i < len){
    eeprom_txbuf[i+2] = buf[i];
    i++;
  }

  chSemWait(&eeprom_sem);

  i2cAcquireBus(&I2CD_eeprom);
  i2cMasterTransmit(&I2CD_eeprom, eeprom_addr, eeprom_txbuf, (len + 2), eeprom_rxbuf, 0);
  i2cReleaseBus(&I2CD_eeprom);

  chThdSleepMilliseconds(5); // задержка, необходимая для записи данных
  chSemSignal(&eeprom_sem);
}



/* Поток для обслуживания запросов записи и чтения из EEPROM
 * Хапает сообещения из почтового ящики и по месту определяет, что надо делать */
static WORKING_AREA(EepromManagerThreadWA, 256);
static msg_t EepromManagerThread(void *arg){
  chRegSetThreadName("EepromManager");
  (void)arg;
  msg_t msg; /* для временного хранения сообщения */

  uint8_t   *buf = NULL;
  uint16_t  len  = 0;
  uint16_t  addr = 0;
  EepromReq *ereq_p = NULL;

  while(TRUE){
    chMBFetch(&eeprommanager_mb, &msg, TIME_INFINITE);
    ereq_p = (EepromReq *)msg;

    addr = ereq_p->addr;
    len  = ereq_p->len;
    buf  = ereq_p->bufp;

    if(len & 0x8000){
      len &= 0x7FFF;                /* не забываем откусить бит записи */
      eeprom_read(addr, len, buf);
    }
    else
      eeprom_write(addr, len, buf);

    ereq_p->bufp = NULL;              /* флаг готовности к приему новых данных */

    /* в качестве подтверждения в почтовый ящик бросается указатель на
     * ЕЕПРОМ запрос, тот самый, что был получен в начале */
    if (ereq_p->mailbox != NULL)
      chMBPost(ereq_p->mailbox, (msg_t)ereq_p, TIME_IMMEDIATE);
  }
}



inline void init_eeprom(void){
  chSemInit(&eeprom_sem, 1);

  chThdCreateStatic(EepromManagerThreadWA,
          sizeof(EepromManagerThreadWA),
          NORMALPRIO,
          EepromManagerThread,
          NULL);
}



#undef I2CD_eeprom

