#ifndef PARAM_H_
#define PARAM_H_


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

bool_t set_global_param(void *value,  GlobalParam_t *param);
void ParametersInit(void);
int32_t _key_index_search(char* key);
void *ValueSearch(char *str);

#endif /* PARAM_H_ */
