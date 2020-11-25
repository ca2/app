#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH plain_edit_view:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      class callback :
         virtual public object
      {
      public:

         virtual ::mutex * get_mutex()
         {
            return mutex();
         }

         virtual void set_expression(const char * pszExp)
         {
         }

      };

      ::calculator::value        m_val;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_view(::layered * pobjectContext);
      virtual ~plain_edit_view();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      bool keyboard_focus_is_focusable();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);

   };


} // namespace calculator




