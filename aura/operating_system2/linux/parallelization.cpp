#include "framework.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
////#include "acme/primitive/primitive/object.h"


//#include "gnome_gnome.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


//namespace process
//{
//

//   CLASS_DECL_AURA bool set_priority(::enum_priority epriority)
//   {
//
//      i32 iPolicy = SCHED_OTHER;
//
//      sched_param schedparam;
//
//      schedparam.sched_priority = 0;
//
//      get_os_priority(&iPolicy, &schedparam, epriority);
//
//      sched_setscheduler(0, iPolicy, &schedparam);
//
//      return true;
//
//   }
//
//
//
//
//} // namespace aura




























void __node_init_thread()
{

}

void __node_term_thread()
{

}














bool __os_init_thread()
{

   //__thread_set_data((itask_t) idthread, ::parallelization::slot_message_queue, 0);

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


int get_processor_count()
{

   int c = 0;

   int s, j;

   cpu_set_t cpuset;

   pthread_t thread = pthread_self();

   s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);

   if (s != 0)
   {

      return -1;

   }

   for (j = 0; j < CPU_SETSIZE; j++)
   {

      if (CPU_ISSET(j, &cpuset))
      {

         c++;

      }

   }

   return c;

}


int get_current_process_affinity_order()
{

   return get_processor_count();

}





//#if OSBIT != 64
//
//::thread_object < _TEB > t_pteb;
//
//struct _TEB * WINAPI NtCurrentTeb(void)
//{
//
//   return t_pteb;
//
//}
//
//#endif


CLASS_DECL_AURA void main_sync_runnable(::object * pobjectRunnable, const class ::time & timeTimeout)
{

   ::pointer<object>prunnable = pobjectRunnable;

   auto pevent = __new(manual_reset_event);

   auto psystem = pobjectRunnable->acmesystem();

   auto pnode = psystem->node();

   pnode->node_post([prunnable, pevent]()
   {

      try
      {

         prunnable->call_run();

      }
      catch(...)
      {

      }

      pevent->SetEvent();

   });

   pevent->wait(timeTimeout);

}


CLASS_DECL_AURA void main_async_runnable(::object * prunnable)
{

   auto psystem = prunnable->acmesystem();

   auto pnode = psystem->node();

   pnode->node_post(prunnable);

}


void task_set_name(const ::string & psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   int iError = pthread_setname_np(pthread_self(), strName);

   if(iError != 0)
   {

      throw ::exception(error_failed);

   }

}


