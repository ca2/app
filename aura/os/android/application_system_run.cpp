#include "framework.h"
//#include "aura/platform/app_core.h"
//#include "windowing.h"


//bool os_init_application()
//{
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
//
//
//
//
//
//
//
//
//
//
//
//string ca2_command_line()
//{
//
//   return "";
//
//}

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

namespace aura
{


   ::estatus system::os_application_system_run()
   {

      if (!m_hthread)
      {

         auto estatus = begin_synch();

         if (!estatus)
         {

            return estatus;

         }

      }

      return ::success;

   }


} // namespace aura

  
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



