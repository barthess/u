#ifndef MICROSD_H_
#define MICROSD_H_

void cmd_tree(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_touch(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_cp(BaseSequentialStream *chp, int argc, char *argv[]);

void StorageInit(void);

#endif /* MICROSD_H_ */
