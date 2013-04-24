#ifndef PARAM_REGISTRY_H_
#define PARAM_REGISTRY_H_

#include "cli_cmd.hpp"

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
typedef enum {
  PARAM_DEFAULT = 1,
  PARAM_SEND_TMO = 2,
  PARAM_SORT_MTRX = 3,
  PARAM_POLARITY = 4,
} param_check_function_t;

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
   * Checker function type.
   */
  const param_check_function_t func;
  /**
   * Parameter type like defined in mavlink headers.
   */
  const uint8_t         param_type;
  /**
   * Help string. Set to NULL if unused.
   */
  const char            *help;
};

/**
 *
 */
class ParamValidator{
public:
  param_status_t set(void *value, const GlobalParam_t *param);

private:
  param_status_t default_val(void *value, const GlobalParam_t *param);
  param_status_t uint_val(void *value, const GlobalParam_t *param);
  param_status_t int_val(void *value, const GlobalParam_t *param);
  param_status_t float_val(void *value, const GlobalParam_t *param);
  param_status_t sendtmo_val(void *value, const GlobalParam_t *param);
  param_status_t sortmtrx_val(void *value, const GlobalParam_t *param);
  param_status_t polarity_val(void *value, const GlobalParam_t *param);
};

/**
 *
 */
class ParamRegistry{
public:
  ParamRegistry(void);
  bool load(void);
  bool saveAll(void);
  bool syncParam(const char* key);
  param_status_t setParam(void *value, const GlobalParam_t *param);
  void *valueSearch(const char *key);
  int32_t paramCount(void);
  const GlobalParam_t *getParam(const char *key, int32_t n, int32_t *i);

private:
  bool load_extensive(void);
  int32_t key_index_search(const char* key);
  ParamValidator validator;
  static const GlobalParam_t *param_array;
  floatint *val;
};



void ParametersInit2(void);

#endif /* PARAM_REGISTRY_H_ */
