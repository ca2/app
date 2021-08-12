#include "framework.h"
#include "acme/operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


#ifndef WINDOWS


CLASS_DECL_ACME int_bool is_process_running(::u32 pid)
{


   int i = kill(pid, 0);

   return (i == 0) || (i == -1 && errno == EPERM);

}


#endif




#if defined(LINUX) || defined(ANDROID)



#ifdef LINUX
# define SCHED_BATCH    3
# define SCHED_IDLE     5

# define SCHED_RESET_ON_FORK  0x40000000

#else

#ifndef ANDROID
# define SCHED_BATCH    SCHED_OTHER
# define SCHED_IDLE     SCHED_OTHER

# define SCHED_RESET_ON_FORK  SCHED_OTHER

#endif



#endif




::e_priority get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


   if (iOsPolicy == SCHED_RR)
   {

      iCa2Min = (int) ::priority_normal;

      iCa2Max = 99;

   }
   else if (iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::priority_normal;

   }
   else
   {

      iCa2Min = (int) ::priority_normal;

      iCa2Max = (int) ::priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if (iOsMax == iOsMin)
   {
      iCa2Priority = (i32) ::priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));

   return (e_priority) iCa2Priority;

}



::e_priority thread_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


void process_get_os_priority(i32 * piPolicy, sched_param * pparam, ::e_priority epriority)
{

   get_os_priority(piPolicy, pparam, epriority);

}


::e_priority process_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}



#endif




