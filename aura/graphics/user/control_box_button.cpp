#include "framework.h"
#include "control_box_button.h"
#include "acme/handler/item.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/user/user/interaction.h"


namespace user
{


   void draw_close_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->øcreate < ::draw2d::pen > ();

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (::is_element(puserinteraction->m_pitemHover, ::e_element_close_button))
      {

         color.m_uchOpacity = 211;
         colorPen.m_uchOpacity = 211;

      }
      else
      {

         color.m_uchOpacity = 89;
         colorPen.m_uchOpacity = 89;

      }

      ppen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::int_size(1, 0), colorLighter);

      //}

      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_close);

   }


   void draw_switch_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::double_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      //::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_uchOpacity = 211;
         //colorPen.m_uchOpacity = 211;

      }
      else
      {

         color.m_uchOpacity = 89;
         //colorPen.m_uchOpacity = 89;

      }

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

   }


   void draw_maximize_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->øcreate < ::draw2d::pen >();

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::double_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_uchOpacity = 211;
         colorPen.m_uchOpacity = 211;

      }
      else
      {

         color.m_uchOpacity = 89;
         colorPen.m_uchOpacity = 89;

      }

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::int_size(1, 0), colorLighter);

      //}

      ppen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);


      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_zoom);

   }


   void draw_minimize_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = puserinteraction->øcreate < ::draw2d::pen >();

      ::draw2d::brush_pointer pbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::double_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_uchOpacity = 211;
         colorPen.m_uchOpacity = 211;

      }
      else
      {

         color.m_uchOpacity = 89;
         colorPen.m_uchOpacity = 89;

      }

      ppen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::int_size(1, 0), colorLighter);

      //}

      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pgraphics->set(ppen);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      pgraphics->draw_stock_icon(rectangle, e_stock_icon_iconify);

   }


} // namespace user


