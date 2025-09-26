#include "framework.h"
#include "parallelization_pthread.h"
#include "acme/operating_system/ansi/_ansi.h"
#include "acme/parallelization/message_queue.h"
#include "acme/parallelization/task_message_queue.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
//#ifdef LINUX
//#include "acme/operating_system/linux/_user.h"
//#endif

#if defined(OPENBSD)  || defined(FREEBSD) || defined(__APPLE__)

#include <string.h>

#endif

#if defined(PARALLELIZATION_PTHREAD)


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002


//#endif


#ifdef __ANDROID__

#include <sys/prctl.h>

#endif


//message_queue * aaa_get_message_queue(itask idthread, bool bCreate);


//CLASS_DECL_ACME void thread_get_os_priority(int * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
//
//CLASS_DECL_ACME void process_get_os_priority(int * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
//
//CLASS_DECL_ACME::enum_priority thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
//
//CLASS_DECL_ACME::enum_priority process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


thread_local ::message_queue * t_pmessagequeue = nullptr;


::message_queue * task_message_queue()
{

   if (!t_pmessagequeue)
   {

      auto taskindex = ::current_task_index();

      t_pmessagequeue=  system()->task_message_queue()->get_message_queue(taskindex, false);

   }

   return t_pmessagequeue;

}

thread_local ::pointer < ::manual_reset_happening >
t_phappeningNotifyLock;
//thread_local ::pointer_array < ::subparticle >
//t_synca;

::e_status MsgWaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * pparticle, const class ::time & timeWait, unsigned int dwWakeMask, unsigned int dwFlags)
{

   class ::time start;

   if (!timeWait.is_infinite())
   {

      start = ::time::now();

   }

//   ::pointer<message_queue>pmq;
//
//   if (dwWakeMask > 0)
//   {
//
//      pmq = ::get_message_queue(current_itask(), false);
//
//   }
   
   message_queue * pmq = ::task_message_queue();

   int_bool bWaitForAll = dwFlags & MWMO_WAITALL;
   //   int_bool bAlertable         = dwFlags & MWMO_ALERTABLE;
   //   int_bool bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 10'000'000;

   if (bWaitForAll)
   {

      while (true)
      {
         int i;
         int j;
         i = 0;
         for (; comparison::lt(i, dwSize);)
         {

            if (::is_set(pmq))
            {

               synchronous_lock synchronouslock(pmq->synchronization(), pmq, SYNCHRONOUS_LOCK_SUFFIX);

               if (pmq->m_messagea.get_count() > 0)
               {

                  return (::enum_status)(((int) signaled_base) + dwSize);

               }

            }

            if (!timeWait.is_infinite() && start.elapsed() > timeWait)
            {

               for (j = 0; j < i; j++)
               {

                  pparticle[j]->unlock();

               }

               return error_wait_timeout;

            }

            if (pparticle[i]->lock(1_ms))
            {

               i++;

            }
            else
            {

               nanosleep(&delay, nullptr);

            }

         }
         //      for(j = 0; j < dwSize; j++)
         //    {
         //     hsynca[j]->unlock();
         //}

         return i == dwSize ? signaled_base : error_wait_timeout;

      }

   }
   else
   {

      int i;

      //while (true)
      //{
      
      if(!t_phappeningNotifyLock)
      {
         
         __raw_construct_new(t_phappeningNotifyLock);
         
      }
      else
      {
         
         t_phappeningNotifyLock->reset_happening();
         
      }
      //auto pnotifylock = øallocate notify_lock(t_phappeningNotifyLock);
      notify_lock notifylock(t_phappeningNotifyLock);

         if (::is_set(pmq))
         {

            
            if (pmq->m_phappeningNewMessage->start_notify_lock(&notifylock))
            {

               return (enum_status)(((int) signaled_base) + dwSize);

            }

         }

         for (i = 0; comparison::lt(i, dwSize); i++)
         {

            auto psync = pparticle[i];

            if (psync->start_notify_lock(&notifylock))
            {

               auto estatus = signaled_base + i;

               return (enum_status)estatus;

            }

         }

   if (notifylock.m_pmanualresethappening->_wait(timeWait))
   {

      return error_wait_timeout;

   }


      auto estatus = signaled_base ;

      return (enum_status)estatus;

      //    for (i = 0; comparison::lt(i, dwSize); i++)
      //    {
      //
      //       auto psync = pparticle[i];
      //
      //       if (psync->_wait(0_ms))
      //       {
      //
      //          auto estatus = signaled_base + i;
      //
      //          return (enum_status)estatus;
      //
      //       }
      //
      //    }
      //
      //    nanosleep(&delay, nullptr);
      //
      //    if (!timeWait.is_infinite() && start.elapsed() > timeWait)
      //    {
      //
      //       return error_wait_timeout;
      //
      //    }
      //
      // }

   }

}


