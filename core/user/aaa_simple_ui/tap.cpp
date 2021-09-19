#include "framework.h"
#include "core/user/simple_ui/_simple_ui.h"

namespace simple_ui
{


   tap::tap()
   {

      m_bAutoStockIconPenWidth   = true;
      m_dStockIconPenWidth       = 2.0;
      m_estockicon               = stock_icon_none;

      m_id                       = "submit";
      m_bDown                    = false;
      m_bMouseMove               = false;

   }


   tap::~tap()
   {
   }


   void tap::install_message_routing(::channel * pchannel)
   {
      //IMPL_IMH(tap, ::user::interaction)
      //   MSG_CREATE
      //   MSG_KEYDOWN
      //   MSG_LBUTTONDOWN
      //   MSG_LBUTTONUP
      //   MSG_MOUSEMOVE
      //   MSG_MOUSELEAVE
      //   END_IMH
      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tap::on_message_create);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &tap::on_message_key_down);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &tap::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tap::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &tap::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &tap::on_message_mouse_leave);
      //MESSAGE_LINK(e_message_create, pchannel, this, &tap::on_message_create);
      //MESSAGE_LINK(e_message_create, pchannel, this, &tap::on_message_create);


   }


   void tap::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      INFO("simple_ui::_001OnDraw pos(%d,%d)", layout().sketch().origin().x, layout().sketch().origin().y);
      INFO("simple_ui::_001OnDraw scr_pos(%d,%d)", screen_origin().x, screen_origin().y);

      simple_ui_draw_volume(pgraphics);

   }


   void tap::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void tap::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->m_bRet = true;

      if(keyboard_focus_is_focusable())
      {

         set_keyboard_focus();

      }
      else
      {

         get_wnd()->show_keyboard(false);

      }

      m_bDown = true;

   }


   void tap::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->m_bRet = true;

      if (m_bDown)
      {

         m_bDown = false;

         on_action(m_id);

      }

   }


   void tap::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      INFO("simple_ui::tap::on_message_mouse_move");

      pmouse->m_bRet = true;

      m_bMouseMove = true;

      if (!m_itemHover.is_set())
      {

         track_mouse_hover();

         m_itemHover = ::e_element_client;

         set_need_redraw();

      }

   }


   void tap::on_message_mouse_leave(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      m_bMouseMove = false;

      m_itemHover = ::e_element_none;

      set_need_redraw();

   }


   bool tap::keyboard_focus_is_focusable() const
   {

#if defined(APPLE_IOS) || defined(VS_NORD)

      return false;

#else

      return true;

#endif

   }


   bool tap::is_hover()
   {

      ::rectangle_i32 rectWindow;

      get_window_rect(&rectWindow);

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      bool bHover = rectWindow.contains(pointCursor);

      if (!bHover)
      {

         m_bMouseMove = false;

      }

      return bHover;


   }



   void tap::simple_ui_draw_simple(::draw2d::graphics_pointer & pgraphics)
   {



      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         ::draw2d::brush_pointer br(e_create);

#if CA2_PLATFORM_VERSION == CA2_BASIS

         br->create_solid(argb(190, 255, 184, 240));

#else

         br->create_solid(argb(190, 190, 255, 177));

#endif

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         pgraphics->fill_rectangle(rectangleClient, br);

      }

      simple_ui_draw_text(pgraphics);

   }


   void tap::simple_ui_draw_volume(::draw2d::graphics_pointer & pgraphics)
   {

      {



         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         color32_t crOut;

         color32_t crIn;

         color32_t crBorderOut;

         color32_t crBorderIn;

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         ::datetime::time timeNow = ::datetime::time::get_current_time();

         if (is_hover() || m_bDown || m_bMouseMove)
         {

#if CA2_PLATFORM_VERSION == CA2_BASIS

            if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
            {

               crOut = argb(114, 255, 230, 255);

               crIn = argb(255, 255, 133, 255);

               crBorderOut = argb(190, 150, 100, 150);

               crBorderIn = argb(190, 255, 240, 255);

            }
            else
            {

               crOut = argb(114, 205, 180, 205);

               crIn = argb(255, 205, 83, 205);

               crBorderOut = argb(190, 100, 50, 100);

               crBorderIn = argb(190, 205, 190, 205);

            }


#else

            if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
            {


               crOut = argb(1140, 230, 255, 225);

               crIn = argb(255, 133, 255, 80 + 49);

               crBorderOut = argb(190, 100, 150, 100);

               crBorderIn = argb(190, 240, 255, 235);
            }
            else
            {
               crOut = argb(1140, 230, 255, 225);

               crIn = argb(255, 133, 255, 80 + 49);

               crBorderOut = argb(190, 100, 150, 100);

               crBorderIn = argb(190, 240, 255, 235);

            }

#endif

         }
         else
         {

#if CA2_PLATFORM_VERSION == CA2_BASIS

            if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
            {

               crOut = argb(190, 255, 210, 255);

               crIn = argb(255, 255, 114, 255);

               crBorderOut = argb(190, 90, 20, 90);

               crBorderIn = argb(190, 255, 240, 255);

            }
            else
            {

               crOut = argb(190, 205, 120, 205);

               crIn = argb(255, 205, 134, 205);

               crBorderOut = argb(190, 40, 0, 40);

               crBorderIn = argb(190, 205, 120, 205);

            }

#else

            crOut = argb(190, 210, 255, 205);

            crIn = argb(255, 133, 255, 80 + 49);

            crBorderOut = argb(190, 20, 90, 20);

            crBorderIn = argb(190, 240, 255, 235);

#endif

         }

         if(m_estockicon != stock_icon_none)
         {

            //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

            ::draw2d::brush_pointer br(e_create);

            br->create_solid(crBorderIn);

            pgraphics->set(br);

            pgraphics->fill_rectangle(rectangleClient,br);

            ::draw2d::pen_pointer pen(e_create);

            pen->create_solid(m_dStockIconPenWidth,crBorderOut);

            pgraphics->set(pen);

            pgraphics->draw_stock_icon(rectangleClient,m_estockicon);

            return;

         }

         i32 iBorderH = rectangleClient.height() / 2;

         ::draw2d::brush_pointer br(e_create);

         br->CreateLinearGradientBrush(point_i32(rectangleClient.left, rectangleClient.top - 1), point_i32(rectangleClient.left, rectangleClient.top + iBorderH + 2), crOut, crIn);

         pgraphics->fill_rectangle(::rectangle_i32(rectangleClient.left + 1, rectangleClient.top + 1, (i32)rectangleClient.width(), iBorderH), br);

         br->CreateLinearGradientBrush(point_i32(rectangleClient.left, rectangleClient.top + iBorderH - 1), point_i32(rectangleClient.left, rectangleClient.top + iBorderH * 2 + 2), crIn, crOut);

         pgraphics->fill_rectangle(::rectangle_i32(rectangleClient.left + 1, rectangleClient.top + iBorderH, rectangleClient.left + (i32)rectangleClient.width(), rectangleClient.top + iBorderH + iBorderH), br);

         /*Gdiplus::Pen pen1(crBorderOut);

         graphics2.DrawRectangle(&pen1, rectangleClient.left, rectangleClient.top, rectangleClient.width(), iBorderH * 2);*/

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1.0, crBorderIn);

         pgraphics->draw_rectangle(::rectangle_i32(rectangleClient.left + 1, rectangleClient.top + 1, rectangleClient.left + (i32)rectangleClient.width() - 2, rectangleClient.top + iBorderH * 2 - 2), pen);

      }

      if(m_estockicon == stock_icon_none)
      {

         simple_ui_draw_text(pgraphics);

      }

   }


   void tap::simple_ui_draw_text(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      color32_t crText;

#if CA2_PLATFORM_VERSION == CA2_BASIS

      if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
      {

         crText = argb(223, 74, 39, 67);

      }
      else
      {

         crText = argb(223, 255, 255, 255);

      }


#else

      if (timeNow.GetHour() >= 6 && timeNow.GetHour() <= 17)
      {

         crText = argb(223, 49, 90, 23);

      }
      else
      {

         crText = argb(223, 49, 90, 23);
      }

#endif

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(crText);

      pgraphics->set(b);

      //float fMargin = (rectangleClient.height() * ((1.0f - 0.7f) / 2.0f));

      float fMargin = (rectangleClient.height() * ((1.0f - 0.84f) / 2.0f));

      rectangleClient.deflate((i32) fMargin, (i32) fMargin);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font(pnode->font_name(e_font_sans_ex), (i32)rectangleClient.height()* 0.7);

      pgraphics->set(f);

      pgraphics->draw_text(get_window_text(), rectangleClient, e_align_left_center);

   }


   void tap::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         on_action(m_id);

         pkey->m_bRet = true;

      }
      else if (iKey == ::user::e_key_tab)
      {

         keyboard_set_focus_next();

         pkey->m_bRet = true;

      }
      else
      {

         pkey->m_bRet = false;

      }

   }


   void tap::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(m_bAutoStockIconPenWidth)
      {

         m_dStockIconPenWidth = rectangleClient.minimum_natural_dimension() / 12.5;

      }

   }


   void tap::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      user::interaction::_000OnDraw(pgraphics);

   }

   void tap::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      user::interaction::_001DrawThis(pgraphics);

   }

   void tap::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      user::interaction::_001CallOnDraw(pgraphics);

   }

} // namespace simple_ui



