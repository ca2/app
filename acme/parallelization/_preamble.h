// Create by camilo on 2021-04-11 00:45 BRT <3TBS_!!
#pragma once


#include "common.h"


namespace factory
{

   class factory;

   using factory_pointer = ::pointer < factory >;

   template < typename TYPE, typename BASE_TYPE >
   class reusable_factory_item;


} // namespace factory

#ifndef WINDOWS


#define MAXIMUM_WAIT_OBJECTS 64


#endif


#ifdef __APPLE__
#include <semaphore.h>
#endif

#ifdef PARALLELIZATION_PTHREAD

#define CRITICAL_SECTION_FUNCTION_RETURN int

//CRITICAL_SECTION_FUNCTION_RETURN pthread_recursive_mutex_init(pthread_mutex_t* pmutex);


#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

using hsynchronization = ::subparticle *;


#else

#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

#define CRITICAL_SECTION_FUNCTION_RETURN void
using hsynchronization = void *;


#endif



#define INVALID_HSYNC_VALUE ((hsynchronization)nullptr)



