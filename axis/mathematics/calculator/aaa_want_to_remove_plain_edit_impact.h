#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS plain_edit_impact:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      ::calculator::value        m_val;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_impact();
      virtual ~plain_edit_impact();


      virtual void set_format(const ::scoped_string & scopedstrFormat) override;
      virtual void set_callback(callback* pcallback) override;


      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & action_context) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      bool keyboard_focus_is_focusable() override;

      //virtual long long increment_reference_count() override;

      //virtual long long decrement_reference_count() override;

      virtual ::payload get_ex_value() override;

   };


} // namespace calculator




