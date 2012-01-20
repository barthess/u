#include "autopilot.h"
#include "servo.h"
#include "message.h"
#include "proto_pns.h"
#include "eeprom.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox autopilot_mb;
extern RoutePoint route_point;
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
/**
 * ������� ��� ��������������� ����������� �������� � ������ ������ �����
 * TODO: ��������� ��������� ������� ����� �����
 */
void EmergencyLanding(void){
  Servo_NeutralSet(); /* �� � ����������� ��������� */
}


/**
 * ���������� ���� ��� ������� ����������.
 * ������ ���������� ������� API �� servo.c ��� ������ ��������.
 */
void ApplyManualDriving(uint8_t *buf){
  set_aileron (buf[0]);
  set_elevator(buf[1]);
  set_throttle(buf[2]);
  set_rudder  (buf[3]);
}


/**
 * ��������� ����������
 */
typedef enum{
  MANUAL_DRV = 1,
  AUTO_DRV = 2,
  EMERGENCY_LANDING = 3,
} autopilot_state;


/**
 *
 */
static WORKING_AREA(AutopilotThreadWA, 256);
Thread *autopilot_tp = NULL;
__attribute__((noreturn))
static msg_t AutopilotThread(void* arg){
  chRegSetThreadName("Autopilot");
  (void)arg;

  #define AP_MANUAL_DRV_TIMEOUT 2000  /* �� ��������� ����� ����������� ������� */
  autopilot_state state = MANUAL_DRV; /* ��������� ����� ������ ����������� */
  msg_t msg = 0;                      /* ��������� ���������� ��� �������� ����������� ������ �� ��������� ����� */
  msg_t mb_status;                    /* ������, ������������ ����� ������ ��������� �����*/

  while(TRUE){

    // TODO: ��������� ���� ���������� �����. ����� ���������� ��������� � ��� ��������� �����
    //      eeprom_write(EEPROM_ROUTE_OFFSET, EEPROM_ROUTEPOINT_SIZE, rpbuf);
    //      eeprom_read(EEPROM_ROUTE_OFFSET, EEPROM_ROUTE_SIZE, rpbuf);
    //      unpack_routepoint(&route_point, rpbuf);


    switch(state){
    case MANUAL_DRV:
      mb_status = chMBFetch(&autopilot_mb, &msg, AP_MANUAL_DRV_TIMEOUT);
      if (mb_status == RDY_TIMEOUT)
        //state = EMERGENCY_LANDING;
        EmergencyLanding();
      else
        ApplyManualDriving((uint8_t*)msg);
      msg = 0;
      break;

    case AUTO_DRV:
      chThdSleepMilliseconds(500);
      break;

    case EMERGENCY_LANDING:
      chThdSleepMilliseconds(10);
      EmergencyLanding();
      break;

    default:
      break;
    }
  }
  #undef AP_MANUAL_DRV_TIMEOUT
}





inline void AutopilotInit(void){

  autopilot_tp = chThdCreateStatic(AutopilotThreadWA,
      sizeof(AutopilotThreadWA),
      NORMALPRIO,
      AutopilotThread,
      NULL);
}
