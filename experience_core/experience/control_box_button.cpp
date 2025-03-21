#include "framework.h"
#include "control_box_button.h"
#include "acme/handler/item.h"
#include "acme/user/user/tool.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/windowing/windowing.h"
#include "base/user/experience/control_box.h"


namespace experience_core
{


   control_box_button::control_box_button()
   {

   }


   control_box_button::~control_box_button()
   {

   }


   void control_box_button::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::_001OnNcClip(pgraphics);

   }


   void control_box_button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::_001OnClip(pgraphics);

   }


   void control_box_button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::_001OnNcDraw(pgraphics);

   }


   void control_box_button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      auto pstyle = get_style(pgraphics);

      auto estate = get_state();

      if (estate & (::user::e_state_hover | ::user::e_state_disabled))
      {

         auto colorBackground = get_color(pstyle, ::e_element_background, estate);

         //::color::color crBackground = _001GetButtonBackgroundColor();

         //auto & linkedpropertyCheck = m_linkedpropertyCheck;

            auto echeck = this->echeck();

            if (echeck == ::e_check_checked)
            {

               if (windowing()->is_sandboxed())
               {



               }
               else
               {

                  ::int_rectangle rectanglePush(rectangleX);

                  ::color::color colorBack(colorBackground);

                  colorBack.hls_rate(0.0, -0.2, 0.0);

                  rectanglePush.deflate(0, 0, 1, 1);

                  ::color::color colorTopLeft(colorBack);

                  ::color::color colorBottomRight(colorBack);

                  colorTopLeft.hls_rate(0.0, -0.65, 0.0);

                  colorBottomRight.hls_rate(0.0, 0.75, 0.0);

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1);

                  pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1);

                  pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1, 0, 1);

                  pgraphics->fill_rectangle(rectanglePush, colorBack);

               }

            }
            else
            {

               if (colorBackground.non_transparent())
               {

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  auto pbrushBackground = draw2d()->create_solid_brush(colorBackground);

                  pgraphics->set(pbrushBackground);

                  pgraphics->fill_ellipse(rectangleX);

               }

            }

      }

   }


   void control_box_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

#ifdef VERBOSE_LOG

      ::time t1 = ::time::now();

#endif

      if ((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

#ifdef VERBOSE_LOG

      ::time d1 = t1.elapsed();

      if (d1 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "is_activeis_activeis_active more than 50ms user::control_box_button wndframe_core";

      }

#endif

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      ::color::color crText = argb(255, 255, 255, 255);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_anti_alias_8x4);

      if (m_pcontrolbox)
      {

         if (!is_window_enabled())
         {

            pgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

            pgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

            crText = m_pcontrolbox->m_colorButtonForeDisabled;

         }
         else if (is_mouse_hover())
         {

            pgraphics->set(m_pcontrolbox->m_pbrushButtonBackSel);

            pgraphics->set(m_pcontrolbox->m_ppenButtonBackSel);

            crText = m_pcontrolbox->m_colorButtonForeSel;

         }
         else if (has_keyboard_focus())
         {

            pgraphics->set(m_pcontrolbox->m_pbrushButtonBackFocus);

            pgraphics->set(m_pcontrolbox->m_ppenButtonBackFocus);

            crText = m_pcontrolbox->m_colorButtonForeFocus;

         }
         else
         {

            pgraphics->set(m_pcontrolbox->m_pbrushButtonBack);

            pgraphics->set(m_pcontrolbox->m_ppenButtonBack);

            crText = m_pcontrolbox->m_colorButtonFore;

         }

      }

      ::int_rectangle rectangleEllipse(rectangleX);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_ellipse(rectangleEllipse);

      pgraphics->draw_ellipse(rectangleEllipse);

      if (m_estockicon == e_stock_icon_none)
      {

         auto strWindowText = get_window_text();

         //get_window_text(str);

         pgraphics->set_font(this, ::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strWindowText, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         auto pbrush = __øcreate < ::draw2d::brush >();

         if (pbrush && pgraphics->get_current_pen())
         {

            pbrush->create_solid(pgraphics->get_current_pen()->m_color);

         }

         pgraphics->set(pbrush);

         auto ppen = __øcreate < ::draw2d::pen > ();

         ppen->create_solid(1.0f, ::color::white);

         pgraphics->set(ppen);

         ::int_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

      }

#ifdef VERBOSE_LOG

      ::time d2 = t1.elapsed();

      if (d2 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "(d2) more than 50ms user::control_box_button wndframe_core";

      }

#endif

   }


   void control_box_button::install_message_routing(::channel *pframewindow)
   {

      ::experience::button::install_message_routing(pframewindow);

   }


   void control_box_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle(::user::e_layout_layout);

      if (rectangleX.is_empty())
      {

         return;

      }

      __øconstruct(m_pregion);
      
      ::double_ellipse ellipse;
      
      ellipse.set(rectangleX);

      m_pregion->create_ellipse(ellipse);

      auto pitemClient = stock_item(e_element_client);

      auto puseritem = user_item(pitemClient);

      __øconstruct(puseritem->m_ppath);

      //m_pitemClient->m_item.m_eelement = e_element_client;

      puseritem->m_ppath->add_ellipse(ellipse);

   }


   bool control_box_button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience



