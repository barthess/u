#ifndef PARAM_H_
#define PARAM_H_


/* периодичность посылки данных в милисекундах */
#define SEND_MIN                  20
#define SEND_MAX                  5000
#define SEND_OFF                  SEND_MIN - 1


#define ONBOARD_PARAM_NAME_LENGTH 15
#define PARAM_ID_SIZE             16


typedef struct GlobalParam_t GlobalParam_t;

typedef bool_t (*setval_t)(float value, GlobalParam_t *param);

struct GlobalParam_t
{
  const char *name;
  const float min;
  float value;
  const float max;
  const uint8_t param_type;
  /* this function checks and sets value. If value out of range than it will
   * be set to neares allowable value */
  const setval_t setval;
};

/**
 * Macro for searching in global value struct with returning parameter checking
 * family - for example "MAG"
 * token  - for example "xoffset"
 */
//  i = KeyValueSearch("MAG_xoffset");
//  if (i == -1)
//    chDbgPanic("key not found");
//  else
//    xoffset_index = i;
#define kvs(family, token){                                                   \
    i = _key_index_search(#family"_"#token);                                  \
    if (i == -1)                                                              \
      chDbgPanic(#family"_"#token "key not found");                           \
    else                                                                      \
      token##_index = i;                                                      \
}

//typedef struct GlobalParam_t GlobalParam_t;
//struct GlobalParam_t
//{
//  const char *name;
//  union{
//    float    f32;
//    uint32_t u32;
//    int32_t  i32;
//    uint16_t u16;
//    int16_t  i16;
//    uint8_t  u8;
//    int8_t   i8;
//  }value;
//  const float min;
//  const float max;
//  const uint8_t param_type;
//};


void ParametersInit(void);
int32_t _key_index_search(char* key);
float *ValueSearch(char *str);

#endif /* PARAM_H_ */
