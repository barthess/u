#ifndef ACS_H_
#define ACS_H_

#include <stdint.h>

typedef enum {
  ACS_STATUS_OK = 0,    // ok
  ACS_STATUS_ERROR = 1, // error
}acs_status_t;

typedef struct {
  uint32_t time_fix;  // ms
  float gamma;        //roll (rad)
  float theta;        //pitch (rad)
  float psi;          //heading (rad)
  float psi_mag;      // heading by magnetometer (rad)
  float lat;          // lattitude from GNSS (WGS-84, rad)
  float lon;          // longitude from GNSS (WGS-84, rad)
  float hmsl;         // altitude from GNSS (WGS-84, m)

  float xn;           // X coordinate, North (m)
  float ye;           // Y coordinate, East (m)
  float hup;          // H coordinate, Up (m)

  float vn;           // speed component, North (m/s)
  float ve;           // speed component, East (m/s)
  float vup;          // speed component, East (m/s)

  float un;           //wind component, North (m/s)
  float ue;           //wind component, East (m/s)
  float uup;          //wind component, Up (m/s)
  uint8_t cor_type;   // 1 - correction available
}acs_input_t;

typedef struct {
  float a0;
  float a1;
  float a2;
}acs_output_t;

typedef struct {
  float c0;
  float c1;
  float c2;
}acs_config_t;


#ifdef __cplusplus
extern "C" {
#endif
  acs_status_t acsInit(const acs_config_t *cfg);
  acs_status_t acsUpdate(const acs_input_t *in, acs_output_t *out);
  acs_status_t acsReset(void);
  acs_status_t acsStop(void);
#ifdef __cplusplus
}
#endif


#endif /* ACS_H_ */
