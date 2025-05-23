#include "framework.h"

//
//#ifdef PARALLELIZATION_PTHREAD
//
//
//#include "acme/operating_system/ansi/_pthread.h"
//
//
//#endif
//
//
//#include "apex/operating_system/ansi/_ansi.h"
//#include "acme/parallelization/message_queue.h"
//#ifdef LINUX
//#include "apex/operating_system/linux/_user.h"
//#endif
//
//
//#ifdef __ANDROID__
//#include <sys/prctl.h>
//#endif
////
//////
//////static __thread char thread_name_buffer[17] = { 0 };
//////
//////const char * thread_name(void)
//////{
//////   /* Try obtaining the thread name.
//////    * If this fails, we'hi return a pointer to an empty string. */
//////   if (!thread_name_buffer[0])
//////      prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);
////
////message_queue * get_message_queue(itask idthread, bool bCreate);
////
////
//CLASS_DECL_APEX void thread_get_os_priority(int * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
////
//CLASS_DECL_APEX void process_get_os_priority(int * piOsPolicy, sched_param * pparam, ::enum_priority epriority);
////
//CLASS_DECL_APEX::enum_priority thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
////
//CLASS_DECL_APEX::enum_priority process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
////
////
////enum_synchronization_result MsgWaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, unsigned int tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags)
////{
////
////   ::duration start;
////
////   if (tickTimeout != (unsigned int)U32_INFINITE_TIMEOUT)
////   {
////
////      start = ::duration::now();
////
////   }
////
////   ::pointer<message_queue>pmq;
////
////   if (dwWakeMask > 0)
////   {
////
////      pmq = ::get_message_queue(current_itask(), false);
////
////   }
////
////   int_bool bWaitForAll = dwFlags & MWMO_WAITALL;
////   //   int_bool bAlertable         = dwFlags & MWMO_ALERTABLE;
////   //   int_bool bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;
////
////   timespec delay;
////
////   delay.tv_sec = 0;
////   delay.tv_nsec = 1000000;
////
////   if (bWaitForAll)
////   {
////
////      int i;
////
////      int j;
////
////      i = 0;
////
////      while (true)
////      {
////
////         for (; comparison::lt(i, dwSize);)
////         {
////
////            if (pmq.is_set())
////            {
////
////               synchronous_lock synchronouslock(pmq->mutex());
////
////               if (pmq->m_messagea.has_element())
////               {
////
////                  return (enum_synchronization_result) (e_synchronization_result_signaled_base + dwSize);
////
////               }
////
////            }
////
////            if (tickTimeout != (unsigned int)U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
////            {
////
////               for (j = 0; j < i; j++)
////               {
////
////                  synca[j]->unlock();
////
////               }
////
////               return e_synchronization_result_error;
////
////            }
////
////            if (synca[i]->lock(0))
////            {
////
////               i++;
////
////            }
////            else
////            {
////
////               nanosleep(&delay, nullptr);
////
////               break;
////
////            }
////
////         }
////
////         if(i >= dwSize)
////         {
////
////            return e_synchronization_result_signaled_base;
////
////         }
////
////      }
////
////   }
////   else
////   {
////
////      int i;
////
////      while (true)
////      {
////
////         if (pmq.is_set())
////         {
////
////            if (pmq->m_happeningNewMessage.lock(::duration(0)))
////            {
////
////               return (enum_synchronization_result) (e_synchronization_result_signaled_base + dwSize);
////
////            }
////
////         }
////
////         for (i = 0; comparison::lt(i, dwSize); i++)
////         {
////
////            if (tickTimeout != (unsigned int)U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
////            {
////
////               return e_synchronization_result_timed_out;
////
////            }
////
////            if (synca[i]->lock(::duration(0)))
////            {
////
////               return (enum_synchronization_result) (e_synchronization_result_signaled_base + i);
////
////            }
////
////         }
////
////         nanosleep(&delay, nullptr);
////
////      }
////
////   }
////
////}
////
////
////::enum_synchronization_result MsgWaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout, unsigned int dwWakeMask)
////{
////
////   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, dwWakeMask, (bWaitForAll ? MWMO_WAITALL : 0));
////
////}
////
////
////::enum_synchronization_result WaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout, int_bool bAlertable)
////{
////
////   return MsgWaitForMultipleObjectsEx(dwSize, synca, tickTimeout, 0, (bWaitForAll ? MWMO_WAITALL : 0) | (bAlertable ? MWMO_ALERTABLE : 0));
////
////}
////
////
////::enum_synchronization_result WaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout)
////{
////
////   return WaitForMultipleObjectsEx(dwSize, synca, bWaitForAll, tickTimeout, false);
////
////}
////
////
////::enum_synchronization_result WaitForSingleObjectEx(hsynchronization hsynchronization, unsigned int tickTimeout, int_bool bAlertable)
////{
////
////   return WaitForMultipleObjectsEx(1, &hsynchronization, true, tickTimeout, bAlertable);
////
////}
////
////
////::enum_synchronization_result WaitForSingleObject(hsynchronization hsynchronization, unsigned int tickTimeout)
////{
////
////   return WaitForSingleObjectEx(hsynchronization, tickTimeout, false);
////
////}
//
//
////thread_data::thread_data()
////{
////
////   pthread_key_create(&m_key, nullptr);
////
////}
////
////
////thread_data::~thread_data()
////{
////
////}
////
////
////void * thread_data::get()
////{
////
////   return pthread_getspecific(m_key);
////
////}
////
////
////void thread_data::set(void * p)
////{
////
////   pthread_setspecific(m_key, p);
////
////}
//
//
//CLASS_DECL_APEX htask current_htask()
//{
//
//   return (htask) ::pthread_self();
//
//}
//
//
//CLASS_DECL_APEX itask current_itask()
//{
//
//   return (itask) ::pthread_self();
//
//}
//
//
//// void __node_init_multitasking()
//// {
//
////    //__node_init_cross_windows_threading();
//
//// }
//
//
//// void __node_term_multitasking()
//// {
//
////    //__node_term_cross_windows_threading();
//
//// }
//
//
//#if defined(LINUX) // || defined(__ANDROID__)
//
//bool (*g_pfn_defer_process_x_message)(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek) = nullptr;
//
//
//bool apex_defer_process_x_message(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek)
//
//{
//
//   if (g_pfn_defer_process_x_message == nullptr)
//      return false;
//
//   return (*g_pfn_defer_process_x_message)(htask, pMsg, oswindow, bPeek);
//
//
//}
//
//void set_defer_process_x_message(bool (*pfn)(htask htask, MESSAGE * pMsg, oswindow oswindow, bool bPeek))
//
//{
//
//   g_pfn_defer_process_x_message = pfn;
//
//}
//
////
////#ifdef LINUX
////
////
////void x11_thread(osdisplay_data * pdisplaydata);
////
////
////#endif
//
//
//#endif
//
//
//extern "C"
//void * os_thread_thread_proc(void * pparameter);
//
////
////namespace parallelization
////{
////
////
////   bool set_priority(htask htask, ::enum_priority epriority)
////   {
////
////      int iPolicy;
////
////      sched_param schedparam;
////
////      thread_get_os_priority(&iPolicy, &schedparam, (::enum_priority)nCa2Priority);
////
////      pthread_setschedparam((pthread_t)htask, iPolicy, &schedparam);
////
////      return true;
////
////   }
////
////
////   enum_priority get_priority(htask  htask)
////   {
////
////      int iOsPolicy = SCHED_OTHER;
////
////      sched_param schedparam;
////
////      schedparam.sched_priority = 0;
////
////      pthread_getschedparam((pthread_t)htask, &iOsPolicy, &schedparam);
////
////      return thread_get_scheduling_priority(iOsPolicy, &schedparam);
////
////   }
////
////
////} // namespace parallelization
//
////
////int get_os_thread_priority(::enum_priority epriority)
////{
////
////   return (int)epriority;
////
////}
////
////
//
//
//
//static htask g_hMainThread = (htask) nullptr;
//
//static itask g_uiMainThread = (itask)-1;
//
//
//CLASS_DECL_APEX void set_main_user_htask(htask htask)
//{
//
//   // MESSAGE msg;
//
//   // PeekMessage function used to create message queue Windows Desktop
//   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);
//
//   g_hMainThread = htask;
//
//}
//
//
//CLASS_DECL_APEX void set_main_user_itask(itask itask)
//{
//
//   //   MESSAGE msg;
//
//   // PeekMessage function used to create message queue Windows Desktop
//   // PeekMessage(&msg, nullptr, 0, 0xffffffff, false);
//
//   g_uiMainThread = itask;
//
//}
//
//
//CLASS_DECL_APEX htask main_user_htask()
//{
//
//   return g_hMainThread;
//
//}
//
//
//CLASS_DECL_APEX itask main_user_itask()
//{
//
//   return g_uiMainThread;
//
//}
//
//
//CLASS_DECL_APEX void attach_thread_input_to_main_thread(bool bAttach)
//{
//
//}
//
//
//
//// LPVOID WINAPI thread_get_data(htask htask, unsigned int dwIndex);
//
//
//// int_bool WINAPI thread_set_data(htask htask, unsigned int dwIndex, LPVOID pTlsValue);
//
//
//
//
//unsigned int g_dwDebug_post_thread_msg_time;
//
//int g_iDebug_post_thread_msg_time;
//
//
//
//
////CLASS_DECL_APEX int_bool WINAPI mq_post(message_queue * pmq, oswindow oswindow, unsigned int Msg, WPARAM wParam, LPARAM lParam)
////CLASS_DECL_APEX int_bool WINAPI mq_post(message_queue * pmq, unsigned int Msg, WPARAM wParam, LPARAM lParam)
////{
////
////   synchronous_lock ml(pmq->mutex());
////
////   MESSAGE msg;
////
////   msg.message = Msg;
////   msg.wParam = wParam;
////   msg.lParam = lParam;
////   msg.pt.x() = I32_MINIMUM;
////   msg.pt.y() = I32_MINIMUM;
////   msg.hwnd = nullptr;
////
////   if (msg.message == e_message_quit)
////   {
////
////      informationf("e_message_quit thread");
////
////   }
////
////   pmq->m_messagea.add(msg);
////
////   pmq->m_happeningNewMessage.set_happening();
////
////   return true;
////
////}
//
//
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
//
//
//
//void get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority)
//{
//
//   int iOsPolicy;
//
//   int iCa2Min;
//
//   int iCa2Max;
//
//   if (epriority == ::e_priority_normal)
//   {
//
//      iOsPolicy = SCHED_OTHER;
//
//      iCa2Min = (int) ::e_priority_normal;
//
//      iCa2Max = (int) ::e_priority_normal;
//
//   }
//   else if (epriority > ::e_priority_normal)
//   {
//
//      iOsPolicy = SCHED_RR;
//
//      iCa2Min = (int) ::e_priority_normal;
//
//      iCa2Max = 99;
//
//   }
//   else
//   {
//
//#if defined(__APPLE__) || defined(FREEBSD)
//      iOsPolicy = SCHED_OTHER;
//#else
//      iOsPolicy = SCHED_IDLE;
//#endif
//
//      iCa2Min = 0;
//
//      iCa2Max = (int) ::e_priority_normal;
//
//   }
//
//   int iOsMax = sched_get_priority_max(iOsPolicy);
//
//   int iOsMin = sched_get_priority_min(iOsPolicy);
//
//   int iOsPriority;
//
//   if (iCa2Min == iCa2Max)
//   {
//      iOsPriority = 0;
//   }
//   else
//   {
//      iOsPriority = (((epriority - iCa2Min) * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
//   }
//
//   iOsPriority = maximum(iOsMin, minimum(iOsMax, iOsPriority));
//
//   *piPolicy = iOsPolicy;
//
//   pparam->sched_priority = iOsPriority;
//
//}
//
//
//void thread_get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority)
//{
//
//   get_os_priority(piPolicy, pparam, epriority);
//
//}
//
//
//::enum_priority get_os_thread_scheduling_priority(int nPriority)
//{
//
//   return (::enum_priority) nPriority;
//
//}
//
//
//#if !defined(__APPLE__) && !defined(__ANDROID__)
//
//string task_get_name()
//{
//
//   char szThreadName[32];
//
//   auto pthread = pthread_self();
//
//   int error = pthread_getname_np(pthread, szThreadName, sizeof(szThreadName));
//
//   if(error)
//   {
//
//      return "";
//
//   }
//
//   return szThreadName;
//
//}
//
//#elif defined(__ANDROID__)
//
//
//
//
//string task_get_name()
//{
//   /* Try obtaining the thread name.
//    * If this fails, we'hi return a pointer to an empty string. */
//   //if (!thread_name_buffer[0])
//   char thread_name_buffer[17] = { 0 };
//   prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);
//
//   return thread_name_buffer;
//
//}
//
//
//#endif
//
//
//
