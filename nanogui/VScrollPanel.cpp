/*
    src/vscrollpanel.cpp -- Adds a vertical scrollbar around a widget
    that is too big to fit into a certain area

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "VScrollPanel.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/windowing.h"


NAMESPACE_BEGIN(nanogui)

VScrollPanel::VScrollPanel(Widget * parent)
   : Widget(parent), m_child_preferred_height(0),
   m_scroll(0.f), m_update_layout(false) 
{ 

}

void VScrollPanel::perform_layout(NVGcontext * ctx, bool bRecalcTextSize) {
   Widget::perform_layout(ctx);

   if (m_children.empty())
      return;
   if (m_children.size() > 1)
      throw std::runtime_error("VScrollPanel should have one child.");

   Widget * child = m_children[0];
   m_child_preferred_height = child->preferred_size(ctx, bRecalcTextSize).y();

   if (m_child_preferred_height > m_size.y()) {
      child->set_position(Vector2i(0, (int)(- m_scroll * (m_child_preferred_height - m_size.y()))));
      child->set_size(Vector2i(m_size.x() - 12, m_child_preferred_height));
   }
   else {
      child->set_position(Vector2i(0));
      child->set_size(m_size);
      m_scroll = 0;
   }
   child->perform_layout(ctx, bRecalcTextSize);
}

Vector2i VScrollPanel::preferred_size(NVGcontext * ctx, bool bRecalcTextSize) {
   if (m_children.empty())
      return Vector2i(0);
   return m_children[0]->preferred_size(ctx, bRecalcTextSize) + Vector2i(12, 0);
}


bool VScrollPanel::mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) 
{

   if (!m_children.empty() && m_child_preferred_height > m_size.y()) 
   {

      float fTrackBarHeight = get_track_bar_height();

      float yMin = fTrackBarHeight / 2.f;
      
      float yMax = m_size.y() - fTrackBarHeight / 2.f;

      float yRange = yMax - yMin;

      float y = std::min(yMax, std::max((float) p.y(), yMin));

      float yRate = (y - yMin) / yRange;
      
      output_debug_string("drag:point=" + __string(p.y()) + ",rate=" + __string(yRate)+ "\n");

      if (is_different(yRate, m_scroll, 0.0001))
      {

         m_scroll = yRate;

         auto child = m_children[0];

         //Vector2i old_pos = child->position();

         auto yOffset = get_y_offset();

         child->set_position(Vector2i(0, (int)yOffset));

         //Vector2i new_pos = child->position();

         m_update_layout = true;

         screen()->m_puserinteraction->set_need_redraw();

         screen()->m_puserinteraction->post_redraw();

      }

      return true;

   }
   else 
   {

      return Widget::mouse_drag_event(p, rel, ekeyModifiers);

   }

}


bool VScrollPanel::mouse_button_event(const Vector2i & p, int button, bool down, const ::user::e_key & ekeyModifiers) 
{
   if (Widget::mouse_button_event(p, button, down, ekeyModifiers))
      return true;

   if (down && button == ::user::e_mouse_left_button && !m_children.empty() &&
      m_child_preferred_height > m_size.y() &&
      p.x() > m_pos.x() + m_size.x() - 13 &&
      p.x() < m_pos.x() + m_size.x() - 4) 
   {

      m_bDrag = true;

      screen()->m_puserinteraction->set_mouse_capture();

      float fTrackBarHeight = get_track_bar_height();

      float yMin = fTrackBarHeight / 2.f;

      float yMax = m_size.y() - fTrackBarHeight / 2.f;

      float yRange = yMax - yMin;

      float y = std::min(yMax, std::max((float)p.y(), yMin));

      float yRate = (y - yMin) / yRange;

      if (is_different(yRate, m_scroll, 0.0001))
      {

         m_scroll = yRate;

         auto child = m_children[0];

         //Vector2i old_pos = child->position();

         auto yOffset = get_y_offset();

         child->set_position(Vector2i(0, (int)yOffset));

         //Vector2i new_pos = child->position();

         m_update_layout = true;

         screen()->m_puserinteraction->set_need_redraw();

         screen()->m_puserinteraction->post_redraw();

      }

      return true;

   }
   else if (m_bDrag && !down)
   {

      screen()->m_puserinteraction->windowing()->release_mouse_capture();

   }

   return false;

}

bool VScrollPanel::scroll_event(const Vector2i & p, const Vector2f & rel) 
{

   if (!m_children.empty() && m_child_preferred_height > m_size.y()) 
   {

      //auto child = m_children[0];

      float fTrackBarHeight = get_track_bar_height();

      float yMin = fTrackBarHeight / 2.f;

      float yMax = m_size.y() - fTrackBarHeight / 2.f;

      float yRange = yMax - yMin;

      float y = std::min(yMax, std::max((float)p.y(), yMin));

      float yRate = (y - yMin) / yRange;

      if (is_different(yRate, m_scroll, 0.0001))
      {

         m_scroll = yRate;

         auto child = m_children[0];

         Vector2i old_pos = child->position();

         auto yOffset = get_y_offset();

         child->set_position(Vector2i(0, (int)yOffset));

         Vector2i new_pos = child->position();

         m_update_layout = true;

         screen()->m_puserinteraction->set_need_redraw();

         screen()->m_puserinteraction->post_redraw();

         child->mouse_motion_event(p - m_pos, old_pos - new_pos, ::user::e_key_none);

      }

      return true;

   }
   else 
   {
      
      return Widget::scroll_event(p, rel);

   }

}


float VScrollPanel::get_track_bar_height() const
{

   float fTrackBarHeight = height() *
      std::min(1.f, height() / (float)m_child_preferred_height);

   return fTrackBarHeight;

}

float VScrollPanel::get_y_offset() const
{


   return m_child_preferred_height > m_size.y() ? -m_scroll * (m_child_preferred_height - m_size.y()) :
      0;
}

void VScrollPanel::draw(NVGcontext * ctx) {
   if (m_children.empty())
      return;

   Widget * child = m_children[0];
   //m_child_preferred_height = child->preferred_size(ctx).y();
   float fTrackBarHeight = get_track_bar_height();
   //int yoffset = 0;
   //if (m_child_preferred_height > m_size.y())
     // yoffset = (int)get_y_offset(m_scroll);
   //child->set_position(Vector2i(0, yoffset));

   if (m_update_layout) 
   {
      m_update_layout = false;
      child->m_iHoverCandidateChildStart = -1;
      child->m_iHoverCandidateChildEnd = -1;
      m_child_preferred_height = child->preferred_size(ctx, false).y();
      child->perform_layout(ctx, false);
   }

   nvgSave(ctx);
   nvgTranslate(ctx, (float)m_pos.x(), (float)m_pos.y());
   nvgIntersectScissor(ctx, 0.f, 0.f, (float)m_size.x(), (float)m_size.y());
   
   if (child->visible())
   {
      child->draw(ctx);
   }
   nvgRestore(ctx);

   if (m_child_preferred_height <= m_size.y())
      return;

   NVGpaint paint = nvgBoxGradient(
      ctx, (float)m_pos.x() + m_size.x() - 12 + 1, (float)m_pos.y() + 4 + 1, 8,
      (float)m_size.y() - 8, 3.f, 4.f, Color(0, 32), Color(0, 92));
   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, m_pos.x() + m_size.x() - 12.f, m_pos.y() + 4.f, 8.f,
      m_size.y() - 8.f, 3.f);
   nvgFillPaint(ctx, paint);
   nvgFill(ctx);

   paint = nvgBoxGradient(
      ctx, m_pos.x() + m_size.x() - 12.f - 1.f,
      m_pos.y() + 4.f + (m_size.y() - 8.f - fTrackBarHeight) * m_scroll - 1.f, 8.f , (float)fTrackBarHeight,
      3.f, 4.f, Color(220, 100), Color(128, 100));

   nvgBeginPath(ctx);
   nvgRoundedRect(ctx, m_pos.x() + m_size.x() - 12.f + 1.f,
      m_pos.y() + 4.f + 1.f + (m_size.y() - 8.f - fTrackBarHeight) * m_scroll, 8.f - 2.f,
      fTrackBarHeight - 2.f, 2.f);
   nvgFillPaint(ctx, paint);
   nvgFill(ctx);
}

NAMESPACE_END(nanogui)
