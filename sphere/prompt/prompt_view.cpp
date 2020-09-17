#include "framework.h"
#include "aura/update.h"
#include "acme/const/timer.h"


namespace prompt
{


   view::view(::layered * pobjectContext) :
      ::object(pobject),
      ::user::interaction(pobject)
   {

   }


   view::~view()
   {

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_SIZE, pchannel, this, &view::_001OnSize);
      IGUI_MSG_LINK(WM_PAINT, pchannel, this, &view::_001OnPaint);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &view::_001OnCreate);
      IGUI_MSG_LINK(WM_CONTEXTMENU, pchannel, this, &view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this, &view::_001OnSetCursor);

      //   IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &::user::interaction::_001OnLButtonUp);
      //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
      //IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &::user::interaction::_001OnKeyUp);

      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_RBUTTONUP, pchannel, this, &view::_001OnRButtonUp);
//

      IGUI_MSG_LINK(MessageOp, pchannel, this, &view::_001OnOp);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &view::_001OnShowWindow);




   }
   /////////////////////////////////////////////////////////////////////////////
   // view drawing

   void view::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
   }

   /////////////////////////////////////////////////////////////////////////////
   // view diagnostics


   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }




   void view::update(::update * pupdate)
   {
      
      if(pupdate->m_id == id_update_current_area)
      {

         SetTimer(::timer_update_current_area, 100, nullptr);

      }

   }


   void view::_001OnDestroy(::message::message * pmessage)
   {
      ::user::impact::_001OnDestroy(pmessage);
   }

   void view::_001OnSize(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::rect rectDesktop;

      best_monitor(rectDesktop);

      ::rect rectClient = get_client_rect();
      
      //get_client_rect(rectClient);
      
      rectClient.deflate(2, 2);
      
      i32 iW = rectClient.width() / 2;
      
      i32 iH = rectClient.height() / 2;
      
      iH = MIN(iH, 120);
      
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (i32) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (i32) (iH * rScreen);
      }
   }

   void view::_001OnPaint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


   void view:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   void view::_001OnCreate(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;
      SetTimer(543218, 1000, nullptr);
   }


   void view::_001OnContextMenu(::message::message * pmessage)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pmessage);
//      ::point point = pcontextmenu->GetPoint();


   }


   void view::_001OnTabClick(i32 iTab)
   {
      if(iTab == 1)
      {
         Application.message_box(nullptr, "Playlist");
      }
   }

   void view::_001OnSetCursor(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::_001OnLButtonDown(::message::message * pmessage)
   {
      //   SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::_001OnLButtonUp(::message::message * pmessage)
   {
      //SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);
      KillTimer(5432180);


   }

   void view::_001OnRButtonUp(::message::message * pmessage)
   {
      //SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::_001OnOp(::message::message * pmessage)
   {
      //SCAST_PTR(::message::base, pbase, pmessage);
      UNREFERENCED_PARAMETER(pmessage);
   }


   void view::_001OnTimer(::timer * ptimer)
   {

      ::user::impact::_001OnTimer(ptimer);

   }


   void view::GetDateTime(string & strDateTime)
   {
      ::datetime::time time = ::datetime::time::get_current_time();
      string strDate;
      string strWeekDay;
      string strTime;
      strDate.Format(
      "%04d-%02d-%02d",
      time.GetYear(),
      time.GetMonth(),
      time.GetDay());
      switch(time.GetDayOfWeek())
      {
      case 1:
         strWeekDay = "domingo";
         break;
      case 2:
         strWeekDay = "segunda-feira";
         break;
      case 3:
         strWeekDay = "terça-feira";
         break;
      case 4:
         strWeekDay = "quarta-feira";
         break;
      case 5:
         strWeekDay = "quinta-feira";
         break;
      case 6:
         strWeekDay = "sexta-feira";
         break;
      case 7:
         strWeekDay = "sábado";
         break;
      }
      strTime.Format("%02d:%02d:%02d",
                     time.GetHour(),
                     time.GetMinute(),
                     time.GetSecond());
      strDateTime.Format("%s %s %s", strDate.c_str(), strWeekDay.c_str(), strTime.c_str());
   }

   void view::_001OnShowWindow(::message::message * pmessage)
   {
      //   SCAST_PTR(::message::show_window, pshowwindow, pmessage);
      UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace prompt

