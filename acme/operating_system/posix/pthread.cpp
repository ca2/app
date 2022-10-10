#include "framework.h"
#include "acme/operating_system/ansi/_ansi.h"
#include "acme/parallelization/message_queue.h"

#include "acme/operating_system/ansi/_pthread.h"
#ifdef LINUX
#include "acme/operating_system/linux/_user.h"


#endif


#if !defined(WINDOWS)


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002


#endif


#ifdef ANDROID

#include <sys/prctl.h>

#endif


message_queue * get_message_queue(itask_t idthread, bool bCreate);


//CLASS_DECL_ACME void thread_get_os_priority(i32 * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
//
//CLASS_DECL_ACME void process_get_os_priority(i32 * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
//
//CLASS_DECL_ACME::enum_priority thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
//
//CLASS_DECL_ACME::enum_priority process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


::e_status MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags)
{

   ::duration start;

   if (tickTimeout != (::u32)INFINITE_TIMEOUT)
   {

      start = ::duration::now();

   }

   ::pointer<message_queue>pmq;

   if (dwWakeMask > 0)
   {

      pmq = ::get_message_queue(get_current_itask(), false);

   }

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
         i32 i;
         i32 j;
         i = 0;
         for (; comparison::lt(i, dwSize);)
         {

            if (pmq.is_set())
            {

               synchronous_lock synchronouslock(pmq->mutex());

               if (pmq->m_messagea.get_count() > 0)
               {

                  return (::enum_status)(((::i32) signaled_base) + dwSize);

               }

            }

            if (tickTimeout != (::u32)INFINITE_TIMEOUT && start.elapsed().integral_millisecond().m_i >= tickTimeout)
            {

               for (j = 0; j < i; j++)
               {

                  synca[j]->unlock();

               }

               return error_wait_timeout;

            }

            if (synca[i]->lock(1_ms))
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

      i32 i;

      while (true)
      {

         if (pmq.is_set())
         {

            if (pmq->m_eventNewMessage._wait(0_s))
            {

               return (enum_status)(((::i32) signaled_base) + dwSize);

            }

         }

         for (i = 0; comparison::lt(i, dwSize); i++)
         {

            auto psync = synca[i];

            if (psync->_wait(0_ms))
            {

               auto estatus = signaled_base + i;

               return (enum_status)estatus;

            }

         }

         nanosleep(&delay, nullptr);

         if (tickTimeout != (::u32)INFINITE_TIMEOUT && start.elapsed().integral_millisecond().m_i >= tickTimeout)
         {

            return error_wait_timeout;

         }

      }

   }

}


::e_status MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, dwWakeMask, (bWaitForAll ? MWMO_WAITALL : 0));

}


::e_status WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, 0, (bWaitForAll ? MWMO_WAITALL : 0) | (bAlertable ? MWMO_ALERTABLE : 0));

}


::e_status WaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, synca, bWaitForAll, tickTimeout, false);

}


::e_status WaitForSingleObjectEx(HSYNC hsync, ::u32 tickTimeout, int_bool bAlertable)
{

   return WaitForMultipleObjectsEx(1, &hsync, true, tickTimeout, bAlertable);

}


::e_status WaitForSingleObject(HSYNC hsync, ::u32 tickTimeout)
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


CLASS_DECL_ACME htask_t get_current_htask()
{

   return (htask_t) ::pthread_self();

}


CLASS_DECL_ACME itask_t get_current_itask()
{

   return (itask_t) ::pthread_self();

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


#if defined(LINUX) // || defined(ANDROID)

bool (*g_pfn_defer_process_x_message)(htask_t htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek) = nullptr;


bool aura_defer_process_x_message(htask_t htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek)

{

   if (g_pfn_defer_process_x_message == nullptr)
      return false;

   return (*g_pfn_defer_process_x_message)(htask, pMsg, oswindow, bPeek);


}

void set_defer_process_x_message(bool (*pfn)(htask_t htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek))

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




i32 get_os_thread_priority(::enum_priority epriority)
{

   return (i32)epriority;

}


static htask_t g_hMainThread = (htask_t) nullptr;

static itask_t g_uiMainThread = (itask_t)-1;


CLASS_DECL_ACME void set_main_user_htask(htask_t htask)
{

   // MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_hMainThread = htask;

}


CLASS_DECL_ACME void set_main_user_itask(itask_t itask)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_uiMainThread = itask;

}


