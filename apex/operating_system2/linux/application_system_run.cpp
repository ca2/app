#include "framework.h"
//#include "_user.h"
////#include "sn/sn.h"
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
//   throw ::exception(::exception());
//
//}

//
//#ifdef WINDOWS
//
//
//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
//{
//
//   __UNREFERENCED_PARAMETER(uiCode);
//
//   __UNREFERENCED_PARAMETER(ppointers);
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
//#ifndef RASPBERRYPIOS
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
//   ::apexacmesystem()->sn_start_context();
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
//#endif // !RASPBERRYPIOS
//




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
//   auto psystem = ::apexacmesystem();
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


namespace apex
{


   // void system::system_main()
   // {

   //    auto estatus = ::acme::system::system_main();

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

//    #ifndef RASPBERRYPIOS
//
//     sn_start_context();
//
//    #endif

    return true;

 }


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

