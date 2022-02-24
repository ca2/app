#pragma once


namespace user
{


   inline void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = __create < ::draw2d::pen > ();

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::rectangle_f64 rectangle_f64(pitem->m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ppen->create_solid(rectangle_f64.minimum_dimension() / 10.0, color);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (puserinteraction->m_pitemHover == ::e_element_close_button)
      {

         color.m_iA = 180;

      }
      else
      {

         color.m_iA = 127;

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectangle_f64, color);

      if (color.get_hls().m_dL <= 0.5)
      {

         // If color is dark (dark mode?)
         // blend lighter pixel at top-right edge
         // so that the button looks more sharply square-edged

         auto colorLighter = color;

         colorLighter.hls_rate(0.0, 0.312569, 0.0);

         colorLighter.m_iA = 127;

         pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::size_i32(1, 0), colorLighter);

      }

      rectangle_f64.deflate(rectangle_f64.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle_f64, stock_icon_close);


   }


} // namespace user


