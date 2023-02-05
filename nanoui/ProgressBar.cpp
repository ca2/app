/*
    src/progressbar.cpp -- Standard widget for visualizing progress

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ProgressBar.h"
#include "nano2d/types.h"
#include "nano2d/context.h"


namespace nanoui
{


ProgressBar::ProgressBar(Widget * parent)
   : Widget(parent), m_value(0.0f) {}

Vector2i ProgressBar::preferred_size(::nano2d::context *, bool bRecalcTextSize) {
   return Vector2i(70, 12);
}

void ProgressBar::draw(::nano2d::context * pcontext) {
   Widget::draw(pcontext);

   ::nano2d::paint paint = pcontext->box_gradient(
      m_pos.x() + 1.f, m_pos.y() + 1.f,
      m_size.x() - 2.f, (float)m_size.y(), 3.f, 4.f, Color(0, 32), Color(0, 92));
   pcontext->begin_path();
   pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.x(), (float)m_size.y(), 3.f);
   pcontext->fill_paint(paint);
   pcontext->fill();

   float value = std::min(std::max(0.0f, m_value), 1.0f);
   int bar_pos = (int)std::round((m_size.x() - 2) * value);

   paint = pcontext->box_gradient(
      (float)m_pos.x(), (float)m_pos.y(),
      bar_pos + 1.5f, m_size.y() - 1.f, 3.f, 4.f,
      Color(220, 100), Color(128, 100));

   pcontext->begin_path();
   pcontext->rounded_rectangle(
      m_pos.x() + 1.f, m_pos.y() + 1.f,
      (float)bar_pos, m_size.y() - 2.f, 3.f);
   pcontext->fill_paint(paint);
   pcontext->fill();
}



} // namespace nanoui


