#include "framework.h"
#include "aura/graphics/draw2d/_draw2d.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/update.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/operating_system/windows_common/graphics.h"


//#if defined(__APPLE__)
//#define ARGB_COLORREF(A, R, G, B) argb(A, R, G, B)
//#define COLORREF_get_a_value(color32) colorref_get_a_value(color32)
//#define COLORREF_get_r_value(color32) colorref_get_r_value(color32)
//#define COLORREF_get_g_value(color32) colorref_get_g_value(color32)
//#define COLORREF_get_b_value(color32) colorref_get_b_value(color32)
//#else
//#define ARGB_COLORREF(A, R, G, B) argb(A, B, G, R)
//#define COLORREF_get_a_value(color32) colorref_get_a_value(color32)
//#define COLORREF_get_r_value(color32) colorref_get_b_value(color32)
//#define COLORREF_get_g_value(color32) colorref_get_g_value(color32)
//#define COLORREF_get_b_value(color32) colorref_get_r_value(color32)
//#endif


namespace app_core_flag
{


   void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h)
   {

      ::color::color crDenmarkRoed = argb(255, 200, 16, 46);

      double dx = w / 90.0;

      double dy = h / 70.0;

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + 0, y + 0, 90.0 * dx, 70.0 * dy), argb(255, 255, 255, 255));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + 0, y + 0, 30.0 * dx, 30.0 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + 40.0 * dx, y, 50 * dx, 30 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + 0, y + 40.0 * dy, 30.0 * dx, 30.0 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + 40.0 * dx, y + 40.0 * dy, 50.0 * dx, 30.0 * dy), crDenmarkRoed);

   }

}


namespace visual
{


   void image_color_with_shade_of_grey(byte & r, byte & g, byte & b, double i, double j, double w, double h)
   {

      double dR, dG, dB;

      double dH = i / w;

      dH *= 6.0;

      double dA = dH - (double)((i32)dH);

      if (dH >= 3.0)
      {
         if (dH >= 4.0)
         {
            if (dH >= 5.0)
            {
               // 5.0
               // magenta to red
               dR = 1.0;
               dG = 0.0;
               dB = 1.0 - dA;
            }
            else
            {
               // 4.0
               // blue to magenta
               dR = dA;
               dG = 0.0;
               dB = 1.0;
            }
         }
         else
         {
            // 3.0
            // cyan to blue
            dR = 0.0;
            dG = 1.0 - dA;
            dB = 1.0;
         }
      }
      else /// if(dH >= 0.0)
      {
         if (dH >= 2.0)
         {
            // 2
            // green to cyan
            dR = 0.0;
            dG = 1.0;
            dB = dA;
         }
         else // (dH >= 0.0 && dH < 2.0)
         {
            if (dH >= 1.0)
            {
               // 1
               // yellow to green
               dR = 1.0 - dA;
               dG = 1.0;
               dB = 0.0;
            }
            else // if(dh >= 0 && dH < 1.0);
            {
               // 0
               // red to yellow
               dR = 1.0;
               dG = dA;
               dB = 0.0;
            }
         }
      }

      double dL = 0.5;

      double dS = 1.0 - IMAGE_Y(j, h) / h;
//#if defined(__APPLE__)
//      dS = 1.0 - dS;
//#endif

      double dCMin;
      double dCAdd;
      double dSL = dS * dL;
      if (dL >= 0.5)
      {
         dCMin = dL - dS + dSL;
         dCAdd = 2.0 * dS - 2.0 * dSL;
      }
      else
      {
         dCMin = dL - dSL;
         dCAdd = 2.0 * dSL;
      }

      double _dR = (dCMin + dR * dCAdd);
      double _dG = (dCMin + dG * dCAdd);
      double _dB = (dCMin + dB * dCAdd);

      r = byte(_dR * 255.0);
      g = byte(_dG * 255.0);
      b = byte(_dB * 255.0);

   }


   void color_with_shade_of_grey(::color::color & color, double i, double j, double dw, double dh)
   {
      
#ifdef __APPLE__

      image_color_with_shade_of_grey(color.red, color.green, color.blue, i, dh - j -1, dw, dh);
      
#else
      
      image_color_with_shade_of_grey(color.red, color.green, color.blue, i, j, dw, dh);
      
#endif

   }


