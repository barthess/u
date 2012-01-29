#ifndef MAIN_H_
#define MAIN_H_


/******************************************************************
 * ��������� ���������� ��� �������
 ******************************************************************/
#define I2C_THREADS_PRIO   (NORMALPRIO + 5)
#define LINK_THREADS_PRIO  (NORMALPRIO - 5)


/******************************************************************
 * ���������� ������� �����
 ******************************************************************/
#define GYRO_CAL        (1UL << 0)  /* ���� ���������� � �������, ������ ���� �������� ���������� */
#define ACCEL_CAL       (1UL << 1)  /* ���� ���������� � �������, ������ ���� �������� �������������� */
#define MAG_CAL         (1UL << 2)  /* ���� ���������� � �������, ������ ���� �������� ������������ */
#define EEPROM_FAILED   (1UL << 3)  /* ������� �������� ���� � EEPROM */
#define POSTAGE_FAILED  (1UL << 4)  /* ���� � ������� �������� ��������� */
#define I2C_RESTARTED   (1UL << 5)  /* I2C ���� ���� ������������ ��-�� ������� */

#define setGlobalFlag(flag)   {chSysLock(); GlobalFlags |= (flag); chSysUnlock();}
#define clearGlobalFlag(flag) {chSysLock(); GlobalFlags &= (~(flag)); chSysUnlock();}

/******************************************************************
 * ���������� �������
 ******************************************************************/

#define SUCCESS   FALSE
#define FAILED    TRUE

#define GROUND_STATION_ID   255

/* ������������ �������� ������ ���� ������ ������������ - ������ ��� ����� ��
 * ��� �������� ��-�� ���������� �������� */
#define BAUDRATE_XBEE 115200
#define xbee_reset_assert() {palClearPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_reset_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_sleep_assert() {palClearPad(GPIOE, GPIOE_XBEE_SLEEP);}
#define xbee_sleep_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}

/* �������� ���������� ������������ */
#define ENABLE_IRQ_STORM    FALSE

#define pwr5v_power_on()  {palSetPad(GPIOA, GPIOA_5V_DOMAIN_EN);}
#define pwr5v_power_off() {palClearPad(GPIOA, GPIOA_5V_DOMAIN_EN);}


/* stop watchdog timer in debugging mode */
/*unlock PR register*/
/*set 1.6384s timeout*/
/*start watchdog*/
#define WATCHDOG_INIT {\
    DBGMCU->CR |= DBGMCU_CR_DBG_IWDG_STOP;\
    IWDG->KR = 0x5555;\
    IWDG->PR = 16;\
    IWDG->KR = 0xCCCC;}

#define WATCHDOG_RELOAD {IWDG->KR = 0xAAAA;}


#endif /* MAIN_H_ */
