#include <stdio.h>
#include <errno.h>

#include "ch.h"
#include "hal.h"

#include "stubs.h"

// FIXME: Stubs - HATE THEM
void _exit(int status){
   (void) status;
   chSysHalt();

   while(TRUE){}
}

pid_t _getpid(void){
   return 1;
}

#undef errno
extern int errno;
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}
