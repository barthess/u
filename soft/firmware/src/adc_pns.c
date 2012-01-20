#include "ch.h"
#include "hal.h"

#include "adc_pns.h"
#include "message.h"
#include "main.h"
#include "i2c.h"
#include "imu.h"
#include "dsp.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;

extern RawData raw_data;
extern LogItem log_item;

extern volatile uint16_t cal_CurrentCoeff;
extern volatile uint8_t  cal_CurrentOffset;
extern volatile uint16_t cal_VoltageCoeff;

extern BinarySemaphore gyroadc_sem;
extern EventSource es_adc;
extern eventmask_t em_adcgyroready;
extern eventmask_t em_adcpowerready;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DEFAULT_CURRENT_COEFF  1912   // ����������� ��������� �� �������� ������ � ������ ��� ������� -- 37, ��� ������� -- 1912
#define DEFAULT_CURRENT_OFFSET 16   // �������� ���� ������� ���� � �������� ���
#define DEFAULT_VOLTAGE_COEFF  1022 // ����������� ��������� �� �������� ������ � ����������

/*
 ******************************************************************************
 * FUNCTIONS PROTOTIPES
 ******************************************************************************
 */
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n);
void adccb_gyrozeroing(ADCDriver *adcp, adcsample_t *buffer, size_t n);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static ADCConfig adccfg; // ��� STM32 -- ������ ���� ��������

/* ������� ������������ ���:
 *
 * SYSCLK/STM32_HPRE_DIV1/STM32_PPRE2_DIV2/STM32_ADCPRE_DIV8 = 72/1/2/4 = 9MHz
 *
 * The total conversion time is calculated as follows:
 * Tconv = Sampling time + 12.5 cycles
 * Example:
 * With an ADCCLK = 9 MHz and a sampling time of 239.5 cycles:
 * Tconv = 239.5 + 12.5 = 252 cycles
 * ��� ������� � 9��� ���������� ����� 28 us.
 *
 * 1. ���������� ��� ����� ������ �� ������� - ��� ��� ���������� ������ �����.
 *
 * 2. ������� ����� ����������� RC-������� ���������� = 140 ��.
 * �� ������� ������������ ����� ������������� ������ ���� ��� �������
 * � 2 ���� ����. � �������� �������� ���� ������� �� 8-10 ����� �� ������.
 * ������ - 140 * 8 = 1000 ��.
*/
static ADCConversionGroup adccg = {
    TRUE,                     // ����� ���������?
    (uint16_t)(ADC_CH_NUM),   // ���������� �������
    adccb_gyrozeroing,        // ���������� ���� ��������� ���� ����������
    NULL,                     // error cb
    0,                        // CR1 register
    ADC_CR2_TSVREFE,          // CR2 register. Vref on
    (0x1000000 - 1),          // SMPR1 (��� �� ������������ �����)
    (0x40000000 - 1),         // SMPR2 (��� �� ������������ �����)
    (ADC_CH_NUM - 1) << 20,   // SQR1
    0,                        // SQR2.
    // z, y, x, current, voltage, joy
    ((10 << 25) | (11 << 20) | (12 << 15) | (13 << 10) | (14 << 5) | 15), // SQR3
};

// ���������� ���.
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_NUM];

// ������� ��� ������� ������ �������
static uint32_t adccnt = (0UL - 1UL);

// ������ ��������� �������� ��� �������� ���������
static uint32_t gxv[4] = {0,0,0,0};
static uint32_t gyv[4] = {0,0,0,0};
static uint32_t gzv[4] = {0,0,0,0};

// ������� ��� �������� �����
static uint32_t zero_cnt = GYRO_AVG_SAMPLES_CNT;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* ������� ��� �������� �����.
 * ����������� ����� ������ ����������� � ���� �� ��� ���, ���� �� ���������
 * ����. ����� ����� ����������� ������ ��������� �� ������ ������� � ����
 * �� ������ ������� �� ��������. */
void adccb_gyrozeroing(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void)adcp;
  (void)n;
  adccnt++;
  if ((adccnt & 0x7) == 0x7){// ������ 8-� ����������
    if (zero_cnt > 0){
      raw_data.gyro_xAvg += buffer[GYRO_ADC_X_OFFSET];
      raw_data.gyro_yAvg += buffer[GYRO_ADC_Y_OFFSET];
      raw_data.gyro_zAvg += buffer[GYRO_ADC_Z_OFFSET];
    }
    else{
      GlobalFlags &= ~GYRO_CAL;
      /* �� �������� ������� ������� ��� ���� */
      adccnt = 0UL - 1UL;
      /* ������ �� ����� �������� ������������� �� �������� ������� */
      adccg.end_cb = adccb;
      return;
    }
    zero_cnt--;
  }
}

