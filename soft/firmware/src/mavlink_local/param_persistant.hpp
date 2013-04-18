#ifndef PARAM_PERSISTANT_H_
#define PARAM_PERSISTANT_H_


bool_t load_params_from_eeprom(void);
bool_t save_all_params_to_eeprom(void);
bool_t save_param_to_eeprom(const char* key);



#endif /* PARAM_PERSISTANT_H_ */
