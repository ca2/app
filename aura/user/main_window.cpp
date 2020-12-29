#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   main_window::main_window()
   {

      m_bitExtendOnParentIfClientOnly = true;

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

      set_prodevian();

      add_user_item({ ::user::e_element_close_button, ::user::e_event_close_app });

   }


   ::e_status main_window::create_main_window()
   {

      ::rect rectWindow;

      bool bInitialFramePosition = _001InitialFramePosition(rectWindow, m_rectInitialRateOrSize);

      auto pcs = __new(::user::create_struct(0, nullptr, Application.m_strAppId, WS_VISIBLE, rectWindow));

      bool bOk = create_window_ex(pcs);

      if (!bOk)
      {

         return false;

      }

      if (bInitialFramePosition)
      {

         place(rectWindow);

      }

      return ::success;

   }



} // namespace user
