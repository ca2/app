#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   main_window::main_window()
   {

      m_bEnableDragMove = true;

      m_bClickDefaultMouseHandling = true;

      m_bHoverDefaultMouseHandling = true;

      m_bExtendOnParentIfClientOnly = true;

   }


   main_window::~main_window()
   {

   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);
      
      //install_hover_default_mouse_handling(pchannel);

   }


   void main_window::on_create_user_interaction()
   {

      defer_set_icon();

      add_user_item({ ::e_element_close_button, ::e_subject_close_app });

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

      return ::success;

   }


} // namespace user



