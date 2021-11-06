#include "framework.h"
#include "aura/update.h"


namespace app_just_message_box
{


   application::application()
   {

      m_strAppId = "app/just_message_box";

      m_strAppName = "app/just_message_box";

      m_strBaseSupportId = "app/just_message_box";

      m_bLicense = false;

      m_bImaging = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      show_message_box();

   }


#ifdef _DEBUG


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void application::show_message_box()
   {

      //auto pprocess = message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);

      //pprocess->then([this](auto future)
      //               {

      //                  if (future->m_edialogresult == e_dialog_result_yes)
      //                  {

      //                     auto papplication = get_application();

      //                     papplication->_001TryCloseApplication();

      //                  }
      //                  else
      //                  {

      //                     show_message_box();

      //                  }

      //               });

   }


} // namespace app_just_message_box



