﻿/*
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


NAMESPACE_BEGIN(nanogui)

Window::Window(Widget * parent, const std::string & title)
   : Widget(parent), m_title(title) , m_button_panel(nullptr),  m_modal(false),
   m_drag(false) {
   m_bPendingCentering = false;
 }


void Window::on_begin_draw(NVGcontext * ctx)
{

   Widget::on_begin_draw(ctx);
   
   if (m_bPendingCentering)
   {

      m_bPendingCentering = false;

      _center(ctx);

   }
   
}



Vector2i Window::preferred_size(NVGcontext * ctx, bool bRecalcTextSize) 
{

   bool bButtonPanelWasVisible = true;

   if (m_button_panel)
   {

      bButtonPanelWasVisible = m_button_panel->m_visible;

      m_button_panel->set_visible(false);

   }
   
   Vector2i result = Widget::preferred_size(ctx, bRecalcTextSize);

   if (m_button_panel)
   {

      m_button_panel->set_visible(bButtonPanelWasVisible);

   }

   if (bRecalcTextSize)
   {

      nvgFontSize(ctx, 18.0f);
      nvgFontFace(ctx, "sans-bold");
      nvgTextBounds(ctx, 0, 0, m_title.c_str(), nullptr, m_boundsHeader);

   }

   return Vector2i(
      std::max(result.x(), (int)(m_boundsHeader[2] - m_boundsHeader[0] + 20)),
      std::max(result.y(), (int)(m_boundsHeader[3] - m_boundsHeader[1]))
   );
}

Widget * Window::button_panel() {
   if (!m_button_panel) {
      m_button_panel = memory_new Widget(this);
      m_button_panel->set_layout(memory_new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 4));
   }
   return m_button_panel;
}

void Window::perform_layout(NVGcontext * ctx, bool bRecalcTextSize) {
   if (!m_button_panel) {
      Widget::perform_layout(ctx, bRecalcTextSize);
   }
   else {
      m_button_panel->set_visible(false);
      Widget::perform_layout(ctx, bRecalcTextSize);
      for (auto w : m_button_panel->children()) {
         w->set_fixed_size(Vector2i(22, 22));
         w->set_font_size(15);
      }
      m_button_panel->set_visible(true);
      m_button_panel->set_size(Vector2i(width(), 22));
      m_button_panel->set_position(Vector2i(
         width() - (m_button_panel->preferred_size(ctx, bRecalcTextSize).x() + 5), 3));
      m_button_panel->perform_layout(ctx, bRecalcTextSize);
   }
}



void Window::draw(NVGcontext * ctx) 
{

   //int ds = m_theme->m_window_drop_shadow_size;
   int cr = m_theme->m_window_corner_radius;
   int hh = m_theme->m_window_header_height;

   /* Draw window */
   nvgSave(ctx);
   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), (float)cr);

   nvgFillColor(ctx, m_mouse_focus ? m_theme->m_window_fill_focused
      : m_theme->m_window_fill_unfocused);
   nvgFill(ctx);


   ///* Draw a drop shadow */
   //NVGpaint shadow_paint = nvgBoxGradient(
   //   ctx, m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), cr * 2, ds * 2,
   //   m_theme->m_drop_shadow, m_theme->m_transparent);

   //nvgSave(ctx);
   //nvgResetScissor(ctx);
   //nvgBeginPath(ctx);
   //nvgRect(ctx, m_pos.x() - ds, m_pos.y() - ds, m_size.x() + 2 * ds, m_size.y() + 2 * ds);
   //nvgRoundedRect(ctx, m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), cr);
   //nvgPathWinding(ctx, NVG_HOLE);
   //nvgFillPaint(ctx, shadow_paint);
   //nvgFill(ctx);
   //nvgRestore(ctx);

   if (!m_title.empty()) {
      /* Draw header */
      NVGpaint header_paint = nvgLinearGradient(
         ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
         (float)m_pos.y() + (float)hh,
         m_theme->m_window_header_gradient_top,
         m_theme->m_window_header_gradient_bot);

      nvgBeginPath(ctx);
      nvgRoundedRect(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)hh, (float)cr);

      nvgFillPaint(ctx, header_paint);
      nvgFill(ctx);

      nvgBeginPath(ctx);
      nvgRoundedRect(ctx, (float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)hh, (float)cr);
      nvgStrokeColor(ctx, m_theme->m_window_header_sep_top);

      //nvgSave(ctx);
      //nvgIntersectScissor(ctx, m_pos.x(), m_pos.y(), m_size.x(), 0.5f);
      //nvgStroke(ctx);
      //nvgRestore(ctx);

      nvgBeginPath(ctx);
      nvgMoveTo(ctx, m_pos.x() + 0.5f, m_pos.y() + hh - 1.5f);
      nvgLineTo(ctx, m_pos.x() + m_size.x() - 0.5f, m_pos.y() + hh - 1.5f);
      nvgStrokeColor(ctx, m_theme->m_window_header_sep_bot);
      nvgStroke(ctx);

      nvgFontSize(ctx, 18.0f);
      nvgFontFace(ctx, "sans-bold");
      nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

      //nvgFontBlur(ctx, 2);
      //nvgFillColor(ctx, m_theme->m_drop_shadow);
      //nvgText(ctx, m_pos.x() + m_size.x() / 2,
        // m_pos.y() + hh / 2, m_title.c_str(), nullptr);

      //nvgFontBlur(ctx, 0);
      nvgFillColor(ctx, m_focused ? m_theme->m_window_title_focused
         : m_theme->m_window_title_unfocused);
      nvgText(ctx, m_pos.x() + m_size.x() / 2.f, m_pos.y() + hh / 2.f - 1.f,
         m_title.c_str(), nullptr);
   }

   nvgRestore(ctx);
   Widget::draw(ctx);

}


