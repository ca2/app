//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#pragma once


#ifdef PARALLELIZATION_PTHREAD


//xxx #undef ___scoped_restore


#include <pthread.h>


class synchronization_object;


using HSYNC = ::pointer<synchronization_object>;


#define PM_NOREMOVE 0
#define PM_REMOVE 1


//#define WAIT_TIMEOUT                         258L    // dderror
//#define WAIT_FAILED              ((::u32   ) 0xFFFFFFFFL)
//#define WAIT_OBJECT_0            ((::u32   ) STATUS_WAIT_0 + 0)
//
//#define WAIT_ABANDONED           ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
//#define WAIT_ABANDONED_0         ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
//
//#define WAIT_IO_COMPLETION                   STATUS_USER_APC


// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


#include "semun.h"


//#include "acme/operating_system/cross/windows/parallelization2.h"

//#include <sched.h>

void get_os_priority(i32 * piPolicy, sched_param * pparam, ::enum_priority epriority);


#endif



