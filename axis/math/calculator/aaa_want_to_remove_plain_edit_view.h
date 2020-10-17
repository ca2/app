#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS plain_edit_view:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      ::calculator::value        m_val;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_view();
      virtual ~plain_edit_view();


      virtual void set_format(const string& strFormat) override;
      virtual void set_callback(callback* pcallback) override;


      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & action_context) override;

      void on_apply(::action * paction) override;

      bool keyboard_focus_is_focusable() override;

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;

      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;

      virtual var get_ex_value() override;

   };


} // namespace calculator




