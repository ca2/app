#include "framework.h"
#include "application.h"



__IMPLEMENT_APPLICATION_RELEASE_TIME(app_just_message_box);
IMPLEMENT_APPLICATION_FACTORY(app_just_message_box);



namespace app_just_message_box
{


   application::application()
   {

   }


   void application::on_request(::request * prequest)
   {

      show_message_box();

   }


   void application::show_message_box()
   {

      auto pmessagebox = __initialize_new::message_box(
         "Showing a message box as requested.\n\nIs it ok?",
         nullptr,
         e_message_box_yes_no_cancel);

      pmessagebox->main_async()
         << [this, pmessagebox]()
         {

            if (pmessagebox->m_payloadResult == e_dialog_result_cancel)
            {

               _001TryCloseApplication();

            }
            else  if (pmessagebox->m_payloadResult == e_dialog_result_no)
            {

               auto pmessageboxNo = __initialize_new::message_box("No!", nullptr, e_message_box_ok);

               pmessageboxNo->async()
                  << [this]()
                  {

                     show_message_box();

                  };

            }
            else  if (pmessagebox->m_payloadResult == e_dialog_result_yes)
            {

               auto pmessageboxYes = __initialize_new::message_box("Yes!!", nullptr, e_message_box_ok);

               pmessageboxYes->async()
                  << [this]()
                  {

                     _001TryCloseApplication();

                  };

            }

         };

   }


} // namespace app_just_message_box



