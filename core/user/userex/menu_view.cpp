#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif


menu_view::menu_view()
{
   
}


void menu_view::on_apply(::action * paction)
{
   ::user::form_view::on_apply(paction);
}


void menu_view::on_control_event(::user::control_event * pevent)
{

   Application.on_control_event(pevent);

   if(pevent->m_bRet)
   {

      return;

   }

   if(m_pcallback != nullptr)
   {

      m_pcallback->on_control_event(pevent);

   }

   if(GetParent() != nullptr)
   {

      GetParent()->on_control_event(pevent);

      if(pevent->m_bRet)
      {

         return;

      }

   }

}


void menu_view::install_message_routing(::channel * pchannel)
{
   ::user::form::install_message_routing(pchannel);
   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &menu_view::_001OnCreate);
//   //IGUI_MSG_LINK(WM_TIMER, pchannel, this, &menu_view::_001OnTimer);
   //IGUI_MSG_LINK(WM_USER + 123, pchannel, this, &menu_view::_001OnUser123);

}


void menu_view::_001OnCreate(::message::message * pmessage)
{
   pmessage->previous();
}


void menu_view::_001OnTimer(::timer * ptimer)
{

   ::user::form_view::_001OnTimer(ptimer);;

   if(m_pcallback != nullptr)
   {

      ::user::control_event ev;

      ev.m_eevent = ::user::event_timer;

      ev.m_uiEvent = ptimer->m_uEvent;
      
      ev.m_etimer = ptimer->m_etimer;

      ev.m_puie = this;

      Application.on_control_event(&ev);

      if(ev.m_bRet)
      {

         return;

      }

      m_pcallback->on_control_event(&ev);

   }

   if(ptimer->m_uEvent == 24)
   {

      KillTimer(24);

      GetTopLevelFrame()->EndModalLoop(IDOK);

   }

}


//void menu_view::_001OnUser123(::message::message * pmessage)
//{
//   SCAST_PTR(::message::base, pbase, pmessage);
//   if(pbase->m_wparam == 0x80000001)
//   {
//      GetTopLevel()->EndModalLoop(IDOK);
//      return;
//   }
//   if(m_pcallback != nullptr)
//   {
//      m_pcallback->OnUser123(pbase->m_wparam, pbase->m_lparam);
//   }
//}
