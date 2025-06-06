#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_CORE tooltip:
      virtual public ::user::interaction
   {
   public:


      string               m_str;
      ::write_text::font_pointer    m_pfont;
      ::int_size               m_size;
      bool                 m_bError;


      tooltip();
      ~tooltip() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      ::int_size CalcSize();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


//      virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, style_context * pcontext) override;


      ::user::enum_window_type get_window_type() override;


   };


} // namespace veritile







