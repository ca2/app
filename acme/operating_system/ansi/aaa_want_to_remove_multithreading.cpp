#include "framework.h" // from "axis/user/user.h"
#include "_c.h"
//#include "_ansios.h"
//#include <time.h>
//#include <pthread.h>
//
//
//CLASS_DECL_ACME void thread_get_os_priority(i32 * piOsPolicy, sched_param * pparam, i32 iCa2Priority);
//
//CLASS_DECL_ACME void process_get_os_priority(i32 * piOsPolicy, sched_param * pparam, i32 iCa2Priority);
//
//CLASS_DECL_ACME i32 thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
//
//CLASS_DECL_ACME i32 process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);
//
//
//::u32 MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * pwaitableptra, ::u32 dwTimeout, ::u32 UNUSED(dwWakeMask), ::u32 dwFlags)
//{
//
//   ::u32 start = 0;
//
//   if(dwTimeout != (::u32) U32_INFINITE_TIMEOUT)
//   {
//      start= ::duration::now();
//   }
//
//
//   int_bool bWaitForAll        = dwFlags & MWMO_WAITALL;
////   int_bool bAlertable         = dwFlags & MWMO_ALERTABLE;
////   int_bool bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;
//
//   timespec delay;
//
//   delay.tv_sec = 0;
//   delay.tv_nsec = 1000000;
//
//   if(bWaitForAll)
//   {
//
//      i32 i;
//      i32 j;
//      i = 0;
//      for(; i < dwSize;)
//      {
//         if(dwTimeout != (::u32) U32_INFINITE_TIMEOUT && ::get_tick() - start >= dwTimeout)
//         {
//            return WAIT_TIMEOUT;
//         }
//         if(pwaitableptra[i]->is_locked())
//         {
//            for(j = 0; j < i; j++)
//            {
//               pwaitableptra[j]->unlock();
//            }
//            nanosleep(&delay, NULL);
//            i = 0;
//         }
//         else
//         {
//            pwaitableptra[i]->lock();
//            i++;
//         }
//      }
////      for(j = 0; j < dwSize; j++)
//  //    {
//    //     pwaitableptra[j]->unlock();
//      //}
//
//      return WAIT_OBJECT_0;
//
//   }
//   else
//   {
//
//      i32 i;
////      i32 j;
//      while(true)
//      {
//
//         for(i = 0; i < dwSize;)
//         {
//            if(dwTimeout != (::u32) U32_INFINITE_TIMEOUT && ::get_tick() - start >= dwTimeout)
//            {
//               return WAIT_TIMEOUT;
//            }
//            if(pwaitableptra[i]->lock(::duration(0)))
//            {
//               return WAIT_OBJECT_0 + i;
//            }
//         }
//
//         nanosleep(&delay, NULL);
//
//      }
//
//   }
//
//}
//
//::u32 MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * pwaitableptra, int_bool bWaitForAll, ::u32 dwTimeout, ::u32 dwWakeMask)
//{
//
//   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));
//
//}
//
//
//::u32 WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * pwaitableptra, int_bool bWaitForAll, ::u32 dwTimeout, int_bool bAlertable)
//{
//
//   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));
//
//}
//
//
//::u32 WaitForMultipleObjects(::u32 dwSize, HSYNC * pwaitableptra, int_bool bWaitForAll, ::u32 dwTimeout)
//{
//
//   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, false);
//
//}
//
//
//::u32 WaitForSingleObjectEx(HSYNC  pwaitable, ::u32 dwTimeout, int_bool bAlertable)
//{
//
//   return WaitForMultipleObjectsEx(1, &pwaitable, true, dwTimeout, bAlertable);
//
//}
//
//
//::u32 WaitForSingleObject(HSYNC  pwaitable, ::u32 dwTimeout)
//{
//
//   return WaitForSingleObjectEx(pwaitable, dwTimeout, false);
//
//}
//
//
//
//
////thread_data::thread_data()
////{
////
////   pthread_key_create(&key, NULL);
////
////}
////
////
////void * thread_data::get()
////{
////
////   return pthread_getspecific(key);
////
////}
////
////
////void thread_data::set(void * p)
////{
////
////   pthread_setspecific(key, p);
////
////}
//
//
//
//CLASS_DECL_ACME htask_t get_current_htask()
//{
//
//   return ::GetCurrentThread();
//
//}
//
//
////CLASS_DECL_ACME pDWORD get_current_itask()
////{
////
////   return ::GetCurrentThreadId();
////
////}
//
//
//
////typedef raw_array < void * > ThreadLocalData;
//
//
////
////thread_pointer < ThreadLocalData > currentThreadData;
////thread_int_ptr < ::u32 > currentThreadId;
////thread_pointer < htask > currentThread;
////thread_pointer < os_thread > t_posthread;
//
//
////raw_array<::u32> * freeTlsIndices = NULL;
////mutex * g_pmutexTlsData = NULL;
//
//
////map < htask_t,htask_t,htask_t,htask_t > * s_pmapHthreadHthread = NULL;
////map < ::u32,::u32,htask_t,htask_t > * s_pmapDwordHthread = NULL;
////map < htask_t,htask_t,::u32,::u32 > * s_pmapHthreadDword = NULL;
////map < htask_t,htask_t,ThreadLocalData *,ThreadLocalData * > * allthreaddata = NULL;
//
//
//
//
//
//
//void __node_init_multitasking()
//{
//
//   //s_pmapHthreadHthread = memory_new map < htask_t,htask_t,htask_t,htask_t >();
//
//   //s_pmapDwordHthread = memory_new map < ::u32,::u32,htask_t,htask_t >();
//
//   //s_pmapHthreadDword = memory_new map < htask_t,htask_t,::u32,::u32 >();
//
//   //allthreaddata = memory_new map < htask_t,htask_t,ThreadLocalData *,ThreadLocalData * >();
//
//   //freeTlsIndices = memory_new raw_array<::u32>();
//
//
//}
//
//
//
//void __node_term_multitasking()
//{
//
//   // delete freeTlsIndices;
//
//   // freeTlsIndices = NULL;
//
//   // delete allthreaddata;
//
//   // allthreaddata = NULL;
//
//   // delete s_pmapHthreadDword;
//
//   // s_pmapHthreadDword = NULL;
//
//   // delete s_pmapDwordHthread;
//
//   // s_pmapDwordHthread = NULL;
//
//   // delete s_pmapHthreadHthread;
//
//   // s_pmapHthreadHthread = NULL;
//
//}
//
//
//
//
//
//
//
//
//
//
//#if defined(LINUX) // || defined(ANDROID)
//
//bool axis_defer_process_x_message(htask_t htask,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek);
//
//#endif
//
//
//
//extern "C"
//void * os_thread_thread_proc(LPVOID lpparameter);
//
//
//message_queue::message_queue()
//{
//
//}
//
//
//
//
//
//
////map < htask_t,htask_t,PendingThreadInfo,PendingThreadInfo > * g_ppendingThreads = NULL;
////
////mutex * g_pmutexPendingThreadsLock = NULL;
////
////mutex * g_pmutexThreadHandleLock = NULL;
////
////mutex * g_pmutexThreadIdHandleLock = NULL;
////
////mutex * g_pmutexThreadIdLock = NULL;
////
////map < htask_t,htask_t,PendingThreadInfo,PendingThreadInfo > & pendingThreads()
////{
////
////   return * g_ppendingThreads;
////
////}
//
//
//
////map < htask_t,htask_t,htask_t,htask_t > & thread_handle_map()
////{
////
////   return *s_pmapHthreadHthread;
////
////}
////
////map < ::u32,::u32,htask_t,htask_t > & thread_id_handle_map()
////{
////
////   return *s_pmapDwordHthread;
////
////}
////
////
////map < htask_t,htask_t,::u32,::u32 > & thread_id_map()
////{
////
////   return *s_pmapHthreadDword;
////
////}
////
////::u32 DwThreadId()
////{
////   static ::u32 g_dw_thread_id = 0;
////
////   if(g_dw_thread_id <= 0)
////      g_dw_thread_id = 1;
////
////   return g_dw_thread_id++;
////}
////
////
////
////static ::u32 nextTlsIndex = 0;
//
////mutex * os_thread::s_pmutex = NULL;
////comparable_raw_array < os_thread * >::type * os_thread::s_pptra = NULL;
//
//
//// Converts a Win32 thread priority to WinRT format.
//i32 GetWorkItemPriority(i32 nPriority)
//{
//   if(nPriority < 0)
//      return nPriority; // WorkItemPriority::Low;
//   else if(nPriority > 0)
//      return nPriority; // WorkItemPriority::High;
//   else
//      return nPriority; // WorkItemPriority::Normal;
//}
//
//
//// Helper shared between CreateThread and ResumeThread.
////thread * StartThread(LPTHREAD_START_ROUTINE pfn,LPVOID pv,htask_t htask,i32 nPriority,SIZE_T cbStack)
////{
////
////   os_thread * pthread = memory_new os_thread(pfn,pv);
////
////   pthread->m_htask = htask;
////
////   htask->m_posthread = pthread;
////
////   pthread_t & thread = pthread->m_pthread;
////
////   pthread_attr_t threadAttr;
////
////   pthread_attr_init(&threadAttr);
////
////   if(cbStack > 0)
////   {
////
////      pthread_attr_setstacksize(&threadAttr,120 * 1024); // Set the stack size of the thread
////
////   }
////
////   int iPolicy;
////
////   sched_param schedparam; // scheduling priority
////
////   thread_get_os_priority(&iPolicy,&schedparam,nPriority);
////
////   pthread_attr_setschedpolicy(&threadAttr,iPolicy);
////
////   pthread_attr_setschedparam(&threadAttr,&schedparam);
////
////   pthread_attr_setdetachstate(&threadAttr,PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join
////
////   pthread_create(&thread,&threadAttr,&os_thread_thread_proc,(LPVOID)pthread); // Create the thread
////
////   return pthread;
////
////}
////
//
//
////htask_t WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes,uptr cbStack,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,u32 dwCreationFlags,u32 * lpdwThreadId)
////{
////   // Validate parameters.
////   //   assert(unusedThreadAttributes == nullptr);
////   //   assert(unusedStackSize == 0);
////   //assert((dwCreationFlags & ~CREATE_SUSPENDED) == 0);
////   //assert(unusedThreadId == nullptr);
////
////   // Create a handle that will be signalled when the thread has completed
////   htask_t threadHandle = memory_new htask();
////
////   if(threadHandle == NULL)
////      return NULL;
////
////
////   synchronous_lock mlThreadId(g_pmutexThreadIdLock);
////
////   thread_id_map().set_at(threadHandle,DwThreadId());
////
////   if(lpdwThreadId != NULL)
////   {
////      *lpdwThreadId = thread_id_map()[threadHandle];
////   }
////
////
////
////   synchronous_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);
////
////   thread_id_handle_map().set_at(thread_id_map()[threadHandle],threadHandle);
////
////   mlThreadIdHandle.unlock();
////
////   mlThreadId.unlock();
////
////   // Make a copy of the handle for internal use. This is necessary because
////   // the caller is responsible for closing the handle returned by CreateThread,
////   // and they may do that before or after the thread has finished running.
////   /*HANDLE completionEvent;
////
////   if (!DuplicateHandle(GetCurrentProcess(), threadHandle, GetCurrentProcess(), &completionEvent, 0, false, DUPLICATE_SAME_ACCESS))
////   {
////   CloseHandle(threadHandle);
////   return nullptr;
////   }*/
////
////   //   synchronous_lock mlThreadHandle(threadHandleLock);
////
////   // thread_handle_map().set_at(completionEvent, threadHandle);
////
////   //mlThreadHandle.unlock();
////
////   PendingThreadInfo info;
////
////   ZERO(info);
////
////   try
////   {
////      if(dwCreationFlags & CREATE_SUSPENDED)
////      {
////         // Store info about a suspended thread.
////
////         info.lpStartAddress     = lpStartAddress;
////         info.lpParameter        = lpParameter;
////         info.m_htask    = threadHandle;
////         info.suspensionEvent    = memory_new event(get_thread_app(),false,true);
////         info.nPriority = 0;
////
////         synchronous_lock lock(g_pmutexPendingThreadsLock);
////
////         pendingThreads()[threadHandle] = info;
////
////         //::WaitForSingleObjectEx(info.suspensionEvent, U32_INFINITE_TIMEOUT, false);
////      }
////      else
////      {
////         // Start the thread immediately.
////         StartThread(lpStartAddress,lpParameter,threadHandle,0,cbStack);
////      }
////
////      return threadHandle;
////   }
////   catch(...)
////   {
////      // Clean up if thread creation fails.
////      threadHandle->m_pevent->set_event();
////      delete threadHandle;
////
////      if(info.suspensionEvent)
////      {
////         info.suspensionEvent->set_event();
////         delete info.suspensionEvent;
////      }
////
////
////      return NULL;
////   }
////}
////
////
////::u32 WINAPI ResumeThread(htask_t htask)
////{
////   synchronous_lock lock(g_pmutexPendingThreadsLock);
////
////   // Look up the requested thread.
////   map < htask_t,htask_t,PendingThreadInfo,PendingThreadInfo >::pair * threadInfo = pendingThreads().plookup(htask);
////
////   if(threadInfo == NULL)
////   {
////      // Can only resume threads while they are in CREATE_SUSPENDED state.
////      //assert(false);
////      return (::u32)-1;
////   }
////
////   // Start the thread.
////   try
////   {
////      PendingThreadInfo& info = threadInfo->m_element2;
////
////      StartThread(info.lpStartAddress,info.lpParameter,info.m_htask,info.nPriority,info.cbStack);
////   }
////   catch(...)
////   {
////      return (::u32)-1;
////   }
////
////   // Remove this thread from the pending list.
////   pendingThreads().erase_key(htask);
////
////   return 0;
////}
////
////

