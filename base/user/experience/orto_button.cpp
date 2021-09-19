#include "framework.h"
#include "base/user/experience/_experience.h"
#include "acme/constant/timer.h"


namespace experience
{


   orto_button::orto_button() :
      m_spregion(e_create)
   {


   }


   orto_button::~orto_button()
   {


   }


   bool orto_button::pre_create_window(::user::system * pusersystem)
   {

      return ::user::button::pre_create_window(pusersystem);

   }


   void orto_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      ::user::interaction::get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      ::color::color crText;

      if (!is_window_enabled())
      {

         pgraphics->fill_rectangle(rectangleClient, argb(255, 90, 90, 80));

         crText = argb(255, 49, 50, 23);

      }
      else if (m_itemHover.is_set())
      {

         pgraphics->fill_rectangle(rectangleClient, argb(190, 49, 50, 23));

         crText = argb(255, 255, 255, 255);

      }
      else if (has_keyboard_focus())
      {

         pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 250, 184));

         crText = argb(255, 255, 255, 255);

      }
      else
      {

         crText = argb(255, 243, 243, 233);

      }

      if (m_estockicon == e_stock_icon_none)
      {

         string str;

         get_window_text(str);

         pgraphics->set_font(this, ::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectangleClient, e_align_center, e_draw_text_single_line);

      }
      else
      {

         ::draw2d::brush_pointer brush(e_create);

         brush->create_solid(crText);

         pgraphics->set(brush);

         ::draw2d::pen_pointer pen(e_create);

         pen->m_dWidth = 1.0;

         pen->m_color = crText;

         pen->set_modified();

         pgraphics->set(pen);

         ::rectangle_i32 rectIcon(rectangleClient);

         rectIcon.deflate(rectIcon.width() / 6, rectIcon.height() / 6);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

      }

   }


   void orto_button::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }

   void orto_button::on_message_left_button_down(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }

   void orto_button::on_message_left_button_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //set_need_redraw();

   }

   //LRESULT orto_button::OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam)
   //{
   //   MESSAGE * pmsg = (MESSAGE *)lParam;

   //   if (wParam == e_message_mouse_move)
   //   {
   //      ::point_i32 pointCursor = pmsg->pt;

   //      ::rectangle_i32 rectangleClient;
   //      ::user::interaction::get_client_rect(rectangleClient);
   //      ::user::interaction::client_to_screen(rectangleClient);

   //      if (rectangleClient.contains(pointCursor))
   //      {
   //         set_need_redraw();
   //      }
   //      else
   //      {
   //         set_need_redraw();
   //      }
   //   }
   //   return 0;
   //}

   void orto_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      UpdateWndRgn();

   }


   void orto_button::_001OnTimer(::timer * ptimer)
   {

      ::experience::button::_001OnTimer(ptimer);
      // TODO: add your message handler code here and/or call default
      if (ptimer->m_uEvent == e_timer_check_focus)
      {
         /*if(m_bFocus)
         {
         ::point_i32 pointCursor;
         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pointCursor = pwindowing->get_cursor_position();
         ::rectangle_i32 rectangleClient;
         ::user::interaction::get_client_rect(rectangleClient);
         ::user::interaction::client_to_screen(rectangleClient);

         if(rectangleClient.is_empty().contains(pointCursor))
         {
         KillTimer(ptimer->m_uEvent);
         m_bFocus = false;
         set_need_redraw();
         }
         }
         else
         {
         KillTimer(ptimer->m_uEvent);
         }*/
      }
      else
      {

         //      __pointer(::user::interaction) puserinteraction = ::user::interaction::get_parent();


         ::rectangle_i32 rectangle;
         ::user::interaction::get_client_rect(rectangle);
      }


   }

   void orto_button::UpdateWndRgn()
   {

      ::rectangle_i32 rectangleClient;

      ::user::interaction::get_client_rect(rectangleClient);

      m_spregion->create_ellipse(rectangleClient);

   }


   void orto_button::install_message_routing(::channel * pchannel)
   {
      ::user::button::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &orto_button::on_message_show_window);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &orto_button::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &orto_button::on_message_left_button_up);
      //MESSAGE_LINK(e_message_size, pchannel, this, &orto_button::on_message_size);
      //   //MESSAGE_LINK(e_message_timer, pchannel, this,&orto_button::_001OnTimer);
   }



   void orto_button::on_hit_test(::item & item)
   {

      if (m_spregion.is_null())
      {

         item = ::e_element_none;

         return;

      }

      if (!m_spregion->contains(item.m_pointHitTest))
      {

         item = ::e_element_none;

         return;

      }

      item = ::e_element_client;

   }


} // namespace user













