/*                      WARNINGS!
 *
 * ��� ���������� ��� -fomit-frame-pointer ������� ���� .
 */

// TODO: ���������� � ������� ������������� ������������ ��� ��� � ���
// TODO: ��������/������ ����� ��������
// TODO: ���������� ������ � �������������� ������ � ���������� �������� ��� ������������� ��������
// TODO: �������� � main(), ������� ��������� ���������� ��� �������� �� ������� ����������������

#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "adc_pns.h"
#include "rtc_pns.h"
#include "link_xbee_api.h"
#include "gps.h"
#include "servo.h"
#include "proto_pns.h"
#include "message.h"
#include "autopilot.h"
#include "bkp.h"
#include "eeprom.h"
#include "exti_pns.h"
#include "storage.h"
#include "cli.h"
#include "imu.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

//RTCTime  timespec;                    /* ��� ����� ��������� �����. ��������� �������. */

uint32_t GlobalFlags = 0;             /* ����� �� ��� ������ ���������� ����� */

RawData raw_data;                     /* ��������� � ������ ������� � �������� */
LogItem log_item;                     /* ���������, ���������� ������ ��� ���� */
RoutePoint route_point;               /* ��������� ��� ����� ������� �������� ����� �� ����� */

BinarySemaphore link_thd_sem;         /* ������� ��� ������������� ������� ����� */
BinarySemaphore imu_sem;              /* ������� ��� ������������� ���������� � ��� */

BinarySemaphore mag3110_sem;
BinarySemaphore mma8451_sem;
BinarySemaphore bmp085_sem;
BinarySemaphore itg3200_sem;

Mailbox autopilot_mb;                 /* ��������� ��� ���������� */
static msg_t autopilot_mb_buf[4];

Mailbox eeprommanager_mb;             /* ��������� ��� ������� ������ */
static msg_t eepromwriter_mb_buf[8];

Mailbox tolink_mb;                    /* ��������� ��� �������� ����� ����� */
static msg_t tolink_mb_buf[8];

uint8_t servo_settings_eeprom_buf[SERVO_SETTINGS_SIZE];// ����� ��� ������, ���������� �� EEPROM
uint8_t servo_settings_xbee_buf[SERVO_SETTINGS_SIZE];  // ����� ��� ������, ��������� � �����

/** ���������� ��� �������� ������������� ������ */
volatile uint16_t cal_CurrentCoeff;   /* ����������� ��������� �� �������� ������ � ������. ��� ������� -- 37, ��� �������  -- 1912 */
volatile uint8_t  cal_CurrentOffset;  /* �������� ���� ������� ���� � �������� ��� */
volatile uint16_t cal_VoltageCoeff;   /* ����������� ��������� �� �������� ������ � ���������� */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* Red LEDs blinker thread. */
//static WORKING_AREA(waBlink, 128);
//static msg_t Blink(void *arg) {
//  chRegSetThreadName("Blink");
//  (void)arg;
//  while (TRUE) {
//    palClearPad(IOPORT3, GPIOC_LED);
//    chThdSleepMilliseconds(500);
//    palSetPad(IOPORT3, GPIOC_LED);
//    chThdSleepMilliseconds(500);
//  }
//  return 0;
//}


int main(void) {
  halInit();
  chSysInit();

  // ��������� ��������������� ����
  raw_data.gyro_xI = 0;
  raw_data.gyro_yI = 0;
  raw_data.gyro_zI = 0;

  // Creates the blinker thread.
  //chThdCreateStatic(waBlink, sizeof(waBlink), LOWPRIO, Blink, NULL);

  /* ���������� ������������� */
  chBSemInit(&link_thd_sem, TRUE);
  chBSemInit(&imu_sem,      TRUE);

  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);

  /* ������� ��������� */
  chMBInit(&autopilot_mb, autopilot_mb_buf, (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&eeprommanager_mb, eepromwriter_mb_buf, (sizeof(eepromwriter_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb, tolink_mb_buf, (sizeof(tolink_mb_buf)/sizeof(msg_t)));

  /* ��������� ������� */
  //chEvtInit(&es_adc);

  /* ������� �������� ����������� */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();
  chThdSleepMilliseconds(50);

  ExtiInit(); /* I2C ������� ���������� ��� */
  I2CInit_pns();    /* ������ ���� ��������, �.�. ����� ���� �������� ��������� �� EEPROM */
//  RtcPnsInit();
//  ServoInit();
  CliInit();
  ADCInit_pns();
//  ImuInit();
//  GPSInit();
//  LinkInitXbeeApi();
//  AutopilotInit();  /* ��������� ������ ���������� ������ ����� ��������� ����� */
  StorageInit();

  #if ENABLE_IRQ_STORM
    chThdSleepMilliseconds(5000);
    IRQStormInit();
  #endif /* ENABLE_IRQ_STORM */

  while (TRUE){
    chThdSleepMilliseconds(200);
    palTogglePad(GPIOB, GPIOB_LED_R);
  }

  return 0;
}

