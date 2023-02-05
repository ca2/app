/*
    src/popup.cpp -- Simple popup widget which is attached to another given
    window (can be nested)

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Popup.h"
#include "nano2d/context.h"


namespace nanoui
{


Popup::Popup(Widget * parent, Window * parent_window)
   : Window(parent, ""), m_parent_window(parent_window), m_anchor_pos(Vector2i(0)),
   m_anchor_offset(30), m_anchor_size(15), m_side(Side::Right) { }

void Popup::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) {
   if (m_layout || m_children.size() != 1) {
      Widget::perform_layout(pcontext, bRecalcTextSize);
   }
   else {
      m_children[0]->set_position(Vector2i(0));
      m_children[0]->set_size(m_size);
      m_children[0]->perform_layout(pcontext, bRecalcTextSize);
   }
   if (m_side == Side::Left)
      m_anchor_pos[0] -= size()[0];
}

void Popup::refresh_relative_placement() {
   if (!m_parent_window)
      return;
   m_parent_window->refresh_relative_placement();
   m_visible &= m_parent_window->visible_recursive();
   m_pos = m_parent_window->position() + m_anchor_pos - Vector2i(0, m_anchor_offset);
}

void Popup::draw(::nano2d::context * pcontext) 
{

   refresh_relative_placement();

   if (!m_visible)
      return;

   int ds = m_theme->m_window_drop_shadow_size, cr = m_theme->m_window_corner_radius;

   pcontext->save();
   pcontext->reset_scissor();

   /* Draw a drop shadow */
   ::nano2d::paint shadow_paint = pcontext->box_gradient((float) m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), cr * 2.f, ds * 2.f,
      m_theme->m_drop_shadow, m_theme->m_transparent);

   pcontext->begin_path();
   pcontext->rectangle((float)m_pos.x() - ds, (float)m_pos.y() - ds, (float)m_size.x() + 2.f * ds, (float)m_size.y() + 2.f *ds);
   pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), (float)cr);
   pcontext->path_winding(::nano2d::e_solidity_hole);
   pcontext->fill_paint(shadow_paint);
   pcontext->fill();

   /* Draw window */
   pcontext->begin_path();
   pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), (float)cr);

   Vector2i base = m_pos + Vector2i(0, m_anchor_offset);
   int sign = -1;
   if (m_side == Side::Left) {
      base.x() += m_size.x();
      sign = 1;
   }

   pcontext->move_to((float)base.x() + m_anchor_size * sign, (float)base.y());
   pcontext->line_to((float)base.x() - 1.f * sign, (float)base.y() - m_anchor_size);
   pcontext->line_to((float)base.x() - 1.f * sign, (float)base.y() + m_anchor_size);

   pcontext->fill_color(m_theme->m_window_popup);
   pcontext->fill();
   pcontext->restore();

   Widget::draw(pcontext);

}




} // namespace nanoui


