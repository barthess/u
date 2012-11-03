#ifndef PARAM_H_
#define PARAM_H_

#include "cli_cmd.h"

/* периодичность посылки данных в милисекундах */
#define SEND_MIN                  20
#define SEND_MAX                  5000
#define SEND_OFF                  0

#define ONBOARD_PARAM_NAME_LENGTH 15
#define PARAM_ID_SIZE             16

/**
 *
 */
typedef enum {
  PARAM_OK = 1,
  PARAM_NOT_CHANGED = 2,  /* parameter allready contain this value */
  PARAM_CLAMPED = 3,      /* value claped to limits */
  PARAM_INCONSISTENT = 4, /* NaN or INF or something else bad value */
  PARAM_WRONG_TYPE = 5,   /* unsuppoerted parameter type */
} param_status_t;

/**
 *
 */
typedef struct GlobalParam_t GlobalParam_t;

/**
 * Combined data type for use in mavlink
 */
typedef union{float f32; int32_t i32; uint32_t u32;} floatint;

/**
 * Fucnction checking parameter's cosherness.
 * @return    Pointer to created thread. Must be NULL if no thread crated.
 */
typedef param_status_t (*checkfunction_t)(void *value, const GlobalParam_t *param);

/**
 * Global parameter
 */
struct GlobalParam_t{
  /**
   * Name of parameter
   */
  const char            *name;
  const floatint        min;        /* allowed min */
  const floatint        def;        /* default */
  const floatint        max;        /* allowed max*/
  /**
   * Pointer to value stored in RAM
   */
  floatint              *valuep;
  /**
   * Checker function. Set to NULL for usage of default "put in range" function.
   */
  const checkfunction_t func;
  /**
   * Parameter type like defined in mavlink headers.
   */
  const uint8_t         param_type;
  /**
   * Help string. Set to NULL if unused.
   */
  const char            *help;
};

int32_t key_index_search(const char* key);
void *ValueSearch(const char *str);
param_status_t set_global_param(void *value, const GlobalParam_t *param);
void ParametersInit(void);


#endif /* PARAM_H_ */
