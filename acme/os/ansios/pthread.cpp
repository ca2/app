//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"


#ifdef PTHREAD_PARALLELIZATION


#include "acme/os/ansios/_pthread.h"


int ithread_equals(ithread_t a, ithread_t b)
{

   return pthread_equal(a, b);

}


#endif // PTHREAD_PARALLELIZATION



