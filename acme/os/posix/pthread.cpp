#include "framework.h"
#include "acme/os/ansios/_ansios.h"
#include "acme/parallelization/message_queue.h"

#include "acme/os/ansios/_pthread.h"
#ifdef LINUX
#include "acme/os/linux/_user.h"


#endif

#ifdef ANDROID

#include <sys/prctl.h>

#endif



message_queue * get_message_queue(itask_t idthread, bool bCreate);


//CLASS_DECL_ACME void thread_get_os_priority(i32 * piOsPolicy, sched_param * pparam, ::e_priority epriority);
//
//CLASS_DECL_ACME void process_get_os_priority(i32 * piOsPolicy, sched_param * pparam, ::e_priority epriority);
//
//CLASS_DECL_ACME::e_priority thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
//
//CLASS_DECL_ACME::e_priority process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


enum_synchronization_result MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags)
{

   millis start;

   if (tickTimeout != (::u32)U32_INFINITE_TIMEOUT)
   {

      start = ::millis::now();

   }

   __pointer(message_queue) pmq;

   if (dwWakeMask > 0)
   {

      pmq = ::get_message_queue(get_current_ithread(), false);

   }

   int_bool bWaitForAll = dwFlags & MWMO_WAITALL;
   //   int_bool bAlertable         = dwFlags & MWMO_ALERTABLE;
   //   int_bool bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;

   if (bWaitForAll)
   {

      while (true)
      {
         i32 i;
         i32 j;
         i = 0;
         for (; comparison::lt(i, dwSize);)
         {

            if (pmq.is_set())
            {

               synchronization_lock synchronizationlock(pmq->mutex());

               if (pmq->m_messagea.get_count() > 0)
               {

                  return (enum_synchronization_result)(e_synchronization_result_signaled_base + dwSize);

               }

            }

            if (tickTimeout != (::u32)U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
            {

               for (j = 0; j < i; j++)
               {

                  synca[j]->unlock();

               }

               return e_synchronization_result_timed_out;

            }

            if (synca[i]->lock(millis(1)))
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

         return e_synchronization_result_timed_out;

      }

   }
   else
   {

      i32 i;

      while (true)
      {

         if (pmq.is_set())
         {

            if (pmq->m_eventNewMessage.lock(millis(0)))
            {

               return (enum_synchronization_result)(e_synchronization_result_signaled_base + dwSize);

            }

         }

         for (i = 0; comparison::lt(i, dwSize); i++)
         {

            if (tickTimeout != (::u32)U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
            {

               return e_synchronization_result_timed_out;

            }

            if (synca[i]->lock(millis(0)))
            {

               return (enum_synchronization_result)(e_synchronization_result_signaled_base + i);

            }

         }

         nanosleep(&delay, nullptr);

      }

   }

}


enum_synchronization_result MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, dwWakeMask, (bWaitForAll ? MWMO_WAITALL : 0));

}


enum_synchronization_result WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, 0, (bWaitForAll ? MWMO_WAITALL : 0) | (bAlertable ? MWMO_ALERTABLE : 0));

}


enum_synchronization_result WaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, synca, bWaitForAll, tickTimeout, false);

}


enum_synchronization_result WaitForSingleObjectEx(HSYNC hsync, ::u32 tickTimeout, int_bool bAlertable)
{

   return WaitForMultipleObjectsEx(1, &hsync, true, tickTimeout, bAlertable);

}


enum_synchronization_result WaitForSingleObject(HSYNC hsync, ::u32 tickTimeout)
{

   return WaitForSingleObjectEx(hsync, tickTimeout, false);

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


CLASS_DECL_ACME htask_t get_current_hthread()
{

   return (htask_t) ::pthread_self();

}


CLASS_DECL_ACME itask_t get_current_ithread()
{

   return (itask_t) ::pthread_self();

}


void __node_init_cross_windows_threading();


void __node_init_multithreading()
{

   __node_init_cross_windows_threading();

}


void __node_term_cross_windows_threading();


void __node_term_multithreading()
{

   __node_term_cross_windows_threading();

}


#if defined(LINUX) // || defined(ANDROID)

bool (*g_pfn_defer_process_x_message)(htask_t hthread, MESSAGE * pMsg, oswindow oswindow, bool bPeek) = nullptr;


bool aura_defer_process_x_message(htask_t hthread, MESSAGE * pMsg, oswindow oswindow, bool bPeek)

{

   if (g_pfn_defer_process_x_message == nullptr)
      return false;

   return (*g_pfn_defer_process_x_message)(hthread, pMsg, oswindow, bPeek);


}

void set_defer_process_x_message(bool (*pfn)(htask_t hthread, MESSAGE * pMsg, oswindow oswindow, bool bPeek))

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



//int_bool WINAPI SetThreadPriority(htask_t hthread, i32 nCa2Priority)
//{
//
//   i32 iPolicy;
//
//   sched_param schedparam;
//
//   thread_get_os_priority(&iPolicy, &schedparam, (::e_priority)nCa2Priority);
//
//   pthread_setschedparam((pthread_t)hthread, iPolicy, &schedparam);
//
//   return true;
//
//}


i32 get_os_thread_priority(::e_priority epriority)
{

   return (i32)epriority;

}





//i32 WINAPI GetThreadPriority(htask_t  hthread)
//{
//
//   int iOsPolicy = SCHED_OTHER;
//
//   sched_param schedparam;
//
//   schedparam.sched_priority = 0;
//
//   pthread_getschedparam((itask_t)hthread, &iOsPolicy, &schedparam);
//
//   return thread_get_scheduling_priority(iOsPolicy, &schedparam);
//
//}




static htask_t g_hMainThread = (htask_t) nullptr;

static itask_t g_uiMainThread = (itask_t)-1;


CLASS_DECL_ACME void set_main_hthread(htask_t hthread)
{

   // MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_hMainThread = hthread;

}


CLASS_DECL_ACME void set_main_ithread(itask_t itask)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_uiMainThread = itask;

}


