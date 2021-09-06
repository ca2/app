#include "framework.h"

#if defined(LINUX) || defined(ANDROID)



#ifdef LINUX
# define SCHED_BATCH    3
# define SCHED_IDLE     5

# define SCHED_RESET_ON_FORK  0x40000000

#else

# define SCHED_BATCH    SCHED_OTHER
# define SCHED_IDLE     SCHED_OTHER

# define SCHED_RESET_ON_FORK  SCHED_OTHER


#endif



void get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if (nCa2Priority == ::e_priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = (int) ::e_priority_normal;

   }
   else if (nCa2Priority > ::e_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = 99;

   }
   else
   {

      iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::e_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iOsPriority;

   if (iCa2Min == iCa2Max)
   {
      iOsPriority = 0;
   }
   else
   {
      iOsPriority = (((nCa2Priority - iCa2Min)  * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
   }

   iOsPriority = maximum(iOsMin, minimum(iOsMax, iOsPriority));

   *piPolicy = iOsPolicy;

   pparam->sched_priority = iOsPriority;

}

int32_t get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
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
      iCa2Priority = (int32_t) ::e_priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void thread_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t thread_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


void process_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t process_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}



#endif