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


      virtual void set_format(const string& strFormat) override;
      virtual void set_callback(callback* pcallback) override;


      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & action_context) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool keyboard_focus_is_focusable() override;

      //virtual i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;

      //virtual i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;

      virtual ::payload get_ex_value() override;

   };


} // namespace calculator




