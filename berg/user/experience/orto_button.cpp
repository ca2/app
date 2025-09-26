#include "framework.h"
#include "orto_button.h"
#include "acme/constant/user_message.h"
#include "acme/constant/timer.h"
#include "acme/handler/item.h"
#include "acme/platform/timer.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"


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

      ::int_rectangle rectangleX;

      rectangleX = ::user::interaction::rectangle();

      if (rectangleX.area() <= 0)
      {

         return;

      }

      ::color::color crText;

      if (!is_window_enabled())
      {

         pgraphics->fill_rectangle(rectangleX, argb(255, 90, 90, 80));

         crText = argb(255, 49, 50, 23);

      }
      else if (::is_set(m_pitemHover))
      {

         pgraphics->fill_rectangle(rectangleX, argb(190, 49, 50, 23));

         crText = argb(255, 255, 255, 255);

      }
      else if (has_keyboard_focus())
      {

         pgraphics->fill_rectangle(rectangleX, argb(255, 255, 250, 184));

         crText = argb(255, 255, 255, 255);

      }
      else
      {

         crText = argb(255, 243, 243, 233);

      }

      if (m_estockicon == e_stock_icon_none)
      {

         auto strWindowText = get_window_text();

         //get_window_text(str);

         pgraphics->set_font(this, ::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strWindowText, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         auto pbrush = øcreate < ::draw2d::brush >();

         pbrush->create_solid(crText);

         pgraphics->set(pbrush);

         auto ppen = øcreate < ::draw2d::pen > ();

         ppen->m_dWidth = 1.0;

         ppen->m_color = crText;

         ppen->set_modified();

         pgraphics->set(ppen);

         ::int_rectangle rectangleIcon(rectangleX);

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

   //   if (wParam == ::user::e_message_mouse_move)
   //   {
   //      ::int_point pointCursor = pmsg->pt;

   //      ::int_rectangle rectangleX;
   //      ::user::interaction::this->rectangle(rectangleX);
   //      ::user::interaction::client_to_screen(rectangleX);

   //      if (rectangleX.contains(pointCursor))
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


   void orto_button::on_timer(::timer * ptimer)
   {

      ::experience::button::on_timer(ptimer);
      // TODO: add your message handler code here and/or call default
      if (ptimer->m_uTimer == e_timer_check_focus)
      {
         /*if(m_bFocus)
         {
         ::int_point pointCursor;
         

         auto puser = user();

         auto pwindowing = system()->windowing();

         pointCursor = pwindowing->get_cursor_position();
         ::int_rectangle rectangleX;
         ::user::interaction::this->rectangle(rectangleX);
         ::user::interaction::client_to_screen(rectangleX);

         if(rectangleX.is_empty().contains(pointCursor))
         {
         kill_timer(ptimer->m_uTimer);
         m_bFocus = false;
         set_need_redraw();
         }
         }
         else
         {
         kill_timer(ptimer->m_uTimer);
         }*/
      }
      else
      {

         //      ::pointer<::user::interaction>puserinteraction = ::user::interaction::get_parent();


         ::int_rectangle rectangle;
         rectangle = ::user::interaction::rectangle();
      }


   }


   void orto_button::UpdateWndRgn()
   {

      ::int_rectangle rectangleX;

      rectangleX = ::user::interaction::rectangle();

      ødefer_construct(m_pregion);
      
      ::double_ellipse ellipse;
      
      ellipse.set(rectangleX);

      m_pregion->create_ellipse(ellipse);

   }


   void orto_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &orto_button::on_message_show_window);
      USER_MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &orto_button::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &orto_button::on_message_left_button_up);
      //USER_MESSAGE_LINK(::user::e_message_size, pchannel, this, &orto_button::on_message_size);
      //   //USER_MESSAGE_LINK(::user::e_message_timer, pchannel, this,&orto_button::on_timer);
   }



   ::item_pointer orto_button::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      if (m_pregion.is_null())
      {

         return øallocate ::item(::e_element_none);

      }

      if (!m_pregion->contains(point))
      {

         return stock_item(::e_element_none);

      }

      return stock_item(::e_element_client);

   }


} // namespace user













