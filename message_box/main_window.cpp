#include "framework.h"
//#include "aura/graphics/user/close_button.h"


//#define STEPPY_DEBUG 0


namespace app_message_box
{


   main_window::main_window()
   {


   }


   main_window::~main_window()
   {


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

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      double dBase = (double)rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      ::rectangle_i32 rectangleButton(rectangleClient);

      rectangleButton.right -= (int) x;

      rectangleButton.bottom -= (int) y;

      rectangleButton.left = (int) (rectangleButton.right - x * 3.5);

      rectangleButton.top = (int) (rectangleButton.bottom - y * 1.65);

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

      auto psequence = m_psystem->message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);

      psequence->then([this](auto psequence)
         {

            if (psequence->m_atomResult == e_dialog_result_yes)
            {

               auto papplication = get_application();

               papplication->_001TryCloseApplication();

            }
            else if (psequence->m_atomResult == e_dialog_result_cancel)
            {

               show_message_box();

            }

         });

   }


} // namespace app_message_box



