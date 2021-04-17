// Create by camilo on 2021-04-11 00:45 BRT <3TBS_!!
#pragma once


#include "common.h"


namespace factory
{


   template < typename TYPE, typename BASE_TYPE >
   class reusable_factory;


} // namespace factory

#ifndef WINDOWS


#define MAXIMUM_WAIT_OBJECTS 64


#endif


#ifdef APPLEOS
#include <semaphore.h>
#endif

#include "synchronization_result.h"

#ifdef PARALLELIZATION_PTHREAD

#define CRITICAL_SECTION_FUNCTION_RETURN int

CRITICAL_SECTION_FUNCTION_RETURN pthread_recursive_mutex_init(pthread_mutex_t* pmutex);

#else

#define CRITICAL_SECTION_FUNCTION_RETURN void

#endif


#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

using hsync = void *;

#define INVALID_HSYNC_VALUE ((hsync)nullptr)



