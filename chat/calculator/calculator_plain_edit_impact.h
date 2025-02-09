#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH plain_edit_impact:
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      class callback :
         virtual public object
      {
      public:

         virtual ::pointer< ::mutex > get_mutex()
         {
            return mutex();
         }

         virtual void set_expression(const ::string & pszExp)
         {
         }

      };

      ::calculator::value        m_val;
      callback *                 m_pcallback;

      string                     m_strFormat;


      plain_edit_impact(::particle * pparticle);
      virtual ~plain_edit_impact();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool keyboard_focus_is_focusable();

      virtual long long increment_reference_count();

      virtual long long decrement_reference_count();

   };


} // namespace calculator




