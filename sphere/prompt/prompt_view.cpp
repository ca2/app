#include "framework.h"
#include "aura/update.h"
#include "acme/constant/timer.h"


namespace prompt
{


   impact::impact(::object * pobject) :
      ::object(pobject),
      ::user::interaction(pobject)
   {

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);
      MESSAGE_LINK(e_message_size, pchannel, this, &impact::on_message_size);
      MESSAGE_LINK(e_message_paint, pchannel, this, &impact::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &impact::on_message_set_cursor);

      //   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
      //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::on_message_left_button_up);
      //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
      //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &impact::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &impact::on_message_left_button_up);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &impact::on_message_right_button_up);
//

      MESSAGE_LINK(MessageOp, pchannel, this, &impact::_001OnOp);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &impact::on_message_show_window);




   }
   /////////////////////////////////////////////////////////////////////////////
   // impact drawing

   void impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
   }

   /////////////////////////////////////////////////////////////////////////////
   // impact diagnostics


   void impact::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // impact message handlers

   // vmpLightView.cpp : implementation of the impact class
   //


   /////////////////////////////////////////////////////////////////////////////
   // impact


   bool impact::pre_create_window(::user::system * pusersystem)
   {



      return ::user::impact::pre_create_window(pusersystem);

   }




   void impact::handle(::subject * psubject, ::context * pcontext)
   {
      
      if(psubject->id() == id_update_current_area)
      {

         SetTimer(::e_timer_update_current_area, 100, nullptr);

      }

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);
   }

   void impact::on_message_size(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      ::rectangle_i32 rectangleDesktop;

      best_monitor(rectangleDesktop);

      ::rectangle_i32 rectangleClient = get_client_rect();
      
      //get_client_rect(rectangleClient);
      
      rectangleClient.deflate(2, 2);
      
      i32 iW = rectangleClient.width() / 2;
      
      i32 iH = rectangleClient.height() / 2;
      
      iH = minimum(iH, 120);
      
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectangleDesktop.width() / (double) rectangleDesktop.height();
      if(r < rScreen)
      {
         iH = (i32) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (i32) (iH * rScreen);
      }
   }

   void impact::_001OnPaint(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }


   void impact:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   void impact::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;
      SetTimer(543218, 1000, nullptr);
   }


   void impact::on_message_context_menu(::message::message * pmessage)
   {
//      __pointer(::message::context_menu) pcontextmenu(pmessage);
//      ::point_i32 point = pcontextmenu->GetPoint();


   }


   void impact::_001OnTabClick(i32 iTab)
   {
      if(iTab == 1)
      {
         message_box(nullptr, "Playlist");
      }
   }

   // void impact::on_message_set_cursor(::message::message * pmessage)
   // {

   //    auto pmouse = pmessage->m_pmouse;

   //    pmouse->m_ecursor = cursor_arrow;

   //    pmessage->previous();

   // }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::on_message_left_button_down(::message::message * pmessage)
   {
      //   auto pmouse = pmessage->m_pmouse;
      __UNREFERENCED_PARAMETER(pmessage);

   }

   void impact::on_message_left_button_up(::message::message * pmessage)
   {
      //auto pmouse = pmessage->m_pmouse;
      __UNREFERENCED_PARAMETER(pmessage);
      KillTimer(5432180);


   }

   void impact::on_message_right_button_up(::message::message * pmessage)
   {
      //auto pmouse = pmessage->m_pmouse;
      __UNREFERENCED_PARAMETER(pmessage);

   }

   void impact::_001OnOp(::message::message * pmessage)
   {
      //__pointer(::user::message) pusermessage(pmessage);
      __UNREFERENCED_PARAMETER(pmessage);
   }


   void impact::_001OnTimer(::timer * ptimer)
   {

      ::user::impact::_001OnTimer(ptimer);

   }


   void impact::GetDateTime(string & strDateTime)
   {
      ::datetime::time time = ::datetime::time::now();
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

   void impact::on_message_show_window(::message::message * pmessage)
   {
      //   __pointer(::message::show_window) pshowwindow(pmessage);
      __UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace prompt

