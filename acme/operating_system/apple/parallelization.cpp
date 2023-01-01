// Internet, 21 de Julho de 2017
// 01:00:30 (friday dawn)
// bilbo (sleeping) and Mummi (Discovery ID)!!
// (after Pizza slice and Lamen...)
// Tectuma (Stacie, Kevin and Dylan...)
// RocketBeans.TV (classical and epic Dark Souls with Colin and Etienne)
// scamwhite
// currently and for ever lasting TBS... (thomas borregaard at 2017 earth milk way) Incancilabile (Uncancelable/Undeletable)!!
#include "framework.h"
#include "acme/platform/system.h"

#define user user2
#include <sys/param.h>
#include <sys/sysctl.h>
#undef user

#include <unistd.h>


#include <dispatch/dispatch.h>


int get_processor_count()
{

   int nm[2];

   size_t len = 4;

   u32 count;

   nm[0] = CTL_HW;

   nm[1] = HW_AVAILCPU;

   sysctl(nm, 2, &count, &len, nullptr, 0);

   if(count < 1)
   {

      nm[1] = HW_NCPU;

      sysctl(nm, 2, &count, &len, nullptr, 0);

      if(count < 1)
      {
         count = 1;

      }

   }

   return count;

   //#else
   // return sysconf(_SC_NPROCESSORS_ONLN);
   //#endif
}


i32 process_get_os_priority(i32 nCa2Priority);


//bool set_process_priority(::enum_priority epriority)
//{
//
//   int iOsPriority = process_get_os_priority(epriority);
//
//   setpriority(PRIO_PROCESS, 0, iOsPriority);
//
//   return true;
//
//}


bool ns_set_thread_name(const ::scoped_string & scopedstr);


char * ns_get_thread_name();


void task_set_name(const ::scoped_string & scopedstr)
{
   
   return ns_set_thread_name(scopedstr);

}

string task_get_name()
{
   
   return ::string_from_strdup(ns_get_thread_name());
   
}


namespace acme
{


   void system::windowing_post(const ::procedure & procedure)
   {

      main_asynchronous(procedure);

   }


} // namespace acme


int get_current_process_affinity_order()
{

   int numCPU = (int) (sysconf(_SC_NPROCESSORS_ONLN));

   return numCPU;
}


void ns_main_async(dispatch_block_t block);


void main_asynchronous(const ::procedure & procedure)
{
   
   auto procedureLocal = procedure;
  
   ns_main_async(^{
      
      procedureLocal();
      
   });
   
}


i32 process_get_os_priority(i32 nCa2Priority)
{

   if(nCa2Priority <= (int) ::e_priority_none)
      return 0;

   if(nCa2Priority <= (int) ::e_priority_normal)
      return maximum(-20, minimum(0, -20 * ((int) ::e_priority_normal - nCa2Priority) / ((int) ::e_priority_normal - (int) ::e_priority_idle)));

   return maximum(0, minimum(20, 20 * (nCa2Priority - (int) ::e_priority_normal) / ((int) ::e_priority_time_critical - (int) ::e_priority_normal)));

}




