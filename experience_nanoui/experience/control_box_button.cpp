#include "platform.h"
#include "control_box_button.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/user/user/frame_interaction.h"
#include "berg/user/experience/control_box.h"


namespace experience_nanoui
{


   control_box_button::control_box_button()
   {

   }


   control_box_button::~control_box_button()
   {

   }


   void control_box_button::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }


   void control_box_button::_001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::interaction::_001OnClip(pdraw2dgraphics);

   }


   void control_box_button::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      class ::time t1 = ::time::now();

      if ((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      class ::time d1 = t1.elapsed();

#ifdef VERBOSE_LOG         

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
         else if (hover_item().is_set())
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

         string str;

         str = get_window_text();

         pdraw2dgraphics->set_font(this, ::e_element_none);

         pdraw2dgraphics->set_solid_color(crText);

         pdraw2dgraphics->draw_text(str, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         auto pbrush = createø < ::draw2d::brush >();

         if (pbrush && pdraw2dgraphics->get_current_pen())
         {

            pbrush->create_solid(pdraw2dgraphics->get_current_pen()->m_color);

         }

         pdraw2dgraphics->set(pbrush);

         auto ppen = createø < ::draw2d::pen >();

         ppen->create_solid(1.0f, ::rgba(255, 255, 255, 255));

         pdraw2dgraphics->set(ppen);

         ::i32_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pdraw2dgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

      }

      class ::time d2 = t1.elapsed();

#ifdef VERBOSE_LOG         

      if (d2 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "(d2) more than 50ms user::control_box_button wndframe_core";

      }

#endif

   }


   void control_box_button::install_message_routing(::channel * pframewindow)
   {

      ::experience::button::install_message_routing(pframewindow);

   }


   void control_box_button::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      defer_constructø(m_pregion);

      ::f64_ellipse ellipse;

      ellipse.set(rectangleX);

      m_pregion->create_ellipse(ellipse);

   }



   bool control_box_button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience_nanoui



