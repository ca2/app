#include "framework.h"
#include "application.h"

#include "acme/handler/request.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_just_message_box);
IMPLEMENT_APPLICATION_FACTORY(app_just_message_box);



namespace app_just_message_box
{


   application::application()
   {

   }


   void application::on_request(::request * prequest)
   {

      if (prequest->m_ecommand == ::e_command_default_start)
      {

         show_message_box();

      }

   }


   void application::show_message_box()
   {

      //auto pmessageboxpayload = __initialize_new ::message_box_payload(
         //"Showing a message box as requested.\n\nIs it ok?", nullptr, ::user::e_message_box_yes_no_cancel);


      post_message_box(
         "Showing a message box as requested.\n\nIs it ok?",
         nullptr,
         ::user::e_message_box_yes_no_cancel,
         [this](::message_box_payload * pmessageboxpayload)
         {

            if (pmessageboxpayload->m_payloadResult == e_dialog_result_cancel)
            {

               _001PostTryCloseApplication();

            }
            else if (pmessageboxpayload->m_payloadResult == e_dialog_result_no)
            {

               post_message_box("No!", nullptr, ::user::e_message_box_ok,
                   [this](::message_box_payload * pmessageboxpayload)
                  {

                     show_message_box();

                  });

            }
            else if (pmessageboxpayload->m_payloadResult == e_dialog_result_yes)
            {


               post_message_box(
                  "Yes!!", nullptr, ::user::e_message_box_ok,
                   [this](::message_box_payload * pmessageboxpayload)
                  {

                     _001PostTryCloseApplication();

                  });

            }

         });

      //post(pmessageboxpayload);


   }


} // namespace app_just_message_box



