#include "framework.h"
#include "acme/operating_system.h"


static HANDLE g_hMainThread = nullptr;
static itask_t g_iMainThread = -1;

void set_main_hthread(htask_t htask)
{

   MSG msg;

   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_hMainThread = (HANDLE)htask;

}


void set_main_ithread(itask_t itask)
{

   MSG msg;

   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_iMainThread = itask;

}


htask_t get_main_hthread()
{

   return (htask_t)g_hMainThread;

}


itask_t get_main_ithread()
{

   return (itask_t)g_iMainThread;

}


//
//htask_t get_current_hthread()
//{
//
//   return (htask_t) ::GetCurrentThread();
//
//}
//
//
//itask_t get_current_ithread()
//{
//
//   return (itask_t) ::GetCurrentThreadId();
//
//}
//


bool on_init_timer_thread()
{

   return true;

}



