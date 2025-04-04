#include "framework.h"
#include "color_selector.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/image32.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/message/user.h"
//#include "aura/operating_system/windows_common/graphics.h"
#include "aura/platform/system.h"
#include "base/user/user/document.h"


namespace app_core_flag
{


   void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h)
   {

      ::color::color crDenmarkRoed = argb(255, 200, 16, 46);

      double Δx = w / 90.0;

      double Δy = h / 70.0;

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + 0, y + 0, 90.0 * Δx, 70.0 * Δy), argb(255, 255, 255, 255));

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + 0, y + 0, 30.0 * Δx, 30.0 * Δy), crDenmarkRoed);

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + 40.0 * Δx, y, 50 * Δx, 30 * Δy), crDenmarkRoed);

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + 0, y + 40.0 * Δy, 30.0 * Δx, 30.0 * Δy), crDenmarkRoed);

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + 40.0 * Δx, y + 40.0 * Δy, 50.0 * Δx, 30.0 * Δy), crDenmarkRoed);

   }

}


namespace graphics
{


   void image_color_with_shade_of_grey(unsigned char & r, unsigned char & g, unsigned char & b, double i, double j, double w, double h)
   {

      double dH = i / w;

      double dS = (h - j) / h;

      ::color::hls hls(dH, 0.5, dS);

      ::color::color color(hls);

      r = color.byte_red();
      g = color.byte_green();
      b = color.byte_blue();


      //dH *= 6.0;

      //double dA = dH - (double)((int)dH);

      //if (dH >= 3.0)
      //{
      //   if (dH >= 4.0)
      //   {
      //      if (dH >= 5.0)
      //      {
      //         // 5.0
      //         // magenta to red
      //         dR = 1.0;
      //         dG = 0.0;
      //         dB = 1.0 - dA;
      //      }
      //      else
      //      {
      //         // 4.0
      //         // blue to magenta
      //         dR = dA;
      //         dG = 0.0;
      //         dB = 1.0;
      //      }
      //   }
      //   else
      //   {
      //      // 3.0
      //      // cyan to blue
      //      dR = 0.0;
      //      dG = 1.0 - dA;
      //      dB = 1.0;
      //   }
      //}
      //else /// if(dH >= 0.0)
      //{
      //   if (dH >= 2.0)
      //   {
      //      // 2
      //      // green to cyan
      //      dR = 0.0;
      //      dG = 1.0;
      //      dB = dA;
      //   }
      //   else // (dH >= 0.0 && dH < 2.0)
      //   {
      //      if (dH >= 1.0)
      //      {
      //         // 1
      //         // yellow to green
      //         dR = 1.0 - dA;
      //         dG = 1.0;
      //         dB = 0.0;
      //      }
      //      else // if(dh >= 0 && dH < 1.0);
      //      {
      //         // 0
      //         // red to yellow
      //         dR = 1.0;
      //         dG = dA;
      //         dB = 0.0;
      //      }
      //   }
      //}

      //double dL = 0.5;

      //double dS = 1.0 - IMAGE_Y(j, h) / h;
      ////#if defined(__APPLE__)
      ////      dS = 1.0 - dS;
      ////#endif

      //double dCMin;
      //double dCAdd;
      //double dSL = dS * dL;
      //if (dL >= 0.5)
      //{
      //   dCMin = dL - dS + dSL;
      //   dCAdd = 2.0 * dS - 2.0 * dSL;
      //}
      //else
      //{
      //   dCMin = dL - dSL;
      //   dCAdd = 2.0 * dSL;
      //}

      //double _dR = (dCMin + dR * dCAdd);
      //double _dG = (dCMin + dG * dCAdd);
      //double _dB = (dCMin + dB * dCAdd);

   /*   r = (unsigned char)(_dR * 255.0);
      g = (unsigned char)(_dG * 255.0);
      b = (unsigned char)(_dB * 255.0);*/

   }


   void color_with_shade_of_grey(::color::color & color, double i, double j, double dw, double dh)
   {

#ifdef __APPLE__

      image_color_with_shade_of_grey(
         color.m_uchRed,
         color.m_uchGreen,
         color.m_uchBlue,
         i, dh - j - 1, dw, dh);

#else

      image_color_with_shade_of_grey(
         color.m_uchRed,
         color.m_uchGreen,
         color.m_uchBlue,
         i, j, dw, dh);

#endif

   }


