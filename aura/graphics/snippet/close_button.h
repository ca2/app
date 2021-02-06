#pragma once


namespace user
{


   inline void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_pointer ppen(e_create);

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::rectangle_f64 rectangle_f64(pitem->m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::user::e_element_background);

      ppen->create_solid(rectangle_f64.minimum_dimension() / 10.0, color);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (puserinteraction->m_itemHover == ::user::e_element_close_button)
      {

         color.alpha = 180;

      }
      else
      {

         color.alpha = 127;

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rect(rectangle_f64, color);

      if (color.get_luminance() <= 0.5)
      {

         // If color is dark (dark mode?)
         // blend lighter pixel at top-right edge
         // so that the button looks more sharply square-edged

         auto colorLighter = color;

         colorLighter.hls_rate(0.0, 0.312569, 0.0);

         colorLighter.alpha = 127;

         pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::size_i32(1, 0), colorLighter);

      }

      rectangle_f64.deflate(rectangle_f64.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle_f64, stock_icon_close);

   }


} // namespace user


