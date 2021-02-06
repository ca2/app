#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif
#include "acme/const/timer.h"


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

      ::rectangle_i32 rectClient;

      ::user::interaction::get_client_rect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      color32_t crText;

      if (!is_window_enabled())
      {

         pgraphics->fill_rect(rectClient, argb(255, 90, 90, 80));

         crText = argb(255, 49, 50, 23);

      }
      else if (m_itemHover.is_set())
      {

         pgraphics->fill_rect(rectClient, argb(190, 49, 50, 23));

         crText = argb(255, 255, 255, 255);

      }
      else if (has_focus())
      {

         pgraphics->fill_rect(rectClient, argb(255, 255, 250, 184));

         crText = argb(255, 255, 255, 255);

      }
      else
      {

         crText = argb(255, 243, 243, 233);

      }

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         pgraphics->set_font(this, ::user::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectClient, e_align_center, e_draw_text_single_line);

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

         ::rectangle_i32 rectIcon(rectClient);

         rectIcon.deflate(rectIcon.width() / 6, rectIcon.height() / 6);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

      }

   }


   void orto_button::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }

   void orto_button::_001OnLButtonDown(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }

   void orto_button::_001OnLButtonUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      //set_need_redraw();

   }

   LRESULT orto_button::OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam)
   {
      MESSAGE * pmsg = (MESSAGE *)lParam;

      if (wParam == e_message_mouse_move)
      {
         ::point_i32 pointCursor = pmsg->pt;

         ::rectangle_i32 rectClient;
         ::user::interaction::get_client_rect(rectClient);
         ::user::interaction::_001ClientToScreen(rectClient);

         if (rectClient.contains(pointCursor))
         {
            set_need_redraw();
         }
         else
         {
            set_need_redraw();
         }
      }
      return 0;
   }

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
         psession->get_cursor_pos(&pointCursor);
         ::rectangle_i32 rectClient;
         ::user::interaction::get_client_rect(rectClient);
         ::user::interaction::_001ClientToScreen(rectClient);

         if(rectClient.is_empty().contains(pointCursor))
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

         //      __pointer(::user::interaction) pwnd = ::user::interaction::get_parent();


         ::rectangle_i32 rectangle;
         ::user::interaction::get_client_rect(rectangle);
      }


   }

   void orto_button::UpdateWndRgn()
   {

      ::rectangle_i32 rectClient;

      ::user::interaction::get_client_rect(rectClient);

      m_spregion->create_oval(rectClient);


   }

   void orto_button::install_message_routing(::channel * pchannel)
   {
      ::user::button::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &orto_button::_001OnShowWindow);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &orto_button::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &orto_button::_001OnLButtonUp);
      //MESSAGE_LINK(e_message_size, pchannel, this, &orto_button::_001OnSize);
      //   //MESSAGE_LINK(e_message_timer, pchannel, this,&orto_button::_001OnTimer);
   }



   void orto_button::on_hit_test(::user::item & item)
   {

      if (m_spregion.is_null())
      {

         item = ::user::e_element_none;

         return;

      }

      if (!m_spregion->contains(item.m_pointHitTest))
      {

         item = ::user::e_element_none;

         return;

      }

      item = ::user::e_element_client;

   }


} // namespace user













