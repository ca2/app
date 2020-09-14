#include "framework.h"
#include <math.h>

#define SHOW_FPS 1

namespace browser
{


   impact_base::impact_base(::layered * pobjectContext):
      object(pobject),

      m_fontDrawStatus(e_create)
   {

      m_prender = nullptr;

      m_fontDrawStatus->create_pixel_font("Arial", 20, 400);

      m_crDrawStatus = ARGB(255, 255, 255, 0);

      m_eeffect                  = effect_none;

      m_dFps                     = 0.0;

      m_ppcre = System.create_pcre("\\:\\-\\)");

   }

   impact_base::~impact_base()
   {
   }

   void impact_base::assert_valid() const
   {
      user::box::assert_valid();
   }

   void impact_base::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void impact_base::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &impact_base::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &impact_base::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &impact_base::_001OnLButtonDown);

   }


   void impact_base::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

      var v;

      data_get("cur_fps", v);

      m_dFps = v.get_double();
auto m_tickRoll = ::tick::now();

   }


   void impact_base::_001OnDestroy(::message::message * pmessage)
   {

   }


   void impact_base::_001OnLButtonDown(::message::message * pmessage)
   {

      if(Application.m_ppaneview != nullptr)
      {

         Application.m_ppaneview->m_pviewLast = this;

      }

   }


   void impact_base::defer_check_on_draw_layout()
   {

   }


   void impact_base::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnNcDraw(pgraphicsParam);

   }

   void impact_base::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //u64 startTime = get_nanos();

      defer_check_on_draw_layout();

      ::rect rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() <= 0)
         return;

/*      m_pimagePost->create_image({this,  rectClient->size()});

      if (m_pimagePost)
      {

         m_pimagePost->fill(0);

      }

      bool bDraw = true;

      if (bDraw)
      {


         on_draw_image_layer(pgraphicsParam);

         if (m_pimagePost)
         {

            _006OnDraw(m_pimagePost->g());

         }

      }


/*      m_pimageTime->create_image({this,  m_pimagePost->get_size()});

      if (m_pimageTime)
      {

         m_pimageTime->fill(0);


         int xOffset;

         xOffset = int(m_pimageTime->width() * m_dFps * __double(m_tickRoll->elapsed()) / 1000->0); // x = v->t; f=fps  1920 * 1FPS * t

         xOffset %= m_pimageTime->width();

         if (xOffset < 0)
         {

            xOffset += m_pimageTime->width();

         }

         m_pimageTime->from(point(xOffset, 0), m_pimagePost, ::point(), ::size(m_pimagePost->width() - xOffset, m_pimagePost->height()));
         m_pimageTime->from(::point(), m_pimagePost, point(m_pimagePost->width() - xOffset, 0), ::size(xOffset, m_pimagePost->height()));

         //m_pimagePost->from(m_pimageTime);
         _001OnPostProcess(m_pimageTime->get_graphics());


         ::draw2d::graphics * pdcParam = pgraphicsParam;

         pdcParam->set_alpha_mode(::draw2d::alpha_mode_blend);

         //      m_pimagePost->get_graphics()->FillSolidRect(110,110,100,100,ARGB(184,177,184,60));


         /*  m_dwaFrame.add(::get_tick());

         for (index i = 0; i < m_dwaFrame.get_size();)
         {

            if (m_tickaFrame[i].elapsed() > 1000)
            {
               m_dwaFrame.remove_at(i);
            }
            else
            {
               i++;
            }

         }

         pdcParam->set_text_color(ARGB(255, 255, 255, 0));

         ::draw2d::font_pointer f(e_create);

         f->create_point_font("Arial", 20, 800);

         pdcParam->set_font(f);

         pdcParam->TextOutA(0, 0, __str(m_dwaFrame.get_size()));*/


         ::size size = m_pimageTime->get_size();

         ::draw2d::graphics_pointer & pgraphics = m_pimageTime->get_graphics();

         pdcParam->from(size, pgraphics, SRCCOPY);

      }


      //pdcScreen->FillSolidRect(10,10,100,100,ARGB(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,ARGB(255,0,255,0),ARGB(255,0,0,255));
      //u64 endTime = get_nanos();

      //u64 micros = (endTime - startTime) / 1000;

      //char sz[512];

      //::output_debug_string("view:");
      //::ansi_from_u64(sz, micros, 10);
      //::output_debug_string(sz);
      //::output_debug_string(", ");

      //image d(e_create);

      //d->create(rectClient.size());

      //d->get_graphics()->BitBlt(rectClient, pimage->g());

      //d.save_to_file(::dir::system() / "obs.png");


      //pdcParam->set_font(m_fontDrawStatus);

      //pdcParam->set_text_color(m_crDrawStatus);

      //string str1;
      //str1 = "FPS: " + __str((int) get_wnd()->m_pimpl.cast<::user::interaction_impl>()->m_dUpdateScreenFps);
      //m_yDrawStatus = 10;
      //pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //m_yDrawStatus += m_fontDrawStatus->m_dFontSize;
      //if (m_prender != nullptr)
      //{
      //
      //   str1 = "Render FPS: " + __str((int) m_prender->m_dRenderFps);
      //   pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //   m_yDrawStatus += m_fontDrawStatus->m_dFontSize;
      //}

