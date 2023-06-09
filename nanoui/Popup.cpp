/*
    src/popup.cpp -- Simple popup pwidget which is attached to another given
    window (can be nested)

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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
   : Window(parent, ""), m_parent_window(parent_window),
   m_anchor_offset(30), m_anchor_size(15), m_side(Side::Right) { }

void Popup::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize) {
   if (m_playout || m_children.size() != 1) {
      Widget::perform_layout(pcontext, bRecalcTextSize);
   }
   else {
      m_children[0]->set_position({});
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
   m_bVisible &= m_parent_window->visible_recursive();
   m_pos = m_parent_window->position() + m_anchor_pos - sequence2_i32(0, m_anchor_offset);
}

void Popup::draw(::nano2d::context * pcontext) 
{

   refresh_relative_placement();

   if (!m_bVisible)
      return;

   int ds = m_ptheme->m_iWindowDropShadowSize;
   int cr = m_ptheme->m_iWindowCorderRadius;

   {
      ::nano2d::guard guard(pcontext);
      //pcontext->save();
      pcontext->reset_scissor();

      /* Draw a drop shadow */
      ::nano2d::paint shadow_paint = pcontext->box_gradient((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)m_size.cy(), cr * 2.f, ds * 2.f,
         m_ptheme->m_colorDropShadow, m_ptheme->m_colorTransparent);

      pcontext->begin_path();
      pcontext->rectangle((float)m_pos.x() - ds, (float)m_pos.y() - ds, (float)m_size.cx() + 2.f * ds, (float)m_size.cy() + 2.f * ds);
      pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)m_size.cy(), (float)cr);
      pcontext->path_winding(::nano2d::e_solidity_hole);
      pcontext->fill_paint(shadow_paint);
      pcontext->fill();

      /* Draw window */
      pcontext->begin_path();
      pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)m_size.cy(), (float)cr);

      auto base = m_pos + sequence2_i32(0, m_anchor_offset);
      int sign = -1;
      if (m_side == Side::Left) {
         base.x() += m_size.cx();
         sign = 1;
      }

      pcontext->move_to((float)base.x() + m_anchor_size * sign, (float)base.y());
      pcontext->line_to((float)base.x() - 1.f * sign, (float)base.y() - m_anchor_size);
      pcontext->line_to((float)base.x() - 1.f * sign, (float)base.y() + m_anchor_size);

      pcontext->fill_color(m_ptheme->m_colorWindowPopup);
      pcontext->fill();
      //pcontext->restore();

   }

   Widget::draw(pcontext);

}




} // namespace nanoui


