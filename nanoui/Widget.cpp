/*
    src/widget.cpp -- Base class of all widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Widget.h"
#include "Layout.h"
#include "Screen.h"
#include "Window.h"
#include "VScrollPanel.h"
#include "acme/parallelization/synchronous_lock.h"
#include "nano2d/context.h"
#include "nano2d/draw2d_context.h"
#include "aura/user/user/interaction.h"


/* Uncomment the following definition to draw red bounding
   boxes around widgets (useful for debugging drawing code) */

   // #define NANOUI_SHOW_WIDGET_BOUNDS 1

namespace nanoui
{


Widget::Widget(Widget * parent)
   : m_parent(nullptr), m_theme(nullptr), m_layout(nullptr),
   m_pos(0), m_size(0), m_fixed_size(0), m_visible(true), m_enabled(true),
   m_focused(false), m_mouse_focus(false), m_tooltip("") , m_font_size(-1) 
   ,m_icon_extra_scale(1.f)/*, m_cursor(Cursor::Arrow)*/ 
{
   m_iHoverCandidateChildStart = -1;
   m_iHoverCandidateChildEnd = -1;
   if (parent)
      parent->add_child(this);
}

Widget::~Widget() {
//   if (std::uncaught_exceptions() > 0) {
//      /* If a widget constructor throws an exception, it is immediately
//         dealloated but may still be referenced by a parent. Be conservative
//         and don't decrease the reference count of children while dispatching
//         exceptions. */
//      return;
//   }
   for (auto child : m_children) {
      if (child)
         child->dec_ref();
   }
}

void Widget::set_theme(Theme * theme) {
   if (m_theme.get() == theme)
      return;
   m_theme = theme;
   for (auto child : m_children)
      child->set_theme(theme);
}


float Widget::font_size() const
{

   return (m_font_size < 0.f && m_theme) ? (float)m_theme->m_standard_font_size : (float)m_font_size;
   
}


void Widget::set_font_size(float font_size)
{
   
   m_font_size = (int) font_size;
   
}


void Widget::set_size(const Vector2i & size)
{

   m_size = size;

}


void Widget::on_begin_draw(::nano2d::context * pcontext)
{
   
   if (m_callbackLayout)
   {

      auto callbackLayout = m_callbackLayout;

      m_callbackLayout.clear();

      callbackLayout(pcontext);

   }
   
}


Vector2i Widget::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{
   if (m_layout)
      return m_layout->preferred_size(pcontext, this, bRecalcTextSize);
   else
      return m_size;
}


void Widget::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) 
{

   if (m_callbackLayout)
   {

      auto callbackLayout = m_callbackLayout;

      m_callbackLayout.clear();

      callbackLayout(pcontext);

   }

   if (m_layout) 
   {

      m_layout->perform_layout(pcontext, this, bRecalcTextSize);

   }
   else 
   {

      for (auto c : m_children) 
      {
      
         Vector2i pref = c->preferred_size(pcontext, bRecalcTextSize), fix = c->fixed_size();

         c->set_size(Vector2i(
            fix[0] ? fix[0] : pref[0],
            fix[1] ? fix[1] : pref[1]
         ));

         c->perform_layout(pcontext);

      }

   }

}


Widget * Widget::find_widget(const Vector2i & p) 
{

   for (auto it = m_children.get_upper_bound(); it >= 0 ; it--) 
   {
   
      Widget * child = m_children[it];

      if (child->visible() && child->contains(p - m_pos))
      {

         return child->find_widget(p - m_pos);

      }

   }

   return contains(p) ? this : nullptr;

}


const Widget * Widget::find_widget(const Vector2i & p) const 
{

   for (auto it = m_children.get_upper_bound(); it >= 0; it--) 
   {
   
      Widget* child = m_children[it];

      if (child->visible() && child->contains(p - m_pos))
      {

         return child->find_widget(p - m_pos);

      }

   }

   return contains(p) ? this : nullptr;

}


