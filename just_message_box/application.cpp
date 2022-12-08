#include "framework.h"
//#include "aura/update.h"

//IMPLEMENT_APPLICATION(app_just_message_box);


namespace app_just_message_box
{


   application::application()
   {

      m_strAppId = "app/just_message_box";

      m_strAppName = "Just Message Box";

      m_strBaseSupportId = "app/just_message_box";

      m_bNetworking = false;

      m_bLicense = false;

      m_bImaging = false;

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


   void application::on_request(::request * prequest)
   {

      show_message_box();

   }


//#ifdef _DEBUG
//
//
//   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//   {
//
//      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   }
//
//
//   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//   {
//
//      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   }
//
//
//#endif


   void application::show_message_box()
   {

      while (true)
      {


         auto result = message_box_synchronous(this, "Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);


         if (result == e_dialog_result_yes)
         {

            _001TryCloseApplication();

            break;

         }
         else  if (result == e_dialog_result_no)
         {

            message_box_synchronous(this, "No!", nullptr, e_message_box_ok);

         }
         else  if (result == e_dialog_result_cancel)
         {

            message_box_synchronous(this, "Cancel", nullptr, e_message_box_ok);

         }

      }

   
      //pprocess->then([this](auto future)
      //               {

      //                  if (future->m_edialogresult == e_dialog_result_yes)
      //                  {

      //                     auto papp = get_app();

      //                     papp->_001TryCloseApplication();

      //                  }
      //                  else
      //                  {

      //                     show_message_box();

      //                  }

      //               });

   }


} // namespace app_just_message_box



