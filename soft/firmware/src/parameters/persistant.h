#ifndef PERSISTANT_H_
#define PERSISTANT_H_


bool_t load_params_from_eeprom(void);
bool_t save_params_to_eeprom(void);

bool_t load_mission_from_eeprom(void);
bool_t save_mission_to_eeprom(void);


#endif /* PERSISTANT_H_ */