////
////
////::u32 WINAPI TlsAlloc()
////{
////
////   synchronous_lock lock(g_pmutexTlsData);
////
////   // Can we reuse a previously freed TLS slot?
////   if(freeTlsIndices->get_count() > 0)
////   {
////      ::u32 result = freeTlsIndices->element_at(freeTlsIndices->get_count() - 1);
////      freeTlsIndices->erase_at(freeTlsIndices->get_count() - 1);
////      return result;
////   }
////
////   // Allocate a memory_new TLS slot.
////   return nextTlsIndex++;
////}
////
////
////int_bool WINAPI TlsFree(::u32 dwTlsIndex)
////{
////
////   synchronous_lock lock(g_pmutexTlsData);
////
////   //assert(dwTlsIndex < nextTlsIndex);
////   /*   for(i32 i = 0; i < freeTlsIndices.get_count(); i++)
////   {
////   assert(freeTlsIndices.element_at(i) != dwTlsIndex);
////   }*/
////
////   // Store this slot for reuse by TlsAlloc.
////   try
////   {
////      freeTlsIndices->add(dwTlsIndex);
////   }
////   catch(...)
////   {
////      return false;
////   }
////
////   // Zero the value for all threads that might be using this now freed slot.
////
////   POSITION pos = allthreaddata->get_start_position();
////   while(pos != NULL)
////   {
////
////      htask_t htask;
////
////      ThreadLocalData * pdata;
////
////      allthreaddata->get_next_assoc(pos,htask,pdata);
////
////      if(pdata->get_count() > dwTlsIndex)
////      {
////         pdata->element_at(dwTlsIndex) = NULL;
////      }
////   }
////
////   return true;
////}
////
////
////LPVOID WINAPI TlsGetValue(::u32 dwTlsIndex)
////{
////   ThreadLocalData* threadData = currentThreadData;
////
////   if(threadData && threadData->get_count() > dwTlsIndex)
////   {
////      // Return the value of an allocated TLS slot.
////      return threadData->element_at(dwTlsIndex);
////   }
////   else
////   {
////      threadData = allthreaddata->operator[](currentThread);
////      if(threadData)
////      {
////         currentThreadData = threadData;
////         if(threadData->get_count() > dwTlsIndex)
////         {
////            return threadData->element_at(dwTlsIndex);
////         }
////      }
////      // Default value for unallocated slots.
////      return NULL;
////   }
////}
////
////
////LPVOID WINAPI TlsGetValue(htask_t htask,::u32 dwTlsIndex)
////{
////
////   try
////   {
////
////      synchronous_lock lock(g_pmutexTlsData);
////
////      if(allthreaddata->is_empty())
////         return NULL;
////
////      ThreadLocalData * threadData = allthreaddata->operator [] (htask);
////
////      if(threadData && threadData->get_count() > dwTlsIndex)
////      {
////
////         // Return the value of an allocated TLS slot.
////         return threadData->element_at(dwTlsIndex);
////
////      }
////      else
////      {
////
////         // Default value for unallocated slots.
////         return NULL;
////
////      }
////
////   }
////   catch(...)
////   {
////
////      return NULL;
////
////   }
////
////}
////
////
////int_bool WINAPI TlsSetValue(::u32 dwTlsIndex,LPVOID lpTlsValue)
////{
////
////   ThreadLocalData* threadData = currentThreadData;
////
////   if(!threadData)
////   {
////      // First time allocation of TLS data for this thread.
////      try
////      {
////         threadData = memory_new ThreadLocalData;
////
////         synchronous_lock lock(g_pmutexTlsData);
////
////         allthreaddata->set_at(currentThread,threadData);
////
////         currentThreadData = threadData;
////
////      }
////      catch(...)
////      {
////         if(threadData)
////            delete threadData;
////
////         return false;
////      }
////   }
////
////   // Store the memory_new value for this slot.
////   threadData->set_at_grow(dwTlsIndex,lpTlsValue);
////
////   return true;
////}
////
////int_bool WINAPI TlsSetValue(htask_t htask,::u32 dwTlsIndex,LPVOID lpTlsValue)
////{
////
////   synchronous_lock lock(g_pmutexTlsData);
////
////   ThreadLocalData * threadData = allthreaddata->operator [] (htask);
////
////   if(!threadData)
////   {
////      // First time allocation of TLS data for this thread.
////      try
////      {
////         threadData = memory_new ThreadLocalData;
////
////         allthreaddata->set_at(htask,threadData);
////
////      }
////      catch(...)
////      {
////         if(threadData)
////            delete threadData;
////
////         return false;
////      }
////   }
////
////   // Store the memory_new value for this slot.
////   threadData->set_at_grow(dwTlsIndex,lpTlsValue);
////
////   return true;
////}
////
////// Called at thread exit to clean up TLS allocations.
////void WINAPI TlsShutdown()
////{
////
////   ThreadLocalData * threadData = currentThreadData;
////
////   if(threadData)
////   {
////
////      /*      try
////      {
////
////      IDWriteFactory * pfactory = TlsGetWriteFactory();
////
////      if(pfactory != NULL)
////      {
////
////      pfactory->Release();
////
////      }
////
////      }
////      catch(...)
////      {
////      }
////
////      try
////      {
////
////      ID2D1Factory1 * pfactory = GetD2D1Factory1();
////
////      if(pfactory != NULL)
////      {
////
////      //pfactory->Release();
////
////      }
////
////      }
////      catch(...)
////      {
////      }
////
////      */
////
////      synchronous_lock ml(g_pmutexTlsData);
////
////      allthreaddata->erase_key(currentThread);
////
////      currentThreadData = NULL;
////
////      delete threadData;
////   }
////}
////
////
////
////
////i32 WINAPI GetThreadPriority(htask_t  htask)
////{
////
////   synchronous_lock lock(g_pmutexPendingThreadsLock);
////
////   // Look up the requested thread.
////   map < htask_t,htask_t,PendingThreadInfo,PendingThreadInfo >::pair * threadInfo = pendingThreads().plookup(htask);
////
////   if(threadInfo == NULL)
////   {
////
////      int iOsPolicy = SCHED_OTHER;
////
////      sched_param schedparam;
////
////      schedparam.sched_priority = 0;
////
////      pthread_getschedparam(htask->m_posthread->m_pthread,&iOsPolicy,&schedparam);
////
////      return thread_get_scheduling_priority(iOsPolicy,&schedparam);
////
////   }
////
////   return threadInfo->m_element2.nPriority;
////
////}
////
////
////
////
////
////os_thread::os_thread(u32(* pfn)(void *),void * pv)
////{
////
////   m_pfn    = pfn;
////   m_pv     = pv;
////   m_bRun   = true;
////
////
////   synchronous_lock ml(&*s_pmutex);
////
////   s_pptra->add(this);
////
////}
////
////
////os_thread::~os_thread()
////{
////
////   synchronous_lock ml(&*s_pmutex);
////
////   for(index i = s_pptra->get_count() - 1; i >= 0; i--)
////   {
////
////      if(s_pptra->element_at(i) == this)
////      {
////
////         s_pptra->erase_at(i);
////
////      }
////
////   }
////
////}
////
////
////os_thread * os_thread::get()
////{
////
////   return t_posthread;
////
////}
////
////void os_thread::set(os_thread * posthread)
////{
////
////   t_posthread = posthread;
////
////}
////
////bool os_thread::get_run()
////{
////
////   return get()->m_bRun;
////
////}
////
////void os_thread::stop_all(u32 millisMaxWait)
////{
////
////   millisMaxWait = millisMaxWait;
////
////   u32 start = get_tick();
////
////   while(get_tick() - start < millisMaxWait)
////   {
////
////      {
////
////         synchronous_lock ml(&*s_pmutex);
////
////         for(int i = 0; i < s_pptra->get_count(); i++)
////         {
////
////            s_pptra->element_at(i)->m_bRun = false;
////
////         }
////
////         if(s_pptra->get_count() <= 0)
////         {
////
////            break;
////
////         }
////
////      }
////
////      sleep(184_ms);
////
////   }
////
////
////}
////
////extern "C"
////void * os_thread_thread_proc(LPVOID lpparameter)
////{
////
////   keep_threading_count keepthreadingcount;
////
////   os_thread * posthread = (os_thread *)lpparameter;
////
////   t_posthread = posthread;
////
////   if(!on_init_thread())
////   {
////
////      return (void *) (iptr) 34;
////
////   }
////
////   void * pvRet = (void *)(iptr)posthread->run();
////
////   t_posthread = NULL;
////
////   on_term_thread();
////
////   delete posthread;
////
////   return pvRet;
////
////}
////
////u32 os_thread::run()
////{
////
////   synchronous_lock mlThreadHandle(g_pmutexThreadHandleLock);
////
////   currentThread =  m_htask;
////
////   mlThreadHandle.unlock();
////
////   synchronous_lock mlThreadId(g_pmutexThreadIdLock);
////
////   currentThreadId =  thread_id_map()[currentThread];
////
////   mlThreadId.unlock();
////
////   mlThreadHandle.unlock();
////
////   // Run the user callback.
////   //attach_thread_input_to_main_thread();
////
////   ::u32 dwRet = 0xffffffff;
////
////   try
////   {
////
////      dwRet = m_pfn(m_pv);
////
////   }
////   catch(...)
////   {
////
////   }
////
////   // Clean up any TLS allocations made by this thread.
////   TlsShutdown();
////
////   // Signal that the thread has completed.
////   currentThread->m_pevent->set_event();
////
////   currentThread->release();
////
////   return dwRet;
////
////}
////
////
////htask_t start_thread(::u32(WINAPI * pfn)(LPVOID),LPVOID pv,i32 iPriority)
////{
////
////   __UNREFERENCED_PARAMETER(iPriority);
////
////   return create_thread(NULL,0,pfn,pv,0,NULL);
////
////}
////
////htask_t create_thread(LPSECURITY_ATTRIBUTES lpsa,uptr cbStack,LPTHREAD_START_ROUTINE pfn,LPVOID pv,u32 f,u32 * lpdwId)
////{
////
////   return ::CreateThread(lpsa,cbStack,pfn,pv,f,lpdwId);
////
////}
////
////
////
////
////
////
////
////static HANDLE g_hMainThread = NULL;
////static ::u32 g_iMainThread = -1;
////
////CLASS_DECL_ACME void set_main_user_htask(htask_t htask)
////{
////
////   //   MESSAGE msg;
////
////   throw "todo"; // PeekMessage function used to create message queue Windows Desktop
////
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, false);
////
////   g_hMainThread = htask;
////
////}
////
////CLASS_DECL_ACME void set_main_user_itask(itask_t itask)
////{
////
////   //   MESSAGE msg;
////
////   throw "todo"; // PeekMessage function used to create message queue Windows Desktop
////
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, false);
////
////   g_iMainThread = itask;
////
////}
////
////
////CLASS_DECL_ACME HANDLE get_main_user_htask()
////{
////   return g_hMainThread;
////
////}
////CLASS_DECL_ACME ::u32   get_main_user_itask()
////{
////   return g_iMainThread;
////}
////
////
////CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
////{
////   return;
////   //   MESSAGE msg;
////
////   // metrowin todo
////   throw "todo"; // PeekMessage function used to create message queue Windows Desktop
////
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, false);
////
////   //   AttachThreadInput(::GetCurrentThreadId(), get_main_user_itask(), bAttach ? true : false); // AttachThreadInput function used to attach thread input to main thread in Windows Desktop
////
////}
////*/
////
/////*
////
////::u32 WINAPI thread_layer::proc(LPVOID lp)
////{
////
////   thread_layer * player   = (thread_layer *)lp;
////
////   return player->run();
////
////}
////
////message_queue * get_message_queue(htask_t  h);
////
////
////message_queue * get_message_queue()
////{
////
////   return get_message_queue(GetCurrentThread());
////
////}
////
////bool is_thread(htask_t h)
////{
////   return GetThreadId(h) != 0;
////}
////
////message_queue * get_message_queue(htask_t  h)
////{
////
////
////   message_queue * pmq = (message_queue *)TlsGetValue(h,::parallelization::slot_message_queue);
////
////   if(pmq != NULL)
////      return pmq;
////
////   pmq               = memory_new message_queue();
////
////   pmq->m_htask    = h;
////
////   pmq->m_uiId       = ::GetThreadId(h);
////
////   TlsSetValue(h,::parallelization::slot_message_queue,pmq);
////
////   return pmq;
////
////}
////*/
////
////
/////*
////
////CLASS_DECL_ACME ::u32 WINAPI GetThreadId(htask_t Thread)
////{
////
////   synchronous_lock mlThreadId(g_pmutexThreadIdLock);
////
////   map < htask_t,htask_t,::u32,::u32 >::pair * p = thread_id_map().plookup(Thread);
////
////   if(p == NULL)
////      return -1;
////
////
////   return p->m_element2;
////
////}
////
////CLASS_DECL_ACME htask_t  WINAPI get_thread_handle(::u32 dw)
////{
////
////   synchronous_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);
////
////   map < ::u32,::u32,htask_t,htask_t >::pair * p = thread_id_handle_map().plookup(dw);
////
////   if(p == NULL)
////      return NULL;
////
////
////   return p->m_element2;
////
////}
////
////*/
////
/////*
////CLASS_DECL_ACME int_bool WINAPI PostThreadMessageW(::u32 idThread,::u32 Msg,WPARAM wParam,LPARAM lParam)
////{
////
////   htask_t h = ::get_thread_handle(idThread);
////
////   if(h == NULL)
////      return false;
////
////
////   message_queue * pmq = get_message_queue(h);
////
////   if(pmq == NULL)
////      return false;
////
////   synchronous_lock ml(&pmq->m_pmutex);
////
////   MESSAGE msg;
////
////   //zero(&msg, sizeof(msg));
////
////   msg.message = Msg;
////   msg.wParam  = wParam;
////   msg.lParam  = lParam;
////   msg.pt.x    = 0x80000000;
////   msg.pt.y    = 0x80000000;
////   msg.hwnd    = NULL;
////
////   pmq->ma.add(msg);
////
////   //   void * p = pmq->ma[pmq->ma.get_count() -1].hwnd;
////
////   pmq->m_eventNewMessage.set_event();
////
////   return true;
////
////}
////*/
////
////CLASS_DECL_ACME int_bool WINAPI PostMessageW(oswindow oswindow,::u32 Msg,WPARAM wParam,LPARAM lParam)
////{
////
////   htask_t  h = oswindow->get_user_interaction()->m_papp->get_os_handle();
////
////   if(h == NULL)
////      return false;
////
////
////   message_queue * pmq = get_message_queue(h);
////
////   if(pmq == NULL)
////      return false;
////
////   synchronous_lock ml(&pmq->m_pmutex);
////
////   MESSAGE msg;
////
////   //zero(&msg, sizeof(msg));
////
////   msg.hwnd       = oswindow;
////   msg.message    = Msg;
////   msg.wParam     = wParam;
////   msg.lParam     = lParam;
////   msg.pt.x       = 0x80000000;
////   msg.pt.y       = 0x80000000;
////
////
////   pmq->ma.add(msg);
////
////   pmq->m_eventNewMessage.set_event();
////
////   return true;
////
////}
////
////
////
////
////
////
////
////void thread_layer::wait_thread(::u32 dwMillis)
////{
////
////   try
////   {
////
////      m_htask->m_pevent->wait(::duration(dwMillis));
////
////   }
////   catch(...)
////   {
////
////   }
////
////}
////
////
////
////
////
////thread_layer::~thread_layer()
////{
////
////   delete m_htask;
////
////}
////
////
////i32 thread_layer::run()
////{
////
////   MESSAGE msg;
////
////   ZERO(msg);
////
////   while(m_bRun)
////   {
////
////      if(m_bRun && !PeekMessage(&msg,NULL,0,0xffffffffu,true))
////      {
////
////         if(m_bRun && !on_idle())
////         {
////
////            sleep(m_iSleepiness);
////
////         }
////
////         continue;
////
////      }
////
////      if(msg.message == e_message_quit)
////         break;
////
////
////      TranslateMessage(&msg);
////
////      DispatchMessage(&msg);
////
////   }
////
////   return m_iResult;
////
////}
////
////bool thread_layer::on_idle()
////{
////
////   return false;
////
////}
////
////
////
////CLASS_DECL_ACME htask_t GetCurrentThread()
////{
////
////   return currentThread;
////
////}
////
////CLASS_DECL_ACME ::u32 GetCurrentThreadId()
////{
////
////   return currentThreadId;
////
////}
////
////
////
////
////
////bool on_init_thread()
////{
////
////   if(!__os_init_thread())
////      return false;
////
////   return true;
////
////}
////
////
////bool on_term_thread()
////{
////
////   bool bOk1 = __os_term_thread();
////
////   return bOk1;
////
////}
////
//
//
//
//
//
//
//
//
////#include <pthread.h>


#ifndef WINDOWS


thread_data_index TlsAlloc(void)
{
	pthread_key_t key;

	if (pthread_key_create(&key, NULL) != 0)
		return -1;

	return key;
}

LPVOID TlsGetValue(thread_data_index dwTlsIndex)
{
	LPVOID value;
	pthread_key_t key;
	key = (pthread_key_t) dwTlsIndex;
	value = (LPVOID) pthread_getspecific(key);
	return value;
}

int_bool TlsSetValue(thread_data_index dwTlsIndex, LPVOID lpTlsValue)
{
	pthread_key_t key;
	key = (pthread_key_t) dwTlsIndex;
	pthread_setspecific(key, lpTlsValue);
	return true;
}

int_bool TlsFree(thread_data_index dwTlsIndex)
{
	pthread_key_t key;
	key = (pthread_key_t) dwTlsIndex;
	pthread_key_delete(key);
	return true;
}


#endif




