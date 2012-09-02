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

#ifndef WPS_H_
#define WPS_H_

// FIXME XXX - TO BE MOVED TO XML
typedef enum {
  MAVLINK_WPM_STATE_IDLE = 0,
  MAVLINK_WPM_STATE_SENDLIST,
  MAVLINK_WPM_STATE_SENDLIST_SENDWPS,
  MAVLINK_WPM_STATE_GETLIST,
  MAVLINK_WPM_STATE_GETLIST_GETWPS,
  MAVLINK_WPM_STATE_GETLIST_GOTALL,
  MAVLINK_WPM_STATE_ENUM_END
}MAVLINK_WPM_STATES;

typedef enum {
  MAVLINK_WPM_CODE_OK = 0,
  MAVLINK_WPM_CODE_ERR_WAYPOINT_ACTION_NOT_SUPPORTED,
  MAVLINK_WPM_CODE_ERR_WAYPOINT_FRAME_NOT_SUPPORTED,
  MAVLINK_WPM_CODE_ERR_WAYPOINT_OUT_OF_BOUNDS,
  MAVLINK_WPM_CODE_ERR_WAYPOINT_MAX_NUMBER_EXCEEDED,
  MAVLINK_WPM_CODE_ENUM_END
}MAVLINK_WPM_CODES;


/* WAYPOINT MANAGER - MISSION LIB */
#ifndef MAVLINK_WPM_TEXT_FEEDBACK
#define MAVLINK_WPM_TEXT_FEEDBACK 0						  ///< Report back status information as text
#endif
#define MAVLINK_WPM_PROTOCOL_TIMEOUT_DEFAULT 5000         ///< Protocol communication timeout in milliseconds
#define MAVLINK_WPM_SETPOINT_DELAY_DEFAULT 1000           ///< When to send a new setpoint
#define MAVLINK_WPM_PROTOCOL_DELAY_DEFAULT 40


typedef struct{
	mavlink_mission_item_t waypoint;      ///< Currently active waypoint
	uint16_t size;
	uint16_t max_size;
	uint16_t rcv_size;
	MAVLINK_WPM_STATES current_state;
	uint16_t current_wp_id;							///< Waypoint in current transmission
	uint16_t current_active_wp_id;					///< Waypoint the system is currently heading towards
	uint16_t current_count;
	uint8_t current_partner_sysid;
	uint8_t current_partner_compid;
	uint64_t timestamp_lastaction;
	uint64_t timestamp_last_send_setpoint;
	uint64_t timestamp_firstinside_orbit;///< timestamp when the MAV was the first time after a waypoint change inside the orbit and had the correct yaw value
	uint64_t timestamp_lastoutside_orbit;///< timestamp when the MAV was last outside the orbit or had the wrong yaw value
	uint32_t timeout;
	uint32_t delay_setpoint;
	float accept_range_yaw;
	float accept_range_distance;
	bool_t yaw_reached;///< boolean for yaw attitude reached
	bool_t pos_reached; ///< boolean for position reached
	bool_t idle;///< indicates if the system is following the waypoints or is waiting
}mavlink_wpm_storage_t;


void MavlinkWpmInit(void);

#endif /* WPS_H_ */
