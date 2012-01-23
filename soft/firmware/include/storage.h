#ifndef STORAGE_H_
#define STORAGE_H_

void cmd_tree(BaseChannel *chp, int argc, char *argv[]);
void cmd_touch(BaseChannel *chp, int argc, char *argv[]);
void cmd_cp(BaseChannel *chp, int argc, char *argv[]);

void StorageInit(void);

#endif /* STORAGE_H_ */
