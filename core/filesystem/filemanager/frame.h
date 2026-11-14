#pragma once


#include "berg/user/simple/frame_window.h"


namespace filemanager
{


   class CLASS_DECL_CORE frame :
      virtual public simple_frame_window
   {
   public:


      atom m_atomTab;
      ::pointer < ::user::toolbar > m_ptoolbarFileManager;


      frame();
      ~frame() override;


      void on_create_bars() override;
      void ensure_filemanager_toolbar();
      void hide_control_bar(::user::control_bar * pcontrolbar) override;
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(_001OnSetText);
      DECLARE_MESSAGE_HANDLER(on_message_create);

      ::pointer < ::experience::frame > frame_experience() override;

   };


} // namespace filamanager





