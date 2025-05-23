#include "framework.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifndef WINDOWS


#include <signal.h>
#include <errno.h>


CLASS_DECL_ACME int_bool is_process_running(unsigned int pid)
{

   int i = kill(pid, 0);

   return (i == 0) || (i == -1 && errno == EPERM);

}


#endif




#if defined(LINUX) || defined(__ANDROID__) || defined(__APPLE__) || defined(__BSD__)



#ifdef LINUX
# define SCHED_BATCH    3
# define SCHED_IDLE     5

# define SCHED_RESET_ON_FORK  0x40000000

#else

#ifndef __ANDROID__
# define SCHED_BATCH    SCHED_OTHER
# define SCHED_IDLE     SCHED_OTHER

# define SCHED_RESET_ON_FORK  SCHED_OTHER

#endif



#endif




::enum_priority get_scheduling_priority(int iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


   if (iOsPolicy == SCHED_RR)
   {

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = 99;

   }
   else if (iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::e_priority_normal;

   }
   else
   {

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = (int) ::e_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if (iOsMax == iOsMin)
   {
      iCa2Priority = (int) ::e_priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));

   return (enum_priority) iCa2Priority;

}


void get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority);



void process_get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority)
{

   get_os_priority(piPolicy, pparam, epriority);

}


::enum_priority process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}



#endif




