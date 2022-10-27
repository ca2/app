//
//  browser_render.cpp
//  app_core_browser
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include <math.h>
#include "app-core/gcom/gcom/gcom_slide.h"


namespace browser
{


   render::render(::object * pobjectParent, bool bAlternate) :
      object(pobjectParent->get_app()),
      thread(pobjectParent),
      m_pfont(e_create),




      m_bAlternate(bAlternate),
      m_blurImageImage(this),
      m_blurImage(this),
      m_blurImageTint(this)
   {
      if (m_bAlternate)
      {

         ::color::color color(argb(255, 200, 200, 180));

         c.get_hls(m_hlsForeground);

      }
      else
      {

         m_hlsForeground.m_dH = 0.0;
         m_hlsForeground.m_dL = 1.0;
         m_hlsForeground.m_dS = 1.0;

      }

      m_bFastOnEmpty = true;
      m_bFast = true;
      m_durationLastFast = 0;
      m_durationAnime = 300;
      m_durationFastAnime = 300;
      m_durationLastOk = 0;

      m_strFontSel = pnode->font_name(e_font_sans);

      m_pimpact = nullptr;

      m_bImageEnable = true;

      m_bDib1 = false;

      m_bLite = true;

      m_bNewLayout = false;
      m_bHelloRender = false;
      m_cx = 0;
      m_cy = 0;
      m_cxCache1 = 0;
      m_cyCache1 = 0;

      m_bVoidTransfer = false;
      m_bFirstDone = false;

      m_dMinRadius = 0.0;
      m_dMaxRadius = 0.0;

      m_bVoidTransfer = false;

      m_bFirstDone = true;

      m_cx = 0;

      m_cy = 0;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bNewLayout = false;

      m_bHelloRender = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;

      m_durationSlidePeriod = 5000;

   }


   render::~render()
   {

   }


