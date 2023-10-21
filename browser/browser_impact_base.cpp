#include "framework.h"
#include <math.h>

#define SHOW_FPS 1

namespace browser
{


   impact_base::impact_base(::particle * pparticle):
      object(pparticle),

      m_pfontDrawStatus(e_create)
   {

      m_prender = nullptr;

      m_pfontDrawStatus->create_pixel_font("Arial", 20, 400);

      m_colorDrawStatus = argb(255, 255, 255, 0);

      m_eeffect                  = effect_none;

      m_frequencyFramesPerSecond                     = 0.0;

      m_ppcre = psystem->compile_pcre("\\:\\-\\)");

   }

   impact_base::~impact_base()
   {
   }

   void impact_base::assert_ok() const
   {
      user::box::assert_ok();
   }

   void impact_base::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void impact_base::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &impact_base::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &impact_base::on_message_destroy);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &impact_base::on_message_left_button_down);

   }


   void impact_base::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      ::payload v;

      datastream()->get("cur_per_second", v);

      m_frequencyFramesPerSecond = v.get_double();
auto m_timeRoll = ::time::now();

   }


   void impact_base::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact_base::on_message_left_button_down(::message::message * pmessage)
   {

      if(papp->m_ppaneimpact != nullptr)
      {

         papp->m_ppaneimpact->m_pimpactLast = this;

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

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
         return;

/*      m_pimagePost->create_image({this,  rectangleX->size()});

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

         xOffset = int(m_pimageTime->width() * m_frequencyFramesPerSecond * __double(m_timeRoll->elapsed()) / 1000->0); // x = v->t; f=fps  1920 * 1FPS * t

         xOffset %= m_pimageTime->width();

         if (xOffset < 0)
         {

            xOffset += m_pimageTime->width();

         }

         m_pimageTime->from(point_i32(xOffset, 0), m_pimagePost, ::point_i32(), ::size_i32(m_pimagePost->width() - xOffset, m_pimagePost->height()));
         m_pimageTime->from(::point_i32(), m_pimagePost, point_i32(m_pimagePost->width() - xOffset, 0), ::size_i32(xOffset, m_pimagePost->height()));

         //m_pimagePost->from(m_pimageTime);
         _001OnPostProcess(m_pimageTime->get_graphics());


         ::draw2d::graphics * pdcParam = pgraphicsParam;

         pdcParam->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //      m_pimagePost->get_graphics()->FillSolidRect(110,110,100,100,argb(184,177,184,60));


         /*  m_dwaFrame.add(::get_tick());

         for (index i = 0; i < m_dwaFrame.get_size();)
         {

            if (m_tickaFrame[i].elapsed() > 1000)
            {
               m_dwaFrame.erase_at(i);
            }
            else
            {
               i++;
            }

         }

         pdcParam->set_text_color(argb(255, 255, 255, 0));

         ::write_text::font_pointer f(e_create);

         f->create_point_font("Arial", 20, 800);

         pdcParam->set_font(f);

         pdcParam->TextOutA(0, 0, as_string(m_dwaFrame.get_size()));*/


         ::size_i32 size = m_pimageTime->get_size();

         ::draw2d::graphics_pointer & pgraphics = m_pimageTime->get_graphics();

         pdcParam->from(size, pgraphics);

      }


      //pdcScreen->FillSolidRect(10,10,100,100,argb(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,argb(255,0,255,0),argb(255,0,0,255));
      //u64 endTime = get_nanos();

      //u64 microsecond = (endTime - startTime) / 1000;

      //char sz[512];

      //::informationf("impact:");
      //::ansi_from_u64(sz, microsecond, 10);
      //::information(sz);
      //::informationf(", ");

      //image d(e_create);

      //d->create(rectangleX.size());

      //d->get_graphics()->BitBlt(rectangleX, pimage->g());

      //d.save_to_file(         auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "obs.png");


      //pdcParam->set_font(m_pfontDrawStatus);

      //pdcParam->set_text_color(m_colorDrawStatus);

      //string str1;
      //str1 = "FPS: " + as_string((int) get_wnd()->m_pimpl.cast<::user::interaction_impl>()->m_dUpdateScreenFps);
      //m_yDrawStatus = 10;
      //pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //m_yDrawStatus += m_pfontDrawStatus->m_dFontSize;
      //if (m_prender != nullptr)
      //{
      //
      //   str1 = "Render FPS: " + as_string((int) m_prender->m_dRenderFps);
      //   pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //   m_yDrawStatus += m_pfontDrawStatus->m_dFontSize;
      //}

#if SHOW_FPS

      m_yDrawStatus = 10;

      string str;
      str.format("Window FPS: %0.1d", get_output_per_second());
      pgraphicsParam->selectFont(m_pfontDrawStatus);
      pgraphicsParam->text_out(10, m_yDrawStatus, str);
      m_yDrawStatus += m_pfontDrawStatus->m_dFontSize;

      if (m_prender != nullptr)
      {
         string str;
         str.format("Hello Browser FPS: %0.1d", m_prender->get_frames_per_second());
         pgraphicsParam->selectFont(m_pfontDrawStatus);
         pgraphicsParam->text_out(10, m_yDrawStatus, str);
         m_yDrawStatus += m_pfontDrawStatus->m_dFontSize;
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

         auto rectangleX = this->rectangle();

         ::size_i32 size = rectangleX.size();

         ::size_i32 size2(size.cx() / iMult, size.cy() / iMult);

/*         m_pimage1->create_image({this,  size2});

         m_pimage1->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         m_pimage1->get_graphics()->StretchBlt(0, 0, size2.cx(), size2->cy(), pgraphics, 0, 0, size_i32->cx(), size_i32->cy());

         //if (0)
         {

            if (pgraphics->m_pimage->is_set())
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

               pgraphics->StretchBlt(0, 0, size.cx(), size.cy(), m_pimage1->get_graphics(), 0, 0, size2->cx(), size2->cy());

            }
            else
            {

/*               m_pimage2->create_image({this,  size_i32});

               m_pimage2->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

               m_pimage2->get_graphics()->StretchBlt(0, 0, size.cx(), size.cy(), m_pimage1->get_graphics(), 0, 0, size2->cx(), size2->cy());

            }


            color32_t color32;

            ::u8 a, r, g, b, rm, gm, bm;

/*            ::image_pointer pimage = pgraphics->m_pimage;

/*            if (pimage->is_null())
            {

/*               pimage = m_pimage2;

            }

/*            pimage->map();

            int h = (size.cy() / 3) * 3;

            int w = (size.cx() / 3) * 3;

/*            int rstride = pimage->scan_size() / sizeof(color32_t);

/*            color32_t * pdata = pimage->get_data();

            int i1;
            int i2;
            int i3;
            color32_t cr1;
            color32_t cr2;
            color32_t cr3;

            for (int i = 0; i < h; i += 3)
            {
               for (int j = 0; j < w; j += 3)
               {
                  i1 = i * rstride + j;
                  i2 = i1 + rstride;
                  i3 = i2 + rstride;
                  color32 = pdata[i1];
                  a = image_a_value(color32);
                  r = image_r_value(color32);
                  g = image_g_value(color32);
                  b = image_b_value(color32);
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

            if (pgraphics->m_pimage->is_null())
            {

               pgraphics->BitBlt(0, 0, size.cx(), size.cy(), m_pimage2->get_graphics(), 0, 0);

            }
            else
            {

/*               pimage->unmap();

            }

            auto ppen = __create < ::draw2d::pen > ();

            ppen->create_solid(0.5, argb(84, 0, 0, 0));

            pgraphics->SelectObject(pen);

            for (int i = 0; i < size.cy(); i += 3)
            {

               pgraphics->draw_line(0, i, size.cx(), i);

            }

         }

      }

   }


} // namespace browser



