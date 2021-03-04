#include "framework.h"
#include "apex/platform/app_core.h"
//#include "windowing.h"


// bool os_init_application()
// {

//    return true;

// }


// void os_term_application()
// {

//    //   if(g_papexapplication != nullptr)
//    //   {
//    //
//    //      g_application_quit(G_APPLICATION(g_papexapplication));
//    //
//    //   }

// }











string ca2_command_line()
{

   return "";

}

//void app_core::system_main()
//{
//
//   if (!system_ini())
//   {
//
//      system_end();
//
//      return;
//
//   }
//
//   system_run();
//
//}
//


namespace apex
{


   ::e_status system::os_application_system_run()
   {

      //string strPrgName = m_strAppId;

      //strPrgName.replace("/", ".");

      //strPrgName.replace("_", "-");

      //m_strProgName = "com." + strPrgName;

      //::set_main_hthread(m_hthread);

      //::set_main_ithread(m_uthread);

      //// System->m_strAppId = m_pmaindata->m_strAppId;

      //if (!begin_synch())
      //{

      //   output_debug_string("Failed to begin_synch the system (::apex::system or ::apex::system derived)");

      //   return ::error_failed;

      //}

      ////::apex::system * psystem = get_context_system();

      ////try
      ////{

      ////   ::user::native_window_initialize initialize;

      ////   initialize.m_rectangle.left = 0;

      ////   initialize.m_rectangle.top = 0;

      ////   node_data_exchange * pdataexchange = psystem->node_ddx();

      ////   initialize.m_rectangle.right = pdataexchange->m_iScreenWidth;

      ////   initialize.m_rectangle.bottom = pdataexchange->m_iScreenHeight;

      ////   psystem->get_context_session()->defer_initialize_host_window(&initialize.m_rectangle);

      ////   //::user::system createstruct;

      ////   //if (!psystem->get_context_session()->m_puiHost->create_window_ex(createstruct))
      ////   //{

      ////   //    return ::error_failed;

      ////   //}

      ////   //__pointer(::user::interaction_impl) pimpl = psystem->get_context_session()->m_puiHost->m_pimpl;

      ////   //if (pimpl)
      ////   //{

      ////   //   ::oswindow_data * pwindow = new oswindow_data;

      ////   //   oswindow window = pwindow;

      ////   //   pimpl->m_oswindow = pwindow;

      ////   //}

      ////}
      ////catch (...)
      ////{

      ////   psystem->m_result.set(error_exception);

      ////   return error_exception;

      ////}

      ////psystem->main();

      ////::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      return ::success;


   }


} // namespace apex



//
//bool os_init_application()
//{
//
//
//   return true;
//
//}
//
//
//void os_term_application()
//{
//
//   //   if(g_papexapplication != nullptr)
//   //   {
//   //
//   //      g_application_quit(G_APPLICATION(g_papexapplication));
//   //
//   //   }
//
//}



void os_post_quit()
{



}



//os_system_window::os_system_window()
//{
//
//
//}
//
//
//os_system_window::~os_system_window()
//{
//
//
//}