/* ������������� ���������� ������� �������������� ��������� 3/8.
 * �������� ������������� � ����� ������������������.
 * ������� �� ������ ��������� ��������� � ����������� ����������:
 * 3 - ���������� ����������� ��������������
 * 8 - �������� �� ���������� ������� ����� ������ � ������ GYRO_AVG_SAMPLES_CNT */
#define s38(a, b, c, d)      ((a) + 3*((b) + (c)) + (d))

/* ������� �������� ��������� ���������� �� �������.
 * ��������� ������������ ���������� ��� �� ���������� ���� ��������������
 * � �� ���������� �������� ��������������.
 * � ��� 6 ������� ��������������. �� ������ ����� �������� 28���, �����
 * 168���. ���� ����� ������ 8-� ��������������:
 * 1344���. ������ ����� ���� ���������� 3 ����� �����,
 * 4-� ����� -- ��� ������, ��� ������ ����� ������ � ��������� ������
 * 4032��� ��� ��������� ���������� ����. */
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void)adcp;
  (void)n;
  (void)buffer;
  uint32_t i = 0;
  adccnt++;
  if ((adccnt & 0xF) == 0xF){// ������ 16-� ����������
    i = (adccnt >> 4) & 3;
    gxv[i] = samples_buf[GYRO_ADC_X_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    gyv[i] = samples_buf[GYRO_ADC_Y_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    gzv[i] = samples_buf[GYRO_ADC_Z_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    if (i == 3){
      raw_data.gyro_x_delta = 3 * (s38(gxv[0],gxv[1],gxv[2],gxv[3]) - raw_data.gyro_xAvg);
      raw_data.gyro_y_delta = 3 * (s38(gyv[0],gyv[1],gyv[2],gyv[3]) - raw_data.gyro_yAvg);
      raw_data.gyro_z_delta = 3 * (s38(gzv[0],gzv[1],gzv[2],gzv[3]) - raw_data.gyro_zAvg);
      gxv[0] = gxv[3];
      gyv[0] = gyv[3];
      gzv[0] = gzv[3];

      chSysLockFromIsr();
      // ����������� ������ ��������� ������������ ������
      chBSemSignalI(&gyroadc_sem);
      chSysUnlockFromIsr();
    }
  }
}
#undef s38


/* ����� ��� ������� ������ ��� �� ������� */
static WORKING_AREA(PollADCThreadWA, 256);
__attribute__((noreturn))
static msg_t PollADCThread(void *arg){
  chRegSetThreadName("PollADC");
  (void)arg;
  systime_t time = chTimeNow();       // T0

  while(TRUE){
    time += MS2ST(NORMAL_ADC_PERIOD); // Next deadline
    chThdSleepUntil(time);

    raw_data.main_current = samples_buf[CURRENT_ADC_OFFSET];
    raw_data.main_voltage = samples_buf[VOLTAGE_ADC_OFFSET];

    log_item.main_current = (uint16_t)((__USAT(raw_data.main_current - cal_CurrentOffset, 15) * 1000) / cal_CurrentCoeff);
    uint16_t voltage = (raw_data.main_voltage * 100) / cal_VoltageCoeff;
    log_item.main_voltage = (uint8_t)__USAT(voltage, 8);
    //chEvtBroadcastFlags(&es_adc, em_adcpowerready);
  }
}


inline void ADCInit_pns(void){
  /* ��������� ����� */
  palSetPadMode(IOPORT3, 0, PAL_MODE_INPUT_ANALOG); // EXT2-7 gyro_Z ADC10
  palSetPadMode(IOPORT3, 1, PAL_MODE_INPUT_ANALOG); // EXT2-8 gyro_Y ADC11
  palSetPadMode(IOPORT3, 2, PAL_MODE_INPUT_ANALOG); // EXT2-9 gyro_X ADC12
  palSetPadMode(IOPORT3, 3, PAL_MODE_INPUT_ANALOG); // ��� ADC13
  palSetPadMode(IOPORT3, 4, PAL_MODE_INPUT_ANALOG); // ��������� ADC14
  palSetPadMode(IOPORT3, 5, PAL_MODE_INPUT_ANALOG); // �������� ADC15
                                                    // ���������� ��� ADC17

  GlobalFlags |= GYRO_CAL;

  adcStart(&ADCD1, &adccfg);
  chThdSleepMilliseconds(500); /* ����� �� ������� ���������� � ��� */
  adcStartConversion(&ADCD1, &adccg, samples_buf, ADC_BUF_DEPTH);

  //"TODO: Read settings from EEPROM here"
  cal_CurrentCoeff  = DEFAULT_CURRENT_COEFF;
  cal_CurrentOffset = DEFAULT_CURRENT_OFFSET;
  cal_VoltageCoeff  = DEFAULT_VOLTAGE_COEFF;

  chThdCreateStatic(PollADCThreadWA,
          sizeof(PollADCThreadWA),
          NORMALPRIO,
          PollADCThread,
          NULL);
}


