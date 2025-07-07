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
#if defined(__ANDROID__)
#if defined(_PTHREAD_H)
#error "informational error (you can comment out): pthread already included"
#else
//#i
//#define __USE_GNU
//#error "informational error (you can comment out): pthread going to be included"
#include <pthread.h>
#endif
#endif

#ifdef __APPLE__
#include <mach/thread_act.h>
#include <errno.h>
#endif

#if defined(__APPLE__) || defined(FREEBSD) || defined(OPENBSD) || defined(NETBSD) || defined(__ANDROID__)

int SetThreadAffinityMask(htask h, unsigned int dwThreadAffinityMask)
{
   
   
#if defined(__APPLE__)
   
   int iSetCount = 0;
   thread_affinity_policy_data_t policydataa[sizeof(dwThreadAffinityMask) * 8];

   for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
   {

         if((1 << i) & dwThreadAffinityMask)
         {

            // 1024? a private namespace of tags represented by a 1024-based index cpu core?
            
            policydataa[iSetCount].affinity_tag = (1024 + i);

            iSetCount++;

       }

   }

   if(iSetCount > 0)
   {

      mach_port_t mach_thread1 = pthread_mach_thread_np(::literal_cast < pthread_t>(h));
      thread_policy_set(mach_thread1, THREAD_AFFINITY_POLICY, (thread_policy_t)policydataa, iSetCount);
      

   }


#elif defined(OPENBSD)

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

       pthread_setaffinity_np(::literal_cast < pthread_t >(h), cpuset_size(pcpuset), pcpuset);

    }

    cpuset_destroy(pcpuset);

    return iCpuSetErrorCount <= 0;

#elif defined(__ANDROID__)
    cpu_set_t c;
    CPU_ZERO(&c);
    for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
    {

        if((1 << i) & dwThreadAffinityMask)
        {

            CPU_SET(i, &c);

        }

    }

    auto pid = pthread_gettid_np(::literal_cast < pthread_t >(h));

    int iRet = sched_setaffinity(pid, sizeof(c), &c);

    return iRet != 0;

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

    pthread_setaffinity_np(::literal_cast < pthread_t >(h), sizeof(c), &c);

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

   pthread_setaffinity_np(::literal_cast< pthread_t>(h.m_h), sizeof(c), &c);

   return 1;

}

#endif


string task_get_name(htask htask)
{

   char szThreadName[32];

#if defined(FREEBSD) || defined(OPENBSD)

   pthread_get_name_np(::literal_cast < pthread_t >( htask.m_h), szThreadName, sizeof(szThreadName));

   int error = errno;

#else

   int error = pthread_getname_np(::literal_cast<pthread_t>(htask.m_h), szThreadName, sizeof(szThreadName));

#endif

   if (error)
   {

      return "";

   }

   return szThreadName;

}





void task_set_name(htask htask, const ::scoped_string & scopedstr)
{

   //auto pthread = pthread_self();

   //auto estatus = task_set_name(pthread, pszThreadName);
    
    string strName(scopedstr);

#if defined(__APPLE__)
   
   if(htask != current_htask())
   {
    
      throw ::exception(error_wrong_state);
      
   }

   int error = pthread_setname_np(strName);

#else

   auto pthread = htask.m_h;

#if defined(FREEBSD) || defined(OPENBSD)

   thread_name_abbreviate(strName, 15);

   errno = 0;

   pthread_set_name_np(::literal_cast < pthread_t >(pthread), strName);

   int error = errno;

#elif defined(NETBSD)

   thread_name_abbreviate(strName, PTHREAD_MAX_NAMELEN_NP - 1);

   int error = pthread_setname_np(::literal_cast < pthread_t >(pthread), "%s", (void *) strName.c_str());

#else

   thread_name_abbreviate(strName, 15);

   int error = pthread_setname_np(literal_cast<pthread_t>(pthread), strName);

#endif

#endif

   if (error)
   {
   
//      printf("task_set_name pthread_t 0x%016lX\n", (long unsigned int)pthread);
      if(error == ESRCH)
      {
      
         print_line("task_set_name error ESRCH");
	      
      }
      else
      {
      
         printf_line("task_set_name error %d", error);
      
      }
      
      //fflush(stdout);

      throw ::exception(error_failed);

   }

   //return ::success;


}



#endif
