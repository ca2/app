#include "framework.h"


CLASS_DECL_ACME bool ＿＿simple_task_sleep()
{

   while (thread_get_run())
   {

      millis_sleep(300);

   }

   return false;

}


CLASS_DECL_ACME bool ＿＿simple_task_sleep(millis millis)
{

   auto i = millis.m_iMilliseconds;

   while (i > 300)
   {

      if (!thread_get_run())
      {

         return false;

      }

      millis_sleep(300);

      i -= 300;

   }

   if (!thread_get_run())
   {

      return false;

   }

   millis_sleep((::u32) i);

   return ::thread_get_run();

}


CLASS_DECL_ACME bool ＿＿simple_task_sleep(sync* psync)
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


CLASS_DECL_ACME bool ＿＿simple_task_sleep(millis millis, sync* psync)
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

      if (＿＿os(millis) == U32_INFINITE_TIMEOUT)
      {

         return ＿＿simple_task_sleep();

      }
      else
      {

         return ＿＿simple_task_sleep(millis);

      }

   }
   else
   {

      if (＿＿os(millis) == U32_INFINITE_TIMEOUT)
      {

         return ＿＿simple_task_sleep(psync);

      }
      else
      {

         return ＿＿simple_task_sleep(millis, psync);

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
