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



