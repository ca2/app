#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/graphics/draw2d/_draw2d.h"


namespace user
{


   void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

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

         ::draw2d::path_pointer ppath;

         ppath.create(puserinteraction);

         ppath->add_rectangle(rectangle, 45_degrees);

         ppath->add_rectangle(rectangle, -45_degrees);

         pitem->m_ppath = ppath;

      }

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      if (::is_element(puserinteraction->m_pitemHover, ::e_element_close_icon))
      {

         color.alpha = 180;

      }
      else
      {

         color.alpha = 127;

      }

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill(pitem->m_ppath);

   }


   void draw_switch_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::item* pitem)
   {

      draw_switch_button(pgraphics, puserinteraction, pitem);

   }


} // namespace user

