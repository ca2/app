#include "framework.h"
#include "_user.h"
#include <gio/gio.h>
//#include "third/sn/sn.h"
#include "apex/platform/app_core.h"
#include "apex_application.h"

extern ::app_core * g_pappcore;

void os_post_quit();
Display * x11_get_display();

CLASS_DECL_CORE i32 ca2_main();

void x11_main();

gboolean linux_start_system(gpointer data);



void CLASS_DECL_CORE __cdecl _ca2_purecall()
{

   __throw(::exception());

}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{

   __UNREFERENCED_PARAMETER(uiCode);

   __UNREFERENCED_PARAMETER(ppointers);

}


string ca2_command_line()
{

   return "";

}




#ifndef RASPBIAN

SnLauncheeContext* g_psncontext = nullptr;

void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);



void sn_start_context()
{


   Display * dpy = x11_get_display();

   SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);

   int iScreen = DefaultScreen(dpy);

   g_psncontext = sn_launchee_context_new(pd, iScreen, ::g_pappcore->m_strProgName);

}


#endif // !RASPBIAN





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
//   psystem->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   if (m_pmainstruct->m_bConsole)
//   {
//
//      psystem->get_session()->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->get_session()->set_context(psystem->m_papplicationStartup);
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


//::e_status os_application_system_run(::aura::system * psystem)
//{
//
////   ::e_status estatus = psystem->begin_synch();
////
////   if(!estatus)
////   {
////
////      return estatus;
////
////   }
////
//   if (!psystem->begin_synch())
//   {
//
//      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");
//
//      return error_failed;
//
//   }
//
//   if(psystem->m_bGtkApp)
//   {
//
//
//
//   }
//   else
//   {
//      //g_thread_init(nullptr);
//
//      g_set_application_name(psystem->m_strAppId);
//
//      g_set_prgname(psystem->m_strProgName);
//
//      //auto idle_source = g_idle_source_new();
//
//      //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);
//
//      //g_source_attach(idle_source, g_main_context_default());
//
//      //int c = 2;
//
//      //const char * argv[]={"app", "--g-fatal-warnings"};
//
//#if !defined(__SANITIZE_ADDRESS__)
//
//      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
//
//#endif
//
//   }
//
//   if(psystem->m_bGtkApp)
//   {
//
//      apex_application_run(psystem->m_strAppId, psystem->m_strProgName);
//
//   }
//   else
//   {
//
//      //gtk_main();
//
//      x11_main();
//
//      //main();
//
//   }
//
//   //::parallelization::post_quit_and_wait(get_context_system(), one_minute());
//
//   return ::success;
//
//}


void sn_start_context();


// bool os_init_application()
// {

//    #ifndef RASPBIAN

//     sn_start_context();

//    #endif

//    return true;

// }

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

gboolean gtk_quit_callback(gpointer data)
{

   gtk_main_quit();

   return false;

}


void os_post_quit()
{

   auto idle_source = g_idle_source_new();

   g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);

   g_source_attach(idle_source, g_main_context_default());

}



