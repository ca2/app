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

      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::_001OnDestroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &view::_001OnSize);
      MESSAGE_LINK(e_message_paint, pchannel, this, &view::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::_001OnCreate);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &view::_001OnContextMenu);
      MESSAGE_LINK(e_message_set_cursor, pchannel, this, &view::_001OnSetCursor);

      //   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::_001OnLButtonDown);
      //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::_001OnLButtonUp);
      //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::_001OnKeyDown);
      //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::_001OnKeyUp);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &view::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &view::_001OnLButtonUp);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &view::_001OnRButtonUp);
//

      MESSAGE_LINK(MessageOp, pchannel, this, &view::_001OnOp);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &view::_001OnShowWindow);




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


   bool view::pre_create_window(::user::create_struct * pcreatestruct)
   {



      return ::user::impact::pre_create_window(pcreatestruct);

   }




   void view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {
      
      if(psubject->id() == id_update_current_area)
      {

         SetTimer(::e_timer_update_current_area, 100, nullptr);

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
      
      iH = min(iH, 120);
      
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
//      __pointer(::message::context_menu) pcontextmenu(pmessage);
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

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::_001OnLButtonDown(::message::message * pmessage)
   {
      //   __pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::_001OnLButtonUp(::message::message * pmessage)
   {
      //__pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);
      KillTimer(5432180);


   }

   void view::_001OnRButtonUp(::message::message * pmessage)
   {
      //__pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::_001OnOp(::message::message * pmessage)
   {
      //__pointer(::message::base) pbase(pmessage);
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
         strWeekDay = "q::u32a-feira";
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
      //   __pointer(::message::show_window) pshowwindow(pmessage);
      UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace prompt

