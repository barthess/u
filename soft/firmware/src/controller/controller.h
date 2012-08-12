#ifndef CONTROLLER_H_
#define CONTROLLER_H_

uint8_t float2thrust(float v);
uint8_t float2servo(float v);
void set_mode_handler(mavlink_set_mode_t *mavlink_set_mode_struct);

void ControllerInit(void);


#endif /* CONTROLLER_H_ */
