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
//DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, HSYNC * pwaitableptra, DWORD dwTimeout, DWORD UNUSED(dwWakeMask), DWORD dwFlags)
//{
//
//   DWORD start = 0;
//
//   if(dwTimeout != (DWORD) INFINITE)
//   {
//      start = ::get_tick();
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
//         if(dwTimeout != (DWORD) INFINITE && ::get_tick() - start >= dwTimeout)
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
//            if(dwTimeout != (DWORD) INFINITE && ::get_tick() - start >= dwTimeout)
//            {
//               return WAIT_TIMEOUT;
//            }
//            if(pwaitableptra[i]->lock(millis(0)))
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
//DWORD MsgWaitForMultipleObjects(DWORD dwSize, HSYNC * pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask)
//{
//
//   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));
//
//}
//
//
//DWORD WaitForMultipleObjectsEx(DWORD dwSize, HSYNC * pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, WINBOOL bAlertable)
//{
//
//   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));
//
//}
//
//
//DWORD WaitForMultipleObjects(DWORD dwSize, HSYNC * pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout)
//{
//
//   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, FALSE);
//
//}
//
//
//DWORD WaitForSingleObjectEx(HSYNC  pwaitable, DWORD dwTimeout, WINBOOL bAlertable)
//{
//
//   return WaitForMultipleObjectsEx(1, &pwaitable, TRUE, dwTimeout, bAlertable);
//
//}
//
//
//DWORD WaitForSingleObject(HSYNC  pwaitable, DWORD dwTimeout)
//{
//
//   return WaitForSingleObjectEx(pwaitable, dwTimeout, FALSE);
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
//CLASS_DECL_ACME HTHREAD get_current_hthread()
//{
//
//   return ::GetCurrentThread();
//
//}
//
//
////CLASS_DECL_ACME pDWORD get_current_ithread()
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
////thread_int_ptr < DWORD > currentThreadId;
////thread_pointer < hthread > currentThread;
////thread_pointer < os_thread > t_posthread;
//
//
////raw_array<DWORD> * freeTlsIndices = NULL;
////mutex * g_pmutexTlsData = NULL;
//
//
////map < HTHREAD,HTHREAD,HTHREAD,HTHREAD > * s_pmapHthreadHthread = NULL;
////map < DWORD,DWORD,HTHREAD,HTHREAD > * s_pmapDwordHthread = NULL;
////map < HTHREAD,HTHREAD,DWORD,DWORD > * s_pmapHthreadDword = NULL;
////map < HTHREAD,HTHREAD,ThreadLocalData *,ThreadLocalData * > * allthreaddata = NULL;
//
//
//
//
//
//
//void __node_init_multithreading()
//{
//
//   //s_pmapHthreadHthread = new map < HTHREAD,HTHREAD,HTHREAD,HTHREAD >();
//
//   //s_pmapDwordHthread = new map < DWORD,DWORD,HTHREAD,HTHREAD >();
//
//   //s_pmapHthreadDword = new map < HTHREAD,HTHREAD,DWORD,DWORD >();
//
//   //allthreaddata = new map < HTHREAD,HTHREAD,ThreadLocalData *,ThreadLocalData * >();
//
//   //freeTlsIndices = new raw_array<DWORD>();
//
//
//}
//
//
//
//void __node_term_multithreading()
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
//bool axis_defer_process_x_message(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek);
//
//#endif
//
//
//
//extern "C"
//void * os_thread_thread_proc(LPVOID lpparameter);
//
//
//mq::mq()
//{
//
//}
//
//
//
//
//
//
////map < HTHREAD,HTHREAD,PendingThreadInfo,PendingThreadInfo > * g_ppendingThreads = NULL;
////
////mutex * g_pmutexPendingThreadsLock = NULL;
////
////mutex * g_pmutexThreadHandleLock = NULL;
////
////mutex * g_pmutexThreadIdHandleLock = NULL;
////
////mutex * g_pmutexThreadIdLock = NULL;
////
////map < HTHREAD,HTHREAD,PendingThreadInfo,PendingThreadInfo > & pendingThreads()
////{
////
////   return * g_ppendingThreads;
////
////}
//
//
//
////map < HTHREAD,HTHREAD,HTHREAD,HTHREAD > & thread_handle_map()
////{
////
////   return *s_pmapHthreadHthread;
////
////}
////
////map < DWORD,DWORD,HTHREAD,HTHREAD > & thread_id_handle_map()
////{
////
////   return *s_pmapDwordHthread;
////
////}
////
////
////map < HTHREAD,HTHREAD,DWORD,DWORD > & thread_id_map()
////{
////
////   return *s_pmapHthreadDword;
////
////}
////
////DWORD DwThreadId()
////{
////   static DWORD g_dw_thread_id = 0;
////
////   if(g_dw_thread_id <= 0)
////      g_dw_thread_id = 1;
////
////   return g_dw_thread_id++;
////}
////
////
////
////static DWORD nextTlsIndex = 0;
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
////thread * StartThread(LPTHREAD_START_ROUTINE pfn,LPVOID pv,HTHREAD hthread,i32 nPriority,SIZE_T cbStack)
////{
////
////   os_thread * pthread = new os_thread(pfn,pv);
////
////   pthread->m_hthread = hthread;
////
////   hthread->m_posthread = pthread;
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
////HTHREAD WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes,uptr cbStack,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,u32 dwCreationFlags,u32 * lpdwThreadId)
////{
////   // Validate parameters.
////   //   assert(unusedThreadAttributes == nullptr);
////   //   assert(unusedStackSize == 0);
////   //assert((dwCreationFlags & ~CREATE_SUSPENDED) == 0);
////   //assert(unusedThreadId == nullptr);
////
////   // Create a handle that will be signalled when the thread has completed
////   HTHREAD threadHandle = new hthread();
////
////   if(threadHandle == NULL)
////      return NULL;
////
////
////   sync_lock mlThreadId(g_pmutexThreadIdLock);
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
////   sync_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);
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
////   //   sync_lock mlThreadHandle(threadHandleLock);
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
////         info.m_hthread    = threadHandle;
////         info.suspensionEvent    = new event(get_thread_app(),false,true);
////         info.nPriority = 0;
////
////         sync_lock lock(g_pmutexPendingThreadsLock);
////
////         pendingThreads()[threadHandle] = info;
////
////         //::WaitForSingleObjectEx(info.suspensionEvent, INFINITE, FALSE);
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
////DWORD WINAPI ResumeThread(HTHREAD hThread)
////{
////   sync_lock lock(g_pmutexPendingThreadsLock);
////
////   // Look up the requested thread.
////   map < HTHREAD,HTHREAD,PendingThreadInfo,PendingThreadInfo >::pair * threadInfo = pendingThreads().plookup(hThread);
////
////   if(threadInfo == NULL)
////   {
////      // Can only resume threads while they are in CREATE_SUSPENDED state.
////      //assert(false);
////      return (DWORD)-1;
////   }
////
////   // Start the thread.
////   try
////   {
////      PendingThreadInfo& info = threadInfo->m_element2;
////
////      StartThread(info.lpStartAddress,info.lpParameter,info.m_hthread,info.nPriority,info.cbStack);
////   }
////   catch(...)
////   {
////      return (DWORD)-1;
////   }
////
////   // Remove this thread from the pending list.
////   pendingThreads().remove_key(hThread);
////
////   return 0;
////}
////
////
////int_bool WINAPI SetThreadPriority(HTHREAD hThread,i32 nCa2Priority)
////{
////
////   sync_lock lock(g_pmutexPendingThreadsLock);
////
////   // Look up the requested thread.
////   map < HTHREAD,HTHREAD,PendingThreadInfo,PendingThreadInfo >::pair * threadInfo = pendingThreads().plookup(hThread);
////
////   if(threadInfo == NULL)
////   {
////
////      i32 iPolicy;
////
////      sched_param schedparam;
////
////      thread_get_os_priority(&iPolicy,&schedparam,nCa2Priority);
////
////      pthread_setschedparam(hThread->m_posthread->m_pthread,iPolicy,&schedparam);
////
////      return TRUE;
////
////   }
////
////   // Store the new priority.
////   threadInfo->m_element2.nPriority = nCa2Priority;
////
////   return TRUE;
////}
////
////
////
////
////DWORD WINAPI TlsAlloc()
////{
////
////   sync_lock lock(g_pmutexTlsData);
////
////   // Can we reuse a previously freed TLS slot?
////   if(freeTlsIndices->get_count() > 0)
////   {
////      DWORD result = freeTlsIndices->element_at(freeTlsIndices->get_count() - 1);
////      freeTlsIndices->remove_at(freeTlsIndices->get_count() - 1);
////      return result;
////   }
////
////   // Allocate a new TLS slot.
////   return nextTlsIndex++;
////}
////
////
////int_bool WINAPI TlsFree(DWORD dwTlsIndex)
////{
////
////   sync_lock lock(g_pmutexTlsData);
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
////      HTHREAD hThread;
////
////      ThreadLocalData * pdata;
////
////      allthreaddata->get_next_assoc(pos,hThread,pdata);
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
////LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex)
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
////LPVOID WINAPI TlsGetValue(HTHREAD hthread,DWORD dwTlsIndex)
////{
////
////   try
////   {
////
////      sync_lock lock(g_pmutexTlsData);
////
////      if(allthreaddata->is_empty())
////         return NULL;
////
////      ThreadLocalData * threadData = allthreaddata->operator [] (hthread);
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
////int_bool WINAPI TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue)
////{
////
////   ThreadLocalData* threadData = currentThreadData;
////
////   if(!threadData)
////   {
////      // First time allocation of TLS data for this thread.
////      try
////      {
////         threadData = new ThreadLocalData;
////
////         sync_lock lock(g_pmutexTlsData);
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
////   // Store the new value for this slot.
////   threadData->set_at_grow(dwTlsIndex,lpTlsValue);
////
////   return true;
////}
////
////int_bool WINAPI TlsSetValue(HTHREAD hthread,DWORD dwTlsIndex,LPVOID lpTlsValue)
////{
////
////   sync_lock lock(g_pmutexTlsData);
////
////   ThreadLocalData * threadData = allthreaddata->operator [] (hthread);
////
////   if(!threadData)
////   {
////      // First time allocation of TLS data for this thread.
////      try
////      {
////         threadData = new ThreadLocalData;
////
////         allthreaddata->set_at(hthread,threadData);
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
////   // Store the new value for this slot.
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
////      sync_lock ml(g_pmutexTlsData);
////
////      allthreaddata->remove_key(currentThread);
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
////i32 WINAPI GetThreadPriority(HTHREAD  hthread)
////{
////
////   sync_lock lock(g_pmutexPendingThreadsLock);
////
////   // Look up the requested thread.
////   map < HTHREAD,HTHREAD,PendingThreadInfo,PendingThreadInfo >::pair * threadInfo = pendingThreads().plookup(hthread);
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
////      pthread_getschedparam(hthread->m_posthread->m_pthread,&iOsPolicy,&schedparam);
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
////   sync_lock ml(&*s_pmutex);
////
////   s_pptra->add(this);
////
////}
////
////
////os_thread::~os_thread()
////{
////
////   sync_lock ml(&*s_pmutex);
////
////   for(index i = s_pptra->get_count() - 1; i >= 0; i--)
////   {
////
////      if(s_pptra->element_at(i) == this)
////      {
////
////         s_pptra->remove_at(i);
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
////         sync_lock ml(&*s_pmutex);
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
////      Sleep(184);
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
////   sync_lock mlThreadHandle(g_pmutexThreadHandleLock);
////
////   currentThread =  m_hthread;
////
////   mlThreadHandle.unlock();
////
////   sync_lock mlThreadId(g_pmutexThreadIdLock);
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
////   DWORD dwRet = 0xffffffff;
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
////HTHREAD start_thread(DWORD(WINAPI * pfn)(LPVOID),LPVOID pv,i32 iPriority)
////{
////
////   UNREFERENCED_PARAMETER(iPriority);
////
////   return create_thread(NULL,0,pfn,pv,0,NULL);
////
////}
////
////HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa,uptr cbStack,LPTHREAD_START_ROUTINE pfn,LPVOID pv,u32 f,u32 * lpdwId)
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
////static UINT g_iMainThread = -1;
////
////CLASS_DECL_ACME void set_main_thread(HANDLE hThread)
////{
////
////   //   MESSAGE msg;
////
////   throw "todo"; // PeekMessage function used to create message queue Windows Desktop
////
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);
////
////   g_hMainThread = hThread;
////
////}
////
////CLASS_DECL_ACME void set_main_thread_id(UINT uiThread)
////{
////
////   //   MESSAGE msg;
////
////   throw "todo"; // PeekMessage function used to create message queue Windows Desktop
////
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);
////
////   g_iMainThread = uiThread;
////
////}
////
////
////CLASS_DECL_ACME HANDLE get_main_thread()
////{
////   return g_hMainThread;
////
////}
////CLASS_DECL_ACME UINT   get_main_thread_id()
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
////   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);
////
////   //   AttachThreadInput(::GetCurrentThreadId(), get_main_thread_id(), bAttach ? TRUE : FALSE); // AttachThreadInput function used to attach thread input to main thread in Windows Desktop
////
////}
////*/
////
/////*
////
////DWORD WINAPI thread_layer::proc(LPVOID lp)
////{
////
////   thread_layer * player   = (thread_layer *)lp;
////
////   return player->run();
////
////}
////
////mq * get_mq(HTHREAD  h);
////
////
////mq * get_mq()
////{
////
////   return get_mq(GetCurrentThread());
////
////}
////
////bool is_thread(HTHREAD h)
////{
////   return GetThreadId(h) != 0;
////}
////
////mq * get_mq(HTHREAD  h)
////{
////
////
////   mq * pmq = (mq *)TlsGetValue(h,::multithreading::slot_message_queue);
////
////   if(pmq != NULL)
////      return pmq;
////
////   pmq               = new mq();
////
////   pmq->m_hthread    = h;
////
////   pmq->m_uiId       = ::GetThreadId(h);
////
////   TlsSetValue(h,::multithreading::slot_message_queue,pmq);
////
////   return pmq;
////
////}
////*/
////
////
/////*
////
////CLASS_DECL_ACME DWORD WINAPI GetThreadId(HTHREAD Thread)
////{
////
////   sync_lock mlThreadId(g_pmutexThreadIdLock);
////
////   map < HTHREAD,HTHREAD,DWORD,DWORD >::pair * p = thread_id_map().plookup(Thread);
////
////   if(p == NULL)
////      return -1;
////
////
////   return p->m_element2;
////
////}
////
////CLASS_DECL_ACME HTHREAD  WINAPI get_thread_handle(DWORD dw)
////{
////
////   sync_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);
////
////   map < DWORD,DWORD,HTHREAD,HTHREAD >::pair * p = thread_id_handle_map().plookup(dw);
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
////CLASS_DECL_ACME int_bool WINAPI PostThreadMessageW(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam)
////{
////
////   HTHREAD h = ::get_thread_handle(idThread);
////
////   if(h == NULL)
////      return FALSE;
////
////
////   mq * pmq = get_mq(h);
////
////   if(pmq == NULL)
////      return FALSE;
////
////   sync_lock ml(&pmq->m_mutex);
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
////CLASS_DECL_ACME int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam)
////{
////
////   HTHREAD  h = oswindow->get_user_interaction()->m_papp->get_os_handle();
////
////   if(h == NULL)
////      return FALSE;
////
////
////   mq * pmq = get_mq(h);
////
////   if(pmq == NULL)
////      return FALSE;
////
////   sync_lock ml(&pmq->m_mutex);
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
////void thread_layer::wait_thread(DWORD dwMillis)
////{
////
////   try
////   {
////
////      m_hthread->m_pevent->wait(millis(dwMillis));
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
////   delete m_hthread;
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
////      if(m_bRun && !PeekMessage(&msg,NULL,0,0xffffffffu,TRUE))
////      {
////
////         if(m_bRun && !on_idle())
////         {
////
////            Sleep(m_iSleepiness);
////
////         }
////
////         continue;
////
////      }
////
////      if(msg.message == WM_QUIT)
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
////CLASS_DECL_ACME HTHREAD GetCurrentThread()
////{
////
////   return currentThread;
////
////}
////
////CLASS_DECL_ACME UINT GetCurrentThreadId()
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

WINBOOL TlsSetValue(thread_data_index dwTlsIndex, LPVOID lpTlsValue)
{
	pthread_key_t key;
	key = (pthread_key_t) dwTlsIndex;
	pthread_setspecific(key, lpTlsValue);
	return TRUE;
}

WINBOOL TlsFree(thread_data_index dwTlsIndex)
{
	pthread_key_t key;
	key = (pthread_key_t) dwTlsIndex;
	pthread_key_delete(key);
	return TRUE;
}


#endif




