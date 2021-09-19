#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "acme/constant/timer.h"


namespace userex
{


   wait_message_dialog::wait_message_dialog()
   {
      
      m_iSecond = -1;

      m_millisStart = 0;

      m_millisDelay = 0;

   }


   wait_message_dialog::~wait_message_dialog()
   {

   }


   void wait_message_dialog::on_show(const ::string & pszMatter)
   {

      ::dialog::on_show(pszMatter);

   }


   void wait_message_dialog::handle(::subject * psubject, ::context * pcontext)
   {
      
      dialog::handle(psubject, pcontext);
      
      if(psubject->user_interaction() == m_pform)
      {
      
         if(psubject->m_id == ::e_subject_create)
         {
            
            if(m_millisDelay > 0)
            {
               
               m_pform->set_timer(e_timer_reload, 50_ms);
               
               payload("wait_message_dialog_timeout") = m_millisDelay.seconds();
               
            }
            
            m_millisStart.Now();

         }
         else if(psubject->m_id == ::e_subject_timer)
         {
            
            if(psubject->m_etimer == e_timer_reload)
            {

               on_timeout_check();
               
            }

         }
         
      }
      else if(psubject->m_id == ::e_subject_click)
      {

         m_idResponse = psubject->user_interaction()->m_id;

         EndModalLoop(m_idResponse);

         psubject->m_bRet = true;

      }

   }


   bool wait_message_dialog::on_timeout_check()
   {

      auto tickTimeout = m_millisStart.elapsed();

      if (tickTimeout > (m_millisDelay - 500_ms))
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


   void wait_message_dialog::on_timer_soft_reload(millis tickTimeout)
   {

      auto iSecond = (m_millisDelay - tickTimeout).seconds();
      
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

         pinteraction->_001SetText(str, ::e_source_sync);

      }

      if (m_pdocument != nullptr)
      {

         payload("wait_message_dialog_timeout") = iSecond;

         m_pform->soft_reload();

      }

      m_pform->set_need_redraw();

   }


} // namespace userex





