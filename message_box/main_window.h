#pragma once


#include "app/app/main_window.h"


namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX main_window :
      virtual public ::app_app::main_window
   {
   public:


      ::pointer<::user::button>    m_pbuttonShowMessageBox;


      main_window();
      ~main_window() override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_close);

      virtual void on_create_user_interaction() override;

      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void show_message_box();


   };


} // namespace app_message_box












