#include "framework.h"
#include <sys/resource.h>


void thread_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   int iOsMax = sched_get_priority_max(SCHED_RR);

   int iOsMin = sched_get_priority_min(SCHED_RR);

   if(nCa2Priority == ::e_priority_normal)
   {

      iOsPolicy = SCHED_RR; // iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = (int) ::e_priority_normal;

      iOsMin = (iOsMin + iOsMax) / 2;

      iOsMax = iOsMin;

   }
   else if(nCa2Priority > ::e_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = 99;

      iOsMin = (iOsMin + iOsMax) / 2;

   }
   else
   {

      iOsPolicy = SCHED_RR; // iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::e_priority_normal;

      iOsMax = (iOsMin + iOsMax) / 2;

   }


   int iOsPriority;

   if(iCa2Min == iCa2Max)
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

i32 thread_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


//   if(iOsPolicy == SCHED_RR)
   {

      iCa2Min = ::e_priority_idle;

      iCa2Max = 99;

   }
   /*
      else if(iOsPolicy == SCHED_IDLE)
      {

         iCa2Min = 0;

         iCa2Max = (int) ::e_priority_normal;

      }
      else
      {

         iCa2Min = (int) ::e_priority_normal;

         iCa2Max = (int) ::e_priority_normal;

      }
   */

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if(iOsMax == iOsMin)
   {
      iCa2Priority = (i32) ::e_priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void process_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

   __throw(::exception("not applicable in Mac OS"));

}

i32 process_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   __throw(::exception("not applicable in Mac OS"));

}


i32 process_get_os_priority(i32 nCa2Priority)
{

   if(nCa2Priority <= (int) ::e_priority_none)
      return 0;

   if(nCa2Priority <= (int) ::e_priority_normal)
      return maximum(-20, minimum(0, -20 * ((int) ::e_priority_normal - nCa2Priority) / ((int) ::e_priority_normal - (int) ::e_priority_idle)));

   return maximum(0, minimum(20, 20 * (nCa2Priority - (int) ::e_priority_normal) / ((int) ::e_priority_time_critical - (int) ::e_priority_normal)));

}


i32 process_get_scheduling_priority(i32 iOsPriority)
{

   if(iOsPriority < -15)
      return ::e_priority_idle;

   if(iOsPriority < -10)
      return ::e_priority_lowest;

   if(iOsPriority < 0)
      return ::e_priority_below_normal;

   if(iOsPriority == 0)
      return ::e_priority_normal;

   if(iOsPriority < 10)
      return ::e_priority_above_normal;

   if(iOsPriority < 15)
      return ::e_priority_highest;

   return ::e_priority_time_critical;


}


namespace parallelization
{



   bool set_priority_class(i32 iCa2Priority)
   {

      int iOsPriority = process_get_os_priority(iCa2Priority);

      setpriority(PRIO_PROCESS, 0, iOsPriority);

      return true;

   }



} // namespace ca2






//void * new_ns_pool();
//void release_pool(void * pool);

//thread_pointer < void > g_ns_pool;


void __node_init_thread()
{

   //g_ns_pool = new_ns_pool();

}


void __node_term_thread()
{

   //release_pool(g_ns_pool);

   //g_ns_pool = nullptr;

}










bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

//   __clear_mq("__os_term_thread", true);

   //thread_shutdown();

   return true;

}


