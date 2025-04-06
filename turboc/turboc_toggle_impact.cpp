#include "framework.h"


namespace turboc
{


   toggle_impact::toggle_impact(::particle * pparticle):
      ::object(pparticle),
      ::user::interaction(pparticle),
      ::user::button(pparticle)
   {

      m_ptopimpact = NULL;

   }
   toggle_impact::~toggle_impact()
   {


   }

   void toggle_impact::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);
      ::user::button::install_message_handling(pdispatch);

   }


   void toggle_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {

      ::aura::impact::handle(ptopic, phandlercontext);

   }


   //void toggle_impact::_001OnAfterChangeText(const ::action_context & context)
   //{

   //   if(!context.is_user_source())
   //      return;

   //   if(m_pmainimpact == NULL || m_pmainimpact->m_pimpact == NULL)
   //      return;

   //   {
   //      synchronous_lock synchronouslock(&m_pmainimpact->m_pimpact->m_pmutexText);
   //      get_text(m_pmainimpact->m_pimpact->m_strNewHelloMultiverse);
   //   }

   //   m_pmainimpact->m_pimpact->post_message(WM_USER + 2000 + 77 + 2);

   //}


   bool toggle_impact::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace turboc













