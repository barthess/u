#ifndef WP_H_
#define WP_H_

void WpSeqOverwrite(uint16_t seq);
void broadcast_mission_current(uint16_t seq);
void broadcast_mission_item_reached(uint16_t seq);
goto_wp_result_t goto_wp(uint16_t seq);

#endif /* WP_H_ */
