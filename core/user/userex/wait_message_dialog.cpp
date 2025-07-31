#include "framework.h"
#include "wait_message_dialog.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/prototype/prototype/atom.h"
#include "base/user/form/impact.h"


namespace userex
{


   wait_message_dialog::wait_message_dialog()
   {
      
   }


   wait_message_dialog::~wait_message_dialog()
   {

   }


   void wait_message_dialog::on_show(const ::scoped_string & scopedstrMatter)
   {

      ::dialog::on_show(scopedstrMatter);

   }


   void wait_message_dialog::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      
      dialog::handle(ptopic, phandlercontext);
      
      if(ptopic->user_interaction() == m_pform)
      {
      
         if(ptopic->id() == ::id_create)
         {
            
            if(m_timeDelay > 0_s)
            {
               
               m_pform->set_timer(e_timer_reload, 50_ms);
               
               payload("wait_message_dialog_timeout") = m_timeDelay;
               
            }
            
            m_timeStart.Now();

         }
         else if(ptopic->id() == ::id_timer)
         {
            
            if(ptopic->_extended_topic()->m_etimer == e_timer_reload)
            {

               on_timeout_check();
               
            }

         }
         
      }
      else if(ptopic->id() == ::id_click)
      {

         m_atomResponse = ptopic->user_interaction()->id();

         EndModalLoop(m_atomResponse);

         ptopic->m_bRet = true;

      }

   }


   bool wait_message_dialog::on_timeout_check()
   {

      auto tickTimeout = m_timeStart.elapsed();

      if (tickTimeout > (m_timeDelay - 500_ms))
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

      m_atomResponse = "timeout";

      return true;

   }


   void wait_message_dialog::on_timer_soft_reload(const class time & tickTimeout)
   {

      auto time = (m_timeDelay - tickTimeout);
      
      if(time <= 0_s)
      {
         
         return;
         
      }
      
      if(time == m_time)
      {
         
         return;
         
      }
      
      m_time = time;
      
      auto pinteraction = m_pform->get_child_by_id("timeout");
      
      if (pinteraction)
      {

         string str;

         str.formatf("%d", time.integral_second());

         pinteraction->set_text(str, ::e_source_sync);

      }

      if (m_pformdocument != nullptr)
      {

         payload("wait_message_dialog_timeout") = time;

         m_pform->soft_reload();

      }

      m_pform->set_need_redraw();

   }


} // namespace userex





