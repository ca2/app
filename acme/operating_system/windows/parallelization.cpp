#include "framework.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/_operating_system.h"


//static HANDLE g_hMainThread = nullptr;
//static itask_t g_iMainThread = -1;
//
//void set_main_user_htask(htask_t htask)
//{
//
//   MSG msg;
//
//   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);
//
//   g_hMainThread = (HANDLE)htask;
//
//}
//

//void set_main_user_itask(itask_t itask)
//{
//
//   MSG msg;
//
//   PeekMessage(&msg, nullptr, 0, 0xffffffff, false);
//
//   g_iMainThread = itask;
//
//}
//

//htask_t main_user_htask()
//{
//
//   return (htask_t)g_hMainThread;
//
//}
//
//
//itask_t main_user_itask()
//{
//
//   return (itask_t)g_iMainThread;
//
//}


//
//htask_t current_htask()
//{
//
//   return (htask_t) ::GetCurrentThread();
//
//}
//
//
//itask_t current_itask()
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


//CLASS_DECL_ACME ::acme::system * system();


CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure)
{

   auto ptask = ::get_task();

   ptask->fork([procedure]()
      {

         procedure();

      });

}


namespace acme
{


   //void system::windowing_post(const ::procedure & procedure)
   //{

   //   main_asynchronous(procedure);

   //}


} // namespace acme



void _do_tasks()
{

   if (is_main_thread())
   {

      auto pwindowing = system()->acme_windowing();

      if (pwindowing)
      {

         pwindowing->process_messages();

      }

   }

   auto pwindowing = system()->acme_windowing();

   if (pwindowing)
   {

      pwindowing->_do_tasks();

   }

}


CLASS_DECL_ACME class ::time default_run_timeout()
{

   class ::time timeDefaultTimeout;

#ifdef DEBUG

   timeDefaultTimeout = 5_min;

#else

   timeDefaultTimeout = 15_s;

#endif

   return timeDefaultTimeout;

}


CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach)
{

   if (bAttach)
   {

      MSG msg;

      PeekMessage(&msg, nullptr, 0, 0xffffffff, PM_NOREMOVE);

   }

   auto idAttach = (DWORD) current_itask();

   auto idAttachTo = (DWORD) main_itask();

   BOOL bOk = ::AttachThreadInput(idAttach, idAttachTo, bAttach ? TRUE : FALSE);

   if (!bOk)
   {

      throw ::exception(error_failed);

   }

}