   void colors_with_shades_of_grey(::image * pimage)
   {

      pimage->map();

      ::count w = pimage->width();

      ::count h = pimage->height();

      ::u32 uScan = pimage->scan_size();

      ::byte * pline;

      for (index i = 0; i < w; i++)
      {

         pline = (byte *) (pimage->get_data() + i);

         for (index j = 0; j < h; j++)
         {

            image_color_with_shade_of_grey(
               pline[IMAGE_R_BYTE_INDEX],
               pline[IMAGE_G_BYTE_INDEX],
               pline[IMAGE_B_BYTE_INDEX],
               (double) i, (double) j, (double) w, (double) h);

            pline[IMAGE_A_BYTE_INDEX] = 255;

            pline+=uScan;

         }

      }

   }


   void shades_of_luminance(::image * pimage, double dH, double dS)
   {

      pimage->map();

      ::count w = pimage->width();

      ::count h = pimage->height();

      ::color::color color;

      auto dh = (double) h;

      ::u32 uScan;

      //dS = 1.0 - ((double)j / dh);

      uScan = pimage->scan_size() / sizeof(::color32_t);

      ::color32_t * pline;

      double dR, dG, dB;

      dH *= 6.0;

      double dA = dH - (double)((i32)dH);

      if (dH >= 3.0)
      {
         if (dH >= 4.0)
         {
            if (dH >= 5.0)
            {
               // 5.0
               // magenta to red
               dR = 1.0;
               dG = 0.0;
               dB = 1.0 - dA;
            }
            else
            {
               // 4.0
               // blue to magenta
               dR = dA;
               dG = 0.0;
               dB = 1.0;
            }
         }
         else
         {
            // 3.0
            // cyan to blue
            dR = 0.0;
            dG = 1.0 - dA;
            dB = 1.0;
         }
      }
      else /// if(dH >= 0.0)
      {
         if (dH >= 2.0)
         {
            // 2
            // green to cyan
            dR = 0.0;
            dG = 1.0;
            dB = dA;
         }
         else // (dH >= 0.0 && dH < 2.0)
         {
            if (dH >= 1.0)
            {
               // 1
               // yellow to green
               dR = 1.0 - dA;
               dG = 1.0;
               dB = 0.0;
            }
            else // if(dh >= 0 && dH < 1.0);
            {
               // 0
               // red to yellow
               dR = 1.0;
               dG = dA;
               dB = 0.0;
            }
         }
      }

      for (index j = 0; j < h; j++)
      {
         double dL = 1.0 - ((double) j / dh);

#if defined(__APPLE__)
         dL = 1.0 - dL;
#endif

         //double dS = 1.0 - ((double)j / dh);

         double dCMin;
         double dCAdd;
         double dSL = dS * dL;
         if (dL >= 0.5)
         {
            dCMin = dL - dS + dSL;
            dCAdd = 2.0 * dS - 2.0 * dSL;
         }
         else
         {
            dCMin = dL - dSL;
            dCAdd = 2.0 * dSL;
         }


         double _dR = (dCMin + dR * dCAdd);
         double _dG = (dCMin + dG * dCAdd);
         double _dB = (dCMin + dB * dCAdd);

         //byte uchR = (byte)primitive_color_round(m_dR * 255.0);
         //m_uchG = (byte)primitive_color_round(m_dG * 255.0);
         //m_uchB = (byte)primitive_color_round(m_dB * 255.0);

         pline = pimage->get_data() + uScan * j;
         ::color32_t color32 = IMAGE_ARGB(255, byte(_dR*255.0), byte(_dG*255.0), byte(_dB*255.0));
         for (index i = 0; i < w; i++)
         {

            *pline = color32;

            pline ++;

         }

      }

   }

}


namespace userex
{


   color_impact::color_impact()
   {

      m_bMouseColorBeam = false;

      m_bCompact = false;

      m_atomImpact = COLORSEL_IMPACT;

      m_bLButtonPressed = false;

      m_atom = impact_color_sel;

   }


   color_impact::~color_impact()
   {


   }


