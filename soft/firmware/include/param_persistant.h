#ifndef PARAM_PERSISTANT_H_
#define PARAM_PERSISTANT_H_



bool_t load_params_from_eeprom(uint32_t n);
bool_t save_params_to_eeprom(uint32_t n);


bool_t load_mission_from_eeprom(void);
bool_t save_mission_to_eeprom(void);


#endif /* PARAM_PERSISTANT_H_ */
