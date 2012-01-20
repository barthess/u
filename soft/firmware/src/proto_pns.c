
#include "proto_pns.h"
#include "message.h"
#include "servo.h"
#include "autopilot.h"
#include "eeprom.h"
#include "rtc.h"
#include "bkp.h"
#include "dsp.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RTCTime timespec;

extern Mailbox autopilot_mb;
extern Mailbox eeprommanager_mb;
extern Mailbox tolink_mb;

extern uint8_t servo_settings_eeprom_buf[SERVO_SETTINGS_SIZE];
extern uint8_t servo_settings_xbee_buf[SERVO_SETTINGS_SIZE];

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static EepromReq eeprom_writeroute_req = {NULL, NULL, 0, 0};
static XbeeMsg servosettings_xbeemsg = {NULL, NULL, 0, SETTINGS_SERVO};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * ������� ���������� ������� ���� � ��������� ����� ��������
 * @param rp -- ��������� �� ���������
 * @param buf -- ��������� �� ����� � �������
 * @return ������ ����������
 */
uint8_t unpack_routepoint(RoutePoint *rp, uint8_t *buf){
  enum{
    SUCCESS = 0,
    VALUEERROR = 1,
    CRCERROR = 2,
  };

  // TODO: �������� �������� �� ��������
  rp->latitude  = pack8to32(&buf[0]);
  rp->longitude = pack8to32(&buf[4]);
  rp->altitude  = pack8to16(&buf[8]);
  rp->speed     = buf[10];
  rp->number    = 0;
  rp->crc       = 0;

  return SUCCESS;
}



/**
 * ���������� ����� ��������.
 * ���������� ��������� ����� 0;0;0;0 ����� ������� ��� ������� ���� ����� �����.
 * ��� �����, ������� �� ���������� � ���������� ��� ��� ����� � EEPROM ����� ����� ���������������.
 */
void WriteRoutePoint(uint8_t *buf){
  const uint8_t zerochecklen = (4 + 4 + 2 + 1); // ����� �������� ������ � ������
  uint8_t i = 0;
  uint16_t sum = 0;

  sum = 0;
  for (i=0; i<zerochecklen; i++)
    sum += buf[i];

  if (sum == 0){
    BKP_DR_ROUTEPOINTNUM = 0;
    return;
  }
  if (BKP_DR_ROUTEPOINTNUM >= EEPROM_ROUTE_POINT_MAX_NR){
    return;
  }
  else{
    // ��������, ������ ������� ��� ���
    chDbgCheck((eeprom_writeroute_req.bufp == NULL), "Data was NOT be fetched from mailbox");
    eeprom_writeroute_req.addr = EEPROM_ROUTE_OFFSET + BKP_DR_ROUTEPOINTNUM * EEPROM_ROUTEPOINT_SIZE;
    eeprom_writeroute_req.len  = EEPROM_ROUTEPOINT_SIZE;
    eeprom_writeroute_req.bufp  = buf;
    chMBPost(&eeprommanager_mb, (msg_t)&eeprom_writeroute_req, TIME_IMMEDIATE);
    BKP_DR_ROUTEPOINTNUM += 1;
  }
}



/**
 * ���������� ��������� �������� ���� � eeprom
 */
void Servo_SettingsEepromSave(uint8_t *buf){
  eeprom_write(EEPROM_SERVO_OFFSET, (EEPROM_SERVO_SIZE + EEPROM_SERVO_CNT), buf);
}



/**
 * ����������� ����� ��������.
 */
void ReadRoutePoint(void){
  ;
}

/**
 * ��������������� �������
 */
inline void proto_settings_servo(packet_direction dir, uint8_t *payload){
  uint8_t status = 0;

  if(dir == WRITE){
    Servo_SettingsApply(payload, TRUE);
  }
  else{
    if (servosettings_xbeemsg.bufp == NULL){
      Servo_ReadFromEeprom(servo_settings_eeprom_buf);
      servosettings_xbeemsg.bufp = servo_settings_eeprom_buf;
      servosettings_xbeemsg.len  = sizeof(servo_settings_eeprom_buf);
      status = chMBPost(&tolink_mb, (msg_t)&servosettings_xbeemsg, TIME_IMMEDIATE);
      chDbgCheck((status == 0), "can not insert");
    }
  }
}

/*
 * ����� ��� �������� �������� � ����������� �������.
 * ������������ ����� ������ ������ � �������� ����������� �����.
 * �������� � ��������� ��������� �� ����� � �������, ���������� �� ���� ID
 */
uint8_t ProtoPnsParser(uint8_t *buf) {
  uint8_t id = 0, dir = 0;
  msg_t tmp; /* ��������� ���������� ��� �������� ������ ������ */
  msg_t status;
  uint8_t *payload = NULL; // ��������� �� ������ (��� ��������)

  // ��, ���������, �� ��� ������
  id = buf[PROTO_ID_OFFSET];
  // ������ ������, ��� �������������
  dir = buf[PROTO_DIRECTION_OFFSET];
  payload = &(buf[PROTO_MSG_OFFSET]);

  switch(id){
    case MANUALDRIVING:
    if(dir == WRITE){ /* ����� � �������� ���� ��������� �� ����� */
      tmp = (msg_t)payload;
      status = chMBPost(&autopilot_mb, tmp, TIME_IMMEDIATE);
    }
    break;

    case TEST:
      if(dir == WRITE){;}
      else{;}
      break;

    case TELEMETRY:
      if(dir == WRITE){;}
      else{;}
      break;

    case RAWDATA:
      if(dir == WRITE){;}
      else{;}
      break;

    case ROUTEPOINT:
      if(dir == WRITE) // ��������� ����� � ������
        WriteRoutePoint(payload);
      else{;} // TODO:���������� ����� �� ������
      break;

    case CONTROL:
      if(dir == WRITE){;}
      else{;}
      break;

    case SETTINGS_SERVO:
      proto_settings_servo(dir, payload);
      break;

    case DATE:
      if(dir == WRITE){
        uint32_t time = 0;
        time += (*payload++) << 24;
        time += (*payload++) << 16;
        time += (*payload++) << 8;
        time += (*payload++);

        timespec.tv_sec = time;
        timespec.tv_msec = 0;
        rtcSetTime(&RTCD1, &timespec);
      }
      else{;}
      break;

    default:
      // ���� ������ ����, ������ ������ ����� � �������� ID ��� ��� ����� ����� ���������
      // TODO: ���������� �����
      return 1;
    break;
  }
  return 0;
}



