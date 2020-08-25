// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "framework.h"
#include "_.h"
#include "aura/platform/mq.h"


#undef System

#pragma push_macro("System")
#undef System
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
#pragma pop_macro("System")


::mutex * g_pmutexThreadIdHandleLock = nullptr;
::mutex * g_pmutexThreadIdLock = nullptr;


//thread_data::thread_data()
//{
//
//   m_dwIndex = thread_alloc();
//
//}
//
//
//thread_data::~thread_data()
//{
//
//   thread_free(m_dwIndex);
//
//}
//
//
//void * thread_data::get()
//{
//
//   return thread_data_get(m_dwIndex);
//
//}
//
//
//void thread_data::set(void * p)
//{
//
//   thread_set_data(m_dwIndex,(LPVOID)p);
//
//}


// Converts a Win32 thread priority to WinRT format.
WorkItemPriority GetWorkItemPriority(int nPriority)
{
   if (nPriority < 0)
      return WorkItemPriority::Low;
   else if (nPriority > 0)
      return WorkItemPriority::High;
   else
      return WorkItemPriority::Normal;
}

//
//HTHREAD start_thread(u32 ( * pfn)(void *), void * pv, int iPriority)
//{
//
//   UNREFERENCED_PARAMETER(iPriority);
//
//   return create_thread(pfn, pv);
//
//}


void attach_thread_input_to_main_thread(int_bool bAttach)
{

}


void _on_aura_thread_detach()
{

}




bool on_init_thread()
{

   if(!__os_init_thread())
   {

      return false;

   }

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}


void __node_init_multithreading()
{

   __node_init_cross_windows_threading();

}


void __node_term_multithreading()
{

   __node_term_cross_windows_threading();

}

//thread_int_ptr < HRESULT > thread_set("hresult_co_initialize");

bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   if(SUCCEEDED(thread_value("hresult_co_initialize").i64()))
   {

      CoUninitialize();

   }

   return true;

}

#pragma warning (disable : 4273)

CLASS_DECL_CORE DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount, const HANDLE* pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(nCount, pHandles, dwMilliseconds, dwWakeMask | (fWaitAll ? MWMO_WAITALL: 0), 0);

}


CLASS_DECL_CORE DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount, const HANDLE* pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
{

   DWORD dwResult = 0;

   if (dwWakeMask & MWMO_ALERTABLE)
   {

      HANDLE* ph = new HANDLE[nCount + 1];

      ::memcpy_dup(ph, pHandles, sizeof(HANDLE) * nCount);

      ph[nCount] = (HANDLE)::get_mq(get_current_ithread(), true)->m_eventNewMessage.hsync();

      dwResult = ::WaitForMultipleObjectsEx(nCount + 1, ph, dwFlags & MWMO_WAITALL, dwMilliseconds, TRUE);

      delete ph;

   }
   else
   {

      dwResult = ::WaitForMultipleObjectsEx(nCount, pHandles, dwFlags, dwMilliseconds, FALSE);

   }

   return dwResult;

}




void _on_os_hthread_end()
{

}


ITHREAD get_current_ithread()
{

   return ::GetCurrentThreadId();

}


HTHREAD get_current_hthread()
{

   return ::GetCurrentThread();

}


HTHREAD g_hMainThread = nullptr;
UINT g_iMainThread = -1;


void set_main_thread(HTHREAD hThread)
{

   g_hMainThread = hThread;

}


void set_main_thread_id(UINT uiThread)
{

   g_iMainThread = uiThread;

}


HTHREAD get_main_thread()
{

   return g_hMainThread;

}


UINT   get_main_thread_id()
{

   return g_iMainThread;

}



