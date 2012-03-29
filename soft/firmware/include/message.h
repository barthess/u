#ifndef MESSAGE_H_
#define MESSAGE_H_


/*
 * ������������ ������.
 */
typedef struct CompensatedData CompensatedData;
struct CompensatedData{
  /* ���� �������� � ������� ��������� ����������. ������������� ����� -- ������ ������� == 2^32 */
  int32_t   xgyro_I;
  int32_t   ygyro_I;
  int32_t   zgyro_I;
  /* ���� �������� � ������� ��������� ����������. ������� */
  float     xgyro_f;
  float     ygyro_f;
  float     zgyro_f;
  /**/
  uint16_t  air_speed;      /* ��������� ��������. ������������� �����. (mm/s)*/
  int8_t    temp_onboard;   /* ����������� c tmp75. ����� �������. */
};


/*
 * ����� ������ ����� � ��������.
 */
typedef struct RawData RawData;
struct RawData{
  // ���� ��������, ����������� ����� ��������
  int32_t xgyro_delta;
  int32_t ygyro_delta;
  int32_t zgyro_delta;
  /* �������� �����, ����������� �� ����� ��������.*/
  int32_t xgyro_zero;
  int32_t ygyro_zero;
  int32_t zgyro_zero;
  // ������ � ���������
  int16_t xgyro;
  int16_t ygyro;
  int16_t zgyro;
  int16_t gyro_temp;
  // �������� � �������� ���
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  //�����������
  //  int16_t magnetic_x;
  //  int16_t magnetic_y;
  //  int16_t magnetic_z;
  // ������������
  //  int16_t acceleration_x;
  //  int16_t acceleration_y;
  //  int16_t acceleration_z;
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
 * ��������� ��� ������ � �������� ���������. ������ ���� ������ �������, �����
 * ������ ������� � ������ �������� 128 ����.
 */
typedef struct LogItem LogItem;
struct LogItem{
  int32_t  gps_latitude;      /* ������, ������� */
  int32_t  gps_longitude;

  uint32_t gps_time;          /* ����� �� GPS. � ������� 115436 -- 11 �����, 54 ������, 36 ������ */

  uint32_t rtc_sec;           /* ����� �� ���������� �����. ������� � ������ ����� */
  uint16_t rtc_msec;          /* ������� ����� */

  uint16_t aileron;           /* ��������� ������������� � �������� (������ �� ��������� ��������) */
  uint16_t elevator;
  uint16_t throttle;
  uint16_t rudder;

  uint16_t altitude_sonar;    /* ������ �� ������. ����� (cm)*/
  uint16_t main_current;      /* ���. ���������� */

  uint16_t gyro_xI;           /* ���� ��������. ������������� ����� -- ������ ������� == 2^16*/
  uint16_t gyro_yI;
  uint16_t gyro_zI;

  int16_t acceleration_x;     /* ��������� (mg)*/
  int16_t acceleration_y;
  int16_t acceleration_z;

  int16_t imu_x;              /* ������������ �������� ���������� ������� �� ��� * 10000 */
  int16_t imu_y;
  int16_t imu_z;

  int16_t baro_altitude;      /* ������ �� ��������� bmp085. ����� (dm)*/
  int16_t gps_altitude;       /* ������ �� GPS. ����� (m)*/

  uint8_t main_voltage;       /* ���������� �������� ���� -- ������� ���� ������ */
  uint8_t air_speed;          /* ��������� ��������. ������������� ����� 5:3. (m/s)*/
  uint8_t engine_rpm;         /* ������� �������� ��������� ��������� (Hz) */

  uint8_t gps_speed;          /* �������� �� GPS. ����� (m/s)*/
  uint8_t gps_course;         /* ������ ������ -- 256 �������� ������. */
  uint8_t cpu_load;           /* �������� CPU (%) */

  int8_t  temp_onboard;       /* ����������� c tmp75. ����� �������. */
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

