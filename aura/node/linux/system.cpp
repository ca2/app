//
// Created by camilo on 29/12/2020. 17:14 BRT <3ThomasBS_, Mummi and bilbo!!
// (as caThworansfer (also fun :/ ... few times... so seriously F****) from aura/os/application_system_run.cpp)
#include "framework.h"
#include "aura/os/linux/_user.h"
#include "aura/user/_user.h"
//#include <gtk/gtk.h>
////#include "third/sn/sn.h"
#include "apex/platform/app_core.h"
//#include "apex/os/linux/gnome_apex_application.h"
#include "aura/user/message_box.h"




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
////   ::e_status system::os_application_system_run()
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





//::e_status app_core::system_start()
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
//   psystem->add_ref(OBJ_REF_DBG_ARGS);
//
//   if (m_pmainstruct->m_bConsole)
//   {
//
//      psystem->get_context_session()->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->get_context_session()->set_context(psystem->m_papplicationStartup);
//
//      psystem->set_context(psystem->m_papplicationStartup);
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


   ::e_status system::start()
   {

//      auto estatus = do_factory_exchange("windowing", "x11");
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

//      estatus = __construct(m_pwindowing);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = m_pwindowing->process_init();
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

//      auto estatus = create_os_node();
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//

      //   ::e_status estatus = psystem->begin_synch();
      //
      //   if(!estatus)
      //   {
      //
      //      return estatus;
      //
      //   }
      //

//      const char *pszName = m_strAppId;

//      g_set_application_name(pszName);

//      const char *pszPrgName = m_strProgName;

//      g_set_prgname(pszPrgName);

      //auto idle_source = g_idle_source_new();

      //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);

      //g_source_attach(idle_source, g_main_context_default());

      //int c = 2;

      //const char * argv[]={"app", "--g-fatal-warnings"};

#if !defined(__SANITIZE_ADDRESS__)

      auto pnode = m_pnode;

      if(pnode)
      {

         if (!pnode->node_init_check(&m_argc, &m_argv))
         {

            return ::error_failed;

         }

      }

#endif

      if (!begin_synch())
      {

         output_debug_string("\nFailed to begin_synch the system (::aura::system or ::aura::system derived)");

         return error_failed;

      }

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto estatus = pwindowing->start();

//      if (m_bUser)
//      {
//
//         m_pwindowing->os_application_system_run();
//
//         if (!XInitThreads())
//         {
//
//            return false;
//
//         }
//
//         XSetErrorHandler(_c_XErrorHandler);
//
//      }
//
//      if(pnode)
//      {
//
//         pnode->os_application_system_run();
//
//      }
//      else
//      {
//
//         x11_main();
//
//      }

      //x11_main();
//      if (m_bGtkApp)
//      {
//
//         apex_application_run(m_strAppId, m_strProgName);
//
//      }
//      else
//      {
//
//         //      g_set_application_name(psystem->m_strAppId);
//         //
//         //      g_set_prgname(psystem->m_strProgName);
//         //
//         //      //auto idle_source = g_idle_source_new();
//         //
//         //      //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);
//         //
//         //      //g_source_attach(idle_source, g_main_context_default());
//         //
//         //      //int c = 2;
//         //
//         //      //const char * argv[]={"app", "--g-fatal-warnings"};
//         //
//         //#if !defined(__SANITIZE_ADDRESS__)
//         //
//         //      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
//         //
//         //#endif
//         //x11_add_gdk_filter();
//         //gtk_main();
//
//      }

      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      return ::success;

   }


   ::e_status system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const promise::process & process)
   {

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      if(!pwindowing)
      {

         return ::error_no_windowing;

      }

      string strMessage(pszMessage);

      string strTitle(pszTitle);

      fork([strMessage, strTitle, emessagebox, process, pwindowing]()
      {

         auto result = pwindowing->message_box(strMessage, strTitle, emessagebox);

         process(result);

      });

      return ::success;

   }


   ::e_status system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const promise::process & process)
   {

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      if(!pwindowing)
      {

         return ::error_no_windowing;

      }

      string strMessage(pszMessage);

      string strTitle(pszTitle);

      fork([strMessage, strTitle, durationTimeout,  emessagebox, process, pwindowing]()
           {

              auto result = pwindowing->message_box_timeout(strMessage, strTitle, durationTimeout, emessagebox);

              process(result);

           });

      return ::success;

   }


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

//
//void os_term_application()
//{
//
////   if(g_papexapplication != nullptr)
////   {
////
////      g_application_quit(G_APPLICATION(g_papexapplication));
////
////   }
//
//}
//

//gboolean gtk_quit_callback(gpointer data)
//{
//
//   gtk_main_quit();
//
//   return false;
//
//}

//
//void os_post_quit()
//{
//
//   auto idle_source = g_idle_source_new();
//
//   g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);
//
//   g_source_attach(idle_source, g_main_context_default());
//
//}
//
//::e_status     run_runnable(::matter * pobjectTask);
//
//
//gboolean gdk_callback_run_runnable(gpointer pdata)
//{
//
//   run_runnable((matter *) pdata);
//
//   return false;
//
//}
//
//
//void gdk_branch(matter * prunnable, e_priority epriority)
//{
//
//   prunnable->add_ref(OBJ_REF_DBG_P_NOTE(nullptr, "gdk_branch"));
//
//   auto idle_source = g_idle_source_new();
//
//   g_source_set_priority(idle_source, G_PRIORITY_DEFAULT);
//
//   g_source_set_callback(idle_source, &gdk_callback_run_runnable, prunnable, nullptr);
//
//   g_source_attach(idle_source, g_main_context_default());
//
//}
//
//
//CLASS_DECL_AURA void main_branch(::matter * prunnable, e_priority epriority)
//{
//
//   prunnable->add_ref(OBJ_REF_DBG_P_NOTE(nullptr, "main_branch"));
//
//   gdk_branch(prunnable, epriority);
//
//}
//
//void init_x11();
//namespace aura
//{
//
//   ::e_status system::defer_initialize_x11()
//   {
//
//      return ::apex::system::defer_initialize_x11();
//
//   }
//
//
//
//} // namespace aura
//
