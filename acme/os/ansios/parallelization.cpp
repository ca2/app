//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#include "framework.h"
#undef __restore
#include "acme/os/ansios/_pthread.h"


void get_os_priority(i32 * piPolicy, sched_param * pparam, ::e_priority epriority);


CLASS_DECL_ACME int ithread_equals(ithread_t a, ithread_t b)
{

   return pthread_equal((pthread_t)a, (pthread_t)b);

}


CLASS_DECL_ACME int hthread_equals(hthread_t a, hthread_t b)
{

   return pthread_equal((pthread_t)a, (pthread_t)b);

}



