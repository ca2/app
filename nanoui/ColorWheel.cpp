/*
    src/colorwheel.cpp -- fancy analog widget to select a color value

    This widget was contributed by Dmitriy Morozov.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ColorWheel.h"
#include "nano2d/types.h"
#include "nano2d/context.h"

//#include <nanoui/colorwheel.h>
//#include <nanoui/theme.h>
//#include <nanoui/opengl.h>

namespace nanoui
{


ColorWheel::ColorWheel(Widget * parent, const Color & rgb)
   : Widget(parent), m_drag_region(None) {
   set_color(rgb);
}

Vector2i ColorWheel::preferred_size(::nano2d::context *, bool bRecalcTextSize) {
   return { 100, 100 };
}


//#define ::nano2d::f_pi MATH_PI

void ColorWheel::draw(::nano2d::context * pcontext) 
{

   Widget::draw(pcontext);

   if (!m_visible)
   {

      return;

   }

   float x = (float)m_pos.x(), y = (float)m_pos.y(),
      w = (float)m_size.x(), h = (float)m_size.y();

   float hue = m_hue;
   ::nano2d::paint paint;

   pcontext->save();

   float cx = x + w * 0.5f;
   float cy = y + h * 0.5f;
   float r1 = (w < h ? w : h) * 0.5f - 5.0f;
   float r0 = r1 * .75f;

   float aeps = 0.5f / r1;   // half a pixel arc length in radians (2pi cancels out).

   for (int i = 0; i < 6; i++) {
      float a0 = (float)i / 6.0f * ::nano2d::f_pi * 2.0f - aeps;
      float a1 = (float)(i + 1.0f) / 6.0f * ::nano2d::f_pi * 2.0f + aeps;
      pcontext->begin_path();
      pcontext->arc(cx, cy, r0, a0, a1, ::nano2d::e_winding_cw);
      pcontext->arc(cx, cy, r1, a1, a0, ::nano2d::e_winding_ccw);
      pcontext->close_path();
      float ax = (float)cx + cosf(a0 - 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      float ay = (float)cy + sinf(a0 - 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      float bx = (float)cx + cosf(a1 + 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      float by = (float)cy + sinf(a1 + 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      paint = pcontext->linear_gradient(ax, ay, bx, by,
         ::nano2d::HSLA_color(a0 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255),
         ::nano2d::HSLA_color(a1 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255));
      pcontext->fill_paint(paint);
      pcontext->fill();
   }

   pcontext->begin_path();
   pcontext->circle(cx, cy, r0 - 0.5f);
   pcontext->circle(cx, cy, r1 + 0.5f);
   pcontext->stroke_color(::nano2d::RGBA_color(0, 0, 0, 64));
   pcontext->stroke_width(1.0f);
   pcontext->stroke();

   // Selector
   pcontext->save();
   pcontext->translate(cx, cy);
   pcontext->rotate(hue * ::nano2d::f_pi * 2);

   // Marker on
   float u = std::max(r1 / 50, 1.5f);
   u = std::min(u, 4.f);
   pcontext->stroke_width(u);
   pcontext->begin_path();
   pcontext->rectangle(r0 - 1, -2 * u, r1 - r0 + 2, 4 * u);
   pcontext->stroke_color(::nano2d::RGBA_color(255, 255, 255, 192));
   pcontext->stroke();

   paint = pcontext->box_gradient(r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, ::nano2d::RGBA_color(0, 0, 0, 128), ::nano2d::RGBA_color(0, 0, 0, 0));
   pcontext->begin_path();
   pcontext->rectangle(r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
   pcontext->rectangle(r0 - 2, -4, r1 - r0 + 4, 8);
   pcontext->path_winding(::nano2d::e_solidity_hole);
   pcontext->fill_paint(paint);
   pcontext->fill();

   // Center triangle
   float r = r0 - 6;
   float ax = -0.5f * r;
   float ay = 0.5f * std::sqrt(3.f) * r;
   float bx = -0.5f * r;
   float by = -0.5f * std::sqrt(3.f) * r;
   pcontext->begin_path();
   pcontext->move_to(r, 0);
   pcontext->line_to(ax, ay);
   pcontext->line_to(bx, by);
   pcontext->close_path();
   paint = pcontext->linear_gradient(r, 0, ax, ay, ::nano2d::HSLA_color(hue, 1.0f, 0.5f, 255), ::nano2d::RGBA_color(255, 255, 255, 255));
   pcontext->fill_paint(paint);
   pcontext->fill();
   paint = pcontext->linear_gradient((r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by, ::nano2d::RGBA_color(0, 0, 0, 0), ::nano2d::RGBA_color(0, 0, 0, 255));
   pcontext->fill_paint(paint);
   pcontext->fill();
   pcontext->stroke_color(::nano2d::RGBA_color(0, 0, 0, 64));
   pcontext->stroke();

   // Select circle on triangle
   float sx = r * (1 - m_white - m_black) + ax * m_white + bx * m_black;
   float sy = ay * m_white + by * m_black;

   pcontext->stroke_width(u);
   pcontext->begin_path();
   pcontext->circle(sx, sy, 2 * u);
   pcontext->stroke_color(::nano2d::RGBA_color(255, 255, 255, 192));
   pcontext->stroke();

   pcontext->restore();

   pcontext->restore();
}


bool ColorWheel::mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, const ::user::e_key& ekeyModifiers)
{
   Widget::mouse_button_event(p, emouse, down, ekeyModifiers);
   if (!m_enabled || emouse != ::user::e_mouse_left_button)
      return false;

   if (down) {
      m_drag_region = adjust_position(p);
      return m_drag_region != None;
   }
   else {
      m_drag_region = None;
      return true;
   }
}


bool ColorWheel::mouse_drag_event(const Vector2i & p, const Vector2i &, const ::user::e_key &) 
{

   return adjust_position(p, m_drag_region) != None;

}


ColorWheel::Region ColorWheel::adjust_position(const Vector2i & p, Region considered_regions)
{

   float x = (float)p.x() - m_pos.x(),
      y = (float)p.y() - m_pos.y(),
      w = (float)m_size.x(),
      h = (float)m_size.y();

   float cx = w * 0.5f;
   float cy = h * 0.5f;
   float r1 = (w < h ? w : h) * 0.5f - 5.0f;
   float r0 = r1 * .75f;

   x -= cx;
   y -= cy;

   float mr = std::sqrt(x * x + y * y);

   if ((considered_regions & OuterCircle) &&
      ((mr >= r0 && mr <= r1) || (considered_regions == OuterCircle))) {
      if (!(considered_regions & OuterCircle))
         return None;
      m_hue = std::atan(y / x);
      if (x < 0)
         m_hue += ::nano2d::f_pi;
      m_hue /= 2 * ::nano2d::f_pi;

      if (m_callback)
         m_callback(color());

      return OuterCircle;
   }

   float a = -m_hue * 2 * ::nano2d::f_pi,
      sin_a = std::sin(a),
      cos_a = std::cos(a);
   Vector2f xy(cos_a * x - sin_a * y,
      sin_a * x + cos_a * y);

   float r = r0 - 6;
   float l0 = (float)(r - xy.x() + std::sqrt(3.f) * xy.y()) / (3.f * r);
   float l1 = (float)(r - xy.x() - std::sqrt(3.f) * xy.y()) / (3.f * r);
   float l2 = 1 - l0 - l1;
   bool triangle_test = l0 >= 0 && l0 <= 1.f && l1 >= 0.f && l1 <= 1.f &&
      l2 >= 0.f && l2 <= 1.f;

   if ((considered_regions & InnerTriangle) &&
      (triangle_test || considered_regions == InnerTriangle)) {
      if (!(considered_regions & InnerTriangle))
         return None;
      l0 = std::min(std::max(0.f, l0), 1.f);
      l1 = std::min(std::max(0.f, l1), 1.f);
      l2 = std::min(std::max(0.f, l2), 1.f);
      float sum = l0 + l1 + l2;
      l0 /= sum;
      l1 /= sum;
      m_white = l0;
      m_black = l1;
      if (m_callback)
         m_callback(color());
      return InnerTriangle;
   }

   return None;
}

Color ColorWheel::hue2rgb(float h) const {
   float s = 1.f;
   float v = 1.f;

   if (h < 0) h += 1;

   int i = int(h * 6);
   float f = h * 6 - i;
   float p = v * (1 - s);
   float q = v * (1 - f * s);
   float t = v * (1 - (1 - f) * s);

   float r = 0, g = 0, b = 0;
   switch (i % 6) {
   case 0:
      {
         r = v;
         g = t;
         b = p;
      }
         break;
   case 1:
      {
         r = q;
         g = v;
         b = p;
      }
         break;
   case 2:
      {
         r = p;
         g = v;
         b = t;
         
      }
         break;
   case 3:
      {
         r = p;
         g = q;
         b = v;
         
      }
         break;
   case 4:
      {
         r = t;
         g = p;
         b = v;
      }
         break;
   case 5:
      {
         r = v;
         g = p;
         b = q;
         
      }
         break;
   }

   return { r, g, b, 1.f };
}

Color ColorWheel::color() const {
   Color rgb = hue2rgb(m_hue);
   Color black{ 0.f, 0.f, 0.f, 1.f };
   Color white{ 1.f, 1.f, 1.f, 1.f };
   return rgb * (1 - m_white - m_black) + black * m_black + white * m_white;
}

void ColorWheel::set_color(const Color & rgb) {
   float r = rgb[0], g = rgb[1], b = rgb[2];

   float M = std::max({ r, g, b });
   float m = std::min({ r, g, b });

   if (M == m) {
      float l = 0.5f * (M + m);
      m_hue = 0.f;
      m_black = 1.f - l;
      m_white = l;
   }
   else {
      float d = M - m, h;

      if (M == r)
         h = (g - b) / d + (g < b ? 6 : 0);
      else if (M == g)
         h = (b - r) / d + 2;
      else
         h = (r - g) / d + 4;
      h /= 6;

      Color ch = hue2rgb(m_hue);
      float M2 = std::max({ ch[0], ch[1], ch[2] });
      float m2 = std::min({ ch[0], ch[1], ch[2] });

      m_white = (M * m2 - m * M2) / (m2 - M2);
      m_black = (M + m2 + m * M2 - m - M * m2 - M2) / (m2 - M2);
      m_hue = h;
   }
}



} // namespace nanoui



