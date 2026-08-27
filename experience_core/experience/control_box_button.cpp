#include "platform.h"
#include "control_box_button.h"
#include "acme/handler/item.h"
#include "acme/user/user/tool.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/stock_icon.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/windowing/windowing.h"
#include "berg/user/experience/control_box.h"


namespace experience_core
{


   control_box_button::control_box_button()
   {

   }


   control_box_button::~control_box_button()
   {

   }


   void control_box_button::_001OnNcClip(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::experience::button::_001OnNcClip(pdraw2dgraphics);

   }


   void control_box_button::_001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::experience::button::_001OnClip(pdraw2dgraphics);

   }


   void control_box_button::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::experience::button::_001OnNcDraw(pdraw2dgraphics);

   }


   void control_box_button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      auto pstyle = get_style(pdraw2dgraphics);

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

                  ::i32_rectangle rectanglePush(rectangleX);

                  ::color::color colorBack(colorBackground);

                  colorBack.hls_rate(0.0, -0.2, 0.0);

                  rectanglePush.deflate(0, 0, 1, 1);

                  ::color::color colorTopLeft(colorBack);

                  ::color::color colorBottomRight(colorBack);

                  colorTopLeft.hls_rate(0.0, -0.65, 0.0);

                  colorBottomRight.hls_rate(0.0, 0.75, 0.0);

                  pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  pdraw2dgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1);

                  pdraw2dgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1);

                  pdraw2dgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

                  rectanglePush.deflate(1, 1, 0, 1);

                  pdraw2dgraphics->fill_rectangle(rectanglePush, colorBack);

               }

            }
            else
            {

               if (colorBackground.non_transparent())
               {

                  pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  auto pbrushBackground = draw2d()->create_solid_brush(colorBackground);

                  pdraw2dgraphics->set(pbrushBackground);

                  pdraw2dgraphics->fill_ellipse(rectangleX);

               }

            }

      }

   }


   void control_box_button::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
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

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_anti_alias_8x4);

      if (m_pcontrolbox)
      {

         if (!is_window_enabled())
         {

            pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

            pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

            crText = m_pcontrolbox->m_colorButtonForeDisabled;

         }
         else if (is_mouse_hover())
         {

            pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackSel);

            pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackSel);

            crText = m_pcontrolbox->m_colorButtonForeSel;

         }
         else if (has_keyboard_focus())
         {

            pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackFocus);

            pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackFocus);

            crText = m_pcontrolbox->m_colorButtonForeFocus;

         }
         else
         {

            pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBack);

            pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBack);

            crText = m_pcontrolbox->m_colorButtonFore;

         }

      }

      ::i32_rectangle rectangleEllipse(rectangleX);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->fill_ellipse(rectangleEllipse);

      pdraw2dgraphics->draw_ellipse(rectangleEllipse);

      if (m_estockicon == e_stock_icon_none)
      {

         auto strWindowText = get_window_text();

         //get_window_text(str);

         pdraw2dgraphics->set_font(this, ::e_element_none);

         pdraw2dgraphics->set_text_color(crText);

         pdraw2dgraphics->draw_text(strWindowText, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         auto pdraw2dbrush = createø < ::draw2d::brush >();

         if (pdraw2dbrush && pdraw2dgraphics->get_current_pen())
         {

            pdraw2dbrush->create_solid(pdraw2dgraphics->get_current_pen()->m_color);

         }

         pdraw2dgraphics->set(pdraw2dbrush);

         auto pdraw2dpen = createø < ::draw2d::pen > ();

         pdraw2dpen->create_solid(1.0f, ::color::white);

         pdraw2dgraphics->set(pdraw2dpen);

         ::i32_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);
         
         defer_construct_newø(m_pstockicon);
         
         m_pstockicon->m_estockiconNew = m_estockicon;

         pdraw2dgraphics->draw(rectangleIcon, m_pstockicon);

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


   void control_box_button::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle(::user::e_layout_layout);

      if (rectangleX.is_empty())
      {

         return;

      }

      constructø(m_pregion);
      
      ::f64_ellipse ellipse;
      
      ellipse.set(rectangleX);

      m_pregion->create_ellipse(ellipse);

      auto pitemClient = stock_item(e_element_client);

      auto puseritem = user_item(pitemClient);

      constructø(puseritem->m_pdraw2dpath);

      //m_pitemClient->m_item.m_eelement = e_element_client;

      puseritem->m_pdraw2dpath->add_ellipse(ellipse);

   }


   bool control_box_button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience



