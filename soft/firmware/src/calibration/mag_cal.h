#ifndef MAG_CAL_H_
#define MAG_CAL_H_


#define MAG_STAT_UPDATED     TRUE
#define MAG_STAT_UNCHANGED   FALSE


bool_t mag_stat_update(int32_t *data);
void MagCalInit(void);


#endif /* MAG_CAL_H_ */