   void colors_with_shades_of_grey(::image::image *pimage)
   {

      pimage->map();

      ::collection::count w = pimage->width();

      ::collection::count h = pimage->height();

      unsigned int uScan = pimage->scan_size();

      unsigned char * pline;

      auto a = pimage->m_colorindexes.m_uchIndexOpacity;
      auto r = pimage->m_colorindexes.m_uchIndexRed;
      auto g = pimage->m_colorindexes.m_uchIndexGreen;
      auto b = pimage->m_colorindexes.m_uchIndexBlue;

      for (::collection::index i = 0; i < w; i++)
      {

         pline = (unsigned char *)(pimage->get_data() + i);

         for (::collection::index j = 0; j < h; j++)
         {

            image_color_with_shade_of_grey(
               pline[r],
               pline[g],
               pline[b],
               (double)i, (double)j, (double)w, (double)h);

            pline[a] = 255;

            pline += uScan;

         }

      }

   }


   void shades_of_luminance(::image::image *pimage, double dH, double dS)
   {

      pimage->map();

      ::collection::count w = pimage->width();

      ::collection::count h = pimage->height();

      ::color::color color;

      auto dh = (double)h;

      unsigned int uScan;

      //dS = 1.0 - ((double)j / dh);

      uScan = pimage->scan_size() / sizeof(::color32_t);

      ::image32_t * pline;

      //double dR, dG, dB;

      //dH *= 6.0;

      //double dA = dH - (double)((int)dH);

      //if (dH >= 3.0)
      //{
      //   if (dH >= 4.0)
      //   {
      //      if (dH >= 5.0)
      //      {
      //         // 5.0
      //         // magenta to red
      //         dR = 1.0;
      //         dG = 0.0;
      //         dB = 1.0 - dA;
      //      }
      //      else
      //      {
      //         // 4.0
      //         // blue to magenta
      //         dR = dA;
      //         dG = 0.0;
      //         dB = 1.0;
      //      }
      //   }
      //   else
      //   {
      //      // 3.0
      //      // cyan to blue
      //      dR = 0.0;
      //      dG = 1.0 - dA;
      //      dB = 1.0;
      //   }
      //}
      //else /// if(dH >= 0.0)
      //{
      //   if (dH >= 2.0)
      //   {
      //      // 2
      //      // green to cyan
      //      dR = 0.0;
      //      dG = 1.0;
      //      dB = dA;
      //   }
      //   else // (dH >= 0.0 && dH < 2.0)
      //   {
      //      if (dH >= 1.0)
      //      {
      //         // 1
      //         // yellow to green
      //         dR = 1.0 - dA;
      //         dG = 1.0;
      //         dB = 0.0;
      //      }
      //      else // if(dh >= 0 && dH < 1.0);
      //      {
      //         // 0
      //         // red to yellow
      //         dR = 1.0;
      //         dG = dA;
      //         dB = 0.0;
      //      }
      //   }
      //}

      for (::collection::index j = 0; j < h; j++)
      {
         double dL = 1.0 - ((double)j / dh);
//
//#if defined(__APPLE__)
//         dL = 1.0 - dL;
//#endif
//
//         //double dS = 1.0 - ((double)j / dh);
//
//         double dCMin;
//         double dCAdd;
//         double dSL = dS * dL;
//         if (dL >= 0.5)
//         {
//            dCMin = dL - dS + dSL;
//            dCAdd = 2.0 * dS - 2.0 * dSL;
//         }
//         else
//         {
//            dCMin = dL - dSL;
//            dCAdd = 2.0 * dSL;
//         }
//
//
//         double _dR = (dCMin + dR * dCAdd);
//         double _dG = (dCMin + dG * dCAdd);
//         double _dB = (dCMin + dB * dCAdd);


         ::color::hls hls(dH, dL, dS);


         //unsigned char uchR = (unsigned char)primitive_color_round(m_dR * 255.0);
         //m_uchG = (unsigned char)primitive_color_round(m_dG * 255.0);
         //m_uchB = (unsigned char)primitive_color_round(m_dB * 255.0);

         ::color::color color(hls);

         pline = pimage->get_data() + uScan * j;
         image32_t color32(argb(255, color.byte_red(), color.byte_green(), color.byte_blue()), pimage->color_indexes());
         for (::collection::index i = 0; i < w; i++)
         {

            *pline = color32;

            pline++;

         }

      }

   }

} // namespace graphics

