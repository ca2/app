#include "framework.h"


namespace turboc
{


   toggle_view::toggle_view(::layered * pobjectContext):
      ::object(pobject),
      ::user::interaction(pobject),
      ::user::button(pobject)
   {

      m_ptopview = NULL;

   }
   toggle_view::~toggle_view()
   {


   }

   void toggle_view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);
      ::user::button::install_message_handling(pdispatch);

   }


   void toggle_view::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {

      ::aura::impact::on_subject(psubject, pcontext);

   }


   //void toggle_view::_001OnAfterChangeText(const ::action_context & context)
   //{

   //   if(!context.is_user_source())
   //      return;

   //   if(m_pmainview == NULL || m_pmainview->m_pview == NULL)
   //      return;

   //   {
   //      sync_lock sl(&m_pmainview->m_pview->m_mutexText);
   //      _001GetText(m_pmainview->m_pview->m_strNewHelloMultiverse);
   //   }

   //   m_pmainview->m_pview->post_message(WM_USER + 2000 + 77 + 2);

   //}


   bool toggle_view::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable() ;

   }


} // namespace turboc