   void color_impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void color_impact::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void color_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &color_impact::on_message_create);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &color_impact::on_message_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &color_impact::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &color_impact::on_message_left_button_up);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &color_impact::on_message_show_window);

      m_pimageTemplate = m_pcontext->m_pauracontext->create_image({2048,  2048});

      ::visual::colors_with_shades_of_grey(m_pimageTemplate);

      m_pimageLuminance = m_pcontext->m_pauracontext->create_image({100,  100});

   }


   void color_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   //void color_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   ::user::impact::handle(ptopic, pcontext);

   //}


   void color_impact::on_message_create(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //auto ppen = __create < ::draw2d::pen > ();

      //ppen->create_solid(1.0, argb(255, 255, 255, 255));

      //m_pimageBeam->g()->set(ppen);

      //m_pimageBeam->g()->DrawEllipse(rectangle_i32_dimension(0, 0, 32, 32));



      //get_parent_frame()->m_atom += ".color_sel";

      pmessage->previous();

      if(get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = this;

      }

      //set_impact_title("__CoLoR_");

      parent_frame()->set_frame_title("__CoLoR_");

   }


   void color_impact::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::show_window) pshowwindow(pmessage);

   }


   ::color::color color_impact::get_color()
   {

      ::color::color color;

      color.set_hls(m_hls);

      color.alpha = 255;

      return color.get_rgba();

   }


   void color_impact::set_color(const ::color::color & color)
   {

      m_bMouseColorBeam = false;

      color.get_hls(m_hls);

      set_need_layout();

      set_need_redraw();

   }


   void color_impact::on_mouse(const ::point_i32 & point)
   {

      if (point.y >= m_rectangleColors.bottom)
      {

         return;

      }

      if (point.x < m_rectangleColors.left)
      {

         return;

      }

      if (point.y < m_rectangleColors.top)
      {

         return;

      }

      int iColorsLeft = m_rectangleColors.left;

      int iColorsWidth = m_pimage->width();

      int iColorsRight = iColorsLeft + iColorsWidth;

      if (point.x < iColorsRight)
      {

         int x = point.x - iColorsLeft;

         int y = point.y - m_rectangleColors.top;

         m_pointMouseColorBeam = point;

         m_bMouseColorBeam = true;

         ::color::color color;

         visual::color_with_shade_of_grey(color,
            x, y,
            iColorsWidth, m_rectangleColors.height());

         ::color::hls hls;

         color.get_hls(hls);

         m_hls.m_dH = hls.m_dH;

         m_hls.m_dS = hls.m_dS;

         rebuild_luminance();
         
         if(has_handler())
         {

            auto ptopic = create_topic(::id_after_change_cur_hover);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);
               
         }

         set_need_redraw();

         post_redraw();

      }
      else if (point.x < m_rectangleColors.center().x + m_rectangleColors.width() / 8)
      {

         auto pointLuminance = point - ::size_i32(m_rectangleColors.center().x, m_rectangleColors.top);

         m_hls.m_dL = 1.0 - ((double)pointLuminance.y / (double) m_pimage->height());
         
         if(has_handler())
         {

            auto ptopic = create_topic(::id_after_change_cur_hover);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);
               
         }

         set_need_redraw();

         post_redraw();

      }

   }


   void color_impact::rebuild_luminance()
   {

      ::visual::shades_of_luminance(m_pimageLuminance, m_hls.m_dH, m_hls.m_dS);

   }


   void color_impact::draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & pointParam)
   {

      point_f64 point(pointParam);

      double dSize = 17.0;

      size_f64 sizeBeam(dSize,dSize);

      rectangle_f64 rectangleOuter(point.x - sizeBeam.cx / 2.0, point.y - sizeBeam.cy / 2.0, point.x + sizeBeam.cx / 2.0, point.y + sizeBeam.cy / 2.0);

      rectangle_f64 rectangleInner(rectangleOuter);

      rectangleInner.deflate(sizeBeam.cx / 4.0, sizeBeam.cy / 4.0);

      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->create_solid(argb(255, 0, 0, 0));

      pgraphics->set(pbrush);

      double dHalfTriBase = dSize / 8.0;

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectangleOuter.left, point.y - dHalfTriBase));
         pointa.add(point_f64(rectangleInner.left, point.y));
         pointa.add(point_f64(rectangleOuter.left, point.y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(point.x - dHalfTriBase, rectangleOuter.top));
         pointa.add(point_f64(point.x, rectangleInner.top));
         pointa.add(point_f64(point.x + dHalfTriBase, rectangleOuter.top));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectangleOuter.right, point.y - dHalfTriBase));
         pointa.add(point_f64(rectangleInner.right, point.y));
         pointa.add(point_f64(rectangleOuter.right, point.y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(point.x - dHalfTriBase, rectangleOuter.bottom));
         pointa.add(point_f64(point.x, rectangleInner.bottom));
         pointa.add(point_f64(point.x + dHalfTriBase, rectangleOuter.bottom));

         pgraphics->fill_polygon(pointa);

      }

   }


   void color_impact::draw_level(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleW, int yParam)
   {

      double y = yParam;

      double dSize = 17.0;

      rectangle_f64 rectangleInner(rectangleW);

      rectangle_f64 rectangleOuter(rectangleInner);

      rectangleOuter.inflate(dSize / 2.0, dSize / 2.0);

      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->create_solid(argb(255, 0, 0, 0));

      pgraphics->set(pbrush);

      double dHalfTriBase = dSize / 8.0;

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectangleOuter.left, y - dHalfTriBase));
         pointa.add(point_f64(rectangleInner.left, y));
         pointa.add(point_f64(rectangleOuter.left, y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectangleOuter.right, y - dHalfTriBase));
         pointa.add(point_f64(rectangleInner.right, y));
         pointa.add(point_f64(rectangleOuter.right, y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

   }


   void color_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rC;

      get_client_rect(rC);

      pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      ::rectangle_i32 rTarget;

      rTarget.top_left() = m_rectangleColors.top_left();

      if (!m_pimage)
      {

         return;

      }

      rTarget.set_size(m_pimage->get_size());

      ::rectangle_i32 rSource = m_pimage->rectangle();

      ::rectangle_i32 rCursor;

      {

         image_source imagesource(m_pimage, rSource);

         image_drawing_options imagedrawingoptions(rTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      ::point_i32 point;

      if (m_bMouseColorBeam)
      {

         point = m_pointMouseColorBeam;

      }
      else
      {

         point.x = (::i32)(rTarget.left + rTarget.width() * m_hls.m_dH);

         point.y = (::i32)(rTarget.top + rTarget.height() * (1.0 - m_hls.m_dS));

      }

      draw_beam(pgraphics, point);

      ::rectangle_i32 rectangleLum1;

      rectangleLum1.top_left() = m_rectangleColors.top_left() + ::size_i32(m_pimage->width()-1, 0);

      rectangleLum1.set_size(m_pimageLuminance->get_size());

      rSource = m_pimageLuminance->rectangle();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      {

         image_source imagesource(m_pimageLuminance);

         image_drawing_options imagedrawingoptions(rectangleLum1);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      rTarget.top_left() = m_rectangleColors.top_left() + ::size_i32(m_pimage->width() - 1 + m_pimageLuminance->get_size().cx - 1, 0);

      rTarget.set_size(m_rectangleColors.right - rTarget.left, m_pimage->height());

      pgraphics->fill_rectangle(rTarget, get_color());

      int y = (int) (rectangleLum1.top + (1.0 - m_hls.m_dL)  * rectangleLum1.height());

      draw_level(pgraphics, rectangleLum1, y);

   }


   void color_impact::on_message_left_button_down(::message::message * pmessage)
   {
      
      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      set_mouse_capture();

      m_bLButtonPressed = true;

   }


   void color_impact::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;
      
      ::point_i32 point = pmouse->m_point;
      
      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

auto pwindowing = windowing();

      pwindowing->release_mouse_capture();

      m_bLButtonPressed = false;
      
      if(has_handler())
      {

         auto ptopic = create_topic(::id_after_change_cur_sel);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext = ::e_source_user;

         route(ptopic);
            
      }

   }


   void color_impact::on_message_mouse_move(::message::message * pmessage)
   {
      
      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_bLButtonPressed)
      {

         ::point_i32 point = pmouse->m_point;

         screen_to_client(point);

         on_mouse(point);

         pmouse->m_bRet = true;

      }

   }


   void color_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::on_layout(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      ::rectangle_i32 rectangleColors;

      get_client_rect(rectangleColors);

      if(!m_bCompact)
      {

         rectangleColors.left = rectangleClient.center().x;
         rectangleColors.bottom = rectangleClient.center().y;

         rectangleColors.deflate(rectangleClient.width() / 16, rectangleClient.height() / 16);

      }

      m_rectangleColors = rectangleColors;

      m_pimage = m_pcontext->m_pauracontext->create_image({m_rectangleColors.width() / 2,  m_rectangleColors.height()});

      {

         image_source imagesource(m_pimageTemplate);

         image_drawing_options imagedrawingoptions(m_pimage->rectangle());

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         m_pimage->g()->draw(imagedrawing);

      }

      m_pimageLuminance = m_pcontext->m_pauracontext->create_image({m_rectangleColors.width() / 8,  m_rectangleColors.height()});

      rebuild_luminance();

   }


} // namespace userex



