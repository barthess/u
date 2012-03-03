#ifndef STUBS_H_
#define STUBS_H_

///* The ABI requires a 64-bit type.  */
__extension__ typedef int __guard __attribute__((mode (__DI__)));

int __cxa_guard_acquire(__guard *);
void __cxa_guard_release (__guard *);
void __cxa_guard_abort (__guard *);

void *__dso_handle = NULL;


#endif /* STUBS_H_ */
