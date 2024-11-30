#pragma once


#include "aura/user/user/plain_edit.h"
#include "base/user/user/show.h"


namespace userex
{


   class CLASS_DECL_CORE top_edit_impact :
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      class ::time                  m_timeLastChange;
      class ::time                  m_timeDelayedAfterChange;
      top_impact *              m_ptopimpact;
      bool                    m_bEnterKeyPressed;
      ::write_text::font_pointer  m_pfont;


      top_edit_impact();
      virtual ~top_edit_impact();

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      ::write_text::font_pointer get_font(::user::style* pstyle, ::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) override;

       void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context& action_context) override;

      void handle(::topic * ptopic, ::context * pcontext) override;



      bool keyboard_focus_is_focusable() override;

      virtual void on_timer(::timer * ptimer) override;

      //virtual bool _is_window_visible() override;


   };


} // namespace userex




