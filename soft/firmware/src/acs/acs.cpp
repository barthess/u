#include "main.h"
#include "acs.hpp"
#include "param_registry.hpp"
#include "waypoint_db.hpp"

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
extern ParamRegistry param_registry;
extern WpDB wpdb;

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
/**
 *
 */
acs_status_t ACS::navigating(const StateVector *in, Impact *out){
  (void)in;
  (void)out;
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::passing_wp(const StateVector *in, Impact *out){
  (void)in;
  (void)out;
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::loitering(const StateVector *in, Impact *out){
  (void)in;
  (void)out;
  return ACS_STATUS_ERROR;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void ACS::start(void){
  this->hdg.start((const float*)param_registry.valueSearch("HDG_iMax"),
                  (const float*)param_registry.valueSearch("HDG_iMin"),
                  (const float*)param_registry.valueSearch("HDG_iGain"),
                  (const float*)param_registry.valueSearch("HDG_pGain"),
                  (const float*)param_registry.valueSearch("HDG_dGain"));
  this->spd.start((const float*)param_registry.valueSearch("SPD_iMax"),
                  (const float*)param_registry.valueSearch("SPD_iMin"),
                  (const float*)param_registry.valueSearch("SPD_iGain"),
                  (const float*)param_registry.valueSearch("SPD_pGain"),
                  (const float*)param_registry.valueSearch("SPD_dGain"));
  this->xtrack.start((const float*)param_registry.valueSearch("XTRACK_iMax"),
                  (const float*)param_registry.valueSearch("XTRACK_iMin"),
                  (const float*)param_registry.valueSearch("XTRACK_iGain"),
                  (const float*)param_registry.valueSearch("XTRACK_pGain"),
                  (const float*)param_registry.valueSearch("XTRACK_dGain"));

  this->state = ACS_STATE_IDLE;
}

/**
 * @brief         Loiter specified time.
 * @param[in] t   time to loiter
 */
acs_status_t loiter(systime_t t){
  (void)t;
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::update(const StateVector *in, Impact *out){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");
  chDbgCheck((NULL != in) && (NULL != out), "");

  switch(this->state){
  case ACS_STATE_IDLE:
    return ACS_STATUS_OK;
    break;

  case ACS_STATE_NAVIGATE_TO_WAYPOINT:
    return navigating(in, out);
    break;

  case ACS_STATE_PASS_WAYPOINT:
    return passing_wp(in, out);
    break;

  case ACS_STATE_LOITER:
    return loitering(in, out);
    break;

  default:
    chDbgPanic("unhandled case");
    return ACS_STATUS_ERROR;
    break;
  }
}

/**
 * @brief   Launch UAV to specified waypoint
 */
acs_status_t ACS::launch(uint16_t seq){
  if (wpdb.getCount() <= seq)
    return ACS_STATUS_NO_SUCH_WP;

  this->seq = seq;
  if (CH_SUCCESS != wpdb.load(&this->wp, this->seq))
    return ACS_STATUS_LOADING_WP_FAILED;
  else{
    state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
    return ACS_STATUS_OK;
  }
}

/**
 *
 */
acs_status_t ACS::overwriteWp(uint16_t seq){
  (void)seq;
  return ACS_STATUS_ERROR;
}
