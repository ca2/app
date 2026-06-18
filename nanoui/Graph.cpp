/*
    src/graph.cpp -- Simple graph pwidget for showing a function plot

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Graph.h"
#include "nano2d/context.h"


//#include <nanoui/graph.h>
//#include <nanoui/theme.h>
//#include <nanoui/opengl.h>

namespace nanoui
{


Graph::Graph(Widget * parent, const ::scoped_string & caption)
   : Widget(parent), m_strCaption(caption) {
   m_colorBackground = ::color::color(20, 128);
   m_fill_color = ::rgba(255, 192, 0, 128);
   m_stroke_color = ::color::color(100, 255);
   m_colorText = ::color::color(240, 192);
}


i32_size Graph::preferred_size(::nano2d::context  *, bool bRecalcTextSize)
{

   return {180, 45 };
   
}


void Graph::draw(::nano2d::context  * pcontext) {
   Widget::draw(pcontext);

   pcontext->begin_path();
   pcontext->rectangle((::f32)m_pos.x, (::f32)m_pos.y, (::f32)m_size.cx, (::f32)m_size.cy);
   pcontext->fill_color(m_colorBackground);
   pcontext->fill();

   if (m_values.size() < 2)
      return;

   pcontext->begin_path();
   pcontext->move_to((::f32)m_pos.x, (::f32)m_pos.y + m_size.cy);
   for (size_t i = 0; i < (size_t)m_values.size(); i++) {
      ::f32 value = m_values[i];
      ::f32 vx = m_pos.x + i * m_size.cx / (::f32)(m_values.size() - 1);
      ::f32 vy = m_pos.y + (1 - value) * m_size.cy;
      pcontext->line_to(vx, vy);
   }

   pcontext->line_to((::f32)m_pos.x + m_size.cx, (::f32)m_pos.y + m_size.cy);
   pcontext->stroke_color(m_stroke_color);
   pcontext->stroke();
   if (m_fill_color.has_opacity()) {
      pcontext->fill_color(m_fill_color);
      pcontext->fill();
   }

   pcontext->font_face("sans");

   if (m_strCaption.has_character()) {
      pcontext->font_size(14.0f);
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);
      pcontext->fill_color(m_colorText);
      pcontext->text(m_pos.x + 3.f, m_pos.y + 1.f, m_strCaption.c_str());
   }

   if (m_header.has_character()) {
      pcontext->font_size(18.0f);
      pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_top);
      pcontext->fill_color(m_colorText);
      pcontext->text(m_pos.x + m_size.cx - 3.f, m_pos.y + 1.f, m_header.c_str());
   }

   if (m_footer.has_character()) {
      pcontext->font_size(15.0f);
      pcontext->text_align(::nano2d::e_align_right | ::nano2d::e_align_bottom);
      pcontext->fill_color(m_colorText);
      pcontext->text(m_pos.x + m_size.cx - 3.f, m_pos.y + m_size.cy - 1.f, m_footer.c_str());
   }

   pcontext->begin_path();
   pcontext->rectangle((::f32)m_pos.x, (::f32)m_pos.y, (::f32)m_size.cx, (::f32)m_size.cy);
   pcontext->stroke_color(::color::color(100, 255));
   pcontext->stroke();
}



} // namespace nanoui


