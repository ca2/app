#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create);

      auto pstyle = puserinteraction->get_style(pgraphics);

      if (!pitem->m_ppath)
      {

         ::rectangle_f64 rectangle(pitem->m_rectangle);

         double dMinimumDimension = rectangle.minimum_dimension();

         double dDeflate = dMinimumDimension / 3.0;

         //double w = rectangle.width();

         //double h = rectangle.height();

         rectangle.deflate(0, dDeflate);

         //double w2 = rectangle.width();

         //double h2 = rectangle.height();

         pitem->m_ppath.create();

         pitem->m_ppath->add_rect(rectangle, 45_degrees);

         pitem->m_ppath->add_rect(rectangle, -45_degrees);

      }

      auto color = puserinteraction->get_color(pstyle, ::user::e_element_background);

      if (puserinteraction->m_itemHover == ::user::e_element_close_icon)
      {

         color.alpha = 180;

      }
      else
      {

         color.alpha = 127;

      }

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill_path(pitem->m_ppath);

   }


   void draw_switch_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::user::item* pitem)
   {

      draw_switch_button(pgraphics, puserinteraction, pitem);

   }


} // namespace user

