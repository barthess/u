#ifndef PARAM_H_
#define PARAM_H_

#include "cli_cmd.h"

/* периодичность посылки данных в милисекундах */
#define SEND_MIN                  20
#define SEND_MAX                  5000
#define SEND_OFF                  SEND_MIN - 1


#define ONBOARD_PARAM_NAME_LENGTH 15
#define PARAM_ID_SIZE             16


typedef struct GlobalParam_t GlobalParam_t;

/**
 * Combined data type for use in mavlink
 */
typedef union{float f32; int32_t i32; uint32_t u32;} floatint;

/**
 * Global parameter
 */
struct GlobalParam_t
{
  const char *name;
  const floatint min;
  floatint value;
  const floatint max;
  const uint8_t param_type;
};


int32_t _key_index_search(const char* key);
void *ValueSearch(const char *str);
bool_t set_global_param(void *value,  GlobalParam_t *param);
void ParametersInit(void);
Thread* param_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);


#endif /* PARAM_H_ */
