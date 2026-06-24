#include "application.h"
#include "../acme/user/interface/message_box.h"
#include "acme/handler/request.h"
#include "framework.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(just_message_box);
IMPLEMENT_APPLICATION_FACTORY(just_message_box);



namespace just_message_box
{


   application::application()
   {

   }


   void application::on_request(::request * prequest)
   {

      auto ecommand = prequest->m_ecommand;

      if (ecommand == ::e_command_default_start)
      {

         show_message_box();

      }

   }


   void application::show_message_box()
   {

      //auto pmessageboxpayload = __initialize_new ::message_box_payload(
         //"Showing a message box as requested.\n\nIs it ok?", nullptr, ::user::e_message_box_yes_no_cancel);

      auto pmessageboxMain = message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, ::user::e_message_box_yes_no_cancel);

      pmessageboxMain->message_box_response_callback() =
      [this](::user_interface::message_box * pmessagebox)
      {

         if (pmessagebox->get_dialog_response() == e_dialog_result_cancel)
         {

            _001PostTryCloseApplication();

         }
         else if (pmessagebox->get_dialog_response() == e_dialog_result_no)
         {

            auto pmessageboxNo = message_box("No!", nullptr, ::user::e_message_box_ok);
            
            pmessageboxNo->message_box_response_callback() =
            [this](::user_interface::message_box * pmessagebox)
            {

               show_message_box();

            };
            
            pmessageboxNo->display(e_display_normal, {});

         }
         else if (pmessagebox->get_dialog_response() == e_dialog_result_yes)
         {


            auto pmessageboxYes = message_box("Yes!!", nullptr, ::user::e_message_box_ok);
            
            pmessageboxYes->message_box_response_callback() =
                [this](::user_interface::message_box * pmessagebox)
               {

                  _001PostTryCloseApplication();

               };
            
            pmessageboxYes->display(e_display_normal, {});

         }

      };
      
      pmessageboxMain->display(e_display_normal, {});

      //post(pmessageboxpayload);


   }


} // namespace app_just_message_box



