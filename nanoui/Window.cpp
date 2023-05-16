/*
    src/window.cpp -- Top-level window widget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Window.h"
#include "Layout.h"
#include "Screen.h"
#include "nano2d/context.h"
#include "aura/user/user/interaction.h"


namespace nanoui
{


   Window::Window(Widget* parent, const ::scoped_string& title)
      : Widget(parent), m_title(title), m_button_panel(nullptr), m_modal(false),
      m_drag(false) {
      m_bPendingCentering = false;
   }


   void Window::on_begin_draw(::nano2d::context* pcontext)
   {

      Widget::on_begin_draw(pcontext);

      if (m_bPendingCentering)
      {

         m_bPendingCentering = false;

         _center(pcontext);

      }

   }


   Vector2i Window::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      bool bButtonPanelWasVisible = true;

      if (m_button_panel)
      {

         bButtonPanelWasVisible = m_button_panel->m_visible;

         m_button_panel->set_visible(false);

      }

      Vector2i result = Widget::preferred_size(pcontext, bRecalcTextSize);

      if (m_button_panel)
      {

         m_button_panel->set_visible(bButtonPanelWasVisible);

      }

      if (bRecalcTextSize)
      {

         pcontext->font_size(18.0f);
         pcontext->font_face("sans-bold");
         pcontext->text_bounds(0, 0, m_title, m_boundsHeader);

      }

      return Vector2i(
         std::max(result.x(), (int)(m_boundsHeader[2] - m_boundsHeader[0] + 20)),
         std::max(result.y(), (int)(m_boundsHeader[3] - m_boundsHeader[1]))
      );
   }


   Widget* Window::button_panel() 
   {
   
      if (!m_button_panel) 
      {
      
         m_button_panel = memory_new Widget(this);

         m_button_panel->set_layout(memory_new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 4));

      }

      return m_button_panel;

   }


   void Window::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize) 
   {

      if (!m_button_panel) 
      {

         Widget::perform_layout(pcontext, bRecalcTextSize);

      }
      else 
      {

         m_button_panel->set_visible(false);

         Widget::perform_layout(pcontext, bRecalcTextSize);

         for (auto w : m_button_panel->children()) 
         {

            w->set_fixed_size(Vector2i(22, 22));

            w->set_font_size(15);

         }

         m_button_panel->set_visible(true);

         m_button_panel->set_size(Vector2i(width(), 22));

         m_button_panel->set_position(Vector2i(
            width() - (m_button_panel->preferred_size(pcontext, bRecalcTextSize).x() + 5), 3));

         m_button_panel->perform_layout(pcontext, bRecalcTextSize);

      }

   }


   void Window::draw(::nano2d::context* pcontext)
   {

      if (!need_to_draw(pcontext))
      {

         return;

      }

      //int ds = m_theme->m_window_drop_shadow_size;
      int cr = m_theme->m_window_corner_radius;
      int hh = m_theme->m_window_header_height;

      /* Draw window */
      pcontext->save();
      pcontext->begin_path();
      pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), (float)cr);

      pcontext->fill_color(m_mouse_focus ? m_theme->m_window_fill_focused
         : m_theme->m_window_fill_unfocused);
      pcontext->fill();


      ///* Draw a drop shadow */
      //::nano2d::paint shadow_paint = pcontext->box_gradient(
      //   ctx, m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), cr * 2, ds * 2,
      //   m_theme->m_drop_shadow, m_theme->m_transparent);

      //pcontext->Save();
      //pcontext->reset_scissor();
      //pcontext->begin_path();
      //pcontext->rectangle(m_pos.x() - ds, m_pos.y() - ds, m_size.x() + 2 * ds, m_size.y() + 2 * ds);
      //pcontext->rounded_rectangle(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), cr);
      //pcontext->path_winding(::nano2d::e_solidity_hole);
      //pcontext->fill_paint(shadow_paint);
      //pcontext->fill();
      //pcontext->Restore();

      if (m_title.has_char()) {
         /* Draw header */
         ::nano2d::paint header_paint = pcontext->linear_gradient(
            (float)m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
            (float)m_pos.y() + (float)hh,
            m_theme->m_window_header_gradient_top,
            m_theme->m_window_header_gradient_bot);

         pcontext->begin_path();
         pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)hh, (float)cr);

         pcontext->fill_paint(header_paint);
         pcontext->fill();

         pcontext->begin_path();
         pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)hh, (float)cr);
         pcontext->stroke_color(m_theme->m_window_header_sep_top);

         //pcontext->Save();
         //pcontext->intersect_scissor(m_pos.x(), m_pos.y(), m_size.x(), 0.5f);
         //pcontext->stroke();
         //pcontext->Restore();

         pcontext->begin_path();
         pcontext->move_to(m_pos.x() + 0.5f, m_pos.y() + hh - 1.5f);
         pcontext->line_to(m_pos.x() + m_size.x() - 0.5f, m_pos.y() + hh - 1.5f);
         pcontext->stroke_color(m_theme->m_window_header_sep_bot);
         pcontext->stroke();

         pcontext->font_size(18.0f);
         pcontext->font_face("sans-bold");
         pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);

         //pcontext->font_blur(2);
         //pcontext->fill_color(m_theme->m_drop_shadow);
         //pcontext->text(m_pos.x() + m_size.x() / 2,
            // m_pos.y() + hh / 2, m_title.c_str(), nullptr);

         //pcontext->font_blur(0);
         pcontext->fill_color(m_focused ? m_theme->m_window_title_focused
            : m_theme->m_window_title_unfocused);
         pcontext->text(m_pos.x() + m_size.x() / 2.f, m_pos.y() + hh / 2.f - 1.f,
            m_title);
      }

      pcontext->restore();

      Widget::draw(pcontext);

   }


   void Window::dispose() 
   {

      screen()->dispose_window(this);

   }


   void Window::_center(::nano2d::context* pcontext) 
   {

      screen()->center_window(this, pcontext);

   }


   bool Window::mouse_enter_event(const Vector2i& p, bool enter, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_enter_event(p, enter, ekeyModifiers);

      return true;

   }


