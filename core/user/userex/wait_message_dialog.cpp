#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif
#include "acme/const/timer.h"


namespace userex
{


   wait_message_dialog::wait_message_dialog()
   {
      
      m_iSecond = -1;

      m_tickStart = 0;

      m_tickDelay = 0;

   }


   wait_message_dialog::~wait_message_dialog()
   {

   }


   void wait_message_dialog::on_show(const char * pszMatter)
   {

      ::dialog::on_show(pszMatter);

   }


   void wait_message_dialog::on_control_event(::user::control_event * pevent)
   {
      
      dialog::on_control_event(pevent);
      
      if(pevent->m_puie == m_pform)
      {
      
         if(pevent->m_eevent == ::user::event_create)
         {
            
            if(m_tickDelay > 0)
            {
               
               m_pform->set_timer(e_timer_reload, 50_ms);
               
               value("wait_message_dialog_timeout") = m_tickDelay.seconds();
               
            }
            
            m_tickStart.Now();

         }
         else if(pevent->m_eevent == ::user::event_timer)
         {
            
            if(pevent->m_etimer == e_timer_reload)
            {

               on_timeout_check();
               
            }

         }
         
      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {

         m_idResponse = pevent->m_puie->m_id;

         EndModalLoop(m_idResponse);

         pevent->m_bRet = true;

      }

   }


   bool wait_message_dialog::on_timeout_check()
   {

      auto tickTimeout = m_tickStart.elapsed();

      if (tickTimeout > (m_tickDelay - 500_ms))
      {

         if (on_timeout())
         {

            EndModalLoop("timeout");

            return true;

         }

      }
      else
      {

         on_timer_soft_reload(tickTimeout);

      }

      return false;

   }


   bool wait_message_dialog::on_timeout()
   {

      m_idResponse = "timeout";

      return true;

   }


   void wait_message_dialog::on_timer_soft_reload(tick tickTimeout)
   {

      auto iSecond = (m_tickDelay - tickTimeout).seconds();
      
      if(iSecond <= 0)
      {
         
         return;
         
      }
      
      if(iSecond == (int) m_iSecond)
      {
         
         return;
         
      }
      
      m_iSecond = (int) iSecond;
      
      auto pinteraction = m_pform->get_child_by_id("timeout");
      
      if (pinteraction)
      {

         string str;

         str.Format("%d", iSecond);

         pinteraction->_001SetText(str, ::source_sync);

      }

      if (m_pdocument != nullptr)
      {

         value("wait_message_dialog_timeout") = iSecond;

         m_pform->soft_reload();

      }

      m_pform->set_need_redraw();

   }


} // namespace userex





