#include "framework.h"






//#include "framework.h"
//
//
//
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


static HANDLE g_hMainThread = nullptr;
static UINT g_iMainThread = -1;

void set_main_thread(HANDLE hThread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,FALSE);

   g_hMainThread = hThread;

}

void set_main_thread_id(UINT uiThread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,FALSE);

   g_iMainThread = uiThread;

}


HANDLE get_main_thread()
{
   return g_hMainThread;

}
UINT   get_main_thread_id()
{
   return g_iMainThread;
}


void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   if (bAttach)
   {

      PeekMessage(&msg, nullptr, 0, 0xffffffff, FALSE);

   }

   AttachThreadInput(::GetCurrentThreadId(),get_main_thread_id(),bAttach ? TRUE : FALSE);

}


HTHREAD get_current_hthread()
{

   return ::GetCurrentThread();

}


ITHREAD get_current_ithread()
{

   return ::GetCurrentThreadId();

}



bool on_init_timer_thread()
{

   return true;

}



bool on_init_thread()
{

   SetThreadLocale(65001);

   
   //attach_thread_input_to_main_thread();
   

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

}



void __node_term_multithreading()
{

}



//extern CLASS_DECL_AQUA thread_int_ptr < HRESULT > thread_set("hresult_co_initialize");



bool __os_init_thread()
{


   //thread_set("hresult_co_initialize") = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);

   //if(FAILED(thread_set("hresult_co_initialize")))
   ////{

   ////   if(thread_set("hresult_co_initialize").operator HRESULT() == RPC_E_CHANGED_MODE)
   ////   {

   ////      thread_set("hresult_co_initialize") = ::CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED);

   ////      if(FAILED(thread_set("hresult_co_initialize")))
   ////      {

   ////         ::message_box(nullptr,"Failed to ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);

   ////         return false;

   ////      }

   ////   }
   ////   else
   ////   {

   ////      ::message_box(nullptr,"Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);

   ////      return false;

   ////   }

   ////}

   return true;

}



bool __os_term_thread()
{

   auto pthread = ::get_thread();

   if(pthread)
   {
   
      if (pthread->m_bCoInitialize)
      {

         pthread->m_bCoInitialize = false;

         if (SUCCEEDED(pthread->m_hresultCoInitialize))
         {

            CoUninitialize();

         }

      }

   }

   return true;

}


//void _on_os_hthread_end(int iRet)
//{
//
//   // allow C-runtime to cleanup, and exit the thread
//   try
//   {
//
//      _endthreadex(iRet);
//
//   }
//   catch(...)
//   {
//
//   }
//
//}

// CLASS_DECL_AQUA u32 thread_alloc()
// {

//    return (u32) TlsAlloc();

// }


// CLASS_DECL_AQUA void * thread_get_data(u32 uiIndex)
// {

//    return (void *) TlsGetValue((DWORD) uiIndex);

// }


// CLASS_DECL_AQUA i32 thread_set_data(u32 uiIndex, void * pvalue)
// {

//    return TlsSetValue((DWORD)uiIndex, (LPVOID) pvalue);

// }


// CLASS_DECL_AQUA int_bool thread_free(u32 uiIndex)
// {

//    return TlsFree((DWORD) uiIndex);

// }


// CLASS_DECL_AQUA void thread_shutdown()
// {

// }


// LPVOID thread_data_get(thread_data_index dwIndex)
// {

//    return TlsGetValue(dwIndex);

// }


// int_bool thread_data_set(thread_data_index dwIndex, void* pvalue)
// {

//    return TlsSetValue(dwIndex, pvalue);


// }


// thread_data_index thread_data_allocate()
// {

//    return TlsAlloc();

// }


// int_bool thread_data_free(thread_data_index dwIndex)
// {

//    return TlsFree(dwIndex);

// }



