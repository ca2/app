//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#pragma once


#ifdef PARALLELIZATION_PTHREAD


//xxx #undef scoped_restore


#include <pthread.h>


inline void pthread_recursive_mutex_init(pthread_mutex_t * pmutex)
{

    ::pthread_mutexattr_t attr;

    ::pthread_mutexattr_init(&attr);

    ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    ::pthread_mutex_init(pmutex, &attr);

    ::pthread_mutexattr_destroy(&attr);

}



//class synchronization;



#define PM_NOREMOVE 0
#define PM_REMOVE 1


//#define WAIT_TIMEOUT                         258L    // dderror
//#define WAIT_FAILED              ((unsigned int   ) 0xFFFFFFFFL)
//#define WAIT_OBJECT_0            ((unsigned int   ) STATUS_WAIT_0 + 0)
//
//#define WAIT_ABANDONED           ((unsigned int   ) STATUS_ABANDONED_WAIT_0 + 0)
//#define WAIT_ABANDONED_0         ((unsigned int   ) STATUS_ABANDONED_WAIT_0 + 0)
//
//#define WAIT_IO_COMPLETION                   STATUS_USER_APC


// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


#include "semun.h"


//#include "acme/operating_system/cross/windows/parallelization2.h"

//#include <sched.h>

void get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority);


#endif



