#include "framework.h"
#include "core/user/userex/_userex.h"
#include "aura/update.h"
#include "core/user/userex/_userex.h"
#include "aura/os/windows_common/graphics.h"


//#if defined(APPLEOS)
//#define ARGB_COLORREF(A, R, G, B) argb(A, R, G, B)
//#define COLORREF_get_a_value(cr) colorref_get_a_value(cr)
//#define COLORREF_get_r_value(cr) colorref_get_r_value(cr)
//#define COLORREF_get_g_value(cr) colorref_get_g_value(cr)
//#define COLORREF_get_b_value(cr) colorref_get_b_value(cr)
//#else
//#define ARGB_COLORREF(A, R, G, B) argb(A, B, G, R)
//#define COLORREF_get_a_value(cr) colorref_get_a_value(cr)
//#define COLORREF_get_r_value(cr) colorref_get_b_value(cr)
//#define COLORREF_get_g_value(cr) colorref_get_g_value(cr)
//#define COLORREF_get_b_value(cr) colorref_get_r_value(cr)
//#endif


namespace flag
{


   void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h)
   {

      color32_t crDenmarkRoed = argb(255, 200, 16, 46);

      double dx = w / 90.0;

      double dy = h / 70.0;

      pgraphics->fill_rectangle(::rectd_dim(x + 0, y + 0, 90.0 * dx, 70.0 * dy), argb(255, 255, 255, 255));

      pgraphics->fill_rectangle(::rectd_dim(x + 0, y + 0, 30.0 * dx, 30.0 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectd_dim(x + 40.0 * dx, y, 50 * dx, 30 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectd_dim(x + 0, y + 40.0 * dy, 30.0 * dx, 30.0 * dy), crDenmarkRoed);

      pgraphics->fill_rectangle(::rectd_dim(x + 40.0 * dx, y + 40.0 * dy, 50.0 * dx, 30.0 * dy), crDenmarkRoed);

   }

}


namespace visual
{


   color32_t image_color_with_shade_of_grey(int i, int j, double dw, double dh)
   {

      double dR, dG, dB;

      double dH = (double)i / (double)dw;

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

      double dS = 1.0 - ((double)j / dh);
#if defined(APPLEOS)
      dS = 1.0 - dS;
#endif

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

      return IMAGE_ARGB(255, byte(_dR * 255.0), byte(_dG * 255.0), byte(_dB * 255.0));

   }

   color32_t color_with_shade_of_grey(int i, int j, double dw, double dh)
   {

      auto cr = image_color_with_shade_of_grey(i, j, dw, dh);

      int a = image_a_value(cr);

      int r = image_r_value(cr);

      int g = image_g_value(cr);

      int b = image_b_value(cr);

      cr = argb(a, r, g, b);

      return cr;

   }


   void colors_with_shades_of_grey(::image * pimage)
   {

      pimage->map();

      ::count w = pimage->width();

      ::count h = pimage->height();

      double dw = (double) w;

      double dh = (double) h;

      ::u32 uScan;

      uScan = pimage->scan_size() / sizeof(color32_t);

      color32_t * pline;

      for (index i = 0; i < w; i++)
      {

         pline = pimage->get_data() + i;

         for (index j = 0; j < h; j++)
         {

            *pline = image_color_with_shade_of_grey((int) i, (int) j, dw, dh);

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

      double dh = (double) h;

      ::u32 uScan;


      //dS = 1.0 - ((double)j / dh);

      uScan = pimage->scan_size() / sizeof(color32_t);

      color32_t * pline;

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

#if defined(APPLEOS)
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
         color32_t cr = IMAGE_ARGB(255, byte(_dR*255.0), byte(_dG*255.0), byte(_dB*255.0));
         for (index i = 0; i < w; i++)
         {

            *pline = cr;

            pline ++;

         }

      }

   }

}


namespace userex
{


   color_view::color_view()
   {

      m_bMouseColorBeam = false;

      m_bCompact = false;

      m_idView = COLORSEL_IMPACT;

      m_bLButtonPressed = false;

   }


   color_view::~color_view()
   {


   }


   void color_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void color_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void color_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &color_view::on_message_create);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &color_view::_001OnMouseMove);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &color_view::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &color_view::on_message_left_button_up);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &color_view::_001OnShowWindow);

      m_pimageTemplate = create_image({2048,  2048});

      ::visual::colors_with_shades_of_grey(m_pimageTemplate);

      m_pimageLuminance = create_image({100,  100});

   }


   void color_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   void color_view::on_control_event(::user::control_event * pevent)
   {

      ::user::impact::on_control_event(pevent);

   }


   void color_view::on_message_create(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //::draw2d::pen_pointer pen(e_create);

      //pen->create_solid(1.0, argb(255, 255, 255, 255));

      //m_pimageBeam->g()->set(pen);

      //m_pimageBeam->g()->DrawEllipse(rect_dim(0, 0, 32, 32));



      //get_parent_frame()->m_id += ".color_sel";

      pmessage->previous();

      if(get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = this;

      }

      //set_impact_title("__CoLoR_");

      get_parent_frame()->set_frame_title("__CoLoR_");

   }


   void color_view::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::show_window) pshowwindow(pmessage);

   }


   ::color::color color_view::get_color()
   {

      ::color::color color;

      color.set_hls(m_hls);

      color.alpha = 255;

      return color.get_rgba();

   }


   void color_view::set_color(::color::color color)
   {

      m_bMouseColorBeam = false;

      color.get_hls(m_hls);

      set_need_layout();

      set_need_redraw();

   }


   void color_view::on_mouse(const ::point_i32 & point)
   {

      if (point.y >= m_rectColors.bottom)
      {

         return;

      }

      if (point.x < m_rectColors.left)
      {

         return;

      }

      if (point.y < m_rectColors.top)
      {

         return;

      }

      int iColorsLeft = m_rectColors.left;

      int iColorsWidth = m_pimage->width();

      int iColorsRight = iColorsLeft + iColorsWidth;

      if (point.x < iColorsRight)
      {

         int x = point.x - iColorsLeft;

         int y = point.y - m_rectColors.top;

         m_pointMouseColorBeam = point;

         m_bMouseColorBeam = true;

         color32_t cr = visual::color_with_shade_of_grey(
            x, y,
            iColorsWidth, m_rectColors.height());

         ::color::color color(cr);

         ::color::hls hls;

         color.get_hls(hls);

         m_hls.m_dH = hls.m_dH;

         m_hls.m_dS = hls.m_dS;

         rebuild_luminance();

         ::user::control_event ev;

         ev.m_eevent = ::user::e_event_after_change_cur_hover;

         ev.m_id = m_idView;

         ev.m_puie = this;

         ev.m_actioncontext = ::e_source_user;

         route_control_event(&ev);

         set_need_redraw();

         post_redraw();

      }
      else if (point.x < m_rectColors.center().x + m_rectColors.width() / 8)
      {

         auto pointLuminance = point - ::size_i32(m_rectColors.center().x, m_rectColors.top);

         m_hls.m_dL = 1.0 - ((double)pointLuminance.y / (double) m_pimage->height());

         ::user::control_event ev;

         ev.m_eevent = ::user::e_event_after_change_cur_hover;

         ev.m_id = m_idView;

         ev.m_puie = this;

         ev.m_actioncontext = ::e_source_user;

         route_control_event(&ev);

         set_need_redraw();

         post_redraw();

      }

   }


   void color_view::rebuild_luminance()
   {

      ::draw2d::device_lock devicelock(this);

      ::visual::shades_of_luminance(m_pimageLuminance, m_hls.m_dH, m_hls.m_dS);

   }


   void color_view::draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & pointParam)
   {

      point_f64 point(pointParam);

      double dSize = 17.0;

      size_f64 sizeBeam(dSize,dSize);

      rectangle_f64 rectOuter(point.x - sizeBeam.cx / 2.0, point.y - sizeBeam.cy / 2.0, point.x + sizeBeam.cx / 2.0, point.y + sizeBeam.cy / 2.0);

      rectangle_f64 rectInner(rectOuter);

      rectInner.deflate(sizeBeam.cx / 4.0, sizeBeam.cy / 4.0);

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(argb(255, 0, 0, 0));

      pgraphics->set(br);

      double dHalfTriBase = dSize / 8.0;

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectOuter.left, point.y - dHalfTriBase));
         pointa.add(point_f64(rectInner.left, point.y));
         pointa.add(point_f64(rectOuter.left, point.y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(point.x - dHalfTriBase, rectOuter.top));
         pointa.add(point_f64(point.x, rectInner.top));
         pointa.add(point_f64(point.x + dHalfTriBase, rectOuter.top));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectOuter.right, point.y - dHalfTriBase));
         pointa.add(point_f64(rectInner.right, point.y));
         pointa.add(point_f64(rectOuter.right, point.y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(point.x - dHalfTriBase, rectOuter.bottom));
         pointa.add(point_f64(point.x, rectInner.bottom));
         pointa.add(point_f64(point.x + dHalfTriBase, rectOuter.bottom));

         pgraphics->fill_polygon(pointa);

      }

   }


   void color_view::draw_level(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectW, int yParam)
   {

      double y = yParam;

      double dSize = 17.0;

      rectangle_f64 rectInner(rectW);

      rectangle_f64 rectOuter(rectInner);

      rectOuter.inflate(dSize / 2.0, dSize / 2.0);

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(argb(255, 0, 0, 0));

      pgraphics->set(br);

      double dHalfTriBase = dSize / 8.0;

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectOuter.left, y - dHalfTriBase));
         pointa.add(point_f64(rectInner.left, y));
         pointa.add(point_f64(rectOuter.left, y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

      {

         point_f64_array pointa;

         pointa.add(point_f64(rectOuter.right, y - dHalfTriBase));
         pointa.add(point_f64(rectInner.right, y));
         pointa.add(point_f64(rectOuter.right, y + dHalfTriBase));

         pgraphics->fill_polygon(pointa);

      }

   }


   void color_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rC;

      get_client_rect(rC);

      pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      ::rectangle_i32 r1;

      r1.top_left() = m_rectColors.top_left();

      if (!m_pimage)
      {

         return;

      }

      r1.set_size(m_pimage->get_size());

      ::rectangle_i32 r2 = m_pimage->rectangle();

      ::rectangle_i32 rCursor;

      pgraphics->stretch(r1, m_pimage, r2);

      ::point_i32 point;

      if (m_bMouseColorBeam)
      {

         point = m_pointMouseColorBeam;

      }
      else
      {

         point.x = (::i32)(r1.left + r1.width() * m_hls.m_dH);

         point.y = (::i32)(r1.top + r1.height() * (1.0 - m_hls.m_dS));

      }

      draw_beam(pgraphics, point);

      ::rectangle_i32 rectLum1;

      rectLum1.top_left() = m_rectColors.top_left() + ::size_i32(m_pimage->width()-1, 0);

      rectLum1.set_size(m_pimageLuminance->get_size());

      r2 = m_pimageLuminance->rectangle();

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->stretch(rectLum1, m_pimageLuminance->g(), r2);

      r1.top_left() = m_rectColors.top_left() + ::size_i32(m_pimage->width() - 1 + m_pimageLuminance->get_size().cx - 1, 0);

      r1.set_size(m_rectColors.right - r1.left, m_pimage->height());

      pgraphics->fill_rectangle(r1, get_color());

      int y = (int) (rectLum1.top + (1.0 - m_hls.m_dL)  * rectLum1.height());

      draw_level(pgraphics, rectLum1, y);

   }


   void color_view::on_message_left_button_down(::message::message * pmessage)
   {
      
      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      _001ScreenToClient(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      set_mouse_capture();

      m_bLButtonPressed = true;

   }


   void color_view::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);
      
      ::point_i32 point = pmouse->m_point;
      
      _001ScreenToClient(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      m_bLButtonPressed = false;

      ::user::control_event ev;

      ev.m_eevent = ::user::e_event_after_change_cur_sel;

      ev.m_id = m_idView;

      ev.m_puie = this;

      ev.m_actioncontext = ::e_source_user;

      route_control_event(&ev);

   }


   void color_view::_001OnMouseMove(::message::message * pmessage)
   {
      
      __pointer(::message::mouse) pmouse(pmessage);

      if (m_bLButtonPressed)
      {

         ::point_i32 point = pmouse->m_point;

         _001ScreenToClient(point);

         on_mouse(point);

         pmouse->m_bRet = true;

      }

   }


   void color_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::on_layout(pgraphics);

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      ::rectangle_i32 rectColors;

      get_client_rect(rectColors);

      if(!m_bCompact)
      {

         rectColors.left = rectClient.center().x;
         rectColors.bottom = rectClient.center().y;

         rectColors.deflate(rectClient.width() / 16, rectClient.height() / 16);

      }

      m_rectColors = rectColors;

      m_pimage = create_image({m_rectColors.width() / 2,  m_rectColors.height()});

      m_pimage->g()->stretch(m_pimage->rectangle(), m_pimageTemplate->get_graphics(), m_pimageTemplate->rectangle());

      m_pimageLuminance = create_image({m_rectColors.width() / 8,  m_rectColors.height()});

      rebuild_luminance();

   }


} // namespace userex



