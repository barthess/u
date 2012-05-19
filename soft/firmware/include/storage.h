#ifndef STORAGE_H_
#define STORAGE_H_

void cmd_tree(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_touch(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_cp(BaseSequentialStream *chp, int argc, char *argv[]);

void StorageInit(void);

#endif /* STORAGE_H_ */
