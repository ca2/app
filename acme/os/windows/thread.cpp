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
static ::u32 g_iMainThread = -1;

void set_main_hthread(hthread_t hthread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,FALSE);

   g_hMainThread = hthread;

}

void set_main_ithread(ithread_t ithread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,FALSE);

   g_iMainThread = ithread;

}


HANDLE get_main_hthread()
{
   return g_hMainThread;

}
::u32   get_main_ithread()
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

   AttachThreadInput(::GetCurrentThreadId(),get_main_ithread(),bAttach ? TRUE : FALSE);

}


hthread_t get_current_hthread()
{

   return ::GetCurrentThread();

}


ithread_t get_current_ithread()
{

   return ::GetCurrentThreadId();

}



bool on_init_timer_thread()
{

   return true;

}



