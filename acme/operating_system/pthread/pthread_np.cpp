//
// Created by camilo on Jul/3/2023.
// From Linux parallelization.cpp <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#if !defined(WINDOWS)
#include "acme/parallelization/task.h"
#if defined(FREEBSD)
#undef _ANSI_SOURCE
#undef _C99_SOURCE
#undef _C11_SOURCE
#define __BSD_VISIBLE 1
#endif
#include <pthread.h>
#if defined(FREEBSD) || defined(OPENBSD)
#include <pthread_np.h>
#include <sched.h>
#include <errno.h>
#else
#include <sched.h>
#endif



#if defined(FREEBSD) || defined(OPENBSD)

int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

#if defined(OPENBSD)

    return 1;

#else

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

#endif

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

#if defined(FREEBSD) || defined(OPENBSD)

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

#if defined(__APPLE__)

   int error = pthread_setname_np(pszTaskName);

#else

   auto pthread = (pthread_t) htask;

   string strName(psz);

   thread_name_abbreviate(strName, 15);

#if defined(FREEBSD) || defined(OPENBSD)

   errno = 0;

   pthread_set_name_np(pthread, strName);

   int error = errno;

#else

   int error = pthread_setname_np(pthread, strName);

#endif

#endif

   if (error)
   {
   
      printf("task_set_name pthread_t 0x%016llX\n", (::uptr) pthread);
      
      printf("task_set_name name %s\n", strName.c_str());
      
      if(error == ESRCH)
      {
      
         printf("task_set_name error ESRCH\n");
	      
      }
      else
      {
      
         printf("task_set_name error %d\n", error);
      
      }
      
      fflush(stdout);

      throw ::exception(error_failed);

   }

   //return ::success;


}



#endif