::e_status MsgWaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, unsigned int dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, dwWakeMask, (bWaitForAll ? MWMO_WAITALL : 0));

}


::e_status WaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout, int_bool bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, 0, (bWaitForAll ? MWMO_WAITALL : 0) | (bAlertable ? MWMO_ALERTABLE : 0));

}


::e_status WaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, const class ::time & tickTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, synca, bWaitForAll, tickTimeout, false);

}


::e_status WaitForSingleObjectEx(hsynchronization hsynchronization, const class ::time & tickTimeout, int_bool bAlertable)
{

   return WaitForMultipleObjectsEx(1, &hsynchronization, true, tickTimeout, bAlertable);

}


::e_status WaitForSingleObject(hsynchronization hsynchronization, const class ::time & tickTimeout)
{

   return WaitForSingleObjectEx(hsynchronization, tickTimeout, false);

}


//thread_data::thread_data()
//{
//
//   pthread_key_create(&m_key, nullptr);
//
//}
//
//
//thread_data::~thread_data()
//{
//
//}
//
//
//void * thread_data::get()
//{
//
//   return pthread_getspecific(m_key);
//
//}
//
//
//void thread_data::set(void * p)
//{
//
//   pthread_setspecific(m_key, p);
//
//}


CLASS_DECL_ACME htask current_htask()
{

   return ::block_cast < htask > (::pthread_self());

}


CLASS_DECL_ACME itask current_itask()
{

   return ::block_cast < itask > (::pthread_self());

}


CLASS_DECL_ACME itask as_itask(htask htask)
{

   return htask.m_h;

}


//void __node_init_cross_windows_threading();


void __node_init_multitasking()
{

   //__node_init_cross_windows_threading();

}


//void __node_term_cross_windows_threading();


void __node_term_multitasking()
{

   //__node_term_cross_windows_threading();

}


#if defined(LINUX) // || defined(__ANDROID__)

bool (*g_pfn_defer_process_x_message)(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek) = nullptr;


bool aura_defer_process_x_message(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek)

{

   if (g_pfn_defer_process_x_message == nullptr)
      return false;

   return (*g_pfn_defer_process_x_message)(htask, pMsg, oswindow, bPeek);


}

void set_defer_process_x_message(bool (*pfn)(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek))

{

   g_pfn_defer_process_x_message = pfn;

}


//#ifdef LINUX
//
//
//void x11_thread(osdisplay_data * pdisplaydata);
//
//
//#endif


#endif


extern "C"
void * os_thread_thread_proc(void * pparameter);




int get_os_thread_priority(::enum_priority epriority)
{

   return (int)epriority;

}



// LPVOID WINAPI thread_get_data(htask htask, unsigned int dwIndex);


// int_bool WINAPI thread_set_data(htask htask, unsigned int dwIndex, LPVOID pTlsValue);




unsigned int g_dwDebug_post_thread_msg_time;

int g_iDebug_post_thread_msg_time;




//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, oswindow oswindow, unsigned int Msg, WPARAM wParam, LPARAM lParam)
//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, unsigned int Msg, WPARAM wParam, LPARAM lParam)
//{
//
//   synchronous_lock ml(pmq->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   MESSAGE msg;
//
//   msg.message = Msg;
//   msg.wParam = wParam;
//   msg.lParam = lParam;
//   msg.pt.x() = I32_MINIMUM;
//   msg.pt.y() = I32_MINIMUM;
//   msg.hwnd = nullptr;
//
//   if (msg.message == ::user::e_message_quit)
//   {
//
//      informationf("::user::e_message_quit thread");
//
//   }
//
//   pmq->m_messagea.add(msg);
//
//   pmq->m_happeningNewMessage.set_happening();
//
//   return true;
//
//}


// CLASS_DECL_ACME htask GetCurrentThread()
// {

//    return pthread_self();

// }

// CLASS_DECL_ACME itask GetCurrentThreadId()
// {

//    return pthread_self();

// }

bool __os_init_thread();

bool os_on_init_thread()
{

   if (!__os_init_thread())
   {

      return false;

   }

   return true;

}

bool __os_term_thread();