   void render::full_render()
   {

      size_i32 sizeNew = size_i32(m_cx, m_cy);

      if (m_bNewLayout)
      {

         synchronous_lock sl2(m_pmutexWork);
         synchronous_lock sl3(m_pmutexDraw);
         synchronous_lock sl4(m_pmutexSwap);

         m_bNewLayout = false;

/*         m_pimageA = create_image(sizeNew);

/*         m_pimageB = create_image(sizeNew);

      }

      browser_draw();

      browser_render();

   }


   bool render::initialize_render(string strId)
   {

      m_pslideshow = __new(::gcom::slide_show(this));

      //      ::database::client::initialize_data_client(&papp->dataserver());

      if (papp->m_XstrAppId == "app-core/flag")
      {

         slideshow().add_slide("matter://cat.gif");
         slideshow().add_slide("matter://nanosvg/23.svg");
         slideshow().add_slide("matter://main/cheetah.png");
         slideshow().add_slide("matter://picachu_by_rondex.png");
         slideshow().add_slide("matter://totoro_plus_plus.png");

      }
      else if (strId == "switcher")
      {

         slideshow().add_slide("matter://cat.gif");
         slideshow().add_slide("matter://picachu_by_rondex.png");
         slideshow().add_slide("matter://totoro_plus_plus.png");

      }
      else
      {

         slideshow().add_slide("matter://cat.gif");
         slideshow().add_slide("matter://nanosvg/23.svg");
         slideshow().add_slide("matter://main/cheetah.png");

      }

      int i = 1;

      for (auto & pslide : slideshow())
      {

         m_pimpact->datastream()->get("slide." + pslide->m_strPath, pslide->m_bDatabase);

         i++;

      }

      defer_update_slide_show();


      return true;

   }


   ::gcom::slide_show & render::slideshow()
   {

      return *m_pslideshow.cast < ::gcom::slide_show>();

   }

   void render::get_browser(string & strHellomultiverse)
   {

      synchronous_lock synchronouslock(m_pmutexText);

      strHellomultiverse = m_strHelloBrowser.c_str();

   }


   double render::get_fps()
   {

      try
      {

         auto pimpact = m_pimpact;

         if(::is_null(pimpact))
         {

            return 0.0;

         }

         double dFps = pimpact->get_config_fps();

         return dFps / 4.0;

      }
      catch(...)
      {

      }

      return 0.0;

   }


   void     render::run()
   {

      ::parallelization::set_priority(::e_priority_below_normal);

      nano_timer nanotimer;

      u64 uNow = get_nanos();

      u64 uFrameNanos = (u64)(1000000000LL / get_fps());

      uFrameNanos = minimum(maximum(100000, uFrameNanos), 1000000000);

      u64 uFrameId = uNow / uFrameNanos;

      u64 uLastFrameId = uFrameId;

      u64 uNextFrame;

      u64 uWait;

      ::count cLost;

      while (task_get_run())
      {

         try
         {

            if (m_bHelloRender)
            {

               full_render();

            }

            uNow = get_nanos();

            uFrameNanos = (u64)(1000000000ULL / get_fps());

            uFrameNanos = minimum(maximum(100000ULL, uFrameNanos), 1000000000ULL);

            uFrameId = uNow / uFrameNanos;

            uNextFrame = (uFrameId + 1) * uFrameNanos;

            uWait = uNextFrame - uNow;

            cLost = uFrameId - uLastFrameId - 1;

            if (cLost < 0 || uWait < (uFrameNanos / 2)) // too much CPU usage?
            {

               uWait += uFrameNanos;

            }

            uLastFrameId = uFrameId;

            nanotimer.wait(uWait);

         }
         catch(...)
         {

            break;

         }

      }

      return ::success;

   }


   void render::term_thread()
   {

      try
      {

         m_pslideshow.release();

      }
      catch (...)
      {

      }

      ::thread::term_thread();

   }


   void render::browser_render()
   {

      synchronous_lock synchronouslock(m_pmutexWork);

/*      ::image_pointer pimage = m_pimageWork;

/*      if (!pimage->is_ok())
      {

         return;

      }

/*      pimage->fill(0, 0, 0, 0);

/*      browser_render(pimage->g());

   }


   void render::browser_render(::draw2d::graphics_pointer & pgraphics)
   {



      //   if(m_bLite)
      {

         browser_render_lite_impact(pgraphics);

      }
      //   else
      //   {
      //
      //      browser_render_full_impact(pimage->g());
      //
      //   }

   }


   void render::browser_draw()
   {

      if (m_bVoidTransfer)
         return;

      synchronous_lock slDraw(m_pmutexDraw);

      if (m_bDib1)
      {

         m_pimageOut = m_pimageA;
         m_pimageWork = m_pimageB;

      }
      else
      {

         m_pimageOut = m_pimageB;
         m_pimageWork = m_pimageA;

      }

      synchronous_lock slSwap(m_pmutexSwap);

      if (m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }

   void render::browser_render_lite_impact(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageWork->area() <= 0)
      {

         return;

      }

      ::get_task()->m_bThreadToolsForIncreasedFps = true;

      ::rectangle_i32 rectangleClient;

      rectangleClient.left = 0;

      rectangleClient.top = 0;

      rectangleClient.right = m_cx;

      rectangleClient.bottom = m_cy;

      auto pbrushText = __create < ::draw2d::brush > ();

      double T = 2.3;

      if (m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::duration::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      ::size_i32 size;

      string strHelloBrowser;

      {

         synchronous_lock synchronouslock(m_pmutexText);

         get_browser(strHelloBrowser);

      }

      pgraphics->set_font(m_pfont);

      size = pgraphics->get_text_extent(strHelloBrowser);

      int iCx = int(size.cx * 1.2);
      int iCy = int(size.cy * 1.2);

      if (iCx != m_cxTarget || iCy != m_cyTarget)
      {

         m_cxTarget = iCx;
         m_cyTarget = iCy;

         m_bFirstDone = false;

      }

      if (!m_bFirstDone)
      {

         if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

            sleep(47_ms);

         }
         else
         {

            m_cxCache1 = m_cxTarget;

            m_cyCache1 = m_cyTarget;

            {

               synchronous_lock slDib(m_pmutexDib);

/*               m_pimage->create_image(this, ::size_i32(m_cxCache1, m_cyCache1));

/*               if (m_pimage)
               {

/*                  m_pimage->fill(0, 0, 0, 0);

/*                  m_pimage->g()->set_font(m_pfont);

/*                  m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*                  m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  pbrushText->create_solid(argb(255, 255, 255, 255));

/*                  m_pimage->g()->SelectObject(pbrushText);

/*                  m_pimage->g()->text_out((m_cxCache1 - size_i32->cx) / 2, (m_cyCache1 - size_i32->cy) / 2, strHelloBrowser);

/*                  m_pimage->map();

/*                  psystem->imaging().spread(m_pimage->g(), ::point_i32(), m_pimage->get_size(), m_pimage->g(), ::point_i32(), int (m_dMaxRadius));

/*                  m_blurImage.blur(m_pimage, int(m_dMaxRadius));

/*                  m_pimageTemplate = create_image(m_pimage->get_size());

                  m_pimageTemplate->fill(0, 0, 0, 0);

/*                  m_pimageTemplate->channel_copy(::color::e_channel_alpha, ::color::e_channel_green, m_pimage);

               }

            }

         }

      }

      string strGetHelloBrowser;

      {

         synchronous_lock synchronouslock(m_pmutexText);

         get_browser(strGetHelloBrowser);

      }

      {

         if (!m_bFirstDone
               && (strHelloBrowser != strGetHelloBrowser
                   || m_cxCache1 != m_cxTarget
                   || m_cyCache1 != m_cyTarget
                   || m_pimageTemplate->area() <= 0))
            return;

      }




      ::color::color ca;


//      if (false)
//      {
//
//         double dPeriod = (5000) * 11;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else if (m_bAlternate)
      if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.23, 0.84);

      }

      if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR,ca->m_iG,ca->m_iB, 140 + 220 * r);
         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR, ca->m_iG, ca->m_iB);

         m_pimageTemplate2->tint(m_pimageTemplate, ca);

      }

      pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      psystem->imaging().bitmap_blend(pgraphics,
                                         point_i32((m_cx - m_pimageTemplate2->width()) / 2, (m_cy - m_pimageTemplate2->height()) / 2)
                                         , m_pimageTemplate2->get_size(),
                                         m_pimageTemplate2->get_graphics(), ::point_i32(), byte (128 + (255 - 128) * r));

      //pgraphics->from(rectangleClient.top_left(),m_pimageTemplate, ::point_i32(), rectangleClient>si);

      pgraphics->set_font(m_pfont);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         pbrushText->create_solid(a_rgb(255, ca));

      }
      else
      {

         ::color::color color(m_hlsForeground);

         color.m_iA = 255;

         pbrushText->create_solid(color);

      }

      pgraphics->SelectObject(pbrushText);

      //if(!m_bAlternate)
      {

         pgraphics->text_out((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser);

      }
      //      pgraphics->FillSolidRect(200,00,100,100,argb(128,128,128,255));

      //    pgraphics->FillSolidRect(200,200,100,100,argb(128,128,128,0));

      if(!m_bFirstDone)
      {

         string strGetHelloBrowser;

         {

            synchronous_lock synchronouslock(m_pmutexText);

            get_browser(strGetHelloBrowser);

         }

         if (strHelloBrowser == strGetHelloBrowser && m_cxCache1 == m_cxTarget && m_cyCache1 == m_cyTarget)
         {

            m_bFirstDone = true;

         }

      }

   }


   void render::browser_render_full_impact(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageWork->area() <= 0)
         return;

      ::rectangle_i32 rectangleClient;

      rectangleClient.left = 0;

      rectangleClient.top = 0;

      rectangleClient.right = m_cx;

      rectangleClient.bottom = m_cy;

      if (rectangleClient.area() <= 0)
         return;

      //      i32 iCount = 30;

      auto pbrushText = __create < ::draw2d::brush > ();

      double T = 2.3;

//      if (false)
//      {
//
//         T = 2.3;
//
//      }
//      else
      if (m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::duration::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      ::color::color ca;

//      if (false)
//      {
//
//         double dPeriod = (5000) * 11;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else
//
      if (m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.23, 0.84);

      }

      pgraphics->set_font(m_pfont);


      string strGetHelloBrowser;

      {

         synchronous_lock synchronouslock(m_pmutexText);

         get_browser(strGetHelloBrowser);

      }

      string strHelloBrowser = strGetHelloBrowser;

      ::size_i32 size = pgraphics->get_text_extent(strHelloBrowser);

      m_cxTarget = int(size.cx * 1.2);

      m_cyTarget = int(size.cy * 1.2);

      {

         synchronous_lock slDib(m_pmutexDib);

         if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

            int iBlur = 5;

            if (m_dMinRadius > 3.0)
            {

               iBlur = dBlur;

            }

/*            m_pimage->create_image(this, ::size_i32(m_cx, m_cy));

/*            m_pimage->defer_realize(pgraphics);

/*            m_pimage->fill(0, 0, 0, 0);

/*            m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*            m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pbrushText->create_solid(argb(255, 255, 255, 255));

/*            m_pimage->g()->SelectObject(pbrushText);

/*            m_pimage->g()->set_font(m_pfont);

/*            m_pimage->g()->text_out((m_cx - size_i32->cx) / 2, (m_cy - size_i32->cy) / 2, strHelloBrowser);

            if (m_dMinRadius > 3.0)
            {

/*               m_blurImage.blur(m_pimage, iBlur);

            }
            else
            {

               for (i32 i = 0; i < dBlur * 2; i++)
               {

/*                  m_blurImage.blur(m_pimage, iBlur);

               }

            }

            if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
            {

/*               m_pimage->channel_copy(::color::e_channel_alpha, ::color::e_channel_green);

/*               m_pimageTint->tint(m_pimage, ca);

            }

         }

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw(rectangleClient, m_pimageTint->get_graphics());

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         pbrushText->create_solid(a_rgb(255, ca));

      }
      else
      {

         ::color::color color(m_hlsForeground);

         color.m_iA = 255;

         pbrushText->create_solid(color);

      }

      pgraphics->SelectObject(pbrushText);

      pgraphics->text_out((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser);

      byte a, R, g, b;

      if (m_bAlternate)
      {
         a = 200;
         R = 180;
         g = 80;
         b = 180;
      }
      else
      {
         a = 180;
         R = 80;
         g = 180;
         b = 80;
      }

#if 0
      if (papp->m_iErrorAiFont == 0)
      {

         synchronous_lock slAiFont(&papp->m_pmutexAiFont);

         FT_Face & face = (FT_Face &)papp->m_faceAi;

         i32 error;

         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  800 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if (error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if (error == 0)
            {

               i64 iChar = ::str::ch().uni_index(unicode_to_utf8(L"愛"));

               i32 glyph_index = FT_Get_Char_Index(face, (i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if (error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if (error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi1;

/*                     pimage = create_image({face->glyph->bitmap.width,  face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(0, 0, pimage->width() / 40, pimage->height() / 40, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

/*                     pgraphics->StretchBlt(0, m_cy - pimage->height() / 40, pimage->width() / 40, pimage->height() / 40, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

                  }

               }

            }

         }


         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  640 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if (error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if (error == 0)
            {

               i64 iChar = ::str::ch().uni_index(unicode_to_utf8(L"愛"));

               i32 glyph_index = FT_Get_Char_Index(face, (i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if (error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if (error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi2;

/*                     pimage = create_image({face->glyph->bitmap.width,  face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32, 0, pimage->width() / 32, pimage->height() / 32, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32, m_cy - pimage->height() / 32, pimage->width() / 32, pimage->height() / 32, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

                  }

               }

            }

         }

      }

#endif

      if (strHelloBrowser == strGetHelloBrowser && m_cx == m_rectangleClient.width() && m_cy == m_rectangleClient.height())
      {

         m_bFirstDone = true;

      }

   }

   void render::slide_draw(::draw2d::graphics_pointer & pgraphics, ::gcom::slide * pslide)
   {

      m_pimageaSlide->set_size(slideshow()->get_size());

/*      auto & pimage = m_pimageaSlide[pslide->m_iDrawable];

/*      if (!pimage)
      {

/*         pimage = get_image(pslide->m_strPath);

      }

/*      psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), pimage->get_size(), pimage, ::point_i32(), pslide->m_iAlpha);

   }


   void render::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      rectangleClient.left = 0;
      rectangleClient.top = 0;
      rectangleClient.right = m_cx;
      rectangleClient.bottom = m_cy;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      ::duration tickPeriod = m_durationSlidePeriod;
      ::duration tickRampUp = tickPeriod / 2;
      ::duration tickSlide = 0;

      try
      {

         slideshow().draw(pgraphics);

      }
      catch (...)
      {

      }

      if (papp->m_etype == application::type_mili)
      {

         {

            string strHelloBrowser;

            {

               synchronous_lock synchronouslock(m_pmutexText);

               strHelloBrowser = m_pimpact->m_strProcessedHellomultiverse.c_str();

            }

            if (m_bNewLayout)
            {

               float fHeight = 100.0;

               auto pfont = __create < ::write_text::font > ();

               pfont->create_pixel_font(pnode->font_name(e_font_sans), fHeight, e_font_weight_bold);

               pgraphics->set_font(font);

               pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

               ::size_i32 size = pgraphics->get_text_extent(strHelloBrowser);

               double ratey = fHeight * 0.84 / size.cy;

               pfont->create_pixel_font(pnode->font_name(e_font_sans), minimum(m_cy * ratey, m_cx * size.cy * ratey / size.cx), e_font_weight_bold);

               m_pfont = font;

               m_bNewLayout = false;

            }

            ::color::color ca;

            double dPeriod = (500) * 11;

            ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

            auto pbrush = __create < ::draw2d::brush >();

            pbrush->create_solid(a_rgb(255, ca));

            pgraphics->SelectObject(brush);

            pgraphics->set_font(m_pfont);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            ::size_i32 size = pgraphics->get_text_extent(strHelloBrowser);

            pgraphics->text_out((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser);

            return;

         }

      }

      //::u32 dw= ::duration::now();

      if (m_bFast || !m_bFirstDone || m_durationLastFast.elapsed() < m_durationFastAnime)
      {

         synchronous_lock sl1(m_pimpact->get_wnd()->mutex());

         synchronous_lock slDraw(m_pmutexDraw);

         if (m_bFast || m_pimageFast->is_null())
         {

            m_bFast = false;


            string strFork;

            {

               synchronous_lock slText(&m_pimpact->m_pmutexText);

               strFork = m_pimpact->m_strProcessedHellomultiverse.c_str();

            }

            browser_fast_render(strFork);

            m_bFirstDone = false;

         }

         if (m_bFast || !m_bFirstDone)
         {

            m_durationLastFast= ::duration::now();

         }

         if (m_pimageFast->is_ok())
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw(::point_i32(), size_i32(m_cx, m_cy), m_pimageFast->get_graphics());

         }

         m_pimpact->m_bOkPending = true;

         return;

      }

      if (m_pimpact->m_bOkPending)
      {

         m_pimpact->m_bOkPending = false;

         m_durationLastOk= ::duration::now();

      }

/*      ::image_pointer pimage;

      ::image_pointer imageFast = m_pimageFast;

      synchronous_lock synchronouslock(m_pmutexDraw);

      synchronous_lock slSwap(m_pmutexSwap);

/*      pimage = m_pimageOut;

/*      if (pimage->area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_durationLastOk.elapsed() < m_durationAnime)
      {

         byte uchAlpha;

         uchAlpha = byte(maximum(0, minimum(255, (m_durationLastOk.elapsed()) * 255 / m_durationAnime)));

/*         psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), pimage->get_size(), pimage->g(), ::point_i32(), uchAlpha);

         psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), imageFast.get_size(), imageFast.get_graphics(), ::point_i32(), 255 - uchAlpha);

      }
      else
      {

/*         pgraphics->from(::point_i32(), pimage->get_size(), pimage->g(), ::point_i32());

      }

   }


   //::image_pointer & render::image23(string strImage)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   auto & pimage = m_mapDib23[strImage];

   //   if (pimage->is_null())
   //   {

   //      pimage->create(this);

   //   }

   //   if (pimage->m_eload == ::draw2d::load_none)
   //   {

   //      pimage->m_eload = ::draw2d::load_going_to_load;

   //      fork([=]()
   //      {

/*   //         image * pimage = nullptr;

   //         {

   //            synchronous_lock synchronouslock(this->synchronization());

   //            pimage = &m_mapDib23[strImage];

   //         }

/*   //         if (!pimage->load_image(strImage, false, true))
   //         {

   //            throw ::exception(::exception("Failed to load \"" + strImage + "\""));

   //         }

   //      });

   //   }

   //   return pimage;

   //}


   void render::defer_update_slide_show()
   {

      synchronous_lock synchronouslock(this->synchronization());

      //for (auto & pslide : slideshow())
      //{

      //   if (is_different(slide.m_bNew, slide.m_bActive))
      //   {

      //      slide.m_bActive = slide.m_bNew;

      //      m_pimageaSlide->add_erase(slide->m_bActive, get_image(slide->m_strPath));

      //m_pimpact->datastream()->set("slide." + slide.m_strPath, slide.m_bActive);

      //   }

      //}

//      m_durationSlideStart = ::duration::now() - m_durationSlidePeriod + 50;

   }


   bool render::in_anime()
   {
      if (m_bFast || m_durationLastFast.elapsed() < m_durationFastAnime)
         return true;
      if (m_durationLastOk.elapsed() < m_durationAnime)
         return true;
      return false;
   }


   void render::browser_fast_render(const ::string & strHelloBrowser)
   {

      if (m_cx <= 0 || m_cy <= 0)
      {

         return;

      }

      synchronous_lock slDraw(m_pmutexDraw);

      ::size_i32 sizeNew = ::size_i32(m_cx, m_cy);


      bool bNewSize = m_pimageFast->width() != sizeNew->cx || m_pimageFast->height() != sizeNew->cy;

/*      m_pimageFast = create_image(sizeNew);

      m_pimageFast->fill(0, 0, 0, 0);

      ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

      float fHeight = 100.0;

      auto pfont = __create < ::write_text::font > ();

      pfont->create_pixel_font(m_pimpact->m_prender->m_strFont, fHeight, e_font_weight_bold);

      pgraphics->set_font(font);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      ::size_i32 size = pgraphics->get_text_extent(strHelloBrowser);

      double ratey = fHeight * 0.84 / size.cy;

      pfont->create_pixel_font(m_pimpact->m_prender->m_strFont, minimum(m_cy * ratey, m_cx * size.cy * ratey / size.cx), e_font_weight_bold);

      m_dMinRadius = maximum(1.0, minimum(m_cy * ratey, m_cx * size.cy * ratey / size.cx) / 46.0);

      m_dMaxRadius = m_dMinRadius * 2.3;

      m_pfont = font;

      pgraphics->set_font(m_pfont);

      size = pgraphics->get_text_extent(strHelloBrowser);

      auto ppath = __create < ::draw2d::path > ();

      ppath->m_bFill = false;

      ppath->add_string((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser, m_pfont);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, argb(255, 90, 90, 80));

      auto ppenW = __create < ::draw2d::pen > ();

      ppenW->create_solid(3.0, argb(84, 255, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->draw(path, ppenW);

      pgraphics->draw(ppath, ppen);

   }


} // namespace browser



