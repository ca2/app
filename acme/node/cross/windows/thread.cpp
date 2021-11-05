#include "framework.h"


CLASS_DECL_ACME bool __simple_task_sleep()
{

   while (task_get_run())
   {

      sleep(300_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __simple_task_sleep(::duration ::duration)
{

   auto i = ::duration.m_i;

   while (i > 300)
   {

      if (!task_get_run())
      {

         return false;

      }

      sleep(300_ms);

      i -= 300;

   }

   if (!task_get_run())
   {

      return false;

   }

   sleep((::duration) i);

   return ::task_get_run();

}


CLASS_DECL_ACME bool __simple_task_sleep(synchronization_object* psync)
{

   while (task_get_run())
   {

      if (psync->wait(300_ms).succeeded())
      {

         return true;

      }

   }

   return false;

}


CLASS_DECL_ACME bool __simple_task_sleep(::duration ::duration, synchronization_object* psync)
{

   auto i = ::duration.m_i;

   while (i > 300)
   {

      if (!task_get_run())
      {

         return false;

      }

      if (psync->wait(300_ms).succeeded())
      {

         return true;

      }

      i -= 300;

   }

   if (!task_get_run())
   {

      return false;

   }

   if (psync->wait(::duration(i)).succeeded())
   {

      return true;

   }

   return ::task_get_run();

}


CLASS_DECL_ACME bool acme_task_sleep(::duration ::duration, synchronization_object* psync)
{

   if (::is_null(psync))
   {

      if (__os(::duration) == U32_INFINITE_TIMEOUT)
      {

         return __simple_task_sleep();

      }
      else
      {

         return __simple_task_sleep(::duration);

      }

   }
   else
   {

      if (__os(::duration) == U32_INFINITE_TIMEOUT)
      {

         return __simple_task_sleep(psync);

      }
      else
      {

         return __simple_task_sleep(::duration, psync);

      }

   }
}


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
