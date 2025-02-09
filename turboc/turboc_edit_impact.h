#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC edit_impact:
      virtual public ::user::edit_plain_text_impact
   {
   public:


      top_impact * m_ptopimpact;


      edit_impact(::particle * pparticle);
      virtual ~edit_impact();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);

      bool keyboard_focus_is_focusable();

      virtual long long increment_reference_count();

      virtual long long decrement_reference_count();

   };


} // namespace turboc




