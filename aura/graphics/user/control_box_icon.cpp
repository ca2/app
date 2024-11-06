#include "framework.h"
#include "control_box_button.h"
#include "acme/handler/item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/user/user/interaction.h"


namespace user
{


   void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      if (!useritem.m_ppath)
      {

         auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

         //::double_rectangle rectangle(useritem.m_rectangle);

         rectangle.rate(0.89);

         double dMinimumDimension = rectangle.minimum_dimension();

         double dDeflate = dMinimumDimension / 3.0;

         //double w = rectangle.width();

         //double h = rectangle.height();

         rectangle.deflate(0, dDeflate);

         //double w2 = rectangle.width();

         //double h2 = rectangle.height();

         ::draw2d::path_pointer ppath;

         puserinteraction->__construct(ppath);

         ppath->add_rectangle(rectangle, 45_degrees);

         ppath->add_rectangle(rectangle, -45_degrees);

         useritem.m_ppath = ppath;

      }

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      if (::is_element(puserinteraction->m_pitemHover, ::e_element_close_icon))
      {

         color.m_uchOpacity = 189;

      }
      else
      {

         color.m_uchOpacity = 121;

      }

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill(useritem.m_ppath);

   }


   void draw_switch_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      draw_switch_button(pgraphics, puserinteraction, useritem, estate);

   }


   void draw_maximize_icon(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->__create < ::draw2d::pen >();

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::double_rectangle rectangle(useritem.m_rectangle);

      auto colorPen = puserinteraction->get_color(pstyle, ::e_element_background);

      if (estate & ::user::e_state_hover)
      {

         colorPen.m_uchOpacity = 189;

      }
      else
      {

         colorPen.m_uchOpacity = 121;

      }

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      rectangle.deflate(rectangle.minimum_dimension() * 0.15, rectangle.minimum_dimension() * 0.15, rectangle.minimum_dimension() * 0.15, rectangle.minimum_dimension() * 0.10);

      ppen->create_solid(rectangle.minimum_dimension() / 3.0, colorPen);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_zoom);


   }


   void draw_minimize_icon(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->__create < ::draw2d::pen >();

      //::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::double_rectangle rectangle(useritem.m_rectangle);

      auto colorPen = puserinteraction->get_color(pstyle, ::e_element_background);

      if (estate & ::user::e_state_hover)
      {

         colorPen.m_uchOpacity = 189;

      }
      else
      {

         colorPen.m_uchOpacity = 121;

      }

      rectangle.deflate(rectangle.minimum_dimension() * 0.077, rectangle.minimum_dimension() * 0.11, rectangle.minimum_dimension() * 0.077, rectangle.minimum_dimension() * 0.13);

      ppen->create_solid(rectangle.minimum_dimension() / 3.0, colorPen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_iconify);

   }


} // namespace user



