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

      if (prequest->m_ecommand == ::e_command_application_start)
      {

         show_message_box();

      }

   }


   void application::show_message_box()
   {

      auto pmessageboxpayload = __initialize_new ::message_box_payload(
         "Showing a message box as requested.\n\nIs it ok?",
         nullptr,
         ::user::e_message_box_yes_no_cancel);

      pmessageboxpayload->m_functionOnDialogResult = [this](const ::payload & payloadResult)
         {

            if (payloadResult == e_dialog_result_cancel)
            {

               _001PostTryCloseApplication();

            }
            else  if (payloadResult == e_dialog_result_no)
            {

               auto pmessageboxNo = __initialize_new ::message_box_payload("No!", nullptr, ::user::e_message_box_ok);

               pmessageboxNo->m_functionOnDialogResult = [this](const ::payload & payloadResult)
                  {

                     show_message_box();

                  };

               post(pmessageboxNo);

            }
            else  if (payloadResult == e_dialog_result_yes)
            {

               auto pmessageboxYes = __initialize_new ::message_box_payload("Yes!!", nullptr, ::user::e_message_box_ok);

               pmessageboxYes->m_functionOnDialogResult = [this](const ::payload & payloadResult)
                  {

                     _001PostTryCloseApplication();

                  };

               post(pmessageboxYes);

            }

         };

      post(pmessageboxpayload);


   }


} // namespace app_just_message_box



