#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_toggle_view :
      virtual public ::user::show < ::user::button >
   {
   public:


      top_view *           m_ptopview;


      top_toggle_view();
      virtual ~top_toggle_view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      virtual bool keyboard_focus_is_focusable() const override;


   };


} // namespace userex




