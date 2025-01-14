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
#if defined(__BSD__)
#include <stdio.h>
#if defined(NETBSD)
#include <pthread.h>
#else
#include <pthread_np.h>
#endif
#include <sched.h>
#include <errno.h>
#else
#include <sched.h>
#endif



#if defined(FREEBSD) || defined(OPENBSD) || defined(NETBSD)

int SetThreadAffinityMask(htask h, unsigned int dwThreadAffinityMask)
{

#if defined(OPENBSD)

    return 1;

#elif defined(NETBSD)

    cpuset_t * pcpuset = cpuset_create();

    if(!pcpuset)
    {

        return 0;

    }

    cpuset_zero(pcpuset);

    int iCpuSetErrorCount = 0;

    for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
    {

       	if((1 << i) & dwThreadAffinityMask)
       	{

           if(cpuset_set(i, pcpuset) < 0)
           {

               iCpuSetErrorCount++;

           }

        }

    }

    if(iCpuSetErrorCount <= 0)
    {

       pthread_setaffinity_np((pthread_t) h, cpuset_size(pcpuset), pcpuset);

    }

    cpuset_destroy(pcpuset);

    return iCpuSetErrorCount <= 0;

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

int SetThreadAffinityMask(htask h, unsigned int dwThreadAffinityMask)
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

   pthread_setaffinity_np(h.m_h, sizeof(c), &c);

   return 1;

}

#endif


string task_get_name(htask htask)
{

   char szThreadName[32];

#if defined(FREEBSD) || defined(OPENBSD)

   pthread_get_name_np((pthread_t) htask, szThreadName, sizeof(szThreadName));

   int error = errno;

#else

   int error = pthread_getname_np(htask.m_h, szThreadName, sizeof(szThreadName));

#endif

   if (error)
   {

      return "";

   }

   return szThreadName;

}





void task_set_name(htask htask, const char * psz)
{

   //auto pthread = pthread_self();

   //auto estatus = task_set_name(pthread, pszThreadName);

#if defined(__APPLE__)

   int error = pthread_setname_np(pszTaskName);

#else

   auto pthread = htask.m_h;

   string strName(psz);

#if defined(FREEBSD) || defined(OPENBSD)

   thread_name_abbreviate(strName, 15);

   errno = 0;

   pthread_set_name_np(pthread, strName);

   int error = errno;

#elif defined(NETBSD)

   thread_name_abbreviate(strName, PTHREAD_MAX_NAMELEN_NP - 1);

   int error = pthread_setname_np(pthread, "%s", (void *) strName.c_str());

#else

   thread_name_abbreviate(strName, 15);

   int error = pthread_setname_np(pthread, strName);

#endif

#endif

   if (error)
   {
   
      printf("task_set_name pthread_t 0x%016lX\n", (long unsigned int)pthread);
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
