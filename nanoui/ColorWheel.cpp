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


   ColorWheel::ColorWheel(Widget* parent, const ::color::hls& hls)
      : Widget(parent)//, m_regionDrag(None) 
   {

      set_sel_color(hls);

   }


   i32_size ColorWheel::preferred_size(::nano2d::context *, bool bRecalcTextSize) 
   {

      return { 100, 100 };

   }


   //#define ::nano2d::f_pi MATH_PI

   void ColorWheel::draw(::nano2d::context * pcontext)
   {

      Widget::draw(pcontext);

      if (!m_bVisible)
      {

         return;

      }

      m_rectangle.left = (::f32) m_pos.x;
      m_rectangle.top = (::f32)m_pos.y;
      m_rectangle.right = (::f32)(m_pos.x + m_size.cx);
      m_rectangle.bottom = (::f32)(m_pos.y + m_size.cy);

      ::graphics::color_wheel::_on_draw(pcontext);

      //::f32 x = (::f32)m_pos.x, y = (::f32)m_pos.y,
      //   w = (::f32)m_size.cx, h = (::f32)m_size.cy;

      //::f32 hue = m_hue;
      //::nano2d::paint paint;

      //{

      //   ::nano2d::guard guard(pcontext);

      //   //      pcontext->save();

      //   ::f32 cx = x + w * 0.5f;
      //   ::f32 cy = y + h * 0.5f;
      //   ::f32 r1 = (w < h ? w : h) * 0.5f - 5.0f;
      //   ::f32 r0 = r1 * .75f;

      //   ::f32 aeps = 0.5f / r1;   // half a pixel arc length in radians (2pi cancels out).

      //   for (::i32 i = 0; i < 6; i++) {
      //      auto a0 = radians((::f32)i / 6.0f * ::nano2d::f_pi * 2.0f - aeps);
      //      auto a1 = radians((::f32)(i + 1.0f) / 6.0f * ::nano2d::f_pi * 2.0f + aeps);
      //      pcontext->begin_path();
      //      pcontext->arc(cx, cy, r0, a0, a1, ::nano2d::e_winding_cw);
      //      pcontext->arc(cx, cy, r1, a1, a0, ::nano2d::e_winding_ccw);
      //      pcontext->close_path();
      //      ::f32 ax = (::f32)cx + cosf(a0 - 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      //      ::f32 ay = (::f32)cy + sinf(a0 - 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      //      ::f32 bx = (::f32)cx + cosf(a1 + 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      //      ::f32 by = (::f32)cy + sinf(a1 + 3.0f * aeps) * (r0 * 0.3f + r1 * 0.7f);
      //      paint = pcontext->linear_gradient(ax, ay, bx, by,
      //         ::color::HSLA_color(a0 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255),
      //         ::color::HSLA_color(a1 / (::nano2d::f_pi * 2), 1.0f, 0.55f, 255));
      //      pcontext->fill_paint(paint);
      //      pcontext->fill();
      //   }

      //   pcontext->begin_path();
      //   pcontext->circle(cx, cy, r0 - 0.5f);
      //   pcontext->circle(cx, cy, r1 + 0.5f);
      //   pcontext->stroke_color(rgba(0, 0, 0, 64));
      //   pcontext->stroke_width(1.0f);
      //   pcontext->stroke();

      //   {
      //      // Selector
      //      ::nano2d::guard guard(pcontext);
      //      //pcontext->save();
      //      pcontext->translate(cx, cy);
      //      pcontext->rotate(hue * ::nano2d::f_pi * 2);

      //      // Marker on
      //      ::f32 u = ::maximum(r1 / 50, 1.5f);
      //      u = ::minimum(u, 4.f);
      //      pcontext->stroke_width(u);
      //      pcontext->begin_path();
      //      pcontext->rectangle(r0 - 1, -2 * u, r1 - r0 + 2, 4 * u);
      //      pcontext->stroke_color(rgba(255, 255, 255, 192));
      //      pcontext->stroke();

      //      paint = pcontext->box_gradient(r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, rgba(0, 0, 0, 128), rgba(0, 0, 0, 0));
      //      pcontext->begin_path();
      //      pcontext->rectangle(r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
      //      pcontext->rectangle(r0 - 2, -4, r1 - r0 + 4, 8);
      //      pcontext->path_winding(::nano2d::e_solidity_hole);
      //      pcontext->fill_paint(paint);
      //      pcontext->fill();

      //      //// Center triangle
      //      ::f32 r = r0 - 6;
      //      ::f32 ax = -0.5f * r;
      //      ::f32 ay = 0.5f * ::sqrt(3.f) * r;
      //      ::f32 bx = -0.5f * r;
      //      ::f32 by = -0.5f * ::sqrt(3.f) * r;
      //      pcontext->begin_path();
      //      pcontext->move_to(r, 0);
      //      pcontext->line_to(ax, ay);
      //      pcontext->line_to(bx, by);
      //      pcontext->close_path();
      //      paint = pcontext->linear_gradient(r, 0, ax, ay, ::color::HSLA_color(hue, 1.0f, 0.5f, 255), rgba(255, 255, 255, 255));
      //      pcontext->fill_paint(paint);
      //      pcontext->fill();
      //      paint = pcontext->linear_gradient((r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by, rgba(0, 0, 0, 0), rgba(0, 0, 0, 255));
      //      pcontext->fill_paint(paint);
      //      pcontext->fill();
      //      pcontext->stroke_color(rgba(0, 0, 0, 64));
      //      pcontext->stroke();

      //      // Select circle on triangle
      //      //::f32 sx = r * (1 - m_white - m_black) + ax * m_white + bx * m_black;
      //      //::f32 sy = ay * m_white + by * m_black;
      //      ::f32 sx = r * (1 - m_white - m_black) + ax * m_white + bx * m_black;
      //      ::f32 sy = m_hls.dS * ay;

      //      pcontext->stroke_width(u);
      //      pcontext->begin_path();
      //      pcontext->circle(sx, sy, 2 * u);
      //      pcontext->stroke_color(rgba(255, 255, 255, 192));
      //      pcontext->stroke();

      //      //pcontext->restore();

      //   }

      //   //pcontext->restore();

      //}

   }


   bool ColorWheel::mouse_button_event(const i32_point& p, ::user::e_key_state ekeystate, bool down, bool bDoubleClick, const ::user::e_key& ekeystate)
   {
      
      if (!m_bEnabled || ebuttonstate != ::user::e_key_state_left)
      {

         return false;

      }

      if (down)
      {
      
         if (on_mouse_down(p))
         {

            return true;

         }
         //m_regionDrag = adjust_position(p);

         //if (m_regionDrag)
         //{
         //   
         //   set_mouse_capture();

         //   return true;

         //}

         return false;

      }
      else 
      {

         if (on_mouse_up(p))
         {
            //m_regionDrag = None;

          //  release_mouse_capture();

            return true;

         }

      }

         return false;
      //Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeystate);


   }


   bool ColorWheel::mouse_motion_event(const i32_point& p, const i32_size& shift, bool bDown, const ::user::e_key& ekeystate)
   {

      //if (m_regionDrag)
      //{

      //   adjust_position(p);

      //   return true;

      //}

      if (on_mouse_motion(p))
      {

         return true;

      }

      return Widget::mouse_motion_event(p, shift, bDown, ekeystate);

   }


   //ColorWheel::Region ColorWheel::adjust_position(const i32_point& p)
   //{

   //   ::f32 x = (::f32) p.x;
   //   
   //   ::f32 y = (::f32) p.y;
   //   
   //   ::f32 pwidget = (::f32)m_size.cx;
   //   
   //   ::f32 h = (::f32)m_size.cy;

   //   ::f32 cx = pwidget / 2.f;

   //   ::f32 cy = h / 2.f;

   //   ::f32 smallest_dimension = minimum(cx, cy);

   //   ::f32 r1 = smallest_dimension - 5.0f;

   //   ::f32 r0 = r1 * .75f;

   //   x -= cx;

   //   y -= cy;

   //   ::f32 mr = ::sqrt(x * x + y * y);

   //   if ((m_regionDrag & OuterCircle) || (!m_regionDrag && (mr >= r0 && mr <= r1))) 
   //   {

   //      m_hue = ::atan(y / x);
   //      
   //      if (x < 0)
   //      {

   //         m_hue += ::nano2d::f_pi;

   //      }

   //      m_hue /= 2 * ::nano2d::f_pi;

   //      auto color = this->color();

   //      if (m_callback)
   //      {

   //         m_callback(color);

   //      }

   //      return OuterCircle;

   //   }

   //   ::f32 a = -m_hue * 2 * ::nano2d::f_pi;
   //   ::f32 sin_a = ::sinf(a);
   //   ::f32 cos_a = ::cosf(a);
   //   
   //   ::f32_point xy(cos_a * x - sin_a * y,
   //      sin_a * x + cos_a * y);

   //   ::f32 r = r0 - 6;
   //   ::f32 l0 = (::f32)(r - xy.x + ::sqrt(3.f) * xy.y) / (3.f * r);
   //   ::f32 l1 = (::f32)(r - xy.x - ::sqrt(3.f) * xy.y) / (3.f * r);
   //   ::f32 l2 = 1 - l0 - l1;
   //   bool triangle_test = l0 >= 0 && l0 <= 1.f && l1 >= 0.f && l1 <= 1.f &&
   //      l2 >= 0.f && l2 <= 1.f;

   //   if ((m_regionDrag & InnerTriangle) || (!m_regionDrag && triangle_test))
   //   {

   //      l0 = ::minimum(::maximum(0.f, l0), 1.f);
   //      l1 = ::minimum(::maximum(0.f, l1), 1.f);
   //      l2 = ::minimum(::maximum(0.f, l2), 1.f);
   //      ::f32 sum = l0 + l1 + l2;
   //      l0 /= sum;
   //      l1 /= sum;
   //      m_white = l0;
   //      m_black = l1;
   //      if (m_callback)
   //         m_callback(this->color());
   //      return InnerTriangle;
   //   }

   //   return ClientArea;

   //}


   //::color::color ColorWheel::hue2rgb(::f32 h) const {
   //   ::f32 s = 1.f;
   //   ::f32 v = 1.f;

   //   if (h < 0) h += 1;

   //   ::i32 i = ::i32(h * 6);
   //   ::f32 f = h * 6 - i;
   //   ::f32 p = v * (1 - s);
   //   ::f32 q = v * (1 - f * s);
   //   ::f32 t = v * (1 - (1 - f) * s);

   //   ::f32 r = 0, g = 0, b = 0;
   //   switch (i % 6) {
   //   case 0:
   //   {
   //      r = v;
   //      g = t;
   //      b = p;
   //   }
   //   break;
   //   case 1:
   //   {
   //      r = q;
   //      g = v;
   //      b = p;
   //   }
   //   break;
   //   case 2:
   //   {
   //      r = p;
   //      g = v;
   //      b = t;

   //   }
   //   break;
   //   case 3:
   //   {
   //      r = p;
   //      g = q;
   //      b = v;

   //   }
   //   break;
   //   case 4:
   //   {
   //      r = t;
   //      g = p;
   //      b = v;
   //   }
   //   break;
   //   case 5:
   //   {
   //      r = v;
   //      g = p;
   //      b = q;

   //   }
   //   break;
   //   }

   //   return rgba( r, g, b, 1.f );

   //}


   //::color::color ColorWheel::color() const 
   //{
   //   
   //   ::color::color rgb = hue2rgb(m_hue);
   //   ::color::color black = ::color::black;
   //   ::color::color white = ::color::white;
   //   //::color::color black{ 0.f, 0.f, 0.f, m_black };
   //   //::color::color white{ m_white, m_white, m_white, m_white };

   //   ::color::color color;

   //   ::f32 luminanceComplement = 1.0f - m_white - m_black;

   //   color.set_red(rgb.f64_red() * luminanceComplement + m_black * black.f64_red() + m_white * white.f64_red());
   //   color.set_green(rgb.f64_green() * luminanceComplement + m_black * black.f64_green() + m_white * white.f64_green());
   //   color.set_blue(rgb.f64_blue() * luminanceComplement + m_black * black.f64_blue() + m_white * white.f64_blue());
   //   color.set_opacity(1.0f);
   //   //color.set_alpha(rgb.fa() * luminanceComplement + m_black * black.fa() + m_white * white.fa());

   //   return color;

   //   //return rgb * () + black * m_black + white * m_white;

   //}


   //void ColorWheel::set_color(const ::color::color& color) 
   //{

   //   auto r = color.f32_red();
   //   auto g = color.f32_green();
   //   auto b = color.f32_blue();

   //   ::f32 M = color.f32_maximum_rgb();

   //   ::f32 m = color.f32_minimum_rgb();

   //   if (M == m) 
   //   {

   //      ::f32 l = 0.5f * (M + m);
   //      m_hue = 0.f;
   //      m_black = 1.f - l;
   //      m_white = l;

   //   }
   //   else 
   //   {

   //      ::f32 d = M - m, h;

   //      if (M == r)
   //      {

   //         h = (g - b) / d + (g < b ? 6 : 0);

   //      }
   //      else if (M == g)
   //      {

   //         h = (b - r) / d + 2;

   //      }
   //      else
   //      {

   //         h = (r - g) / d + 4;

   //      }

   //      h /= 6;

   //      ::color::color ch = hue2rgb(m_hue);

   //      ::f32 M2 = ch.f32_maximum_rgb();

   //      ::f32 m2 = ch.f32_minimum_rgb();

   //      m_white = (M * m2 - m * M2) / (m2 - M2);

   //      m_black = (M + m2 + m * M2 - m - M * m2 - M2) / (m2 - M2);

   //      m_hue = h;

   //   }

   //}


void ColorWheel::graphics_set_mouse_capture()
{

   set_mouse_capture();

}
void ColorWheel::graphics_release_mouse_capture()
{

   release_mouse_capture();

}
void ColorWheel::graphics_redraw()
{
   set_need_redraw();

   post_redraw();


}




} // namespace nanoui