namespace core
{
   namespace graphics
   {


      color_selector::color_selector()
      {

         //m_bMouseColorBeam = false;

         m_bCompact = false;

         //m_atomImpact = COLORSEL_IMPACT;

         m_bLButtonPressedOnHue = false;
         m_bLButtonPressedOnLuminance = false;

         //id() = COLORSEL_IMPACT;

         m_strOk = "OK";

      }


      color_selector::~color_selector()
      {


      }


      //void color_selector::assert_ok() const
      //{

      //   ::user::impact::assert_ok();

      //}


      //void color_selector::dump(dump_context & dumpcontext) const
      //{

      //   ::user::impact::dump(dumpcontext);

      //}


      //void color_selector::install_message_routing(::channel * pchannel)
      //{

      //   ::user::impact::install_message_routing(pchannel);

      //   MESSAGE_LINK(e_message_create, pchannel, this, &color_selector::on_message_create);
      //   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &color_selector::on_message_mouse_move);
      //   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &color_selector::on_message_left_button_down);
      //   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &color_selector::on_message_left_button_up);
      //   MESSAGE_LINK(e_message_show_window, pchannel, this, &color_selector::on_message_show_window);

      //   m_pimageTemplate = image()->create_image({ 2048,  2048 });

      //   ::visual::colors_with_shades_of_grey(m_pimageTemplate);

      //   m_pimageLuminance = image()->create_image({ 100,  100 });

      //}


      void color_selector::on_initialize_particle()
      {

         ::particle::on_initialize_particle();

         m_pimageTemplate = image()->create_image({ 2048,  2048 });

         ::graphics::colors_with_shades_of_grey(m_pimageTemplate);

         m_pimageLuminance = image()->create_image({ 100,  100 });

         if (__defer_construct(m_pfontOk))
         {

            m_pfontOk->create_font(e_font_sans_ui, 16_pt, e_font_weight_light);

         }

      }



      //void color_selector::set_sel_color(const ::color::hls & hls)
      //{

      //   color_selector_set_color(hls);

      //}


      //::color::hls color_selector::get_sel_color()
      //{

      //   return color_selector_get_color().get_hls();

      //}


      void color_selector::handle(::topic * ptopic, ::handler_context * pcontext)
      {

         //::user::impact::handle(ptopic, phandlercontext);

      }


      //void color_selector::handle(::topic * ptopic, ::handler_context * pcontext)
      //{

      //   ::user::impact::handle(ptopic, phandlercontext);

      //}


      //void color_selector::on_message_create(::message::message * pmessage)
      //{

      //   //m_pimageBeam->create_image(this, ::int_size(32, 32));

      //   //m_pimageBeam->fill(0);

      //   //auto ppen = __øcreate < ::draw2d::pen > ();

      //   //ppen->create_solid(1.0, argb(255, 255, 255, 255));

      //   //m_pimageBeam->g()->set(ppen);

      //   //m_pimageBeam->g()->DrawEllipse(int_rectangle_dimension(0, 0, 32, 32));



      //   //get_parent_frame()->id() += ".color_sel";

      //   pmessage->previous();

      //   if (get_document()->m_pviewTopic == nullptr)
      //   {

      //      get_document()->m_pviewTopic = this;

      //   }

      //   //set_impact_title("__CoLoR_");

      //   parent_frame()->set_frame_title("__CoLoR_");

      //}


      //void color_selector::on_message_show_window(::message::message * pmessage)
      //{

      //   __UNREFERENCED_PARAMETER(pmessage);
      //   //::pointer<::message::show_window>pshowwindow(pmessage);

      //}


      //::color::color color_selector::color_selector_get_color()
      //{

      //   ::color::color color;

      //   color.set_hls(m_hls);

      //   color.m_uchOpacity = 255;

      //   return color;

      //}


      //void color_selector::color_selector_set_color(const ::color::color & color)
      //{

      //   m_bMouseColorBeam = false;

      //   color.get_hls(m_hls);

      //   //set_need_layout();

      //   //set_need_redraw();

      //}


