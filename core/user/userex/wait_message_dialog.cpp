﻿#include "framework.h"
#include "wait_message_dialog.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/primitive/primitive/atom.h"
#include "base/user/form/impact.h"


namespace userex
{


   wait_message_dialog::wait_message_dialog()
   {
      
      m_second.m_i = -1;

   }


   wait_message_dialog::~wait_message_dialog()
   {

   }


   void wait_message_dialog::on_show(const ::string & pszMatter)
   {

      ::dialog::on_show(pszMatter);

   }


   void wait_message_dialog::handle(::topic * ptopic, ::context * pcontext)
   {
      
      dialog::handle(ptopic, pcontext);
      
      if(ptopic->user_interaction() == m_pform)
      {
      
         if(ptopic->m_atom == ::id_create)
         {
            
            if(m_timeDelay > 0_s)
            {
               
               m_pform->set_timer(e_timer_reload, 50_ms);
               
               payload("wait_message_dialog_timeout") = m_timeDelay;
               
            }
            
            m_timeStart.Now();

         }
         else if(ptopic->m_atom == ::id_timer)
         {
            
            if(ptopic->_extended_topic()->m_etimer == e_timer_reload)
            {

               on_timeout_check();
               
            }

         }
         
      }
      else if(ptopic->m_atom == ::id_click)
      {

         m_atomResponse = ptopic->user_interaction()->m_atom;

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

      auto second = (m_timeDelay - tickTimeout).integral_second();
      
      if(second.m_i <= 0)
      {
         
         return;
         
      }
      
      if(second == m_second)
      {
         
         return;
         
      }
      
      m_second = second;
      
      auto pinteraction = m_pform->get_child_by_id("timeout");
      
      if (pinteraction)
      {

         string str;

         str.format("%d", second.m_i);

         pinteraction->_001SetText(str, ::e_source_sync);

      }

      if (m_pformdocument != nullptr)
      {

         payload("wait_message_dialog_timeout") = second;

         m_pform->soft_reload();

      }

      m_pform->set_need_redraw();

   }


} // namespace userex





