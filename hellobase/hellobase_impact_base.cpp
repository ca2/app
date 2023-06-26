#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace hellobase
{



   impact_base::impact_base(::particle * pparticle):
      object(pparticle),
      m_pimagePost,
      m_pimageTime,
      m_pimage1,
      m_pimage2,
      
      m_pfontDrawStatus(e_create)
   {
      m_prender = nullptr;
      m_pfontDrawStatus->create_pixel_font("Arial", 20, 400);
      m_colorDrawStatus = argb(255, 255, 255, 0);



      m_eeffect                  = effect_none;

      m_frequencyFramesPerSecond                     = 0.0;

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

      ::parallelization::post_quit_and_wait(m_prender, seconds(15));


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

      auto rectangleClient = client_rectangle();

      if (rectangleClient.area() <= 0)
         return;

/*      m_pimagePost = create_image(rectangleClient->size());

      m_pimagePost->Fill(00, 00, 00, 00);

      bool bDraw = true;

      if (bDraw)
      {


         on_draw_image_layer(pgraphicsParam);

/*         ::image_pointer pimage = m_pimagePost;

/*         _006OnDraw(pimage->g());

      }


/*      m_pimageTime = create_image(m_pimagePost->get_size());

      m_pimageTime->Fill(0, 0, 0, 0);


      int xOffset;

      xOffset = int (m_pimageTime->width() * m_frequencyFramesPerSecond * (double)(m_timeRoll->elapsed()) / 1000->0); // x = v->t; f=fps  1920 * 1FPS * t

      xOffset %= m_pimageTime->width();

      if (xOffset < 0)
      {

         xOffset += m_pimageTime->width();

      }

      m_pimageTime->from(point_i32(xOffset, 0), m_pimagePost, ::point_i32(), ::size_i32(m_pimagePost->width() - xOffset, m_pimagePost->height()));
      m_pimageTime->from(::point_i32(), m_pimagePost, point_i32(m_pimagePost->width() - xOffset, 0), size_i32(xOffset, m_pimagePost->height()));

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


      size_i32 s = m_pimageTime->get_size();

      ::draw2d::graphics_pointer & pgraphics = m_pimageTime->get_graphics();

      pdcParam->from(s, pgraphics);

      //pdcScreen->FillSolidRect(10,10,100,100,argb(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,argb(255,0,255,0),argb(255,0,0,255));
      //u64 endTime = get_nanos();

      //u64 microsecond = (endTime - startTime) / 1000;

      //char sz[512];

      //::infomration("impact:");
      //::ansi_from_u64(sz, microsecond, 10);
      //::infomration(sz);
      //::infomration(", ");

      //image d(e_create);

      //d->create(rectangleClient.size());

      //d->get_graphics()->BitBlt(rectangleClient, pimage->g());

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

         auto rectangleClient = client_rectangle();

         size_i32 s = rectangleClient.size();

         size_i32 s2(s.cx() / iMult, s.cy() / iMult);

/*         m_pimage1 = create_image(s2);

         m_pimage1->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         m_pimage1->get_graphics()->StretchBlt(0, 0, s2.cx(), s2->cy(), pgraphics, 0, 0, s->cx(), s->cy());

         //if (0)
         {

/*            if (pgraphics->m_pimage != nullptr)
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
               pgraphics->StretchBlt(0, 0, s.cx(), s.cy(), m_pimage1->get_graphics(), 0, 0, s2->cx(), s2->cy());


            }
            else
            {

/*               m_pimage2 = create_image(s);

               m_pimage2->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
               m_pimage2->get_graphics()->StretchBlt(0, 0, s.cx(), s.cy(), m_pimage1->get_graphics(), 0, 0, s2->cx(), s2->cy());


            }


            color32_t color32;

            ::u8 a, r, g, b, rm, gm, bm;

/*            ::image_pointer pimage = pgraphics->m_pimage;

/*            if (pimage->is_null())
            {

/*               pimage = m_pimage2;

            }

/*            pimage->map();

            int h = (s.cy() / 3) * 3;

            int w = (s.cx() / 3) * 3;

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
                  a = color32_u8_opacity(color32);
                  r = color32_u8_red(color32);
                  g = color32_u8_green(color32);
                  b = color32_u8_blue(color32);
                  rm = (g + b) / 4;
                  gm = (r + b) / 4;
                  bm = (r + g) / 4;

                  cr1 = REASSEMBLE_ARGB(a, gm, g, gm);
                  cr2 = REASSEMBLE_ARGB(a, bm, bm, b);
                  cr3 = REASSEMBLE_ARGB(a, r, rm, rm);
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

/*            if (pgraphics->m_pimage == nullptr)
            {

               pgraphics->BitBlt(0, 0, s.cx(), s.cy(), m_pimage2->get_graphics(), 0, 0);

            }
            else
            {

/*               pimage->unmap();

            }

            auto ppen = __create < ::draw2d::pen > ();

            ppen->create_solid(0.5, argb(84, 0, 0, 0));

            pgraphics->SelectObject(pen);

            for (int i = 0; i < s.cy(); i += 3)
            {

               pgraphics->draw_line(0, i, s.cx(), i);

            }

         }


      }




   }










} // namespace hellobase

















