#include "platform.h"
#include "control_box_button.h"
#include "acme/handler/item.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/stock_icon.h"
#include "aura/user/user/interaction.h"


namespace user
{


   void draw_close_button(::draw2d::graphics_pointer& pdraw2dgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pdraw2dpen = puserinteraction->createø < ::draw2d::pen > ();

      ::draw2d::brush_pointer pdraw2dbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pdraw2dgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pdraw2dbrush->create_solid(color);

      pdraw2dgraphics->set(pdraw2dbrush);

      if (::is_element(puserinteraction->m_pitemHover, ::e_element_close_button))
      {

         color.m_u8Opacity = 211;
         colorPen.m_u8Opacity = 211;

      }
      else
      {

         color.m_u8Opacity = 89;
         colorPen.m_u8Opacity = 89;

      }

      pdraw2dpen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pdraw2dgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pdraw2dgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::i32_size(1, 0), colorLighter);

      //}

      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pdraw2dgraphics->set(pdraw2dpen);

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      puserinteraction->defer_construct_newø(pstockicon);
      
      pstockicon->m_estockiconNew = e_stock_icon_close;
      
      pdraw2dgraphics->draw(rectangle, pstockicon);

   }


   void draw_switch_button(::draw2d::graphics_pointer& pdraw2dgraphics, ::user::interaction* puserinteraction, ::user::item & useritem, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::draw2d::brush_pointer pdraw2dbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pdraw2dgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::f64_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      //::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pdraw2dbrush->create_solid(color);

      pdraw2dgraphics->set(pdraw2dbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_u8Opacity = 211;
         //colorPen.m_u8Opacity = 211;

      }
      else
      {

         color.m_u8Opacity = 89;
         //colorPen.m_u8Opacity = 89;

      }

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pdraw2dgraphics->fill_rectangle(rectangle, color);

   }


   void draw_maximize_button(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pdraw2dpen = puserinteraction->createø < ::draw2d::pen >();

      ::draw2d::brush_pointer pdraw2dbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pdraw2dgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::f64_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pdraw2dbrush->create_solid(color);

      pdraw2dgraphics->set(pdraw2dbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_u8Opacity = 211;
         colorPen.m_u8Opacity = 211;

      }
      else
      {

         color.m_u8Opacity = 89;
         colorPen.m_u8Opacity = 89;

      }

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pdraw2dgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pdraw2dgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::i32_size(1, 0), colorLighter);

      //}

      pdraw2dpen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);


      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pdraw2dgraphics->set(pdraw2dpen);

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);
      
      puserinteraction->defer_construct_newø(pstockicon);
      
      pstockicon->m_estockiconNew = e_stock_icon_zoom;

      pdraw2dgraphics->draw(rectangle, pstockicon);

   }


   void draw_minimize_button(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::interaction * puserinteraction, ::user::item & useritem, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pdraw2dpen = puserinteraction->createø < ::draw2d::pen >();

      ::draw2d::brush_pointer pdraw2dbrush(e_create, puserinteraction);

      auto pstyle = puserinteraction->get_style(pdraw2dgraphics);

      auto rectangle = puserinteraction->user_item_rectangle(&useritem, ::user::e_layout_design);

      //::f64_rectangle rectangle(useritem.m_rectangle);

      auto color = puserinteraction->get_color(pstyle, ::e_element_background);

      ::color::color colorPen = puserinteraction->get_color(pstyle, ::e_element_text);

      pdraw2dbrush->create_solid(color);

      pdraw2dgraphics->set(pdraw2dbrush);

      if (estate & ::user::e_state_hover)
      {

         color.m_u8Opacity = 211;
         colorPen.m_u8Opacity = 211;

      }
      else
      {

         color.m_u8Opacity = 89;
         colorPen.m_u8Opacity = 89;

      }

      pdraw2dpen->create_solid(rectangle.minimum_dimension() / 10.0, colorPen);

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pdraw2dgraphics->fill_rectangle(rectangle, color);

      //if (color.get_luminance() <= 0.5)
      //{

      //   // If color is dark (dark mode?)
      //   // blend lighter pixel at top-right edge
      //   // so that the button looks more sharply square-edged

      //   auto colorLighter = color;

      //   colorLighter.hls_rate(0.0, 0.31256, 0.0);

      //   colorLighter.alpha = 127;

      //   pdraw2dgraphics->blend_pixel(pitem->m_rectangle.top_right() - ::i32_size(1, 0), colorLighter);

      //}

      rectangle.deflate(rectangle.minimum_dimension() / 5.0);

      pdraw2dgraphics->set(pdraw2dpen);

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      puserinteraction->defer_construct_newø(pstockicon);
      
      pstockicon->m_estockiconNew = e_stock_icon_iconify;

      pdraw2dgraphics->draw(rectangle, pstockicon);

   }


} // namespace user


