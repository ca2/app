#include "framework.h"
#include "acme/platform/timer.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



menu_impact::menu_impact()
{
   
}


void menu_impact::handle(::topic * ptopic, ::context * pcontext)
{
   ::user::form_impact::handle(ptopic, pcontext);

   auto papp = get_app();

   papp->handle(ptopic, pcontext);

   if (ptopic->m_bRet)
   {

      return;

   }

   if (m_pcallback != nullptr)
   {

      m_pcallback->handle(ptopic, pcontext);

   }

   if (get_parent() != nullptr)
   {

      get_parent()->handle(ptopic, pcontext);

      if (ptopic->m_bRet)
      {

         return;

      }

   }


}

//
//void menu_impact::handle(::topic * ptopic, ::context * pcontext)
//{
//
//   auto papp = get_app();
//
//   papp->handle(ptopic, pcontext);
//
//   if(ptopic->m_bRet)
//   {
//
//      return;
//
//   }
//
//   if(m_pcallback != nullptr)
//   {
//
//      m_pcallback->handle(ptopic, pcontext);
//
//   }
//
//   if(get_parent() != nullptr)
//   {
//
//      get_parent()->handle(ptopic, pcontext);
//
//      if(ptopic->m_bRet)
//      {
//
//         return;
//
//      }
//
//   }
//
//}
//

void menu_impact::install_message_routing(::channel * pchannel)
{
   ::user::form::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &menu_impact::on_message_create);
//   //MESSAGE_LINK(e_message_timer, pchannel, this, &menu_impact::_001OnTimer);
   //MESSAGE_LINK(WM_USER + 123, pchannel, this, &menu_impact::_001OnUser123);

}


void menu_impact::on_message_create(::message::message * pmessage)
{
   pmessage->previous();
}


void menu_impact::_001OnTimer(::timer * ptimer)
{

   ::user::form_impact::_001OnTimer(ptimer);;

   if(m_pcallback != nullptr)
   {

      auto pextendedtopic = create_extended_topic(::id_timer);

      pextendedtopic->m_uiEvent = ptimer->m_uEvent;
      
      pextendedtopic->m_etimer = ptimer->m_etimer;

      pextendedtopic->m_puserelement = this;

      auto papp = get_app();

      papp->route(pextendedtopic);

      if(pextendedtopic->m_bRet)
      {

         return;

      }

      m_pcallback->route(pextendedtopic);

   }

   if(ptimer->m_uEvent == 24)
   {

      KillTimer(24);

      top_level_frame()->EndModalLoop(e_dialog_result_ok);

   }

}


//void menu_impact::_001OnUser123(::message::message * pmessage)
//{
//   __pointer(::user::message) pusermessage(pmessage);
//   if(pusermessage->m_wparam == 0x80000001)
//   {
//      get_top_level()->EndModalLoop(e_dialog_result_ok);
//      return;
//   }
//   if(m_pcallback != nullptr)
//   {
//      m_pcallback->OnUser123(pusermessage->m_wparam, pusermessage->m_lparam);
//   }
//}
