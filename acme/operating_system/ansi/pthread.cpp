//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"


#ifdef PTHREAD_PARALLELIZATION


#include "acme/operating_system/ansi/_pthread.h"


int itask_equals(itask_t a, itask_t b)
{

   return pthread_equal(a, b);

}


#endif // PTHREAD_PARALLELIZATION



