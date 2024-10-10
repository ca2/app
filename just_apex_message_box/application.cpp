#include "framework.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_just_apex_message_box);


namespace app_just_apex_message_box
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_just_message_box));


   application::application()
   {

      m_strAppId = "app/just_apex_message_box";

      m_strAppName = "Just Apex Message Box";

      m_strBaseSupportId = "app/just_apex_message_box";

      m_bNetworking = false;

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use innate_ui icon?

   }


   //application::~application()
   //{

   //}


   //void application::init_instance()
   //{

   //   ::aura::application::init_instance();

   //   //if (!::aura::application::init_instance())
   //   //{

   //   //   return false;

   //   //}

   //   //return true;

   //}


   //void application::term_application()
   //{

   //   ::aura::application::term_application();

   //}


//   void application::on_request(::request * prequest)
//   {
//
//      show_message_box();
//
//   }
//
//
////#ifdef _DEBUG
////
////
////   int64_t application::increment_reference_count()
////   {
////
////      return ::object::increment_reference_count();
////
////   }
////
////
////   int64_t application::decrement_reference_count()
////   {
////
////      return ::object::decrement_reference_count();
////
////   }
////
////
////#endif
//
//
//   void application::show_message_box()
//   {
//
//      while (true)
//      {
//
//
//         auto pmessagebox = __initialize_new ::message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);
//
//         pmessagebox->sync();
//
//         auto result = pmessagebox->m_payloadResult.as_atom().m_edialogresult;
//
//         if (result == e_dialog_result_cancel)
//         {
//
//            _001TryCloseApplication();
//
//            break;
//
//         }
//         else  if (result == e_dialog_result_no)
//         {
//
//            auto pmessagebox = __initialize_new ::message_box("No!", nullptr, e_message_box_ok);
//
//            pmessagebox->sync();
//
//         }
//         else  if (result == e_dialog_result_yes)
//         {
//
//            auto pmessagebox = __initialize_new ::message_box("Yes!!", nullptr, e_message_box_ok);
//
//            pmessagebox->sync();
//
//            _001TryCloseApplication();
//
//            break;
//
//         }
//
//      }
//
//   
//      //pprocess->then([this](auto future)
//      //               {
//
//      //                  if (future->m_edialogresult == e_dialog_result_yes)
//      //                  {
//
//      //                     auto papp = get_app();
//
//      //                     papp->_001TryCloseApplication();
//
//      //                  }
//      //                  else
//      //                  {
//
//      //                     show_message_box();
//
//      //                  }
//
//      //               });
//
//   }


} // namespace app_just_apex_message_box



