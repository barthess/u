#ifndef MESSAGE_H_
#define MESSAGE_H_


/*
 * ������������ ������.
 */
typedef struct CompensatedData CompensatedData;
struct CompensatedData{
  /* ����������� ���� �������� � ������� ��������� ���������� (��� �������). ������� */
  float     xgyro_angle;
  float     ygyro_angle;
  float     zgyro_angle;
  /* ������������ ������� �������� � ���/� */
  float     xgyro;
  float     ygyro;
  float     zgyro;
  /* ������������ ������� �������� � uRad/s */
  int32_t   xgyroi;
  int32_t   ygyroi;
  int32_t   zgyroi;
  /* ��������� �� ���� � mG */
  int16_t   xacc;
  int16_t   yacc;
  int16_t   zacc;

  /**/
  int16_t   baro_altitude;  /* ������ �� ��������� bmp085. ����� (dm)*/
  uint16_t  air_speed;      /* ��������� ��������. ������������� �����. (mm/s)*/
  int8_t    temp_onboard;   /* ����������� c tmp75. ����� �������. */
  // ���������� � ��� �������� ����
  uint16_t main_voltage;      // mV
  uint32_t main_current;      // mA
  uint16_t secondary_voltage; // mV ������� � ���������� ��������� ������� ��� ���� � ���������
};


/*
 * ����� ������ ����� � ��������.
 */
typedef struct RawData RawData;
struct RawData{
  /* �������� ����� ���������, ����������� �� ����� ��������.*/
  int32_t xgyro_zero;
  int32_t ygyro_zero;
  int32_t zgyro_zero;
  /* ������ � ���������. ��� ��� �� ������� ��������� � ����� ����� ����������,
   * ��� �������� ��������� �� ��������� ������� � ��� �������, � �������
   * ������������ */
  int16_t xgyro;
  int16_t ygyro;
  int16_t zgyro;
  int16_t gyro_temp;
  // �������� � �������� ���
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  /* ������ � ������������. ��� ��� �� ������� ��������� � ����� ����� ����������,
   * ��� �������� ��������� �� ��������� ������� � ��� �������, � �������
   * ������������ */
  int16_t xmag;
  int16_t ymag;
  int16_t zmag;
  /* ������ � �������������. ��� ��� �� ������� ��������� � ����� ����� ����������,
   * ��� �������� ��������� �� ��������� ������� � ��� �������, � �������
   * ������������ */
  int16_t xacc;
  int16_t yacc;
  int16_t zacc;
  // ��������� ������������� (������ �� ��������� ��������)
  uint16_t servo1;
  uint16_t servo2;
  uint16_t servo3;
  uint16_t servo4;
  uint16_t servo5;
  uint16_t servo6;
  uint16_t servo7;
  uint16_t servo8;
  // ���������� � ��� �������� ����
  uint16_t main_voltage;
  uint16_t main_current;
  uint16_t secondary_voltage; // ������� � ���������� ��������� ������� ��� ���� � ���������
  // ����������� c tmp75 (����� ���� �������)
  int16_t temp_tmp75;
  // ����������� � ��������� bmp085 (������� ���� �������)
  int16_t temp_bmp085;
  // �������� c bmp085 (��)
  uint32_t pressure_static;
  // GPS
  int32_t  gps_latitude;
  int32_t  gps_longitude;
  int32_t  gps_altitude;
  int32_t  gps_speed_knots;
  int32_t  gps_course;
  uint32_t gps_time;
  uint8_t  gps_satellites;

  uint32_t rtc_sec;           /* ����� �� ���������� �����. ������� � ������ ����� */
  uint16_t rtc_msec;          /* ������� ����� */

  uint16_t engine_rpm;        /* �������� (rpm)*/
};


/**
 * ��������� ���������� ������ ��������� ���� "������" ��� ������ �������.
 */
typedef struct Mail Mail;
struct Mail{
  /**
   * @brief ��������� �� ������� �����.
   * @details ����� ����, ��� ������ ������� �������
   * ��������, ��������� ��������������� � NULL. ��� ����� �������� ���
   * ������ �������.
   */
  void *payload;
  /**
   * ���� ����������� �� ���������� ����������, ����� ��������� ��� ������.
   */
  msg_t invoice;
  /**
   * ��������� �� �������� ����, � ������� ���� �������� �������������
   * ��������� ����������. ����� �������������� ��� ������������� �������������
   * ������. �������� ��������� ������ �� �������� ������.
   * ����� ���� NULL.
   */
  Mailbox *confirmbox;
};

#endif /* MESSAGE_H_ */

