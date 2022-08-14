#include "framework.h"


namespace turboc
{


   toggle_impact::toggle_impact(::object * pobject):
      ::object(pobject),
      ::user::interaction(pobject),
      ::user::button(pobject)
   {

      m_ptopview = NULL;

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

      ::aura::impact::handle(ptopic, pcontext);

   }


   //void toggle_impact::_001OnAfterChangeText(const ::action_context & context)
   //{

   //   if(!context.is_user_source())
   //      return;

   //   if(m_pmainimpact == NULL || m_pmainimpact->m_pimpact == NULL)
   //      return;

   //   {
   //      synchronous_lock synchronouslock(&m_pmainimpact->m_pimpact->m_mutexText);
   //      _001GetText(m_pmainimpact->m_pimpact->m_strNewHelloMultiverse);
   //   }

   //   m_pmainimpact->m_pimpact->post_message(WM_USER + 2000 + 77 + 2);

   //}


   bool toggle_impact::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace turboc












