#include "ch.h"
#include "hal.h"

#define ARM_MATH_CM4

#include "arm_math.h"

#include "message.h"
#include "dsp.h"
#include "main.h"
#include "i2c_pns.h"

#include "max1236.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define max1236addr 0b0110100

/**����� ������ Vcc/1024 ����� �� ��
 * ����������� ����������� ��� Vcc/4096
 * �����: ��� ��������� ������ � �� ���� ���������� ��������� �������� �� 4 */
#define SONAR_COEF 4

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;

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
/** ����� max1236
 * ����� ��������� ���������� ������ ������ �� ���� ������, �� 2 ����� �� �����
 * ����� �������� ������� ��� �������� ����� �������� �� 8.3uS, ����� ����
 * ������ ���������. ��� ������ ������ ������� ������ ���������� ���� - ����
 * � ���� STOP.
 * ��� ������� 100��� �� ����������� 4 �������� ����� ��������:
 * 10 * (4 * 2 * 8) + 8.3 * 4 = 673.2 uS
 *
 *---------------- ��� ��������: --------------------------------------
 * �������� ����� � �������� ���. ������� �� �����������
 * if (t_tmp75 > 26):
 *     pressure_offset = 1530 + 11.5 * t_tmp75
 * else:
 *     pressure_offset = 1530 + 11.0 * t_tmp75
 * k = 11.08 # ����������� �������� �������������
 * r = 5.0/4096 # ����� �� ������� ���
 * s = 0.00045 # ����� �� �������
 * dyn = (((raw_pressure - pressure_offset) * r) / k) / s # � ��������
 * ����� ��������� ��������� ��������:
 * (raw_pressure - pressure_offset) * 0,2448 (��)
 * ���
 * (raw_pressure - pressure_offset) * 245 (���)
 *
 *
 * ����� ������ �� ��������:
 * ��� ��������� ����������� �������� ���� 0.201 V, ���������� �������� 0.183 V,
 * �� ������ ��������� 0.167 V
 */
static WORKING_AREA(PollMax1236ThreadWA, 256);
static msg_t PollMax1236Thread(void *arg) {
  chRegSetThreadName("PollMax1236");
  (void)arg;

  int32_t pres_dyn;         // ������������ ��������
  uint32_t pres_dyn_offset; // �������� �����, ��������� �� �����������

  while (TRUE) {
    chThdSleepMilliseconds(20);

    if (i2c_receive(max1236addr, rxbuf, MAX1236_RX_DEPTH) == RDY_OK){
       /* Process the results */
      int16_t max0 = ((rxbuf[0] & 0xF) << 8) + rxbuf[1];
      int16_t max1 = ((rxbuf[2] & 0xF) << 8) + rxbuf[3];

      /* ��������� �������� */
      // TODO: �������� ���������������� if'�� �����-������ ������������ ��������
      if(raw_data.temp_tmp75 > 2600)
        pres_dyn_offset = 1540 + (115 * raw_data.temp_tmp75) / 1000;
      else
        pres_dyn_offset = 1540 + (110 * raw_data.temp_tmp75) / 1000;

      pres_dyn = (max0 - pres_dyn_offset) * 245;
      pres_dyn = __USAT(pres_dyn, 31);
      raw_data.pressure_dynamic = (uint16_t)(pres_dyn / 1000); // (��)

      /* ��������, ��� ������� �������� �� ��������� 4096, ����� ��������
       * �� 3 ������� ����� ��������� ������� �������� � "����������" �������
       * � ������� �� 3^2 ������� ����� ���������� ����� ��������� ������� � "��������"
       * ��� ���������� ����� ��������� ���������:
       * (arm_sqrt_q15((� * 2^18)/32768)) / 2^9      */
      q15_t in = (2L * pres_dyn / 1225L) << 3;
      q15_t out = 0;
      arm_sqrt_q15(in, &out);
      //log_item.air_speed = (uint8_t)__USAT((out >> 9), 8); // ��� ��������� �����
      log_item.air_speed = (uint8_t)__USAT((out >> 6), 8); // ��� ��������� ������������� ����� 5:3

      /* ������ �� ������ */
      raw_data.altitude_sonar = max1;
      log_item.altitude_sonar = raw_data.altitude_sonar; // save to log
    }
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
          NORMALPRIO,
          PollMax1236Thread,
          NULL);
}