      bool color_selector::on_mouse_down(const ::int_point & point)
      {
         
         m_bLButtonPressedOnHue = false;
         
         m_bLButtonPressedOnLuminance = false;

         if (point.y() < m_rectangleColors.top())
         {

            return false;

         }

         if (point.y() > m_rectangleColors.bottom())
         {

            return false;

         }

         if (point.x() < m_rectangleColors.left())
         {

            return false;

         }

         int iColorsLeft = m_rectangleColors.left();

         int iColorsWidth = m_pimage->width();

         int iColorsRight = iColorsLeft + iColorsWidth;

         if (point.x() < iColorsRight)
         {

            m_bLButtonPressedOnHue = true;

            on_mouse_motion(point);

            graphics_set_mouse_capture();

            return true;

         }
         else if (point.x() < m_rectangleColors.center().x() + m_rectangleColors.width() / 8)
         {

            m_bLButtonPressedOnLuminance = true;

            on_mouse_motion(point);

            graphics_set_mouse_capture();

            return true;

         }

         return  false;

      }


      bool color_selector::on_mouse_up(const ::int_point & point)
      {

         if (!m_bLButtonPressedOnHue && !m_bLButtonPressedOnLuminance)
         {

            return false;

         }

         m_bLButtonPressedOnHue = false;

         m_bLButtonPressedOnLuminance = false;

         graphics_release_mouse_capture();

         return true;

      }

      bool color_selector::on_mouse_motion(const ::int_point & point)
      {

         if (!m_bLButtonPressedOnHue && !m_bLButtonPressedOnLuminance)
         {

            return false;

         }

         int iColorsLeft = m_rectangleColors.left();

         int iColorsWidth = m_pimage->width();

         int iColorsRight = iColorsLeft + iColorsWidth;

         //if (point.x() < iColorsRight)
         if(m_bLButtonPressedOnHue)
         {

            int x = point.x() - m_rectangleColors.left();

            int y = point.y() - m_rectangleColors.top();

            x = minimum_maximum(x, 0, m_pimage->width());

            y = minimum_maximum(y, 0, m_pimage->height());

            m_pointMouseColorBeam = {m_rectangleColors.left()+ x,
               m_rectangleColors.top()+ y};

            //m_bMouseColorBeam = true;

            ::color::color color;

            ::graphics::color_with_shade_of_grey(color,
               x, y,
               iColorsWidth, m_pimage->height());

            ::color::hls hls(color);

            m_hls.m_dH = hls.m_dH;

            m_hls.m_dS = hls.m_dS;

            rebuild_luminance();

            on_color_change();

         }
         //else if (point.x() < m_rectangleColors.center().x() + m_rectangleColors.width() / 8)
         else if (m_bLButtonPressedOnLuminance)
         {

            auto pointLuminance = point - ::int_size(m_rectangleColors.center().x(), m_rectangleColors.top());

            int y = minimum_maximum(point.y(), 0, m_pimage->height());

            m_hls.m_dL = 1.0 - ((double)y / (double)m_pimage->height());

            on_color_change();

            //if (has_handler())
            //{

            //   auto ptopic = create_topic(::id_after_change_cur_hover);

            //   ptopic->m_puserelement = this;

            //   ptopic->m_actioncontext = ::e_source_user;

            //   route(ptopic);

            //}

            //set_need_redraw();

            //post_redraw();

         }

         return true;

      }


      bool color_selector::is_ok_target(const ::int_point & point)
      {

         return m_strOk.has_character() && m_pfontOk && m_rectangleTarget.contains(point);

      }


      void color_selector::rebuild_luminance()
      {

         if (m_dLastLuminanceH == m_hls.m_dH
            && m_dLastLuminanceS == m_hls.m_dS)
         {

            return;

         }

            m_dLastLuminanceH = m_hls.m_dH;
            m_dLastLuminanceS = m_hls.m_dS;

            ::graphics::shades_of_luminance(m_pimageLuminance, m_hls.m_dH, m_hls.m_dS);

         //}

      }


