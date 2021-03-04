#include "framework.h"
//#include "aura/platform/app_core.h"
//#include "windowing.h"
CLASS_DECL_AURA::e_status android_os_message_box(const char * pText, const char * lpCaption, const ::e_message_box & emessagebox, const ::future & process);

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


   ::e_status system::os_application_system_run()
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


   ::e_status system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
   {

      android_os_message_box(pszMessage, pszTitle, emessagebox, process);

      return success;

   }


   ::e_status system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const ::future & process)
   {

      auto estatus = System->message_box_timeout(pszMessage, pszTitle, durationTimeout, emessagebox, process);

      return estatus;

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