#define __MOUSE_LEFT_BUTTON 0
#define __MOUSE_RIGHT_BUTTON 1


   bool Window::mouse_motion_event(const Vector2i&, const Vector2i& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      if (m_drag && (ekeyModifiers & ::user::e_key_left_button) != 0 && bDown)
      {

         auto rectanglePrevious = interaction_rectangle();

         m_pos += rel;

         m_pos = max(m_pos, Vector2i(0));

         m_pos = min(m_pos, parent()->size() - m_size);

         auto rectangle = interaction_rectangle();

         screen()->m_puserinteraction->set_need_redraw(rectanglePrevious);

         screen()->m_puserinteraction->set_need_redraw(rectangle);

         post_redraw();

         return true;

      }

      return false;

   }


   bool Window::mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      if (emouse == ::user::e_mouse_left_button)
      {

         if (down)
         {

            auto bDrag = down && (p.y() - m_pos.y()) < m_theme->m_window_header_height;

            m_drag = bDrag;

            if (bDrag)
            {

               set_mouse_capture();

               return true;

            }

         }
         else
         {

            if (m_drag)
            {

               release_mouse_capture();

               if (m_functionOnMoved)
               {

                  m_functionOnMoved();

               }

               m_drag = false;

               return true;

            }

         }

      }

      if (Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers))
      {

         return true;

      }

      return false;

   }


   bool Window::scroll_event(const Vector2i& p, const Vector2f& rel)
   {

      Widget::scroll_event(p, rel);

      return true;

   }


   void Window::refresh_relative_placement() {
      /* Overridden in \ref Popup */
   }

   //void Window::_nanoui_to_user(::user::interaction * puserinteraction)
   //{
   //
   //   //puserinteraction->__construct(m_pbox);
   //
   //   //m_pbox->create_control(puserinteraction, (iptr)(void*) this);
   //
   //   //m_pbox->display();
   //
   //   //m_pbox->place({ 10, 10, 99, 99 });
   //
   //   //m_pbox->set_need_layout();
   //
   //   //m_pbox->set_need_redraw();
   //
   //   //m_pbox->post_redraw();
   //
   //   //Widget::_nanoui_to_user(m_pbox);
   //
   //}



} // namespace nanoui


