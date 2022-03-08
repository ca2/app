#include "framework.h"


CLASS_DECL_ACME bool __simple_task_sleep()
{

   while (task_get_run())
   {

      preempt(300_ms);

   }

   return false;

}


//CLASS_DECL_ACME bool __simple_task_sleep(class ::wait wait)
//{
//
//   auto waitStart = class ::wait::now();
//
//   while (waitStart > 300)
//   {
//
//      if (!task_get_run())
//      {
//
//         return false;
//
//      }
//
//      preempt(300_ms);
//
//      iMillisecond -= 300;
//
//   }
//
//   if (!task_get_run())
//   {
//
//      return false;
//
//   }
//
//   preempt((::duration)iMillisecond);
//
//   return ::task_get_run();
//
//}
//
//
//CLASS_DECL_ACME bool __simple_task_sleep(synchronization_object* psync)
//{
//
//   while (task_get_run())
//   {
//
//      if (psync->wait(300_ms).succeeded())
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//CLASS_DECL_ACME bool __simple_task_sleep(class ::wait wait, synchronization_object* psync)
//{
//
//   auto iMillisecond = wait.m_iMillisecond;
//
//   while (iMillisecond > 300)
//   {
//
//      if (!task_get_run())
//      {
//
//         return false;
//
//      }
//
//      if (psync->wait(300_ms).succeeded())
//      {
//
//         return true;
//
//      }
//
//      iMillisecond -= 300;
//
//   }
//
//   if (!task_get_run())
//   {
//
//      return false;
//
//   }
//
//   if (psync->wait(::duration(iMillisecond)).succeeded())
//   {
//
//      return true;
//
//   }
//
//   return ::task_get_run();
//
//}
//

//CLASS_DECL_ACME bool acme_task_sleep(::duration ::duration, synchronization_object* psync)
//{
//
//   if (::is_null(psync))
//   {
//
//      if (__os(::duration) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __simple_task_sleep();
//
//      }
//      else
//      {
//
//         return __simple_task_sleep(::duration);
//
//      }
//
//   }
//   else
//   {
//
//      if (__os(::duration) == U32_INFINITE_TIMEOUT)
//      {
//
//         return __simple_task_sleep(psync);
//
//      }
//      else
//      {
//
//         return __simple_task_sleep(::duration, psync);
//
//      }
//
//   }
//}


//PFN_task_sleep g_pfnThreadSleep = acme_task_sleep;

//CLASS_DECL_ACME bool tas_sleep(::duration ::duration, synchronization_object* psync)
//{
//
//   return g_pfnThreadSleep(::duration, psync);
//
//}

//
//CLASS_DECL_ACME void set_task_sleep(PFN_task_sleep pfnThreadSleep)
//{
//
//   g_pfnThreadSleep = pfnThreadSleep;
//
//}
//


CLASS_DECL_ACME void set_main_user_itask(itask_t itask);


CLASS_DECL_ACME void set_main_user_htask(htask_t htask);


CLASS_DECL_ACME itask_t get_main_user_itask();


CLASS_DECL_ACME void set_main_user_thread()
{

   set_main_user_itask(get_current_itask());

   set_main_user_htask(get_current_htask());

}


CLASS_DECL_ACME bool is_main_thread()
{

   return get_current_itask() == get_main_user_itask();

}



