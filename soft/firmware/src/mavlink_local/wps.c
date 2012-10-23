/*******************************************************************************
 
 Copyright (C) 2011 Lorenz Meier lm ( a t ) inf.ethz.ch
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ****************************************************************************/

#include "uav.h"
#include <math.h>

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
EepromFileStream EepromWaypointFile;

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
//static mavlink_wpm_storage_t wpm;
static uint8_t eeprom_buf[EEPROM_TX_DEPTH];

static const I2CEepromFileConfig eeprom_waypoint_cfg = {
  &EEPROM_I2CD,
  EEPROM_MISSION_WP_CNT_OFFSET,
  EEPROM_MISSION_END,
  EEPROM_SIZE,
  EEPROM_PAGE_SIZE,
  EEPROM_I2C_ADDR,
  MS2ST(EEPROM_WRITE_TIME_MS),
  FALSE,
  eeprom_buf,
};

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
void _mavlink_wpm_init(void){
//	state->size = 0;
//	state->max_size = 1;
//	state->current_state = MAVLINK_WPM_STATE_IDLE;
//	state->current_partner_sysid = 0;
//	state->current_partner_compid = 0;
//	state->timestamp_lastaction = 0;
//	state->timestamp_last_send_setpoint = 0;
//	state->timeout = MAVLINK_WPM_PROTOCOL_TIMEOUT_DEFAULT;
//	state->delay_setpoint = MAVLINK_WPM_SETPOINT_DELAY_DEFAULT;
//	state->idle = FALSE;
//	state->current_active_wp_id = -1;
//	state->yaw_reached = FALSE;
//	state->pos_reached = FALSE;
//	state->timestamp_lastoutside_orbit = 0;
//	state->timestamp_firstinside_orbit = 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

void MavlinkWpmInit(void){
  _mavlink_wpm_init();
    /* open EEPROM region as file */
  EepromFileOpen(&EepromWaypointFile, &eeprom_waypoint_cfg);
}


