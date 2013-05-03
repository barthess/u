#include "acs.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

acs_status_t acsInit(const acs_config_t *cfg){
  (void)cfg;
  return ACS_STATUS_OK;
}

acs_status_t acsUpdate(const acs_input_t *in, acs_output_t *out){
  out->a0 = in->gamma * in->lat;
  return ACS_STATUS_OK;
}

acs_status_t acsReset(void){
  return ACS_STATUS_OK;
}

acs_status_t acsStop(void){
  return ACS_STATUS_OK;
}
