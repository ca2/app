#include "framework.h"


namespace turboc
{


   edit_impact::edit_impact(::object * pobject):
      ::object(pobject),
      ::user::interaction(pobject),
      ::user::scroll_impact(pobject),
      ::data::listener(pobject),
      ::user::edit_plain_text(pobject),
      ::user::edit_plain_text_impact(pobject)
   {

      m_ptopview = NULL;

   }

   edit_impact::~edit_impact()
   {

   }


   void edit_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {

      ::user::edit_plain_text_impact::handle(ptopic, pcontext);

   }


   void edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      if(!context.is_user_source())
         return;

      if(m_ptopview == NULL || m_ptopview->m_pimpact == NULL)
         return;

      {

         synchronous_lock synchronouslock(&m_ptopview->m_pimpact->m_mutexText);

         _001GetText(m_ptopview->m_pimpact->m_strNewHelloMultiverse);

      }

      m_ptopview->m_pimpact->post_message(WM_USER + 2000 + 77 + 2);

   }


   bool edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   i64 edit_impact::increment_reference_count()
   {
      return ::root::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
   }
   i64 edit_impact::decrement_reference_count()
   {
      return ::root::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
   }



} // namespace turboc




