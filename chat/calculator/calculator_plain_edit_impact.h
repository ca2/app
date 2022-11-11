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

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      bool keyboard_focus_is_focusable();

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   };


} // namespace calculator




