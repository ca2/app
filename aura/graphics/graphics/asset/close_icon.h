#pragma once

namespace user
{


   inline void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      if (!pitem->m_ppath)
      {

         ::rectd rect(pitem->m_rect);

         double dMinimumDimension = rect.minimum_dimension();

         double dDeflate = dMinimumDimension / 3.0;

         double w = rect.width();

         double h = rect.height();

         rect.deflate(0, dDeflate);

         double w2 = rect.width();

         double h2 = rect.height();

         pitem->m_ppath.create();

         pitem->m_ppath->add_rect(rect, 45_degrees);

         pitem->m_ppath->add_rect(rect, -45_degrees);

      }

      auto color = puserinteraction->get_color(pstyle, ::user::e_element_background);

      if (puserinteraction->m_itemHover == ::user::e_element_close_icon)
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

