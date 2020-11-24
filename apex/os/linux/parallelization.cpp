#include "framework.h"
#include "_linux.h"
#include "gnome_gnome.h"


namespace process
{


   CLASS_DECL_APEX bool set_priority(::e_priority epriority)
   {

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, epriority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

   }




} // namespace apex




























void ＿＿node_init_thread()
{

}

void ＿＿node_term_thread()
{

}














bool ＿＿os_init_thread()
{

   //＿＿thread_set_data((ithread_t) idthread, ::parallelization::slot_message_queue, 0);

   return true;

}



bool ＿＿os_term_thread()
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




CLASS_DECL_APEX void main_sync_runnable(::context_object * pobjectRunnable, ::duration durationTimeout)
{

   ＿＿pointer(context_object) prunnable = pobjectRunnable;

   auto pevent = ＿＿new(manual_reset_event);

   gdk_fork([prunnable, pevent]()
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


CLASS_DECL_APEX void main_async_runnable(::context_object * prunnableParam)
{

   ＿＿pointer(context_object) prunnable = prunnableParam;

   gdk_fork([prunnable]()
   {

      prunnable->operator()();

   });

}







