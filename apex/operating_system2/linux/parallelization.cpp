#include "framework.h"
#include "_linux.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif



   CLASS_DECL_APEX bool set_process_priority(::enum_priority epriority)
   {

      int iPolicy = SCHED_OTHER;

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

   //__thread_set_data((itask) idthread, ::parallelization::slot_message_queue, 0);

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




//CLASS_DECL_APEX void main_sync_runnable(::object * pobjectRunnable, ::time timeTimeout)
//{
//
//   ::pointer<object>prunnable = pobjectRunnable;
//
//   auto pevent = __allocate manual_reset_happening();
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
//      ptopic->set_happening();
//
//   });
//
//   ptopic->wait(timeTimeout);
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







