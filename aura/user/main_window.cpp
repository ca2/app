#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   main_window::main_window()
   {

      m_bExtendOnParentIfClientOnly = true;

   }


   main_window::~main_window()
   {

   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

   }


   void main_window::on_create_user_interaction()
   {

      //set_prodevian();

      add_user_item({ ::user::e_element_close_button, ::user::e_event_close_app });

   }


   ::e_status main_window::create_main_window()
   {

      ::rectangle_i32 rectWindow;

      bool bInitialFramePosition = _001InitialFramePosition(rectWindow, m_rectInitialRateOrSize);

      place(rectWindow);

      bool bOk = create_host();

      if (!bOk)
      {

         return false;

      }

      //if (bInitialFramePosition)
      //{
      //   
      //   place(rectWindow);

      //}

      return ::success;

   }



} // namespace user
