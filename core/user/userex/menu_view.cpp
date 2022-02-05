#include "framework.h"
#include "acme/platform/timer.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



menu_view::menu_view()
{
   
}


void menu_view::handle(::topic * ptopic, ::context * pcontext)
{
   ::user::form_view::handle(ptopic, pcontext);

   auto papplication = get_application();

   papplication->handle(ptopic, pcontext);

   if (ptopic->m_pextendedtopic->m_bRet)
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

      if (ptopic->m_pextendedtopic->m_bRet)
      {

         return;

      }

   }


}

//
//void menu_view::handle(::topic * ptopic, ::context * pcontext)
//{
//
//   auto papplication = get_application();
//
//   papplication->handle(ptopic, pcontext);
//
//   if(ptopic->m_pextendedtopic->m_bRet)
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
//      if(ptopic->m_pextendedtopic->m_bRet)
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

void menu_view::install_message_routing(::channel * pchannel)
{
   ::user::form::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &menu_view::on_message_create);
//   //MESSAGE_LINK(e_message_timer, pchannel, this, &menu_view::_001OnTimer);
   //MESSAGE_LINK(WM_USER + 123, pchannel, this, &menu_view::_001OnUser123);

}


void menu_view::on_message_create(::message::message * pmessage)
{
   pmessage->previous();
}


void menu_view::_001OnTimer(::timer * ptimer)
{

   ::user::form_view::_001OnTimer(ptimer);;

   if(m_pcallback != nullptr)
   {

      ::topic topic;

      topic.m_id = ::id_timer;

      topic.m_uiEvent = ptimer->m_uEvent;
      
      topic.m_etimer = ptimer->m_etimer;

      topic.m_puserelement = this;

      auto papplication = get_application();

      papplication->route(&topic);

      if(topic.m_bRet)
      {

         return;

      }

      m_pcallback->route(&topic);

   }

   if(ptimer->m_uEvent == 24)
   {

      KillTimer(24);

      top_level_frame()->EndModalLoop(e_dialog_result_ok);

   }

}


//void menu_view::_001OnUser123(::message::message * pmessage)
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
