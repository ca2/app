/*
    nanoui/slider.cpp -- Fractional slider widget with mouse control

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Slider.h"
#include "nano2d/types.h"
#include "nano2d/context.h"


namespace nanoui
{


Slider::Slider(Widget * parent)
   : Widget(parent), m_value(0.0f), m_range(0.f, 1.f),
   m_highlighted_range(0.f, 0.f) {
   m_highlight_color =  ::color::color(255, 80, 80, 70);
}


Vector2i Slider::preferred_size(::nano2d::context *, bool bRecalcTextSize)
{
   
   return Vector2i(70, 16);

}


bool Slider::mouse_motion_event(const Vector2i & p, const Vector2i & /* rel */, bool bDown,const ::user::e_key & /* modifiers */)
{

   if (!m_enabled || !bDown)
   {

      return false;

   }

   const float kr =(m_size.y() * 0.4f), kshadow = 3.f;
   const float start_x = kr + kshadow + m_pos.x() - 1.f;
   const float width_x = m_size.x() - 2.f * (kr + kshadow);

   float value = (p.x() - start_x) / width_x, old_value = m_value;
   value = value * (m_range.second - m_range.first) + m_range.first;
   m_value = std::min(std::max(value, m_range.first), m_range.second);
   if (m_callback && m_value != old_value)
      m_callback(m_value);
   return true;
}

bool Slider::mouse_button_event(const Vector2i & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & /* modifiers */) {
   if (!m_enabled)
      return false;

   const float kr = (m_size.y() * 0.4f), kshadow = 3.f;
   const float start_x = kr + kshadow + m_pos.x() - 1;
   const float width_x = m_size.x() - 2 * (kr + kshadow);

   float value = (p.x() - start_x) / width_x, old_value = m_value;
   value = value * (m_range.second - m_range.first) + m_range.first;
   m_value = std::min(std::max(value, m_range.first), m_range.second);
   if (m_callback && m_value != old_value)
      m_callback(m_value);
   if (m_final_callback && !down)
      m_final_callback(m_value);
   return true;
}

void Slider::draw(::nano2d::context * pcontext) {
   Vector2f center = Vector2f(m_pos) + Vector2f(m_size) * 0.5f;
   float kr = (m_size.y() * 0.4f), kshadow = 3.f;

   float start_x = kr + kshadow + m_pos.x();
   float width_x = m_size.x() - 2 * (kr + kshadow);

   Vector2f knob_pos(start_x + (m_value - m_range.first) /
      (m_range.second - m_range.first) * width_x,
      center.y() + 0.5f);

   ::nano2d::paint bg = pcontext->box_gradient(
      start_x, center.y() - 3 + 1, width_x, 6, 3, 3,
                                               ::color::color(0, m_enabled ? 32 : 10),  ::color::color(0, m_enabled ? 128 : 210));

   pcontext->begin_path();
   pcontext->rounded_rectangle(start_x, center.y() - 3 + 1, width_x, 6, 2);
   pcontext->fill_paint(bg);
   pcontext->fill();

   if (m_highlighted_range.second != m_highlighted_range.first) {
      pcontext->begin_path();
      pcontext->rounded_rectangle(start_x + m_highlighted_range.first * m_size.x(),
         center.y() - kshadow + 1,
         width_x *
         (m_highlighted_range.second - m_highlighted_range.first),
         kshadow * 2, 2);
      pcontext->fill_color(m_highlight_color);
      pcontext->fill();
   }

   ::nano2d::paint knob_shadow =
      pcontext->radial_gradient(knob_pos.x(), knob_pos.y(), kr - kshadow,
         kr + kshadow,  ::color::color(0, 64), m_theme->m_colorTransparent);

   pcontext->begin_path();
   pcontext->rectangle(knob_pos.x() - kr - 5, knob_pos.y() - kr - 5, kr * 2 + 10,
      kr * 2 + 10 + kshadow);
   pcontext->circle(knob_pos.x(), knob_pos.y(), kr);
   pcontext->path_winding(::nano2d::e_solidity_hole);
   pcontext->fill_paint(knob_shadow);
   pcontext->fill();

   ::nano2d::paint knob = pcontext->linear_gradient(
      (float)m_pos.x(), center.y() - kr, (float)m_pos.x(), center.y() + kr,
      m_theme->m_colorBorderLight, m_theme->m_colorBorderMedium);
   ::nano2d::paint knob_reverse = pcontext->linear_gradient(
      (float)m_pos.x(), center.y() - kr, (float)m_pos.x(), center.y() + kr,
      m_theme->m_colorBorderMedium,
      m_theme->m_colorBorderLight);

   pcontext->begin_path();
   pcontext->circle(knob_pos.x(), knob_pos.y(), kr);
   pcontext->stroke_color(m_theme->m_colorBorderDark);
   pcontext->fill_paint(knob);
   pcontext->stroke();
   pcontext->fill();
   pcontext->begin_path();
   pcontext->circle(knob_pos.x(), knob_pos.y(), kr / 2);
   pcontext->fill_color( ::color::color(150, m_enabled ? 255 : 100));
   pcontext->stroke_paint(knob_reverse);
   pcontext->stroke();
   pcontext->fill();
}



} // namespace nanoui


