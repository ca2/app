#include "framework.h"
#include "acme/library.h"
//#include "acme/platform/static_start.h"


#ifndef WINDOWS


int ithread_equals(ithread_t a, ithread_t b)
{

   return pthread_equal(a, b);

}


#endif



