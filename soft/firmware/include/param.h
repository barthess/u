#ifndef PARAM_H_
#define PARAM_H_

#include <mavlink.h>
#include <common.h>
#include <bart.h>


#define ONBOARD_PARAM_NAME_LENGTH 15
#define PARAM_ID_SIZE             16



typedef struct GlobalParam_t GlobalParam_t;
struct GlobalParam_t
{
  const char *name;
  float value;
  const float min;
  const float max;
  const uint8_t param_type;
};



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
int32_t key_value_search(char* key);
bool_t load_params_from_eeprom(void);
bool_t save_params_to_eeprom(void);
bool_t load_mission_from_eeprom(void);
bool_t save_mission_to_eeprom(void);

#endif /* PARAM_H_ */