      void color_selector::draw_beam(::draw2d::graphics_pointer & pgraphics, const ::int_point & pointParam)
      {

         double_point point(pointParam);

         double dSize = 17.0;

         double_size sizeBeam(dSize, dSize);

         double_rectangle rectangleOuter(point.x() - sizeBeam.cx() / 2.0, point.y() - sizeBeam.cy() / 2.0, point.x() + sizeBeam.cx() / 2.0, point.y() + sizeBeam.cy() / 2.0);

         double_rectangle rectangleInner(rectangleOuter);

         rectangleInner.deflate(sizeBeam.cx() / 4.0, sizeBeam.cy() / 4.0);

         auto pbrush = __øcreate < ::draw2d::brush >();

         pbrush->create_solid(argb(255, 0, 0, 0));

         pgraphics->set(pbrush);

         double dHalfTriBase = dSize / 8.0;

         {

            double_point_array pointa;

            pointa.add(double_point(rectangleOuter.left(), point.y() - dHalfTriBase));
            pointa.add(double_point(rectangleInner.left(), point.y()));
            pointa.add(double_point(rectangleOuter.left(), point.y() + dHalfTriBase));

            pgraphics->fill_polygon(pointa);

         }

         {

            double_point_array pointa;

            pointa.add(double_point(point.x() - dHalfTriBase, rectangleOuter.top()));
            pointa.add(double_point(point.x(), rectangleInner.top()));
            pointa.add(double_point(point.x() + dHalfTriBase, rectangleOuter.top()));

            pgraphics->fill_polygon(pointa);

         }

         {

            double_point_array pointa;

            pointa.add(double_point(rectangleOuter.right(), point.y() - dHalfTriBase));
            pointa.add(double_point(rectangleInner.right(), point.y()));
            pointa.add(double_point(rectangleOuter.right(), point.y() + dHalfTriBase));

            pgraphics->fill_polygon(pointa);

         }

         {

            double_point_array pointa;

            pointa.add(double_point(point.x() - dHalfTriBase, rectangleOuter.bottom()));
            pointa.add(double_point(point.x(), rectangleInner.bottom()));
            pointa.add(double_point(point.x() + dHalfTriBase, rectangleOuter.bottom()));

            pgraphics->fill_polygon(pointa);

         }

      }


      void color_selector::draw_level(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleW, int yParam)
      {

         double y = yParam;

         double dSize = 17.0;

         double_rectangle rectangleInner(rectangleW);

         double_rectangle rectangleOuter(rectangleInner);

         rectangleOuter.inflate(dSize / 2.0, dSize / 2.0);

         auto pbrush = __øcreate < ::draw2d::brush >();

         pbrush->create_solid(argb(255, 0, 0, 0));

         pgraphics->set(pbrush);

         double dHalfTriBase = dSize / 8.0;

         {

            double_point_array pointa;

            pointa.add(double_point(rectangleOuter.left(), y - dHalfTriBase));
            pointa.add(double_point(rectangleInner.left(), y));
            pointa.add(double_point(rectangleOuter.left(), y + dHalfTriBase));

            pgraphics->fill_polygon(pointa);

         }

         {

            double_point_array pointa;

            pointa.add(double_point(rectangleOuter.right(), y - dHalfTriBase));
            pointa.add(double_point(rectangleInner.right(), y));
            pointa.add(double_point(rectangleOuter.right(), y + dHalfTriBase));

            pgraphics->fill_polygon(pointa);

         }

      }


      void color_selector::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         ::int_rectangle rC;

         //rC = this->rectangle();

         rC = m_rectangleColors;

         pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         auto & rTarget = m_rectangleTarget;

         rTarget.top_left() = m_rectangleColors.top_left();

         if (!m_pimage)
         {

            return;

         }

         rTarget.set_size(m_pimage->get_size());

         ::int_rectangle rSource = m_pimage->rectangle();

         ::int_rectangle rCursor;

