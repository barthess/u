#include <math.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "imu.h"

#include <mavlink.h>
#include <common.h>
#include <bart.h>



/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define ONBOARD_PARAM_COUNT       5
#define PARAM_SYSTEM_ID           0
#define PARAM_COMPONENT_ID        1
#define ONBOARD_PARAM_NAME_LENGTH 14

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */



struct global_struct
{
  float param[ONBOARD_PARAM_COUNT];
  char param_name[ONBOARD_PARAM_COUNT][MAVLINK_MSG_PARAM_SET_FIELD_PARAM_ID_LEN];
};

struct global_struct global_data;




/**
 * @brief   Performs key-value search.
 *
 * @return      Index in dictionary.
 * @retval -1   key not found.
 */
int32_t key_value_search(char* key){
  uint32_t i = 0;
  uint32_t j = 0;

  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){
    for (j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++){
      // Compare keys
      if (global_data.param_name[i][j] != key[j])
        return -1;
      // End matching if null termination is reached
      if (global_data.param_name[i][j] == '\0')
        return i;
    }
  }
  return -1;
}




void set_global_mavlink_value(mavlink_param_set_t *set){
  int32_t index = -1;

  index = key_value_search(set->param_id);

  if (index >= 0){
    // Only write and emit changes if there is actually a difference
    // AND only write if new value is NOT "not-a-number"
    // AND is NOT infinity
    if (set->param_type == MAVLINK_TYPE_FLOAT){
      if (isnan(set->param_value) || isinf(set->param_value)){
        goto ERROR;
      }
    }
    if (global_data.param[index] == set->param_value){
      goto ERROR;
    }

    global_data.param[index] = set->param_value;
    // TODO: Report back new value
//    mavlink_msg_param_value_send(MAVLINK_COMM_0,
//          (int8_t*) global_data.param_name[index],
//          global_data.param[index], MAVLINK_TYPE_FLOAT);
  }

ERROR:
  return;
}




