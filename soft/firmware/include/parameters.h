#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <mavlink.h>
#include <common.h>
#include <bart.h>


typedef struct GlobalParam_t GlobalParam_t;
struct GlobalParam_t
{
  const char *name;
  float value;
  const float min;
  const float max;
  const uint8_t param_type;
};


void ParametersInit(void);

#endif /* PARAMETERS_H_ */
