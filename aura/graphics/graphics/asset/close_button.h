#pragma once


namespace user
{


   inline void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = øcreate < ::draw2d::pen > ();

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::double_rectangle double_rectangle(pitem->m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ppen->create_solid(double_rectangle.minimum_dimension() / 10.0, color);

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

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(double_rectangle, color);

      if (color.get_hls().m_dL <= 0.5)
      {

         // If color is dark (dark mode?)
         // blend lighter pixel at top-right edge
         // so that the button looks more sharply square-edged

         auto colorLighter = color;

         colorLighter.hls_rate(0.0, 0.312569, 0.0);

         colorLighter.m_iA = 127;

         pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::int_size(1, 0), colorLighter);

      }

      double_rectangle.deflate(double_rectangle.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(double_rectangle, stock_icon_close);


   }


} // namespace user


