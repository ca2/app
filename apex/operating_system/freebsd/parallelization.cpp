#include "framework.h"
#include "_freebsd.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif



   CLASS_DECL_APEX bool set_process_priority(::enum_priority epriority)
   {

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, epriority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

   }

























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




//CLASS_DECL_APEX void main_sync_runnable(::object * pobjectRunnable, ::duration durationTimeout)
//{
//
//   ::pointer<object>prunnable = pobjectRunnable;
//
//   auto pevent = __new(manual_reset_event);
//
//   auto pnode = Node;
//
//   pnode->node_fork([prunnable, pevent]()
//   {
//
//      try
//      {
//
//         prunnable->operator()();
//
//      }
//      catch(...)
//      {
//
//      }
//
//      ptopic->SetEvent();
//
//   });
//
//   ptopic->wait(durationTimeout);
//
//}

//
//CLASS_DECL_APEX void main_async_runnable(::object * prunnableParam)
//{
//
//   ::pointer<object>prunnable = prunnableParam;
//
//   auto pnode = Node;
//
//   pnode->node_fork([prunnable]()
//   {
//
//      prunnable->operator()();
//
//   });
//
//}