CLASS_DECL_ACME htask_t get_main_hthread()
{

   return g_hMainThread;

}


CLASS_DECL_ACME itask_t get_main_ithread()
{

   return g_uiMainThread;

}


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
{

}



// LPVOID WINAPI thread_get_data(htask_t hthread, ::u32 dwIndex);


// int_bool WINAPI thread_set_data(htask_t hthread, ::u32 dwIndex, LPVOID pTlsValue);




::u32 g_dwDebug_post_thread_msg_time;

int g_iDebug_post_thread_msg_time;




//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, oswindow oswindow, ::u32 Msg, WPARAM wParam, LPARAM lParam)
//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, ::u32 Msg, WPARAM wParam, LPARAM lParam)
//{
//
//   synchronization_lock ml(pmq->mutex());
//
//   MESSAGE msg;
//
//   msg.message = Msg;
//   msg.wParam = wParam;
//   msg.lParam = lParam;
//   msg.pt.x = 0x80000000;
//   msg.pt.y = 0x80000000;
//   msg.hwnd = nullptr;
//
//   if (msg.message == e_message_quit)
//   {
//
//      output_debug_string("e_message_quit thread");
//
//   }
//
//   pmq->m_messagea.add(msg);
//
//   pmq->m_eventNewMessage.set_event();
//
//   return true;
//
//}


// CLASS_DECL_ACME htask_t GetCurrentThread()
// {

//    return pthread_self();

// }

// CLASS_DECL_ACME itask_t GetCurrentThreadId()
// {

//    return pthread_self();

// }

//
//namespace parallelization
//{
//
//   CLASS_DECL_ACME bool set_priority(::e_priority epriority)
//   {
//
//      return (::SetThreadPriority(::get_current_hthread(), epriority) != 0);
//   }
//
//
//   CLASS_DECL_ACME i32 priority()
//   {
//
//      return ::GetThreadPriority(::get_current_hthread());
//
//   }
//
//
//} // namespace acme


//bool on_init_thread()
//{
//
//   if (!__os_init_thread())
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//bool on_term_thread()
//{
//
//   bool bOk1 = __os_term_thread();
//
//   return bOk1;
//
//}


CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



void get_os_priority(i32 * piPolicy, sched_param * pparam, ::e_priority epriority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if (epriority == ::priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::priority_normal;

      iCa2Max = (int) ::priority_normal;

   }
   else if (epriority > ::priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::priority_normal;

      iCa2Max = 99;

   }
   else
   {

#ifdef APPLEOS
      iOsPolicy = SCHED_OTHER;
#else
      iOsPolicy = SCHED_IDLE;
#endif

      iCa2Min = 0;

      iCa2Max = (int) ::priority_normal;

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


void thread_get_os_priority(i32 * piPolicy, sched_param * pparam, ::e_priority epriority)
{

   get_os_priority(piPolicy, pparam, epriority);

}


::e_priority get_os_thread_scheduling_priority(int nPriority)
{

   return (::e_priority) nPriority;

}


#if !defined(__APPLE__) && !defined(ANDROID)


namespace parallelization
{


   string thread_get_name()
   {

      char szThreadName[32];

      auto pthread = pthread_self();

      int error = pthread_getname_np(pthread, szThreadName, sizeof(szThreadName));

      if (error)
      {

         return "";

      }

      return szThreadName;

   }


} // namespace parallelization


#elif defined(ANDROID)




string thread_get_name()
{
   /* Try obtaining the thread name.
    * If this fails, we'll return a pointer to an empty string. */
    //if (!thread_name_buffer[0])
   char thread_name_buffer[17] = { 0 };
   prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);

   return thread_name_buffer;

}

#endif