         {

            ::image::image_source imagesource(m_pimage, rSource);

            ::image::image_drawing_options imagedrawingoptions(rTarget);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

         ::int_point point;

         if (m_bLButtonPressedOnHue)
         {

            point = m_pointMouseColorBeam;

         }
         else
         {

            //::color::hsv hsv(m_hls);

            point.x() = (int)(rTarget.left() + rTarget.width() * m_hls.m_dH);

            point.y() = (int)(rTarget.top() + rTarget.height() * (1.0-m_hls.m_dS));

         }

         draw_beam(pgraphics, point);

         ::int_rectangle rectangleLum1;

         rectangleLum1.top_left() = m_rectangleColors.top_left() + ::int_size(m_pimage->width() - 1, 0);

         rectangleLum1.set_size(m_pimageLuminance->get_size());

         rSource = m_pimageLuminance->rectangle();

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         {

            ::image::image_source imagesource(m_pimageLuminance);

            ::image::image_drawing_options imagedrawingoptions(rectangleLum1);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

         rTarget.top_left() = m_rectangleColors.top_left() + ::int_size(m_pimage->width() - 1 + m_pimageLuminance->get_size().cx() - 1, 0);

         rTarget.set_size(m_rectangleColors.right() - rTarget.left(), m_pimage->height());

         pgraphics->fill_rectangle(rTarget, get_sel_color());

         int y = (int)(rectangleLum1.top() + (1.0 - m_hls.m_dL) * rectangleLum1.height());

         draw_level(pgraphics, rectangleLum1, y);

         if (m_strOk.has_character() && m_pfontOk)
         {

            pgraphics->set(m_pfontOk);

            if (m_hls.m_dL >= 0.5)
            {

               pgraphics->set_text_color(argb(255, 0, 0, 0));

            }
            else
            {

               pgraphics->set_text_color(argb(255, 255, 255, 255));

            }

            pgraphics->draw_text(m_strOk, rTarget, e_align_center);

         }

      }


      //void color_selector::on_message_left_button_down(::message::message * pmessage)
      //{

      //   auto pmouse = pmessage->m_union.m_pmouse;

      //   ::int_point point = pmouse->m_pointHost;

      //   host_to_client()(point);

      //   on_mouse(point);

      //   pmouse->m_bRet = true;

      //   set_mouse_capture();

      //   m_bLButtonPressed = true;

      //}


      //void color_selector::on_message_left_button_up(::message::message * pmessage)
      //{

      //   auto pmouse = pmessage->m_union.m_pmouse;

      //   ::int_point point = pmouse->m_pointHost;

      //   host_to_client()(point);

      //   on_mouse(point);

      //   pmouse->m_bRet = true;

      //   defer_release_mouse_capture();

      //   m_bLButtonPressed = false;

      //   if (has_handler())
      //   {

      //      auto ptopic = create_topic(::id_after_change_cur_sel);

      //      ptopic->m_puserelement = this;

      //      ptopic->m_actioncontext = ::e_source_user;

      //      route(ptopic);

      //   }

      //}


      //void color_selector::on_message_mouse_move(::message::message * pmessage)
      //{

      //   auto pmouse = pmessage->m_union.m_pmouse;

      //   if (m_bLButtonPressed)
      //   {

      //      ::int_point point = pmouse->m_pointHost;

      //      host_to_client()(point);

      //      on_mouse(point);

      //      pmouse->m_bRet = true;

      //   }

      //}

      void color_selector::on_color_change()
      {

         ::color::hsv hsv(m_hls);

         int x = (int) (hsv.m_dH * m_pimage->width());

         int y = (int) (hsv.m_dS * m_pimage->height());

         if (m_callbackHls)
         {

            m_callbackHls(m_hls, false);

         }

         rebuild_luminance();


      }


      void color_selector::layout_color_selector(const ::int_rectangle & rectangle)
      {

         //   ::user::impact::on_layout(pgraphics);

         //   auto rectangleX = this->rectangle();

         if (rectangle.is_empty())
         {

            return;

         }

         information() << "rectangle : " << rectangle;

         ::int_rectangle rectangleColors;

         rectangleColors = rectangle;

         if (!m_bCompact)
         {

            rectangleColors.left() = rectangle.center().x();
            rectangleColors.bottom() = rectangle.center().y();

            rectangleColors.deflate(rectangle.width() / 16, rectangle.height() / 16);

         }

         information() << "rectangleColors : " << rectangleColors;

         m_rectangleColors = rectangleColors;

         __defer_construct(m_pimage);

         auto sizeImage = ::int_size(m_rectangleColors.width() / 2, m_rectangleColors.height());

         if (sizeImage.is_empty())
         {

            return;

         }

         m_pimage->create(sizeImage);

         {

            ::image::image_source imagesource(m_pimageTemplate);

            ::image::image_drawing_options imagedrawingoptions(m_pimage->rectangle());

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            m_pimage->g()->draw(imagedrawing);

         }

         m_pimageLuminance = image()->create_image({ m_rectangleColors.width() / 8,  m_rectangleColors.height() });

         rebuild_luminance();

      }


   } // namespace graphics


} // namespace core