CLASS_DECL_ACME htask_t get_main_user_htask()
{

   return g_hMainThread;

}


CLASS_DECL_ACME itask_t get_main_user_itask()
{

   return g_uiMainThread;

}


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
{

}



// LPVOID WINAPI thread_get_data(htask_t htask, ::u32 dwIndex);


// int_bool WINAPI thread_set_data(htask_t htask, ::u32 dwIndex, LPVOID pTlsValue);




::u32 g_dwDebug_post_thread_msg_time;

int g_iDebug_post_thread_msg_time;




//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, oswindow oswindow, ::u32 Msg, WPARAM wParam, LPARAM lParam)
//CLASS_DECL_ACME int_bool WINAPI mq_post(message_queue * pmq, ::u32 Msg, WPARAM wParam, LPARAM lParam)
//{
//
//   synchronous_lock ml(pmq->mutex());
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

bool __os_init_thread();

bool on_init_thread()
{

   if (!__os_init_thread())
   {

      return false;

   }

   return true;

}

bool __os_term_thread();

bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}


::enum_priority get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam);


::enum_priority thread_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



void get_os_priority(i32 * piPolicy, sched_param * pparam, ::enum_priority epriority)
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

#if defined(__APPLE__) || defined(FREEBSD)
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


void thread_get_os_priority(i32 * piPolicy, sched_param * pparam, ::enum_priority epriority)
{

   get_os_priority(piPolicy, pparam, epriority);

}


::enum_priority get_os_thread_scheduling_priority(int nPriority)
{

   return (::enum_priority) nPriority;

}


#if !defined(ANDROID)


//namespace parallelization
//{


string task_get_name(htask_t htask)
{

   char szThreadName[32];

   int error = pthread_getname_np((pthread_t) htask, szThreadName, sizeof(szThreadName));

   if (error)
   {

      return "";

   }

   return szThreadName;

}


#if !defined(__APPLE__)

string task_get_name()
{

   auto pthread = pthread_self();

   auto strTaskName = task_get_name((htask_t) pthread);

   return strTaskName;
   
}


using htask_t = void *;

using htask_t = void *;

//extern "C"
//int   imp_stubs_pthread_setname_np(pthread_t,const char*);

//
//void task_set_name(htask_t htask, const char * pszTaskName)
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

void task_set_name(const char * pszTaskName)
{

   //auto pthread = pthread_self();

   //auto estatus = task_set_name(pthread, pszThreadName);

#ifdef __APPLE__
   
      int error = pthread_setname_np(pszTaskName);

#else

   auto pthread = pthread_self();

   string strName(pszTaskName);

   thread_name_abbreviate(strName, 15);

   int error = pthread_setname_np(pthread, strName);

#endif
   
      if (error)
      {
   
         throw ::exception(error_failed);
   
      }
   
      //return ::success;

   
}


#endif // __APPLE__

//
//
//} // namespace parallelization


#elif defined(ANDROID)




string task_get_name()
{
   /* Try obtaining the thread name.
    * If this fails, we'll return a pointer to an empty string. */
    //if (!thread_name_buffer[0])
   char thread_name_buffer[17] = { 0 };
   prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);

   return thread_name_buffer;

}

#endif



CLASS_DECL_ACME int itask_equals(itask_t a, itask_t b)
{
   
   return pthread_equal((pthread_t) a, (pthread_t) b);
   
}


CLASS_DECL_ACME int htask_equals(itask_t a, itask_t b)
{
   
   return pthread_equal((pthread_t) a, (pthread_t) b);
   
}


namespace parallelization
{



   CLASS_DECL_ACME bool set_priority(::enum_priority epriority)
   {

      return set_priority(get_current_htask(), epriority);

   }


   CLASS_DECL_ACME bool set_priority(htask_t htask, enum_priority epriority)
   {

      i32 iPolicy;

      sched_param schedparam;

      thread_get_os_priority(&iPolicy, &schedparam, epriority);

      pthread_setschedparam((pthread_t)htask, iPolicy, &schedparam);

      return true;

   }



   CLASS_DECL_ACME ::enum_priority get_priority()
   {

      return get_priority(get_current_htask());

   }


   ::enum_priority get_priority(htask_t htask)
   {

      int iOsPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      pthread_getschedparam((pthread_t)htask, &iOsPolicy, &schedparam);

      return thread_get_scheduling_priority(iOsPolicy, &schedparam);

   }


} // namespace parallelization



