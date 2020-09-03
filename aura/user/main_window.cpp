#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   main_window::main_window()
   {

   }


   main_window::~main_window()
   {

   }


   void main_window::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

   }


   void main_window::on_create_user_interaction()
   {

      set_prodevian();

      add_user_item({ ::user::element_close_button, ::user::event_close_app });

   }


} // namespace user
