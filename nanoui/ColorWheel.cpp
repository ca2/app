/*
    src/colorwheel.cpp -- fancy analog pwidget to select a ::color::color value

    This pwidget was contributed by Dmitriy Morozov.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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


   ColorWheel::ColorWheel(Widget* parent, const ::color::color& rgb)
      : Widget(parent), m_regionDrag(None) 
   {

      set_color(rgb);

   }


   vector2_i32 ColorWheel::preferred_size(::nano2d::context*, bool bRecalcTextSize) 
   {

      return { 100, 100 };

   }


   //#define ::nano2d::f_pi MATH_PI

   void ColorWheel::draw(::nano2d::context* pcontext)
   {

      Widget::draw(pcontext);

      if (!m_bVisible)
      {

         return;

      }

      float x = (float)m_pos.x()(), y = (float)m_pos.y()(),
         w = (float)m_size.x()(), h = (float)m_size.y()();

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
            ::color::HSLA_color(a0 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255),
            ::color::HSLA_color(a1 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255));
         pcontext->fill_paint(paint);
         pcontext->fill();
      }

      pcontext->begin_path();
      pcontext->circle(cx, cy, r0 - 0.5f);
      pcontext->circle(cx, cy, r1 + 0.5f);
      pcontext->stroke_color(::color::RGBA_color(0, 0, 0, 64));
      pcontext->stroke_width(1.0f);
      pcontext->stroke();

      // Selector
      pcontext->save();
      pcontext->translate(cx, cy);
      pcontext->rotate(hue * ::nano2d::f_pi * 2);

      // Marker on
      float u = ::maximum(r1 / 50, 1.5f);
      u = ::minimum(u, 4.f);
      pcontext->stroke_width(u);
      pcontext->begin_path();
      pcontext->rectangle(r0 - 1, -2 * u, r1 - r0 + 2, 4 * u);
      pcontext->stroke_color(::color::RGBA_color(255, 255, 255, 192));
      pcontext->stroke();

      paint = pcontext->box_gradient(r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, ::color::RGBA_color(0, 0, 0, 128), ::color::RGBA_color(0, 0, 0, 0));
      pcontext->begin_path();
      pcontext->rectangle(r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
      pcontext->rectangle(r0 - 2, -4, r1 - r0 + 4, 8);
      pcontext->path_winding(::nano2d::e_solidity_hole);
      pcontext->fill_paint(paint);
      pcontext->fill();

      //// Center triangle
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
      paint = pcontext->linear_gradient(r, 0, ax, ay, ::color::HSLA_color(hue, 1.0f, 0.5f, 255), ::color::RGBA_color(255, 255, 255, 255));
      pcontext->fill_paint(paint);
      pcontext->fill();
      paint = pcontext->linear_gradient((r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by, ::color::RGBA_color(0, 0, 0, 0), ::color::RGBA_color(0, 0, 0, 255));
      pcontext->fill_paint(paint);
      pcontext->fill();
      pcontext->stroke_color(::color::RGBA_color(0, 0, 0, 64));
      pcontext->stroke();

      // Select circle on triangle
      float sx = r * (1 - m_white - m_black) + ax * m_white + bx * m_black;
      float sy = ay * m_white + by * m_black;

      pcontext->stroke_width(u);
      pcontext->begin_path();
      pcontext->circle(sx, sy, 2 * u);
      pcontext->stroke_color(::color::RGBA_color(255, 255, 255, 192));
      pcontext->stroke();

      pcontext->restore();

      pcontext->restore();

   }


   bool ColorWheel::mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {
      
      if (!m_bEnabled || emouse != ::user::e_mouse_left_button)
      {

         return false;

      }

      if (down)
      {
      
         m_regionDrag = adjust_position(p);

         if (m_regionDrag)
         {
            
            set_mouse_capture();

            return true;

         }

         return false;

      }
      else 
      {

         m_regionDrag = None;

         release_mouse_capture();

         return true;

      }

      Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);


   }


   bool ColorWheel::mouse_motion_event(const vector2_i32& p, const vector2_i32& shift, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      if (m_regionDrag)
      {

         adjust_position(p);

         return true;

      }

      return Widget::mouse_motion_event(p, shift, bDown, ekeyModifiers);

   }


   ColorWheel::Region ColorWheel::adjust_position(const vector2_i32& p)
   {

      float x = (float) p.x()();
      
      float y = (float) p.y()();
      
      x -= (float) m_pos.x()();
      
      y -= (float) m_pos.y()();

      float pwidget = (float)m_size.x()();
      
      float h = (float)m_size.y()();

      float cx = pwidget / 2.f;

      float cy = h / 2.f;

      float smallest_dimension = minimum(cx, cy);

      float r1 = smallest_dimension - 5.0f;

      float r0 = r1 * .75f;

      x -= cx;

      y -= cy;

      float mr = std::sqrt(x * x + y * y);

      if ((m_regionDrag & OuterCircle) || (!m_regionDrag && (mr >= r0 && mr <= r1))) 
      {

         m_hue = std::atan(y / x);
         
         if (x < 0)
         {

            m_hue += ::nano2d::f_pi;

         }

         m_hue /= 2 * ::nano2d::f_pi;

         auto color = this->color();

         if (m_callback)
         {

            m_callback(color);

         }

         return OuterCircle;

      }

      float a = -m_hue * 2 * ::nano2d::f_pi,
         sin_a = std::sin(a),
         cos_a = std::cos(a);
      vector2_f32 xy(cos_a * x - sin_a * y,
         sin_a * x + cos_a * y);

      float r = r0 - 6;
      float l0 = (float)(r - xy.x()() + std::sqrt(3.f) * xy.y()()) / (3.f * r);
      float l1 = (float)(r - xy.x()() - std::sqrt(3.f) * xy.y()()) / (3.f * r);
      float l2 = 1 - l0 - l1;
      bool triangle_test = l0 >= 0 && l0 <= 1.f && l1 >= 0.f && l1 <= 1.f &&
         l2 >= 0.f && l2 <= 1.f;

      if ((m_regionDrag & InnerTriangle) || (!m_regionDrag && triangle_test))
      {

         l0 = ::minimum(::maximum(0.f, l0), 1.f);
         l1 = ::minimum(::maximum(0.f, l1), 1.f);
         l2 = ::minimum(::maximum(0.f, l2), 1.f);
         float sum = l0 + l1 + l2;
         l0 /= sum;
         l1 /= sum;
         m_white = l0;
         m_black = l1;
         if (m_callback)
            m_callback(this->color());
         return InnerTriangle;
      }

      return ClientArea;

   }


   ::color::color ColorWheel::hue2rgb(float h) const {
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

   ::color::color ColorWheel::color() const 
   {
      
      ::color::color rgb = hue2rgb(m_hue);
      ::color::color black{ 0.f, 0.f, 0.f, 1.f };
      ::color::color white{ 1.f, 1.f, 1.f, 1.f };
      //::color::color black{ 0.f, 0.f, 0.f, m_black };
      //::color::color white{ m_white, m_white, m_white, m_white };

      ::color::color color;

      float luminanceComplement = 1.0f - m_white - m_black;

      color.set_red(rgb.fr() * luminanceComplement + m_black * black.fr() + m_white * white.fr());
      color.set_green(rgb.fg() * luminanceComplement + m_black * black.fg() + m_white * white.fg());
      color.set_blue(rgb.fb() * luminanceComplement + m_black * black.fb() + m_white * white.fb());
      color.set_alpha(1.0f);
      //color.set_alpha(rgb.fa() * luminanceComplement + m_black * black.fa() + m_white * white.fa());

      return color;

      //return rgb * () + black * m_black + white * m_white;

   }


   void ColorWheel::set_color(const ::color::color& rgb) 
   {

      float r = rgb.fr(), g = rgb.fg(), b = rgb.fb();

      float M = ::maximum({ r, g, b });

      float m = ::minimum({ r, g, b });

      if (M == m) 
      {

         float l = 0.5f * (M + m);
         m_hue = 0.f;
         m_black = 1.f - l;
         m_white = l;

      }
      else 
      {

         float d = M - m, h;

         if (M == r)
         {

            h = (g - b) / d + (g < b ? 6 : 0);

         }
         else if (M == g)
         {

            h = (b - r) / d + 2;

         }
         else
         {

            h = (r - g) / d + 4;

         }

         h /= 6;

         ::color::color ch = hue2rgb(m_hue);

         float M2 = ::maximum({ ch.fr(), ch.fb(), ch.fb() });

         float m2 = ::minimum({ ch.fr(), ch.fg(), ch.fb() });

         m_white = (M * m2 - m * M2) / (m2 - M2);

         m_black = (M + m2 + m * M2 - m - M * m2 - M2) / (m2 - M2);

         m_hue = h;

      }

   }



} // namespace nanoui



