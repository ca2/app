// From nanoui by camilo on 2025-03-11 22:20 <3ThomasBorregaardSorensen!!
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
#include "color_wheel.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/image/image.h"
#include "nano2d/draw2d_context.h"


namespace graphics
{


   color_wheel::color_wheel()
   {
      m_ehittestDrag = e_hit_test_none;
   }

   color_wheel::~color_wheel()
   {

   }


   void color_wheel::_on_draw(::nano2d::context * pcontext)
   {

      //Widget::draw(pcontext);

      //if (!m_bVisible)
      //{

      //   return;

      //}

      double x = (double)m_rectangle.left();
      double y = (double)m_rectangle.top();
      double w = (double)m_rectangle.width();
      double h = (double)m_rectangle.height();

      double diam1 = (w < h ? w : h);
      double r1 = diam1 * 0.48;
      double r0 = r1 * .75;
      double u;
      u = ::maximum(r1 / 50, 1.5f);
      u = ::minimum(u, 4.f);


      int diamRound = (((int)ceil(diam1) - 1) / 2) * 2;

      int_size sizeImageOffset;
      sizeImageOffset.cx() = x + (w - diam1) / 2.0;
      sizeImageOffset.cy() = y + (h - diam1) / 2.0;

      ::double_point center;

      center = sizeImageOffset + ::double_size(diamRound / 2, diamRound / 2);

      double hue = m_hls.m_dH;
      
      int centerX = diamRound / 2;

      int centerY = diamRound / 2;

      double dAlphaThickness = u / 2.0;

      ::nano2d::paint paint;

      {

         ::nano2d::guard guard(pcontext);


         //::double_ellipse ellipse1;

         //ellipse1.left() = center.x() - r1;
         //ellipse1.top() = center.y() - r1;
         //ellipse1.right() = center.x() + r1;
         //ellipse1.bottom() = center.y() + r1;

         //::double_ellipse ellipse0;

         //ellipse0.left() = center.x() - r0;
         //ellipse0.top() = center.y() - r0;
         //ellipse0.right() = center.x() + r0;
         //ellipse0.bottom() = center.y() + r0;

         ::cast < ::nano2d::draw2d_context > p = pcontext;

         auto pgraphics = p->m_pgraphics;

         pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

         pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         //::draw2d::path_pointer ppath;

         //__øconstruct(ppath);

         //ppath->set_fill_mode(::draw2d::e_fill_mode_alternate);

         //ppath->add_ellipse(ellipse1);
         //ppath->add_ellipse(ellipse0);

         //pgraphics->set_clip(ppath);
         //pcontext->clip();

         if (!m_pimageCircle || diamRound != m_pimageCircle->width())
         {

            __øconstruct(m_pimageCircle);

            m_pimageCircle->create({ diamRound, diamRound });

            m_pimageCircle->map();

            m_pimageCircle->fill_byte(0);

            for (int x = 0; x < diamRound; x++)
            {

               for (int y = 0; y < diamRound; y++)
               {

                  int dx = x - centerX;

                  int dy = y - centerY;

                  double dHue = atan2(dy, dx);
                  double dRadius = sqrt((dx * dx) + (dy * dy));

                  unsigned char opacity = 0;

                  if (dRadius >= r1)
                  {

                     double d = dAlphaThickness - dRadius + r1;

                     opacity = (unsigned char)(minimum_maximum(d / dAlphaThickness, 0., 1.0) * 255.);

                     if (opacity == 0)
                     {

                        continue;

                     }

                  }
                  else if (dRadius > r0)
                  {

                     opacity = (unsigned char)255;

                  }
                  else if (dRadius > r0 - dAlphaThickness)
                  {

                     double d = dRadius - r0 + dAlphaThickness;

                     opacity = (unsigned char)(minimum_maximum(d / dAlphaThickness, 0., 1.0) * 255.);

                  }
                  else
                  {

                     //opacity = (unsigned char)0;

                     continue;

                  }

                  dHue /= 2.0 * MATH_PI;

                  ::color::hls hls(dHue);

                  ::color::color color(hls);

                  color.set_opacity(opacity);

                  m_pimageCircle->set_pixel(x, y, color);

               }

            }

            m_pimageCircle->unmap();

            //m_pimageCirce->g()->fill_ellipse(ellipse0);

         }
         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
         {

            ::image::image_source imagesource(m_pimageCircle);

            ::image::image_drawing_options imagedrawingoptions(m_pimageCircle->rectangle() + sizeImageOffset);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

         //      pcontext->save();

         //double cx = x + w * 0.5;
         //double cy = y + h * 0.5;
         double cx = sizeImageOffset.cx() + centerX;
         double cy = sizeImageOffset.cy() + centerY;
         //double r1 = (w < h ? w : h) * 0.5;
         //double r0 = r1 * .75;

         ////float aeps = 0.5f / r1;   // half a pixel arc length in radians (2pi cancels out).
         //float aeps = 1. / r0;   // one pixel arc length in radians (2pi cancels out).

         //for (int i = 0; i < 6; i++) 
         //{
         //   //auto a0 = (double)i / 6.0 * ::nano2d::f_pi * 2.0 - aeps;
         //   //auto a1 = (double)(i + 1.0) / 6.0 * ::nano2d::f_pi * 2.0 + aeps;
         //   auto a0precis = radians((double)i / 6.0 * ::nano2d::f_pi * 2.0);
         //   auto a1precis = radians((double)(i + 1.0) / 6.0 * ::nano2d::f_pi * 2.0);
         //   auto a0 = radians((double)i / 6.0 * ::nano2d::f_pi * 2.0 - aeps);
         //   auto a1 = radians((double)(i + 1.0) / 6.0 * ::nano2d::f_pi * 2.0 + aeps);
         //   pcontext->begin_path();
         //   pcontext->arc(cx, cy, r0, a0, a1, ::nano2d::e_winding_cw);
         //   pcontext->arc(cx, cy, r1, a1, a0, ::nano2d::e_winding_ccw);
         //   pcontext->close_path();
         //   //float ax = (float)cx + cos(a0 - 3. * aeps) * (r0 * 0.3 + r1 * 0.7);
         //   //float ay = (float)cy + sin(a0 - 3. * aeps) * (r0 * 0.3 + r1 * 0.7);
         //   //float bx = (float)cx + cos(a1 + 3. * aeps) * (r0 * 0.3 + r1 * 0.7);
         //   //float by = (float)cy + sin(a1 + 3. * aeps) * (r0 * 0.3 + r1 * 0.7);
         //   float ax = (float)cx + cos(a0 - 3. * aeps) * (r1);
         //   float ay = (float)cy + sin(a0 - 3. * aeps) * (r1);
         //   float bx = (float)cx + cos(a1 + 3. * aeps) * (r1);
         //   float by = (float)cy + sin(a1 + 3. * aeps) * (r1);
         //   //float ax = (float)cx + cos(a0) * (r0 * 0.3 + r1 * 0.7);
         //   //float ay = (float)cy + sin(a0) * (r0 * 0.3 + r1 * 0.7);
         //   //float bx = (float)cx + cos(a1) * (r0 * 0.3 + r1 * 0.7);
         //   //float by = (float)cy + sin(a1) * (r0 * 0.3 + r1 * 0.7);
         //   paint = pcontext->linear_gradient(ax, ay, bx, by,
         //      ::color::HSLA_color(a0precis.m_fAngle / (::nano2d::f_pi * 2), 1.0, 0.55, 255),
         //      ::color::HSLA_color(a1precis.m_fAngle / (::nano2d::f_pi * 2), 1.0, 0.55, 255));
         //   pcontext->fill_paint(paint);
         //   pcontext->fill();
         //}

         ::color::hsv hsv;

         {
            // Selector
            ::nano2d::guard guard(pcontext);
            //pcontext->save();
            pcontext->translate(cx, cy);
            pcontext->rotate(hue * ::nano2d::f_pi * 2);

            pcontext->stroke_width(u);

            pcontext->begin_path();
            pcontext->circle(0, 0, r0 - 0.5f);
            pcontext->circle(0, 0, r1 + 0.5f);
            pcontext->stroke_color(rgba(0, 0, 0, 64));
            //pcontext->stroke_width(1.0f);
            pcontext->stroke();


            // Marker on
            pcontext->begin_path();
            pcontext->rectangle(r0 - 1, -2 * u, r1 - r0 + 2, 4 * u);
            pcontext->stroke_color(rgba(255, 255, 255, 192));
            pcontext->stroke();

            paint = pcontext->box_gradient(r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, rgba(0, 0, 0, 128), rgba(0, 0, 0, 0));
            pcontext->begin_path();
            pcontext->rectangle(r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
            pcontext->rectangle(r0 - 2, -4, r1 - r0 + 4, 8);
            pcontext->path_winding(::nano2d::e_solidity_hole);
            pcontext->fill_paint(paint);
            pcontext->fill();

            //// Center triangle
            float r = r0 - 6.0;
            float ax = -0.5f * r;
            float ay = 0.5f * ::sqrt(3.f) * r;
            float bx = -0.5f * r;
            float by = -0.5f * ::sqrt(3.f) * r;
            pcontext->begin_path();
            pcontext->move_to(r, 0);
            pcontext->line_to(ax, ay);
            pcontext->line_to(bx, by);
            pcontext->close_path();
            paint = pcontext->linear_gradient(r, 0, ax, ay, ::color::HSLA_color(hue, 1.0f, 0.5f, 255), rgba(255, 255, 255, 255));
            pcontext->fill_paint(paint);
            pcontext->fill();
            paint = pcontext->linear_gradient((r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by, rgba(0, 0, 0, 0), rgba(0, 0, 0, 255));
            pcontext->fill_paint(paint);
            pcontext->fill();
            pcontext->stroke_color(rgba(0, 0, 0, 64));
            pcontext->stroke();

            //hsv = m_hls;

            // Select circle on triangle
            //float sx =-r -( r * (1.0 -hsv.m_dV - hsv.m_dS) + ax * hsv.m_dV + bx * hsv.m_dS);
            //float sy = ay * hsv.m_dV + by * hsv.m_dS;

            double dTriangleSide = sqrt(3.0) * r;
            double dTriangleHeight = 3.0 * r / 2.0;

            //auto triangle_y_top = [&](double x)
            //   {

            //      return (1.0 - (x - bx) / 1.5 * r) * (-dTriangleSide / 2.);

            //   };


            auto triangle_x_right = [&](double y)
               {

                  return (1.0 - fabs(y * 2.0 / dTriangleSide)) * 1.5 * r + bx;

               };

            //auto triangle_y_top = [&](double x)
//   {

//      return (1.0 - (x - bx) / 1.5 * r) * (-dTriangleSide / 2.);

//   };


//auto triangle_y_bottom = [&](double x)
//   {

//      return (1.0 - (x - bx) / 1.5 * r) * (dTriangleSide / 2.);

//   };

            float sx = bx + (dTriangleHeight * m_hls.m_dS);
            float sy = dTriangleSide * (m_hls.m_dL - 0.5);

            auto max_sx_for_given_sx = triangle_x_right(sy);

            if (sx > max_sx_for_given_sx)
            {
               sx = max_sx_for_given_sx;

            }


            pcontext->stroke_width(u);
            pcontext->begin_path();
            pcontext->circle(sx, sy, 2 * u);
            pcontext->stroke_color(rgba(255, 255, 255, 192));
            pcontext->stroke();

            //pcontext->restore();

         }

         //pcontext->restore();

      }


   }



   void color_wheel::on_draw(::draw2d::graphics * pgraphics)
   {

      ::nano2d::draw2d_context context(this);

      context.set_graphics(pgraphics);

      //__defer_construct_new(m_pfontsink);

      //context.set_font_sink(m_pfontsink);

      ::nano2d::context * pcontext = &context;

      _on_draw(pcontext);

   }


   bool color_wheel::on_mouse_down(const int_point & p)
   {

      if (!m_rectangle.contains(p + m_rectangle.top_left()))
      {

         return false;

      }

      m_ehittestDrag = adjust_position_and_hit_test(p);

      if (m_ehittestDrag)
      {

         graphics_set_mouse_capture();

         return true;

      }

      return false;

   }


   bool color_wheel::on_mouse_up(const int_point & p)
   {

      if (m_ehittestDrag)
      {

         m_ehittestDrag = e_hit_test_none;

         graphics_release_mouse_capture();

         return true;

      }

      return false;

   }


   bool color_wheel::on_mouse_motion(const int_point & p)
   {

      if (m_ehittestDrag)
      {

         adjust_position_and_hit_test(p);

         return true;

      }

      return false;

   }



   color_wheel::enum_hit_test color_wheel::adjust_position_and_hit_test(const int_point & p)
   {

      //double x = (double)m_rectangle.left();
      //double y = (double)m_rectangle.top();
      double x = 0.;
      double y = 0.;
      double w = (double)m_rectangle.width();
      double h = (double)m_rectangle.height();

      double diam1 = (w < h ? w : h);
      double r1 = diam1 * 0.48;
      double r0 = r1 * .75;
      double u;
      u = ::maximum(r1 / 50, 1.5f);
      u = ::minimum(u, 4.f);


      int diamRound = (((int)ceil(diam1) - 1) / 2) * 2;

      int_size sizeImageOffset;
      sizeImageOffset.cx() = x + (w - diam1) / 2.0;
      sizeImageOffset.cy() = y + (h - diam1) / 2.0;

      ::double_point center;

      center = sizeImageOffset + ::double_size(diamRound / 2, diamRound / 2);

      auto cx = p.x() - center.x();

      auto cy = p.y() - center.y();

      double smallest_dimension = diamRound /2;

      double mr = ::sqrt(cx * cx + cy * cy);

      if ((m_ehittestDrag & e_hit_test_outer_circle) || (!m_ehittestDrag && (mr >= r0 && mr <= r1)))
      {

         double dAngle = ::atan2(cy, cx);

         if (dAngle < 0.0)
         {

            dAngle += 2.0 * ::nano2d::f_pi;

         }                                      

         m_hls.m_dH = dAngle / (2.0 * ::nano2d::f_pi);

         on_color_change();

         auto color = this->get_sel_color();

         if (m_callback)
         {

            m_callback(color);

         }

         graphics_redraw();

         return e_hit_test_outer_circle;

      }

      double a = -m_hls.m_dH * 2.0 * ::nano2d::f_pi;
      double sin_a = ::sin(a);
      double cos_a = ::cos(a);

      double_point xy(cos_a * cx - sin_a * cy, sin_a * cx + cos_a * cy);

      //double r = r0 - 6;

      double r = r0;

      //float sx = bx + (1.5 * r * m_hls.m_dS * 2.0 * minimum(m_hls.m_dL, 1.0 - m_hls.m_dL));
      //float sy = sqrt(3.) * r * (m_hls.m_dL - 0.5) * (1.0 - m_hls.m_dS * minimum(m_hls.m_dL, 1.0 - m_hls.m_dL));

      double sx = xy.x();
      double sy = xy.y();

      double bx = -0.5f * r;

      double dTriangleSide = sqrt(3.0) * r;
      double dTriangleHeight= 3.0 * r / 2.0;


      double l0 = (double)(r - xy.x() + ::sqrt(3.) * xy.y()) / (3. * r);
      double l1 = (double)(r - xy.x() - ::sqrt(3.) * xy.y()) / (3. * r);
      double l2 = 1. - l0 - l1;
      bool triangle_test = l0 >= 0. && l0 <= 1. && l1 >= 0. && l1 <= 1. &&
         l2 >= 0. && l2 <= 1.;

      triangle_test = true;

      if ((m_ehittestDrag & e_hit_test_inner_triangle) || (!m_ehittestDrag && triangle_test))
      {

         l0 = ::minimum(::maximum(0., l0), 1.);
         l1 = ::minimum(::maximum(0., l1), 1.);
         l2 = ::minimum(::maximum(0., l2), 1.);
         double sum = l0 + l1 + l2;
         l0 /= sum;
         l1 /= sum;
         double dMinY = -dTriangleSide / 2.0;
         double dMaxY = dTriangleSide / 2.0;
         sx = minimum_maximum(sx, bx, bx + 1.5*r);
         double dRangeY =(bx + 1.5 * r - sx)/ fabs(1.5*r);
         sy = minimum_maximum(sy, dMinY * dRangeY, dMaxY * dRangeY);

         //color::hsv hsv(m_hls);
         m_hls.m_dL = (sy - dMinY) / (dTriangleSide);
         if (m_hls.m_dL <= 0.0 || m_hls.m_dL >= 1.0)
         {
            m_hls.m_dS = 0.;
         }
         else
         {
            m_hls.m_dS = (sx - bx) / (1.5 * r);
         }
         on_color_change();
         if (m_callback)
            m_callback(this->get_sel_color());
         graphics_redraw();
         return e_hit_test_inner_triangle;
      }

      return e_hit_test_client_area;

   }




   //::color::color color_wheel::color() const
   //{

   //   ::color::color rgb = hue2rgb(m_hls.m_dH);
   //   ::color::color black = ::color::black;
   //   ::color::color white = ::color::white;
   //   //::color::color black{ 0.f, 0.f, 0.f, m_black };
   //   //::color::color white{ m_white, m_white, m_white, m_white };

   //   ::color::color color;

   //   ::color::hsv

   //   color.set_opacity(1.0f);
   //   //color.set_alpha(rgb.fa() * luminanceComplement + m_black * black.fa() + m_white * white.fa());

   //   return color;

   //   //return rgb * () + black * m_black + white * m_white;

   //}


   //void color_wheel::set_color(const ::color::color & color)
   //{

   //   auto r = color.f32_red();
   //   auto g = color.f32_green();
   //   auto b = color.f32_blue();

   //   float M = color.f32_maximum_rgb();

   //   float m = color.f32_minimum_rgb();

   //   if (M == m)
   //   {

   //      float l = 0.5f * (M + m);
   //      m_hue = 0.f;
   //      m_black = 1.f - l;
   //      m_white = l;

   //   }
   //   else
   //   {

   //      float d = M - m, h;

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

   //      float M2 = ch.f32_maximum_rgb();

   //      float m2 = ch.f32_minimum_rgb();

   //      m_white = (M * m2 - m * M2) / (m2 - M2);

   //      m_black = (M + m2 + m * M2 - m - M * m2 - M2) / (m2 - M2);

   //      m_hue = h;

   //   }

   //}



} // namespace nanoui