void os_on_term_thread()
{

   __os_term_thread();

}


::enum_priority get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


::enum_priority thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


CLASS_DECL_ACME unsigned long long translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



void get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if (epriority == ::e_priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = (int) ::e_priority_normal;

   }
   else if (epriority > ::e_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::e_priority_normal;

      iCa2Max = 99;

   }
   else
   {

#if defined(__APPLE__) || defined(__BSD__)
      iOsPolicy = SCHED_OTHER;
#else
      iOsPolicy = SCHED_IDLE;
#endif

      iCa2Min = 0;

      iCa2Max = (int) ::e_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iOsPriority;

   if (iCa2Min == iCa2Max)
   {
      iOsPriority = 0;
   }
   else
   {
      iOsPriority = (((epriority - iCa2Min) * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
   }

   iOsPriority = maximum(iOsMin, minimum(iOsMax, iOsPriority));

   *piPolicy = iOsPolicy;

   pparam->sched_priority = iOsPriority;

}


void thread_get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority)
{

   get_os_priority(piPolicy, pparam, epriority);

}


::enum_priority get_os_thread_scheduling_priority(int nPriority)
{

   return (::enum_priority) nPriority;

}


#if !defined(__ANDROID__)


//namespace parallelization
//{




#if !defined(__APPLE__)

string task_get_name()
{

   auto pthread = pthread_self();

   auto strTaskName = task_get_name(::block_cast < htask > (pthread));

   return strTaskName;
   
}


//using htask = void *;

//using htask = void *;

//extern "C"
//int   imp_stubs_pthread_setname_np(pthread_t,const_char_pointer );

//
//void task_set_name(htask htask, const ::scoped_string & scopedstrTaskName)
//{
//
//   int error = imp_stubs_pthread_setname_np((pthread_t)htask, pszTaskName);
//
//   if (error)
//   {
//
//      return error_failed;
//
//   }
//
//   return ::success;
//
//}
//




void task_set_name(const scoped_string & scopedstr)
{

   return task_set_name(::block_cast < htask > (pthread_self()), scopedstr);

}


#endif // __APPLE__

//
//
//} // namespace parallelization


#elif defined(__ANDROID__)




string task_get_name()
{
   /* Try obtaining the thread name.
    * If this fails, we'hi return a pointer to an empty string. */
    //if (!thread_name_buffer[0])
   char thread_name_buffer[17] = { 0 };
   prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);

   return thread_name_buffer;

}

#endif


bool itask::operator == (const itask & i) const
{
   
   if(!i)
   {
      
      if(this->is_null())
      {
         
         return true;
         
      }
      else
      {
         
         return false;
         
      }
      
   }
   else if(this->is_null())
   {
      
      return false;
      
   }
   
   return pthread_equal(::literal_cast < pthread_t > (m_i), ::literal_cast < pthread_t > (i.m_i));
   
}


bool htask::operator == (const htask & h) const
{
   
   if(!h)
   {
      
      if(this->is_null())
      {
         
         return true;
         
      }
      else
      {
         
         return false;
         
      }
      
   }
   else if(this->is_null())
   {
      
      return false;
      
   }
   
   return pthread_equal(::literal_cast < pthread_t > (m_h), ::literal_cast < pthread_t > (h.m_h));
   
}


bool itask::is_null() const
{
   
   itask iNull;
   
   return memcmp(&m_i, &iNull, sizeof(m_i)) == 0;
   
}


bool htask::is_null() const
{
   
   htask hNull;
   
   return memcmp(&m_h, &hNull, sizeof(m_h)) == 0;
   
   
}


namespace parallelization
{



   CLASS_DECL_ACME bool set_priority(::enum_priority epriority)
   {

      return set_priority(current_htask(), epriority);

   }


   CLASS_DECL_ACME bool set_priority(htask htask, enum_priority epriority)
   {

      int iPolicy;

      sched_param schedparam;

      thread_get_os_priority(&iPolicy, &schedparam, epriority);

      pthread_setschedparam(::literal_cast < pthread_t > (htask.m_h), iPolicy, &schedparam);

      return true;

   }



   CLASS_DECL_ACME ::enum_priority get_priority()
   {

      return get_priority(current_htask());

   }


   ::enum_priority get_priority(htask htask)
   {

      int iOsPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      pthread_getschedparam(::literal_cast < pthread_t > (htask.m_h), &iOsPolicy, &schedparam);

      return thread_get_scheduling_priority(iOsPolicy, &schedparam);

   }


} // namespace parallelization


#endif



