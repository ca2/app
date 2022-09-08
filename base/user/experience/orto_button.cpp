#include "framework.h"
#include "orto_button.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "acme/constant/timer.h"
//#include "aura/graphics/draw2d/_component.h"
#include "acme/platform/timer.h"


namespace experience
{


   orto_button::orto_button()
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
      else if (::is_set(m_pitemHover))
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

         auto pbrush = __create < ::draw2d::brush >();

         pbrush->create_solid(crText);

         pgraphics->set(pbrush);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->m_dWidth = 1.0;

         ppen->m_color = crText;

         ppen->set_modified();

         pgraphics->set(ppen);

         ::rectangle_i32 rectangleIcon(rectangleClient);

         rectangleIcon.deflate(rectangleIcon.width() / 6, rectangleIcon.height() / 6);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

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

      __defer_construct(m_pregion);

      m_pregion->create_ellipse(rectangleClient);

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



   ::item_pointer orto_button::on_hit_test(const ::point_i32 &point)
   {

      if (m_pregion.is_null())
      {

         return __new(::item(::e_element_none));

      }

      if (!m_pregion->contains(point))
      {

         return __new(::item(::e_element_none));

      }

      return __new(::item(::e_element_client));

   }


} // namespace user













