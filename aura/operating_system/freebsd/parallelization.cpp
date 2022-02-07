#include "framework.h"
#include "_freebsd.h"
//#include "gnome_gnome.h"
#define bitset freebsd_bitset
#include <pthread_np.h>
#undef bitset


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

   cpuset_t cpuset;

   pthread_t thread = pthread_self();

   s = pthread_getaffinity_np(thread, sizeof(cpuset_t), &cpuset);

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


CLASS_DECL_AURA void main_sync_runnable(::object * pobjectRunnable, ::duration durationTimeout)
{

   __pointer(object) prunnable = pobjectRunnable;

   auto pevent = __new(manual_reset_event);

   auto psystem = pobjectRunnable->m_psystem;

   auto pnode = psystem->node();

   pnode->node_fork([prunnable, pevent]()
   {

      try
      {

         prunnable->operator()();

      }
      catch(...)
      {

      }

      pevent->SetEvent();

   });

   pevent->wait(durationTimeout);

}


CLASS_DECL_AURA void main_async_runnable(::object * prunnableParam)
{

   __pointer(object) prunnable = prunnableParam;

   auto psystem = prunnableParam->m_psystem;

   auto pnode = psystem->node();

   pnode->node_fork([prunnable]()
   {

      prunnable->operator()();

   });

}


void task_set_name(const ::string & psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   return !pthread_setname_np(pthread_self(), strName);

}



