#pragma once


namespace user
{


   inline void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_pointer ppen(e_create);

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::rectd rectd(pitem->m_rect);

      auto color = puserinteraction->get_color(pstyle, ::user::element_background);

      ppen->create_solid(rectd.minimum_dimension() / 10.0, color);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (puserinteraction->m_itemHover == ::user::element_close_button)
      {

         color.m_iA = 180;

      }
      else
      {

         color.m_iA = 127;

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rect(rectd, color);

      if (color.get_hls().m_dL <= 0.5)
      {

         // If color is dark (dark mode?)
         // blend lighter pixel at top-right edge
         // so that the button looks more sharply square-edged

         auto colorLighter = color;

         colorLighter.hls_rate(0.0, 0.312569, 0.0);

         colorLighter.m_iA = 127;

         pgraphics->blend_pixel(pitem->m_rect.top_right() - ::size(1, 0), colorLighter);

      }

      rectd.deflate(rectd.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      pgraphics->draw_stock_icon(rectd, stock_icon_close);


   }


} // namespace user


