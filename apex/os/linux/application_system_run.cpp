#include "framework.h"
//#include "_user.h"
////#include "third/sn/sn.h"
//#include "apex/platform/app_core.h"
//#include "gnome_apex_application.h"

/*
extern ::app_core * g_pappcore;

void os_post_quit();
Display * x11_get_display();

CLASS_DECL_APEX i32 ca2_main();

*/


//gboolean linux_start_system(gpointer data);



//void CLASS_DECL_APEX __cdecl _ca2_purecall()
//{
//
//   __throw(::exception::exception());
//
//}

//
//#ifdef WINDOWS
//
//
//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
//{
//
//   UNREFERENCED_PARAMETER(uiCode);
//
//   UNREFERENCED_PARAMETER(ppointers);
//
//}
//
//
//#endif


//s/*tring ca2_command_line()
//{
//
//   return "";
//
//}*/

//
//
//
//#ifndef RASPBIAN
//
//SnLauncheeContext* g_psncontext = nullptr;
//
//void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);
//
//void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
//
//
//
///*void sn_start_context()
//{
//
//   ::apex::get_system()->sn_start_context();
//
//}*/

//   Display * dpy = x11_get_display();
//
//   SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);
//
//   int iScreen = DefaultScreen(dpy);
//
//   g_psncontext = sn_launchee_context_new(pd, iScreen, ::g_pappcore->m_strProgName);
//
//}
//
//
//#endif // !RASPBIAN
//




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
//   auto psystem = ::apex::get_system();
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
//#ifdef LINUX
//i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
//#endif


namespace apex
{


   // ::e_status system::system_main()
   // {

   //    auto estatus = class ::system::system_main();

   //    if(!estatus)
   //    {

   //       return estatus;

   //    }

   //    return estatus;

   // }


} // namespace apex


//void sn_start_context();


 bool os_init_application()
 {

//    #ifndef RASPBIAN
//
//     sn_start_context();
//
//    #endif

    return true;

 }


void os_term_application()
{

//   if(g_papexapplication != nullptr)
//   {
//
//      g_application_quit(G_APPLICATION(g_papexapplication));
//
//   }

}