#if SHOW_FPS

      m_yDrawStatus = 10;

      string str;
      str.Format("Window FPS: %0.1d", get_output_fps());
      pgraphicsParam->selectFont(m_fontDrawStatus);
      pgraphicsParam->text_out(10, m_yDrawStatus, str);
      m_yDrawStatus += m_fontDrawStatus->m_dFontSize;

      if (m_prender != nullptr)
      {
         string str;
         str.Format("Hello Browser FPS: %0.1d", m_prender->get_fps());
         pgraphicsParam->selectFont(m_fontDrawStatus);
         pgraphicsParam->text_out(10, m_yDrawStatus, str);
         m_yDrawStatus += m_fontDrawStatus->m_dFontSize;
      }
#endif



   }

   void impact_base::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {


   }

   void impact_base::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }

   void impact_base::_001OnPostProcess(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_eeffect == effect_crt)
      {
         int iFactor = 2;
         int iMult = 1 << iFactor;

         ::rect rectClient;

         get_client_rect(rectClient);

         ::size size = rectClient.size();

         ::size size2(size.cx / iMult, size.cy / iMult);

/*         m_pimage1->create_image({this,  size2});

         m_pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_pimage1->get_graphics()->StretchBlt(0, 0, size2.cx, size2->cy, pgraphics, 0, 0, size->cx, size->cy, SRCCOPY);

         //if (0)
         {

            if (pgraphics->m_pimageimplDraw2dGraphics->is_set())
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

               pgraphics->StretchBlt(0, 0, size.cx, size.cy, m_pimage1->get_graphics(), 0, 0, size2->cx, size2->cy, SRCCOPY);

            }
            else
            {

/*               m_pimage2->create_image({this,  size});

               m_pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               m_pimage2->get_graphics()->StretchBlt(0, 0, size.cx, size.cy, m_pimage1->get_graphics(), 0, 0, size2->cx, size2->cy, SRCCOPY);

            }


            COLORREF cr;

            byte a, r, g, b, rm, gm, bm;

/*            ::image_pointer pimage = pgraphics->m_pimageimplDraw2dGraphics;

/*            if (pimage->is_null())
            {

/*               pimage = m_pimage2;

            }

/*            pimage->map();

            int h = (size.cy / 3) * 3;

            int w = (size.cx / 3) * 3;

/*            int rstride = pimage->scan_size() / sizeof(COLORREF);

/*            COLORREF * pdata = pimage->get_data();

            int i1;
            int i2;
            int i3;
            COLORREF cr1;
            COLORREF cr2;
            COLORREF cr3;

            for (int i = 0; i < h; i += 3)
            {
               for (int j = 0; j < w; j += 3)
               {
                  i1 = i * rstride + j;
                  i2 = i1 + rstride;
                  i3 = i2 + rstride;
                  cr = pdata[i1];
                  a = image_a_value(cr);
                  r = image_r_value(cr);
                  g = image_g_value(cr);
                  b = image_b_value(cr);
                  rm = (g + b) / 4;
                  gm = (r + b) / 4;
                  bm = (r + g) / 4;

                  cr1 = IMAGE_ARGB(a, gm, g, gm);
                  cr2 = IMAGE_ARGB(a, bm, bm, b);
                  cr3 = IMAGE_ARGB(a, r, rm, rm);
                  pdata[i1] = cr3;
                  pdata[i1 + 1] = cr1;
                  pdata[i1 + 2] = cr2;
                  pdata[i2] = cr3;
                  pdata[i2 + 1] = cr1;
                  pdata[i2 + 2] = cr2;
                  pdata[i3] = cr3;
                  pdata[i3 + 1] = cr1;
                  pdata[i3 + 2] = cr2;

               }

            }

            if (pgraphics->m_pimageimplDraw2dGraphics->is_null())
            {

               pgraphics->BitBlt(0, 0, size.cx, size.cy, m_pimage2->get_graphics(), 0, 0, SRCCOPY);

            }
            else
            {

/*               pimage->unmap();

            }

            ::draw2d::pen_pointer pen(e_create);

            pen->create_solid(0.5, ARGB(84, 0, 0, 0));

            pgraphics->SelectObject(pen);

            for (int i = 0; i < size.cy; i += 3)
            {

               pgraphics->draw_line(0, i, size.cx, i);

            }

         }

      }

   }


} // namespace browser



