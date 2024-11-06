#include "framework.h"


namespace turboc
{


   edit_impact::edit_impact(::particle * pparticle):
      ::object(pparticle),
      ::user::interaction(pparticle),
      ::user::scroll_impact(pparticle),
      ::data::listener(pparticle),
      ::user::edit_plain_text(pparticle),
      ::user::edit_plain_text_impact(pparticle)
   {

      m_ptopimpact = NULL;

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

      if(m_ptopimpact == NULL || m_ptopimpact->m_pimpact == NULL)
         return;

      {

         synchronous_lock synchronouslock(&m_ptopimpact->m_pimpact->m_pmutexText);

         get_text(m_ptopimpact->m_pimpact->m_strNewHelloMultiverse);

      }

      m_ptopimpact->m_pimpact->post_message(WM_USER + 2000 + 77 + 2);

   }


   bool edit_impact::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   huge_integer edit_impact::increment_reference_count()
   {
      return ::root::increment_reference_count();
   }
   huge_integer edit_impact::decrement_reference_count()
   {
      return ::root::decrement_reference_count();
   }



} // namespace turboc




