// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "framework.h"
#include "_.h"
#include "acme/parallelization/message_queue.h"
#include "acme/operating_system/cross/windows/windows_thread_impl.h"


#undef ::apexacmesystem()

#pragma push_macro("::apexacmesystem()")
#undef ::apexacmesystem()
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::apexacmesystem()::Threading;
#pragma pop_macro("::apexacmesystem()")


::pointer< ::mutex > g_pmutexThreadIdHandleLock = nullptr;
::pointer< ::mutex > g_pmutexThreadIdLock = nullptr;


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
//htask_t start_thread(u32 ( * pfn)(void *), void * pv, int iPriority)
//{
//
//   __UNREFERENCED_PARAMETER(iPriority);
//
//   return create_thread(pfn, pv);
//
//}


//void attach_thread_input_to_main_thread(int_bool bAttach)
//{
//
//}


void _on_apex_thread_detach()
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


// void __node_init_multitasking()
// {

//    __node_init_cross_windows_threading();

// }


// void __node_term_multitasking()
// {

//    __node_term_cross_windows_threading();

// }

//thread_int_ptr < HRESULT > thread_set("hresult_co_initialize");

bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //thread_shutdown();

   if(SUCCEEDED(thread_property("hresult_co_initialize").i64()))
   {

      CoUninitialize();

   }

   return true;

}

#pragma warning (disable : 4273)

CLASS_DECL_APEX DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount, const HANDLE* pHandles, BOOL fWaitAll, DWORD dw::durations, DWORD dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(nCount, pHandles, dw::durations, dwWakeMask | (fWaitAll ? MWMO_WAITALL: 0), 0);

}


//CLASS_DECL_APEX ::u32 WINAPI MsgWaitForMultipleObjectsEx(::u32 nCount, const HANDLE* pHandles, ::u32 dw::durations, ::u32 dwWakeMask, ::u32 dwFlags)
//{
//
//   ::u32 dwResult = 0;
//
//   if (dwWakeMask & MWMO_ALERTABLE)
//   {
//
//      HANDLE* ph = memory_new HANDLE[nCount + 1];
//
//      ::memcpy_dup(ph, pHandles, sizeof(HANDLE) * nCount);
//
//      ph[nCount] = (HANDLE)::get_message_queue(get_current_itask(), true)->m_eventNewMessage.hsync();
//
//      dwResult = ::WaitForMultipleObjectsEx(nCount + 1, ph, dwFlags & MWMO_WAITALL, dw::durations, true);
//
//      delete ph;
//
//   }
//   else
//   {
//
//      dwResult = ::WaitForMultipleObjectsEx(nCount, pHandles, dwFlags, dw::durations, false);
//
//   }
//
//   return dwResult;
//
//}
//



void _on_os_htask_end()
{

}


//itask_t get_current_itask()
//{
//
//   return ::GetCurrentThreadId();
//
//}
//
//
//htask_t get_current_htask()
//{
//
//   return ::GetCurrentThread();
//
//}


htask_t g_hMainThread = nullptr;
::u32 g_iMainThread = -1;


void set_main_user_htask(htask_t htask)
{

   g_hMainThread = htask;

}


void set_main_user_itask(itask_t itask)
{

   g_iMainThread = itask;

}


htask_t get_main_user_htask()
{

   return g_hMainThread;

}


::u32   get_main_user_itask()
{

   return g_iMainThread;

}





// void __node_init_cross_windows_threading()
// {

// }


// void __node_term_cross_windows_threading()
// {

// }

