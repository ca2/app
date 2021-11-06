#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->__create < ::draw2d::pen > ();

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::rectangle_f64 rectangle(pitem->m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ppen->create_solid(rectangle.minimum_dimension() / 10.0, color);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (puserinteraction->m_itemHover == ::e_element_close_button)
      {

         color.alpha = 180;

      }
      else
      {

         color.alpha = 127;

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

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

      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_close);

   }


   void draw_switch_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      ::rectangle_f64 rectangle(pitem->m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (puserinteraction->m_itemHover == ::e_element_switch_button)
      {

         color.alpha = 180;

      }
      else
      {

         color.alpha = 127;

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

   }


} // namespace user


