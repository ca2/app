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


   bool orto_button::pre_create_window(::user::create_struct& cs)
   {
      //   cs.style |= BS_OWNERDRAW;
      return ::user::button::pre_create_window(cs);
   }



   void orto_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      ::user::interaction::get_client_rect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      COLORREF crText;

      if (!is_window_enabled())
      {

         pgraphics->fill_rect(rectClient, ARGB(255, 90, 90, 80));

         crText = ARGB(255, 49, 50, 23);

      }
      else if (m_itemHover.is_set())
      {

         pgraphics->fill_rect(rectClient, ARGB(190, 49, 50, 23));

         crText = ARGB(255, 255, 255, 255);

      }
      else if (has_focus())
      {

         pgraphics->fill_rect(rectClient, ARGB(255, 255, 250, 184));

         crText = ARGB(255, 255, 255, 255);

      }
      else
      {

         crText = ARGB(255, 243, 243, 233);

      }

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         pgraphics->set_font(this);

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

         ::rect rectIcon(rectClient);

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
      LPMESSAGE pmsg = (LPMESSAGE)lParam;

      if (wParam == WM_MOUSEMOVE)
      {
         ::point pointCursor = pmsg->pt;

         ::rect rectClient;
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
      if (ptimer->m_nIDEvent == timer_check_focus)
      {
         /*if(m_bFocus)
         {
         ::point pointCursor;
         Session.get_cursor_pos(&pointCursor);
         ::rect rectClient;
         ::user::interaction::get_client_rect(rectClient);
         ::user::interaction::_001ClientToScreen(rectClient);

         if(rectClient.is_empty().contains(pointCursor))
         {
         KillTimer(ptimer->m_nIDEvent);
         m_bFocus = false;
         set_need_redraw();
         }
         }
         else
         {
         KillTimer(ptimer->m_nIDEvent);
         }*/
      }
      else
      {

         //      __pointer(::user::interaction) pwnd = ::user::interaction::GetParent();


         ::rect rect;
         ::user::interaction::get_client_rect(rect);
      }


   }

   void orto_button::UpdateWndRgn()
   {

      ::rect rectClient;

      ::user::interaction::get_client_rect(rectClient);

      m_spregion->create_oval(rectClient);


   }

   void orto_button::install_message_routing(::channel * pchannel)
   {
      ::user::button::install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &orto_button::_001OnShowWindow);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &orto_button::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &orto_button::_001OnLButtonUp);
      //IGUI_MSG_LINK(WM_SIZE, pchannel, this, &orto_button::_001OnSize);
      //   //IGUI_MSG_LINK(WM_TIMER, pchannel, this,&orto_button::_001OnTimer);
   }



   void orto_button::on_hit_test(::user::item & item)
   {

      if (m_spregion.is_null())
      {

         item = ::user::element_none;

         return;

      }

      if (!m_spregion->contains(item.m_pointHitTest))
      {

         item = ::user::element_none;

         return;

      }

      item = ::user::element_client;

   }


} // namespace user













