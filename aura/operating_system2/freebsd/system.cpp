//
// Created by camilo on 29/12/2020. 17:14 BRT <3ThomasBS_, Mummi and bilbo!!
// (as caThworansfer (also fun :/ ... few times... so seriously F****) from aura/os/application_system_run.cpp)
#include "framework.h"
#include "aura/operating_system/linux/_user.h"
////#include "aura/user/user/_component.h"
//#include <gtk/gtk.h>
////#include "sn/sn.h"
//#include "apex/platform/app_core.h"
//#include "apex/os/linux/gnome_apex_application.h"
#include "aura/user/user/message_box.h"




//#ifndef RASPBERRYPIOS
//
//SnLauncheeContext* g_psncontext = nullptr;
//
//void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);
//
//void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
////
////namespace aura
////{
////
//
////   void system::os_application_system_run()
////   {
////
////
////
////      auto estatus = ::apex::system::os_application_system_run();
////
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
////
////   }
//
//
//
//#endif // !RASPBERRYPIOS





//void app_core::system_start()
//{
//
//   ::e_status estatus = system_pre_run();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   auto psystem = get_context_system();
//
//   psystem->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   if (m_pmainstruct->m_bConsole)
//   {
//
//      psystem->get_session()->set_context_app(psystem->acmeapplication());
//
//      psystem->set_context_app(psystem->acmeapplication());
//
//      psystem->get_session()->set_context(psystem->acmeapplication());
//
//      psystem->set_context(psystem->acmeapplication());
//
//   }
//
//
//
//   return estatus;
//
//}
//#ifdef LINUX
//i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
//#endif


//void x11_add_gdk_filter();


namespace aura
{


   // void system::system_main()
   // {

   //    auto estatus = ::apex::system::system_main();

   //    if(!estatus)
   //    {

   //       return estatus;

   //    }

   //    return estatus;

   // }

//   void system::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, const future & process)
//   {
//
//      auto psession = get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = puser->windowing();
//
//      if(!pwindowing)
//      {
//
//         return ::error_no_windowing;
//
//      }
//
//      string strMessage(pszMessage);
//
//      string strTitle(pszTitle);
//
//      fork([strMessage, strTitle, emessagebox, process, pwindowing]()
//      {
//
//         auto result = pwindowing->message_box(strMessage, strTitle, emessagebox);
//
//         process(result);
//
//      });
//
//      return ::success;
//
//   }


//   void system::message_box_timeout(const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, const future & process)
//   {
//
//      auto psession = get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = puser->windowing();
//
//      if(!pwindowing)
//      {
//
//         return ::error_no_windowing;
//
//      }
//
//      string strMessage(pszMessage);
//
//      string strTitle(pszTitle);
//
//      fork([strMessage, strTitle, timeTimeout,  emessagebox, process, pwindowing]()
//           {
//
//              auto result = pwindowing->message_box_timeout(strMessage, strTitle, timeTimeout, emessagebox);
//
//              process(result);
//
//           });
//
//      return ::success;
//
//   }


} // namespace aura


void sn_start_context();


bool os_init_application()
{

//#ifndef RASPBERRYPIOS
//
//   sn_start_context();
//
//#endif

   return true;

}


