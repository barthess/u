#ifndef GCC_STUBS_H_
#define GCC_STUBS_H_

///* The ABI requires a 64-bit type.  */
__extension__ typedef int __guard __attribute__((mode (__DI__)));

int __cxa_guard_acquire(__guard *);
void __cxa_guard_release (__guard *);
void __cxa_guard_abort (__guard *);

void *__dso_handle = NULL;


#endif /* GCC_STUBS_H_ */
