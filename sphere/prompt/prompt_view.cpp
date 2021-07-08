#include "framework.h"
#include "aura/update.h"
#include "acme/const/timer.h"


namespace prompt
{


   view::view(::object * pobject) :
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

      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &view::on_message_size);
      MESSAGE_LINK(e_message_paint, pchannel, this, &view::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &view::_001OnContextMenu);
      MESSAGE_LINK(e_message_set_cursor, pchannel, this, &view::on_message_set_cursor);

      //   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
      //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::on_message_left_button_up);
      //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
      //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &view::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &view::on_message_left_button_up);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &view::on_message_right_button_up);
//

      MESSAGE_LINK(MessageOp, pchannel, this, &view::_001OnOp);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &view::on_message_show_window);




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


   bool view::pre_create_window(::user::system * pusersystem)
   {



      return ::user::impact::pre_create_window(pusersystem);

   }




   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {
      
      if(psubject->id() == id_update_current_area)
      {

         SetTimer(::e_timer_update_current_area, 100, nullptr);

      }

   }


   void view::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);
   }

   void view::on_message_size(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::rectangle_i32 rectDesktop;

      best_monitor(rectDesktop);

      ::rectangle_i32 rectangleClient = get_client_rect();
      
      //get_client_rect(rectangleClient);
      
      rectangleClient.deflate(2, 2);
      
      i32 iW = rectangleClient.width() / 2;
      
      i32 iH = rectangleClient.height() / 2;
      
      iH = minimum(iH, 120);
      
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


   void view::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;
      SetTimer(543218, 1000, nullptr);
   }


   void view::_001OnContextMenu(::message::message * pmessage)
   {
//      __pointer(::message::context_menu) pcontextmenu(pmessage);
//      ::point_i32 point = pcontextmenu->GetPoint();


   }


   void view::_001OnTabClick(i32 iTab)
   {
      if(iTab == 1)
      {
         message_box(nullptr, "Playlist");
      }
   }

   void view::on_message_set_cursor(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::on_message_left_button_down(::message::message * pmessage)
   {
      //   __pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::on_message_left_button_up(::message::message * pmessage)
   {
      //__pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);
      KillTimer(5432180);


   }

   void view::on_message_right_button_up(::message::message * pmessage)
   {
      //__pointer(::message::mouse) pmouse(pmessage);
      UNREFERENCED_PARAMETER(pmessage);

   }

   void view::_001OnOp(::message::message * pmessage)
   {
      //__pointer(::user::message) pusermessage(pmessage);
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

   void view::on_message_show_window(::message::message * pmessage)
   {
      //   __pointer(::message::show_window) pshowwindow(pmessage);
      UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace prompt

