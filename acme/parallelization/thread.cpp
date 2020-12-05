#include "framework.h"


CLASS_DECL_ACME bool __simple_task_sleep()
{

   while (thread_get_run())
   {

      sleep(300_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __simple_task_sleep(millis millis)
{

   auto i = millis.m_iMilliseconds;

   while (i > 300)
   {

      if (!thread_get_run())
      {

         return false;

      }

      sleep(300_ms);

      i -= 300;

   }

   if (!thread_get_run())
   {

      return false;

   }

   sleep((::millis) i);

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


CLASS_DECL_ACME bool __simple_task_sleep(millis millis, sync* psync)
{

   auto i = millis.m_iMilliseconds;

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


CLASS_DECL_ACME bool acme_task_sleep(millis millis, sync* psync)
{

   if (::is_null(psync))
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __simple_task_sleep();

      }
      else
      {

         return __simple_task_sleep(millis);

      }

   }
   else
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __simple_task_sleep(psync);

      }
      else
      {

         return __simple_task_sleep(millis, psync);

      }

   }
}


//PFN_task_sleep g_pfnThreadSleep = acme_task_sleep;

//CLASS_DECL_ACME bool tas_sleep(millis millis, sync* psync)
//{
//
//   return g_pfnThreadSleep(millis, psync);
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