bool Widget::mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & ekeyModifiers) 
{

   for (auto it = m_children.get_upper_bound(); it >= 0; it--) 
   {

      Widget* child = m_children[it];

      if (child->visible() && child->contains(p - m_pos) && child->mouse_button_event(p - m_pos, emouse, down, bDoubleClick, ekeyModifiers))
      {

         return true;

      }

   }
   
   if (emouse == ::user::e_mouse_left_button && down && !m_focused)
   {

      request_focus();

   }

   return false;

}


bool Widget::mouse_motion_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) 
{

   bool handled = false;

   index iCount = 0;

   ::index iStart = 0;

   ::index iEnd = (::index) m_children.size() - 1;

   if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
   {

      iStart = m_iHoverCandidateChildStart;

      iEnd = m_iHoverCandidateChildEnd;

   }

   for (auto i = iStart; i <= iEnd; i++)
   {

      Widget * child = m_children[i];

      if (!child->visible())
      {

         continue;

      }

      bool contained = child->contains(p - m_pos);
         
      bool prev_contained = child->contains(p - m_pos - rel);

      if (contained != prev_contained)
      {

         handled |= child->mouse_enter_event(p, contained, ekeyModifiers);

      }

      if (contained || prev_contained)
      {

         handled |= child->mouse_motion_event(p - m_pos, rel, ekeyModifiers);

      }

      iCount++;

   }

   return handled;

}


bool Widget::scroll_event(const Vector2i & p, const Vector2f & rel) 
{

   for (auto it = m_children.get_upper_bound(); it >= 0; it--) 
   {
   
      Widget * child = m_children[it];

      if (!child->visible())
      {

         continue;

      }

      if (child->contains(p - m_pos) && child->scroll_event(p - m_pos, rel))
      {

         return true;

      }

   }

   return false;

}


bool Widget::mouse_drag_event(const Vector2i &, const Vector2i &, const ::user::e_key &) 
{

   return false;

}


bool Widget::mouse_enter_event(const Vector2i &, bool enter, const ::user::e_key & ekeyModifiers)
{

   m_mouse_focus = enter;

   return false;

}


bool Widget::focus_event(bool focused) 
{

   m_focused = focused;

   return false;

}


bool Widget::keyboard_event(::user::enum_key , int, int, const ::user::e_key &, const ::string & strText) 
{

   return false;

}


bool Widget::keyboard_character_event(unsigned int) 
{

   return false;

}


void Widget::add_child(int index, Widget * widget) 
{
   synchronous_lock lock(screen()->m_puserinteraction->synchronization());
   m_iHoverCandidateChildStart = -1;
   m_iHoverCandidateChildEnd = -1;
   assert(index <= child_count());
   m_children.insert_at(index, widget);
   widget->inc_ref();
   widget->set_parent(this);
   widget->set_theme(m_theme);
}

void Widget::add_child(Widget * widget) {
   add_child(child_count(), widget);
}



void Widget::remove_child(const Widget * widget) 
{
   synchronous_lock lock(screen()->m_puserinteraction->synchronization());
   m_iHoverCandidateChildStart = -1;
   m_iHoverCandidateChildEnd = -1;
   size_t child_count = m_children.size();
   m_children.erase(std::remove(m_children.begin(), m_children.end(), widget),
      m_children.end());
   if (m_children.size() == child_count)
      throw std::runtime_error("Widget::remove_child(): widget not found!");
   widget->dec_ref();
}

void Widget::remove_child_at(int index) {
   if (index < 0 || index >= (int)m_children.size())
      throw std::runtime_error("Widget::remove_child_at(): out of bounds!");
   Widget * widget = m_children[index];
   m_children.erase(m_children.begin() + index);
   widget->dec_ref();
}

Window * Widget::window() {
   Widget * widget = this;
   while (true) {
      if (!widget)
         return nullptr;
      Window * window = dynamic_cast<Window *>(widget);
      if (window)
         return window;
      widget = widget->parent();
   }
}