void Window::dispose() {
   screen()->dispose_window(this);
}

void Window::_center(NVGcontext * pcontext) {
   screen()->center_window(this, pcontext);
}


bool Window::mouse_enter_event(const Vector2i & p, bool enter, const ::user::e_key & ekeyModifiers)
{

   Widget::mouse_enter_event(p, enter, ekeyModifiers);

   return true;

}


#define __MOUSE_LEFT_BUTTON 0
#define __MOUSE_RIGHT_BUTTON 1


bool Window::mouse_drag_event(const Vector2i &, const Vector2i & rel, const ::user::e_key & ekeyModifiers) 
{

   if (m_drag && (ekeyModifiers & ::user::e_key_left_button) != 0) 
   {
    
      m_pos += rel;
      
      m_pos = max(m_pos, Vector2i(0));

      m_pos = min(m_pos, parent()->size() - m_size);
 
                           
      return true;

   }

   return false;

}


bool Window::mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, const ::user::e_key & ekeyModifiers)
{

   if (Widget::mouse_button_event(p, emouse, down, ekeyModifiers))
   {

      return true;

   }

   if (emouse == ::user::e_mouse_left_button) 
   {
   
      auto bDrag = down && (p.y() - m_pos.y()) < m_theme->m_window_header_height;
      
      if(m_drag && !bDrag)
      {
         
         if(m_functionOnMoved)
         {
            m_functionOnMoved();
         }
         
      }
      
      m_drag = bDrag;

      return true;

   }

   return false;

}


bool Window::scroll_event(const Vector2i & p, const Vector2f & rel) 
{

   Widget::scroll_event(p, rel);

   return true;

}


void Window::refresh_relative_placement() {
   /* Overridden in \ref Popup */
}

//void Window::_nanogui_to_user(::user::interaction * puserinteraction)
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
//   //Widget::_nanogui_to_user(m_pbox);
//
//}

NAMESPACE_END(nanogui)
