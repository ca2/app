#include "framework.h"
#include "acme/operating_system.h"


static HANDLE g_hMainThread = nullptr;
static itask_t g_iMainThread = -1;

void set_main_hthread(htask_t hthread)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_hMainThread = (HANDLE) hthread;

}


void set_main_ithread(itask_t itask)
{

   MSG msg;

   PeekMessage(&msg,nullptr,0,0xffffffff,false);

   g_iMainThread = itask;

}


htask_t get_main_hthread()
{

   return (htask_t) g_hMainThread;

}


itask_t get_main_ithread()
{

   return (itask_t) g_iMainThread;

}


void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   if (bAttach)
   {

      PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   }

   AttachThreadInput(::GetCurrentThreadId(), (DWORD) get_main_ithread(),bAttach ? true : false);

}


htask_t get_current_hthread()
{

   return (htask_t) ::GetCurrentThread();

}


itask_t get_current_ithread()
{

   return (itask_t) ::GetCurrentThreadId();

}



bool on_init_timer_thread()
{

   return true;

}



