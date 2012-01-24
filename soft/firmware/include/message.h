/*
 * message.h
 *
 *  Created on: 24.03.2011
 *      Author: barthess
 *
 *  ���� ��������� ������ ���������� ��������� ������
 */
#ifndef MESSAGE_H_
#define MESSAGE_H_

#define HEADER_LENGTH 2
#define LENGTH_LENGTH 1
#define CRC_LENGTH 1 // 1 ����
// ����������� ������ ������
#define FRAME_LENGTH (64 - LENGTH_LENGTH - HEADER_LENGTH - CRC_LENGTH)

// �������� ��������� ������
#define HEADER_OFFSET 0
#define LENGTH_OFFSET (HEADER_OFFSET + HEADER_LENGTH)

#define FRAME_OFFSET (LENGTH_OFFSET + LENGTH_LENGTH)

// ����� ��� �������� ������
#define UART_BUF_DEPTH (FRAME_LENGTH + CRC_LENGTH + LENGTH_LENGTH + HEADER_LENGTH)


/*
 * ���������� �������������� �������
 */
typedef enum {
  TEST           = 0, /* �������� �����, ����� ���� ��� ������ */
  MANUALDRIVING  = 1, /* ����� � ������� ������� ���������� */
  TELEMETRY      = 2, /* ���������� */
  RAWDATA        = 3, /* ��������� ������ ��� ������� */
  LOGITEM        = 4, /* ��������� ������ �� ���, ��� ������� � EEPROM */
  ROUTEPOINT     = 5, /* ����� �������� */
  CONTROL        = 6, /* ������������ ������� �� ���� */
  SETTINGS_SERVO = 7, /* ��������� ���� */
  SETTINGS_OTHER = 8, /* ��������� ��������� ����� */
  DATE           = 9, /* ��������� ������� */
} packet_id;


/**
 * ����������� ������.
 * ����������� ������ � �������, �������� � ��������.
 */
typedef enum {
  READ  = 0,
  WRITE = 1,
} packet_direction;


/*
 * ������.
 * ������ ������� ���������� � �����.
 */
typedef struct ManualDriving ManualDriving;
struct ManualDriving {
  uint8_t aileron;
  uint8_t elevator;
  uint8_t throttle;
  uint8_t rudder;

  // �������������. ���� ��� ������ ��������.
//  bool_t self_annihilation;
};



/*
 * ����. 
 * ����� ������ ����� � �������� (��� ������).
 */
typedef struct RawData RawData;
struct RawData{
  /* ���� �������� � ������� ��������� ����������. ������������� ����� -- ������ ������� == 2^32 */
  uint32_t gyro_xI;
  uint32_t gyro_yI;
  uint32_t gyro_zI;
  // ���� ��������, ����������� ����� ��������
  int32_t gyro_x_delta;
  int32_t gyro_y_delta;
  int32_t gyro_z_delta;
  /* �������� �����, ����������� �� ����� ��������.*/
  uint32_t gyro_xAvg;
  uint32_t gyro_yAvg;
  uint32_t gyro_zAvg;
  // ������ � ���������
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
  int16_t gyro_temp;
  // �������� � �������� ���
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  //�����������
  int16_t magnetic_x;
  int16_t magnetic_y;
  int16_t magnetic_z;
  // ������������
  int16_t acceleration_x;
  int16_t acceleration_y;
  int16_t acceleration_z;
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
 * ���������������. 
 * ����� ��������. ���� ����� �� ���������.  ��� ������� ����� ����������
 * �������� �� �����. ��������� ���� ���� ������ ����, �� �� ���������� �����
 * ���������������. ������������� ���������� �� ���������� � ����.
 */
typedef struct RoutePoint RoutePoint;
struct RoutePoint{
  // ������, �������, ������ (TODO: ��� ������� ��� ����� ����, ���� ��������)
  int32_t latitude; // in units of 10^(-5) degrees
  int32_t longitude;// in units of 10^(-5) degrees
  int16_t altitude; // �����

  // ��������.
  uint8_t speed; //TODO: ������������ ������� ��� �����. ��������
  // ����� �����.
  uint8_t number;
  // ����������� ����� �����
  uint8_t crc;
};


/*
 * ������. 
 * ������ ��� ������������ ������� ������ (���������\������, ��������������
 * ������ ������\�� ������� � �.�. � �.�.)
 */
typedef struct Control Control;
struct Control{
  // ������������� �� ������ ����������
  bool_t manual_driving;
  // �������������� ���������� ����������
  bool_t telemetry_auto_send;
  // �������������� ������ �������� ��� ������������ �����������������
  // ��� ���� ��������, �������� � RoutePoint ������������
  bool_t power_saving;
};

/**
 * ��������� ���������� ������ ��������� ��� ��������� xbee.
 */
typedef struct XbeeMsg XbeeMsg;
struct XbeeMsg{
  /**
   * ��������� �� �������� ����, � ������� ���� �������� �������������
   * ��������� ����������. �������� ��������� ������ �� �������� ������.
   * ����� ���� NULL
   */
  Mailbox *mailbox;
  /**
   * @brief ��������� �� ������� �����.
   * @details ����� ����, ��� ������ ������� �������
   * ��������, ��������� ��������������� � NULL. ��� ����� �������� ���
   * ������ �������.
   */
  uint8_t *bufp;
  /**
   * ������� ���� ����������
   * @details ������� ���� �������� ��������� R/W
   *          0 - write
   *          1 - read
   *          ����� ��� ��, ��� � ��� I2C
   */
  uint16_t  len;
  /**
   * ������������� ������.
   */
  packet_id id;
};



/**
 * ��������� ���������� ������ ��������� ��� ��������� ������.
 * ����� ���� ��� �������� ������, ��� � ������
 */
typedef struct EepromReq EepromReq;
struct EepromReq{
  /**
   * ��������� �� �������� ����, � ������� ���� �������� �������������
   * ��������� ����������. �������� ��������� ������ �� �������� ������.
   * ����� ���� NULL
   */
  Mailbox *mailbox;
  /**
   * @brief ��������� �� ������� �����.
   * @details ����� ����, ��� ������ ������� �������
   * ��������, ��������� ��������������� � NULL. ��� ����� �������� ���
   * ������ �������.
   */
  uint8_t *bufp;
  /**
   * ������� ���� ����������
   * @details ������� ���� �������� ��������� R/W
   *          0 - write
   *          1 - read
   *          ����� ��� ��, ��� � ��� I2C
   */
  uint16_t  len;
  /**
   * ����� � ������. �� ���� ����� ����������� ������
   */
  uint16_t addr;
};



#endif /* MESSAGE_H_ */

