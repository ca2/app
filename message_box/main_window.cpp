#include "framework.h"
#include "main_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/nano/nano.h"
#include "aura/user/user/button.h"
#include "aura/platform/application.h"


namespace app_message_box
{


   main_window::main_window()
   {


   }


   main_window::~main_window()
   {


   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &main_window::on_message_close);

   }


   void main_window::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      auto psequencer = nano()->message_box("Are you sure you want to close application?", nullptr, e_message_box_yes_no);

      psequencer->then([this](auto * pmessagebox)
         {

            if (pmessagebox->m_payloadResult.as_i32() == e_dialog_result_yes)
            {

               auto papp = get_app();

               papp->_001TryCloseApplication();

            }
            else if (pmessagebox->m_payloadResult.as_i32() == e_dialog_result_cancel)
            {

               show_message_box();

            }

         });

      psequencer->do_asynchronously();

   }


   void main_window::on_create_user_interaction()
   {

      ::app_app::main_window::on_create_user_interaction();

      __construct(m_pbuttonShowMessageBox);

      m_pbuttonShowMessageBox->create_child(this);

      m_pbuttonShowMessageBox->set_window_text("Show message box");

      m_pbuttonShowMessageBox->add_handler(this);

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      m_pbuttonShowMessageBox->display();

      auto rectangleClient = client_rectangle();

      double dBase = (double)rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      ::rectangle_i32 rectangleButton(rectangleClient);

      rectangleButton.right -= (int) x;

      rectangleButton.bottom -= (int) y;

      rectangleButton.left = (int) (rectangleButton.right - dBase * 11.0);
      
      rectangleButton.top = (int) (rectangleButton.bottom - dBase * 5.0);

      m_pbuttonShowMessageBox->place(rectangleButton);

   }


   void main_window::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == ::id_click)
      {

         if (ptopic->user_interaction() == m_pbuttonShowMessageBox && ptopic->m_actioncontext.is_user_source())
         {

            try
            {

               show_message_box();

               ptopic->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }

   }


   void main_window::show_message_box()
   {

      auto psequencer = nano()->message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);

      psequencer->then([this](auto pmessagebox)
         {

            if (pmessagebox->m_payloadResult.as_i32() == e_dialog_result_yes)
            {

               post_message(MESSAGE_CLOSE);

            }
            else if (pmessagebox->m_payloadResult.as_i32() == e_dialog_result_cancel)
            {

               show_message_box();

            }

         });

      psequencer->do_asynchronously();

   }


} // namespace app_message_box



