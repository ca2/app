#include "framework.h"


CLASS_DECL_ACME bool __simple_task_sleep()
{

   while (thread_get_run())
   {

      Sleep(300);

   }

   return false;

}


CLASS_DECL_ACME bool __simple_task_sleep(tick tick)
{

   auto i = tick.m_i;

   while (i > 300)
   {

      if (!thread_get_run())
      {

         return false;

      }

      Sleep(300);

      i -= 300;

   }

   if (!thread_get_run())
   {

      return false;

   }

   Sleep((DWORD) i);

   return ::thread_get_run();

}


CLASS_DECL_ACME bool __simple_task_sleep(sync* psync)
{

   while (thread_get_run())
   {

      if (psync->wait(300_ms).succeeded())
      {

         return true;

      }

   }

   return false;

}


CLASS_DECL_ACME bool __simple_task_sleep(tick tick, sync* psync)
{

   auto i = tick.m_i;

   while (i > 300)
   {

      if (!thread_get_run())
      {

         return false;

      }

      if (psync->wait(300_ms).succeeded())
      {

         return true;

      }

      i -= 300;

   }

   if (!thread_get_run())
   {

      return false;

   }

   if (psync->wait(::millis(i)).succeeded())
   {

      return true;

   }

   return ::thread_get_run();

}


CLASS_DECL_ACME bool acme_task_sleep(tick tick, sync* psync)
{

   if (::is_null(psync))
   {

      if (__os(tick) == INFINITE)
      {

         return __simple_task_sleep();

      }
      else
      {

         return __simple_task_sleep(tick);

      }

   }
   else
   {

      if (__os(tick) == INFINITE)
      {

         return __simple_task_sleep(psync);

      }
      else
      {

         return __simple_task_sleep(tick, psync);

      }

   }
}


//PFN_task_sleep g_pfnThreadSleep = acme_task_sleep;

//CLASS_DECL_ACME bool tas_sleep(tick tick, sync* psync)
//{
//
//   return g_pfnThreadSleep(tick, psync);
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
