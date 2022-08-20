//
// Created by camilo on 29/12/2020. 17:14 BRT <3ThomasBS_, Mummi and bilbo!!
// (as caThworansfer (also fun :/ ... few times... so seriously F****) from aura/os/application_system_run.cpp)
#include "framework.h"
#include "aura/operating_system/linux/_user.h"
#include "aura/user/user/_component.h"
//#include <gtk/gtk.h>
////#include "sn/sn.h"
//#include "apex/platform/app_core.h"
//#include "apex/os/linux/gnome_apex_application.h"
#include "aura/user/user/message_box.h"




//#ifndef RASPBIAN
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
//#endif // !RASPBIAN





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
//      psystem->get_session()->set_context_app(psystem->m_pappStartup);
//
//      psystem->set_context_app(psystem->m_pappStartup);
//
//      psystem->get_session()->set_context(psystem->m_pappStartup);
//
//      psystem->set_context(psystem->m_pappStartup);
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

//    void system::on_start_system()
//    {

// //      auto estatus = ([a-z0-9_]+)_factory("windowing", "x11");
// //
// //      if(!estatus)
// //      {
// //
// //         return estatus;
// //
// //      }

// //      estatus = __construct(m_pwindowing);
// //
// //      if(!estatus)
// //      {
// //
// //         return estatus;
// //
// //      }
// //
// //      estatus = m_pwindowing->process_init();
// //
// //      if(!estatus)
// //      {
// //
// //         return estatus;
// //
// //      }

// //      auto estatus = create_os_node();
// //
// //      if(!estatus)
// //      {
// //
// //         return estatus;
// //
// //      }
// //

//       //   ::e_status estatus = psystem->begin_synch();
//       //
//       //   if(!estatus)
//       //   {
//       //
//       //      return estatus;
//       //
//       //   }
//       //

// //      const char *pszName = m_XstrAppId;

// //      g_set_application_name(pszName);

// //      const char *pszPrgName = m_strProgName;

// //      g_set_prgname(pszPrgName);

//       //auto idle_source = g_idle_source_new();

//       //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);

//       //g_source_attach(idle_source, g_main_context_default());

//       //int c = 2;

//       //const char * argv[]={"app", "--g-fatal-warnings"};
// //
// //#if !defined(__SANITIZE_ADDRESS__)
// //
// //      auto pnode = m_pnode;
// //
// //      if(pnode)
// //      {
// //
// //         if (!pnode->node_init_check(&m_argc, &m_argv))
// //         {
// //
// //            return ::error_failed;
// //
// //         }
// //
// //      }
// //
// //#endif

//       auto estatus = ::apex::system::on_start_system();

//       if(!estatus)
//       {

//          return estatus;

//       }

// //
// //      if (!begin_synch())
// //      {
// //
// //         output_debug_string("\nFailed to begin_synch the system (::aura::system or ::aura::system derived)");
// //
// //         return error_failed;
// //
// //      }
// //
// //      auto psession = get_session();
// //
// //      auto puser = psession->user();
// //
// //      auto pwindowing = puser->windowing();
// //
// //      auto estatus = pwindowing->start();

// //      if (m_bUser)
// //      {
// //
// //         m_pwindowing->os_application_system_run();
// //
// //         if (!XInitThreads())
// //         {
// //
// //            return false;
// //
// //         }
// //
// //         XSetErrorHandler(_c_XErrorHandler);
// //
// //      }
// //
// //      if(pnode)
// //      {
// //
// //         pnode->os_application_system_run();
// //
// //      }
// //      else
// //      {
// //
// //         x11_main();
// //
// //      }

//       //x11_main();
// //      if (m_bGtkApp)
// //      {
// //
// //         apex_application_run(m_XstrAppId, m_strProgName);
// //
// //      }
// //      else
// //      {
// //
// //         //      g_set_application_name(psystem->m_XstrAppId);
// //         //
// //         //      g_set_prgname(psystem->m_strProgName);
// //         //
// //         //      //auto idle_source = g_idle_source_new();
// //         //
// //         //      //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);
// //         //
// //         //      //g_source_attach(idle_source, g_main_context_default());
// //         //
// //         //      //int c = 2;
// //         //
// //         //      //const char * argv[]={"app", "--g-fatal-warnings"};
// //         //
// //         //#if !defined(__SANITIZE_ADDRESS__)
// //         //
// //         //      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
// //         //
// //         //#endif
// //         //x11_add_gdk_filter();
// //         //gtk_main();
// //
// //      }

//       //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

//       return ::success;

//    }


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


//   void system::message_box_timeout(const ::string & pszMessage, const ::string & pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const future & process)
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
//      fork([strMessage, strTitle, durationTimeout,  emessagebox, process, pwindowing]()
//           {
//
//              auto result = pwindowing->message_box_timeout(strMessage, strTitle, durationTimeout, emessagebox);
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

//#ifndef RASPBIAN
//
//   sn_start_context();
//
//#endif

   return true;

}


