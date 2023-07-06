//
// Created by camilo on Jul/3/2023.
// From Linux parallelization.cpp <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/parallelization/task.h"
#if defined(FREEBSD)
#undef _ANSI_SOURCE
#undef _C99_SOURCE
#undef _C11_SOURCE
#endif
#include <pthread_np.h>
#if defined(FREEBSD)
#include <sched.h>
#include <errno.h>
#endif


#ifdef FREEBSD

int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

    cpuset_t c;

    CPU_ZERO(&c);

    for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
    {

        if((1 << i) & dwThreadAffinityMask)
        {

            CPU_SET(i, &c);

        }

    }

    pthread_setaffinity_np((pthread_t) h, sizeof(c), &c);

    return 1;

}

#else

int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

   cpu_set_t c;

   CPU_ZERO(&c);

   for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
   {

      if((1 << i) & dwThreadAffinityMask)
      {

         CPU_SET(i, &c);

      }

   }

   pthread_setaffinity_np((pthread_t) h, sizeof(c), &c);

   return 1;

}

#endif


string task_get_name(htask_t htask)
{

   char szThreadName[32];

#ifdef FREEBSD

   pthread_get_name_np((pthread_t) htask, szThreadName, sizeof(szThreadName));

   int error = errno;

#else

   int error = pthread_getname_np((pthread_t) htask, szThreadName, sizeof(szThreadName));

#endif

   if (error)
   {

      return "";

   }

   return szThreadName;

}





void task_set_name(htask_t htask, const char * psz)
{

   //auto pthread = pthread_self();

   //auto estatus = task_set_name(pthread, pszThreadName);

#ifdef __APPLE__

   int error = pthread_setname_np(pszTaskName);

#else

   auto pthread = (pthread_t) htask;

   string strName(psz);

   thread_name_abbreviate(strName, 15);

#if defined(FREEBSD)

   pthread_set_name_np(pthread, strName);

   int error = errno;

#else

   int error = pthread_setname_np(pthread, strName);

#endif

#endif

   if (error)
   {

      throw ::exception(error_failed);

   }

   //return ::success;


}



