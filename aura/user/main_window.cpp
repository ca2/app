#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   main_window::main_window()
   {

      m_bExtendOnParentIfClientOnly = true;

      enable_drag_move();

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

      __pointer(::aura::application) papplication = get_application();

      string strCaption = papplication->get_app_user_friendly_task_bar_name();

      set_window_text(strCaption);

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
