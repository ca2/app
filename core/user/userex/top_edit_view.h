#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_edit_view :
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      millis                  m_millisLastChange;
      millis                  m_millisDelayedAfterChange;
      top_view *              m_ptopview;
      bool                    m_bEnterKeyPressed;
      ::write_text::font_pointer  m_pfont;


      top_edit_view();
      virtual ~top_edit_view();

      virtual void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnKeyDown);

      virtual ::write_text::font_pointer get_font(::user::style* pstyle, ::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const override;

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context& action_context) override;

      void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;



      bool keyboard_focus_is_focusable() const override;

      virtual void _001OnTimer(::timer * ptimer) override;

      //virtual bool _is_window_visible() override;


   };


} // namespace userex




