#include "ch.h"
#include "hal.h"

#include "message.h"
#include "dsp.h"
#include "pmu.h"
#include "main.h"
#include "i2c_pns.h"
#include "max1236.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define max1236addr 0b0110100

/**сонар выдает Vcc/1024 вольт на см
 * разрешающая способность АЦП Vcc/4096
 * Итого: для получения высоты в см надо полученный результат поделить на 4 */
#define SONAR_COEF 4

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData compensated_data;
extern Mailbox tolink_mb;
extern uint64_t TimeUsec;
extern mavlink_raw_pressure_t mavlink_raw_pressure_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[MAX1236_RX_DEPTH];
static uint8_t txbuf[MAX1236_TX_DEPTH];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/** Опрос max1236
 * после настройки достаточно просто читать из него данные, по 2 байта на канал
 * после отправки запроса АЦП занимает линию примерно на 8.3uS, после чего
 * отдает результат. Как только мастер вычитал нужное количество байт - дает
 * в шину STOP.
 * При частоте 100кГц на вычитывание 4 значений уйдет примерно:
 * 10 * (4 * 2 * 8) + 8.3 * 4 = 673.2 uS
 */
static WORKING_AREA(PollMax1236ThreadWA, 512);
static msg_t PollMax1236Thread(void *arg) {
  chRegSetThreadName("PollMax1236");
  (void)arg;
  int16_t press_diff_raw = 0;
  int16_t sonar_raw = 0;

  Mail air_data_mail;
  air_data_mail.payload = NULL;
  air_data_mail.invoice = MAVLINK_MSG_ID_RAW_PRESSURE;
  air_data_mail.confirmbox = NULL;

  uint32_t n = 0;

  while (TRUE) {
    chThdSleepMilliseconds(20);

    if (i2c_receive(max1236addr, rxbuf, MAX1236_RX_DEPTH) == RDY_OK){
      press_diff_raw = ((rxbuf[0] & 0xF) << 8) + rxbuf[1];
      sonar_raw = ((rxbuf[2] & 0xF) << 8) + rxbuf[3];

      /* рассчет воздушной скорости и сохранение для нужд автопилота */
      compensated_data.air_speed = (uint16_t)(1000 * calc_air_speed(press_diff_raw));

      raw_data.altitude_sonar = sonar_raw;
    }

    mavlink_raw_pressure_struct.time_usec = TimeUsec;
    mavlink_raw_pressure_struct.press_diff1 = press_diff_raw;
    mavlink_raw_pressure_struct.press_diff2 = compensated_data.air_speed;
    mavlink_raw_pressure_struct.temperature = raw_data.temp_tmp75;

    if (((n & 7) == 7) && (air_data_mail.payload == NULL)){
      air_data_mail.payload = &mavlink_raw_pressure_struct;
      chMBPost(&tolink_mb, (msg_t)&air_data_mail, TIME_IMMEDIATE);
    }

    n++;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * see datasheet on page 13 how to initialize ADC
 */
void init_max1236(void){

#if CH_DBG_ENABLE_ASSERTS
  // clear bufers. Just to be safe.
  uint8_t i = 0;
  for (i = 0; i < MAX1236_TX_DEPTH; i++){txbuf[i] = 0x55;}
  for (i = 0; i < MAX1236_RX_DEPTH; i++){rxbuf[i] = 0x55;}
#endif

  txbuf[0] = 0b11110011;
  txbuf[1] = 0b00000101;

  while(i2c_transmit(max1236addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollMax1236ThreadWA,
          sizeof(PollMax1236ThreadWA),
          I2C_THREADS_PRIO,
          PollMax1236Thread,
          NULL);
}

