#include "framework.h"
#include "acme/operating_system.h"


static HANDLE g_hMainThread = nullptr;
static itask_t g_iMainThread = -1;

void set_main_user_htask(htask_t htask)
{

   MSG msg;

   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_hMainThread = (HANDLE)htask;

}


void set_main_user_itask(itask_t itask)
{

   MSG msg;

   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   g_iMainThread = itask;

}


htask_t get_main_user_htask()
{

   return (htask_t)g_hMainThread;

}


itask_t get_main_user_itask()
{

   return (itask_t)g_iMainThread;

}


//
//htask_t get_current_htask()
//{
//
//   return (htask_t) ::GetCurrentThread();
//
//}
//
//
//itask_t get_current_itask()
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


CLASS_DECL_ACME ::acme::system * get_system();


CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure)
{

   auto psystem = get_system();

   psystem->fork([procedure]()
      {

         procedure();

      });

}


namespace acme
{


   void system::windowing_post(const ::procedure & procedure)
   {

      main_asynchronous(procedure);

   }


} // namespace acme



