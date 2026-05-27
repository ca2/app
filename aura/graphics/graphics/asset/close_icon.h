#pragma once

namespace user
{


   inline void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      if (!pitem->m_ppath)
      {

         ::f64_rectangle rectangle(pitem->m_rectangle);

         ::f64 dMinimumDimension = rectangle.minimum_dimension();

         ::f64 dDeflate = dMinimumDimension / 3.0;

         ::f64 w = rectangle.width();

         ::f64 h = rectangle.height();

         rectangle.deflate(0, dDeflate);

         ::f64 w2 = rectangle.width();

         ::f64 h2 = rectangle.height();

         pitem->m_ppath.create();

         pitem->m_ppath->add_rect(rectangle, 45_degrees);

         pitem->m_ppath->add_rect(rectangle, -45_degrees);

      }

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      if (puserinteraction->m_pitemHover == ::e_element_close_icon)
      {

         color.m_iA = 180;

      }
      else
      {

         color.m_iA = 127;

      }

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill_path(pitem->m_ppath);

   }


} // namespace user

