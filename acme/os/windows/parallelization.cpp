#include "framework.h"
#include "acme/operating_system.h"


static HANDLE g_hMainThread = nullptr;
static ::u32 g_iMainThread = -1;

void set_main_hthread(hthread_t hthread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_hMainThread = (HANDLE) hthread;

}


void set_main_ithread(ithread_t ithread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_iMainThread = ithread;

}


hthread_t get_main_hthread()
{

   return (hthread_t) g_hMainThread;

}


ithread_t get_main_ithread()
{

   return (ithread_t) g_iMainThread;

}


void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   if (bAttach)
   {

      PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   }

   AttachThreadInput(::GetCurrentThreadId(),get_main_ithread(),bAttach ? true : false);

}


hthread_t get_current_hthread()
{

   return (hthread_t) ::GetCurrentThread();

}


ithread_t get_current_ithread()
{

   return (ithread_t) ::GetCurrentThreadId();

}



bool on_init_timer_thread()
{

   return true;

}



