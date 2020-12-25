#pragma once


namespace calculator
{


   class CLASS_DECL_CORE plain_edit_view :
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      ::calculator::payload      m_payload;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_view();
      virtual ~plain_edit_view();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void set_format(const string& strFormat) override;
      virtual void set_callback(callback* pcallback) override;


      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context& action_context) override;

      void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual bool keyboard_focus_is_focusable() const override;

      virtual ::payload get_payload() override;

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace calculator




