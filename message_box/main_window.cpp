#include "framework.h"
#include "main_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/micro/user.h"
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

      ::app_app::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &main_window::on_message_create);
      MESSAGE_LINK(e_message_close, pchannel, this, &main_window::on_message_close);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &main_window::on_message_destroy);

   }


   void main_window::on_message_create(::message::message * pmessage)
   {

      //::app_app::main_window::on_create_user_interaction();

      __øconstruct(m_pbuttonShowMessageBox);

      m_pbuttonShowMessageBox->create_child(this);

      m_pbuttonShowMessageBox->set_window_text("Show message box");

      m_pbuttonShowMessageBox->add_handler(this);

   }


   void main_window::on_message_destroy(::message::message * pmessage)
   {

      m_pbuttonShowMessageBox.release();

   }


   void main_window::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      auto pmessagebox = __initialize_new ::message_box("Are you sure you want to close application?", nullptr, e_message_box_yes_no);

      pmessagebox->async()
         << [this, pmessagebox]()
         {

            if (pmessagebox->m_payloadResult.as_int() == e_dialog_result_yes)
            {

               auto papp = get_app();

               papp->_001TryCloseApplication();

            }
            else if (pmessagebox->m_payloadResult.as_int() == e_dialog_result_cancel)
            {

               show_message_box();

            }

         };

      //pmessagebox->async();

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::app_app::main_window::on_layout(pgraphics);

      m_pbuttonShowMessageBox->display();

      auto rectangleX = this->rectangle();

      double dBase = (double)rectangleX.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      ::int_rectangle rectangleButton(rectangleX);

      rectangleButton.right() -= (int) x;

      rectangleButton.bottom() -= (int) y;

      rectangleButton.left() = (int) (rectangleButton.right() - dBase * 11.0);
      
      rectangleButton.top() = (int) (rectangleButton.bottom() - dBase * 5.0);

      m_pbuttonShowMessageBox->place(rectangleButton, ::user::e_layout_layout, pgraphics);

   }


   void main_window::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      if (ptopic->id() == ::id_click)
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

      auto pmessagebox = __initialize_new ::message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);

      pmessagebox->async()
         << [this, pmessagebox]()
         {

            if (pmessagebox->m_payloadResult == e_dialog_result_yes)
            {

               post_message(e_message_close);

            }
            else if (pmessagebox->m_payloadResult == e_dialog_result_cancel)
            {

               show_message_box();

            }

         };

      //pmessagebox->async();

   }


} // namespace app_message_box



