#include <stdio.h>
#include <errno.h>

#include "ch.h"

#include "gcc_stubs.hpp"

// Glibc stubs - HATE THEM
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

void _open_r(void){
  return;
}

#ifdef __cplusplus
extern "C" {
#endif
  void __cxa_pure_virtual() { chDbgPanic("Pure virtual function call."); }
#ifdef __cplusplus
}
#endif
