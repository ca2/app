#include "framework.h"
#include "_linux.h"
#include "gtk_things/gnome_gnome.h"


namespace process
{


   CLASS_DECL_CORE bool set_priority(::enum_priority epriority)
   {

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, epriority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

   }




} // namespace aura




























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






// int get_current_process_affinity_order()
// {

//    return get_processor_count();

// }






#if OSBIT != 64

::thread_object < _TEB > t_pteb;

struct _TEB * WINAPI NtCurrentTeb(void)
{

   return t_pteb;

}

#endif


#include <sys/time.h>



CLASS_DECL_CORE i64 get_nanos()
{


#ifdef RASPBIAN

   struct timeval tv;

   if(gettimeofday(&tv, nullptr) != 0)
   {

      return 0;

   }

   return tv.tv_sec * 1000 * 1000 * 1000 + tv.tv_usec * 1000;

#else
   struct timespec ts;
   if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
   {
      //error
      return 0;
   }

   return ts.tv_sec * 1000 * 1000 * 1000 + ts.tv_nsec;
#endif

}


CLASS_DECL_CORE void main_sync_runnable(::object * pobjectRunnable, ::duration durationTimeout)
{

   ::pointer<object>prunnable = pobjectRunnable;

   auto pevent = __new(manual_reset_event);

   gdk_fork([prunnable, pevent]()
   {

      try
      {

         prunnable->call();

      }
      catch(...)
      {

      }

      ptopic->SetEvent();

   });

   ptopic->wait(durationTimeout);

}


CLASS_DECL_CORE void main_async_runnable(::object * prunnableParam)
{

   ::pointer<object>prunnable = prunnableParam;

   gdk_fork([prunnable]()
   {

      prunnable->call();

   });

}





bool task_set_name(const ::string & psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   return !pthread_setname_np(pthread_self(), strName);

}



