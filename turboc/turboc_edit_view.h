#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC edit_view:
      virtual public ::user::edit_plain_text_view
   {
   public:


      top_view * m_ptopview;


      edit_view(::object * pobject);
      virtual ~edit_view();

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);

      bool keyboard_focus_is_focusable();

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   };


} // namespace turboc




