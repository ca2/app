//
// Created by camilo on 13/02/2021 <3TBS_!!
// as copy of source excerpt at https://man7.org/tlpi/code/online/dist/svsem/semun.h.html
//
/* semun.h

   Definition of the semun union used by the ::acmeacmesystem() V semaphore semop()
   system call.
*/


#if !defined(ANDROID)
#ifndef SEMUN_H
#define SEMUN_H                 /* Prevent accidental double inclusion */

#include <sys/types.h>          /* For portability */
#include <sys/sem.h>
#if defined(__APPLE__)
#include <sys/ipc.h>
#endif

//#if ! defined(__FreeBSD__) && ! defined(__OpenBSD__) &&
#if  ! defined(__OpenBSD__) && ! defined(__sgi) && ! defined(__APPLE__)
/* Some implementations already declare this union */

union semun {                   /* Used in calls to semctl() */
   int                 val;
   struct semid_ds *   buf;
   unsigned short *    array;
#if defined(__linux__)
   struct seminfo *    __buf;
#endif
};

#endif

#endif // !defined(SEMUN_H)
#endif // !defined(ANDROID)