Screen * Widget::screen() {
   Widget * widget = this;
   while (true) {
      if (!widget)
         return nullptr;
      Screen * screen = dynamic_cast<Screen *>(widget);
      if (screen)
         return screen;
      widget = widget->parent();
   }
}

const Screen * Widget::screen() const { return const_cast<Widget *>(this)->screen(); }

const Window * Widget::window() const { return const_cast<Widget *>(this)->window(); }


void Widget::request_focus() 
{

   Widget * widget = this;

   while (widget->parent())
   {

      widget = widget->parent();

   }

   ((Screen *)widget)->update_focus(this);

}


void Widget::draw(::nano2d::context * pcontext)
{

#if defined(NANOUI_SHOW_WIDGET_BOUNDS)
   
   pcontext->StrokeWidth(ctx, 1.0f);
   
   pcontext->begin_path(ctx);
   
   pcontext->rectangle(ctx, m_pos.x() - 0.5f, m_pos.y() - 0.5f, m_size.x() + 1, m_size.y() + 1);
   
   pcontext->stroke_color(ctx, ::color::RGBA_color(255, 0, 0, 255));
   
   pcontext->stroke(ctx);

#endif

   if (m_children.empty())
   {

      return;

   }

   ::rectangle_i32 rectangleThis;
   
   auto pscrollPanel = dynamic_cast <VScrollPanel *>(parent());
   
   if (pscrollPanel)
   {

      auto pparent = m_parent;

      auto yOffset = pscrollPanel->get_y_offset();

      rectangleThis = ::rectangle_i32_dimension(0, -yOffset, pparent->m_size.x(), pparent->m_size.y());

   }
   else
   {

      rectangleThis = ::rectangle_i32_dimension(0, 0, m_size.x(), m_size.y());

   }

   ::index iStart = 0;

   ::index iEnd = (::index)m_children.size() - 1;

   if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
   {

      iStart = m_iHoverCandidateChildStart;

      iEnd = m_iHoverCandidateChildEnd;

   }

   pcontext->translate((float)m_pos.x(), (float)m_pos.y());

   for (index i = iStart; i <= iEnd; i++) 
   {

      auto child = m_children[i];

      if (!child->visible())
      {

         continue;

      }
      
      child->on_begin_draw(pcontext);

      auto rectangleChild = ::rectangle_i32_dimension(child -> m_pos.x(), child -> m_pos.y(), child ->m_size.x(), child ->m_size.y());

      if (rectangleChild.intersects(rectangleThis))
      {

         if (pscrollPanel)
         {

            if (i < m_iHoverCandidateChildStart || m_iHoverCandidateChildStart < 0)
            {

               m_iHoverCandidateChildStart = i;

            }

            if (i > m_iHoverCandidateChildEnd)
            {


               m_iHoverCandidateChildEnd = i;
            }

         }

#if !defined(NANOUI_SHOW_WIDGET_BOUNDS)
         
         pcontext->save();

         pcontext->intersect_scissor((float)child->m_pos.x(), (float)child->m_pos.y(),
            (float)child->m_size.x(), (float)child->m_size.y());

#endif

         child->draw(pcontext);

#if !defined(NANOUI_SHOW_WIDGET_BOUNDS)
         
         pcontext->restore();

#endif

      }
      else
      {

//         output_debug_string("optimized");

      }

   }

   pcontext->translate((float)-m_pos.x(), (float)-m_pos.y());

}


//void Widget::_nanoui_to_user(::user::interaction * puserinteraction)
//{
//
//   m_puserinteraction = puserinteraction;
//
//   if (::is_null(m_puserinteraction))
//   {
//
//      m_puserinteraction->m_pappearance = this;
//
//   }
//
//   return;
//
////   for (auto & pchild : m_children)
////   {
////
////      pchild->_nanoui_to_user(m_puserinteraction);
////
////   }
//
//}



} // namespace nanoui


