#ifndef PARAM_H_
#define PARAM_H_

#include "cli_cmd.h"

/* периодичность посылки данных в милисекундах */
#define SEND_MIN                  20
#define SEND_MAX                  5000
#define SEND_OFF                  SEND_MIN - 1

#define ONBOARD_PARAM_NAME_LENGTH 15
#define PARAM_ID_SIZE             16

/**
 *
 */
typedef struct GlobalParam_t GlobalParam_t;

/**
 * Combined data type for use in mavlink
 */
typedef union{float f32; int32_t i32; uint32_t u32;} floatint;

/**
 * Global parameter
 */
struct GlobalParam_t{
  char      *name;
  floatint  min;
  floatint  *valuep;
  floatint  max;
  uint8_t   param_type;
  char      *help;
};

/**
 *
 */
typedef enum {
  PARAM_OK = 1,
  PARAM_NOT_CHANGED = 2,  /* parameter allready contain this value */
  PARAM_CLAMPED = 3,      /* value claped to limits */
  PARAM_INCONSISTENT = 4, /* NaN or INF */
  PARAM_WRONG_TYPE = 5,   /* unsuppoerted parameter type */
} param_status_t;


int32_t key_index_search(const char* key);
void *ValueSearch(const char *str);
param_status_t set_global_param(void *value, const GlobalParam_t *param);
void ParametersInit(void);


#endif /* PARAM_H_ */
