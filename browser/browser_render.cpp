//
//  browser_render.cpp
//  app_core_browser
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
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
      m_timeLastFast = 0;
      m_timeAnime = 300;
      m_timeFastAnime = 300;
      m_timeLastOk = 0;

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

      m_timeSlidePeriod = 5000;

   }


   render::~render()
   {

   }


   void render::full_render()
   {

      int_size sizeNew = int_size(m_cx, m_cy);

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


   bool render::initialize_render(const ::scoped_string & scopedstrId)
   {

      m_pslideshow = __allocate ::gcom::slide_show(this);

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


   double render::get_frames_per_second()
   {

      try
      {

         auto pimpact = m_pimpact;

         if(::is_null(pimpact))
         {

            return 0.0;

         }

         ::frequency frequencyFramesPerSecond = pimpact->get_config_per_second();

         return frequencyFramesPerSecond / 4.0;

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

      unsigned long long uNow = get_nanos();

      unsigned long long uFrameNanos = (unsigned long long)(1000000000LL / get_frames_per_second());

      uFrameNanos = minimum(maximum(100000, uFrameNanos), 1000000000);

      unsigned long long uFrameId = uNow / uFrameNanos;

      unsigned long long uLastFrameId = uFrameId;

      unsigned long long uNextFrame;

      unsigned long long uWait;

      ::collection::count cLost;

      while (task_get_run())
      {

         try
         {

            if (m_bHelloRender)
            {

               full_render();

            }

            uNow = get_nanos();

            uFrameNanos = (unsigned long long)(1000000000ULL / get_frames_per_second());

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

/*      ::image::image_pointer pimage = m_pimageWork;

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

      ::int_rectangle rectangleX;

      rectangleX.left() = 0;

      rectangleX.top() = 0;

      rectangleX.right() = m_cx;

      rectangleX.bottom() = m_cy;

      auto pbrushText = øcreate < ::draw2d::brush > ();

      double T = 2.3;

      if (m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::time::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      ::int_size size;

      string strHelloBrowser;

      {

         synchronous_lock synchronouslock(m_pmutexText);

         get_browser(strHelloBrowser);

      }

      pgraphics->set_font(m_pfont);

      size = pgraphics->get_text_extent(strHelloBrowser);

      int iCx = int(size.cx() * 1.2);
      int iCy = int(size.cy() * 1.2);

      if (iCx != m_cxTarget || iCy != m_cyTarget)
      {

         m_cxTarget = iCx;
         m_cyTarget = iCy;

         m_bFirstDone = false;

      }

      if (!m_bFirstDone)
      {

         if (session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
         {

            sleep(47_ms);

         }
         else
         {

            m_cxCache1 = m_cxTarget;

            m_cyCache1 = m_cyTarget;

            {

               synchronous_lock slDib(m_pmutexDib);

/*               m_pimage->create_image(this, ::int_size(m_cxCache1, m_cyCache1));

/*               if (m_pimage)
               {

/*                  m_pimage->fill(0, 0, 0, 0);

/*                  m_pimage->g()->set_font(m_pfont);

/*                  m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*                  m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  pbrushText->create_solid(argb(255, 255, 255, 255));

/*                  m_pimage->g()->SelectObject(pbrushText);

/*                  m_pimage->g()->text_out((m_cxCache1 - int_size->cx()) / 2, (m_cyCache1 - int_size->cy()) / 2, strHelloBrowser);

/*                  m_pimage->map();

/*                  psystem->imaging().spread(m_pimage->g(), ::int_point(), m_pimage->get_size(), m_pimage->g(), ::int_point(), int (m_dMaxRadius));

/*                  m_blurImage.blur(m_pimage, int(m_dMaxRadius));

/*                  m_pimageTemplate = create_image(m_pimage->get_size());

                  m_pimageTemplate->fill(0, 0, 0, 0);

/*                  m_pimageTemplate->channel_copy(::color::e_channel_opacity, ::color::e_channel_green, m_pimage);

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

      if (!session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
      {

         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR,ca->m_iG,ca->m_iB, 140 + 220 * r);
         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR, ca->m_iG, ca->m_iB);

         m_pimageTemplate2->tint(m_pimageTemplate, ca);

      }

      pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      psystem->imaging().bitmap_blend(pgraphics,
                                         int_point((m_cx - m_pimageTemplate2->width()) / 2, (m_cy - m_pimageTemplate2->height()) / 2)
                                         , m_pimageTemplate2->get_size(),
                                         m_pimageTemplate2->get_graphics(), ::int_point(), unsigned char (128 + (255 - 128) * r));

      //pgraphics->from(rectangleX.top_left(),m_pimageTemplate, ::int_point(), rectangleX>si);

      pgraphics->set_font(m_pfont);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
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

         pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBrowser);

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

      ::int_rectangle rectangleX;

      rectangleX.left() = 0;

      rectangleX.top() = 0;

      rectangleX.right() = m_cx;

      rectangleX.bottom() = m_cy;

      if (rectangleX.area() <= 0)
         return;

      //      int iCount = 30;

      auto pbrushText = øcreate < ::draw2d::brush > ();

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

      double t= ::time::now() / 1000.0;

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

      ::int_size size = pgraphics->get_text_extent(strHelloBrowser);

      m_cxTarget = int(size.cx() * 1.2);

      m_cyTarget = int(size.cy() * 1.2);

      {

         synchronous_lock slDib(m_pmutexDib);

         if (!session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
         {

            int iBlur = 5;

            if (m_dMinRadius > 3.0)
            {

               iBlur = dBlur;

            }

/*            m_pimage->create_image(this, ::int_size(m_cx, m_cy));

/*            m_pimage->defer_realize(pgraphics);

/*            m_pimage->fill(0, 0, 0, 0);

/*            m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*            m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pbrushText->create_solid(argb(255, 255, 255, 255));

/*            m_pimage->g()->SelectObject(pbrushText);

/*            m_pimage->g()->set_font(m_pfont);

/*            m_pimage->g()->text_out((m_cx - int_size->cx()) / 2, (m_cy - int_size->cy()) / 2, strHelloBrowser);

            if (m_dMinRadius > 3.0)
            {

/*               m_blurImage.blur(m_pimage, iBlur);

            }
            else
            {

               for (int i = 0; i < dBlur * 2; i++)
               {

/*                  m_blurImage.blur(m_pimage, iBlur);

               }

            }

            if (!session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
            {

/*               m_pimage->channel_copy(::color::e_channel_opacity, ::color::e_channel_green);

/*               m_pimageTint->tint(m_pimage, ca);

            }

         }

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw(rectangleX, m_pimageTint->get_graphics());

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
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

      pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBrowser);

      unsigned char a, R, g, b;

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

         int error;

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

               long long iChar = unicode_index(unicode_to_utf8(L"Love"));

               int glyph_index = FT_Get_Char_Index(face, (int)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if (error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if (error == 0)
                  {

/*                     ::image::image_pointer & pimage = m_pimageAi1;

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

               long long iChar = unicode_index(unicode_to_utf8(L"Love"));

               int glyph_index = FT_Get_Char_Index(face, (int)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if (error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if (error == 0)
                  {

/*                     ::image::image_pointer & pimage = m_pimageAi2;

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

      if (strHelloBrowser == strGetHelloBrowser && m_cx == m_rectangleX.width() && m_cy == m_rectangleX.height())
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

/*      psystem->imaging().bitmap_blend(pgraphics, ::int_point(), pimage->get_size(), pimage, ::int_point(), pslide->m_iAlpha);

   }


   void render::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::int_rectangle rectangleX;

      rectangleX.left() = 0;
      rectangleX.top() = 0;
      rectangleX.right() = m_cx;
      rectangleX.bottom() = m_cy;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      ::time tickPeriod = m_timeSlidePeriod;
      ::time tickRampUp = tickPeriod / 2;
      ::time tickSlide = 0;

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

               auto pfont = øcreate < ::write_text::font > ();

               pfont->create_pixel_font(pnode->font_name(e_font_sans), fHeight, e_font_weight_bold);

               pgraphics->set_font(font);

               pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

               ::int_size size = pgraphics->get_text_extent(strHelloBrowser);

               double ratey = fHeight * 0.84 / size.cy();

               pfont->create_pixel_font(pnode->font_name(e_font_sans), minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()), e_font_weight_bold);

               m_pfont = font;

               m_bNewLayout = false;

            }

            ::color::color ca;

            double dPeriod = (500) * 11;

            ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

            auto pbrush = øcreate < ::draw2d::brush >();

            pbrush->create_solid(a_rgb(255, ca));

            pgraphics->SelectObject(brush);

            pgraphics->set_font(m_pfont);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            ::int_size size = pgraphics->get_text_extent(strHelloBrowser);

            pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBrowser);

            return;

         }

      }

      //unsigned int dw= ::time::now();

      if (m_bFast || !m_bFirstDone || m_timeLastFast.elapsed() < m_timeFastAnime)
      {

         synchronous_lock sl1(m_pimpact->get_wnd()->synchronization());

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

            m_timeLastFast= ::time::now();

         }

         if (m_pimageFast->is_ok())
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw(::int_point(), int_size(m_cx, m_cy), m_pimageFast->get_graphics());

         }

         m_pimpact->m_bOkPending = true;

         return;

      }

      if (m_pimpact->m_bOkPending)
      {

         m_pimpact->m_bOkPending = false;

         m_timeLastOk= ::time::now();

      }

/*      ::image::image_pointer pimage;

      ::image::image_pointer imageFast = m_pimageFast;

      synchronous_lock synchronouslock(m_pmutexDraw);

      synchronous_lock slSwap(m_pmutexSwap);

/*      pimage = m_pimageOut;

/*      if (pimage->area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_timeLastOk.elapsed() < m_timeAnime)
      {

         unsigned char uchAlpha;

         uchAlpha = unsigned char(maximum(0, minimum(255, (m_timeLastOk.elapsed()) * 255 / m_timeAnime)));

/*         psystem->imaging().bitmap_blend(pgraphics, ::int_point(), pimage->get_size(), pimage->g(), ::int_point(), uchAlpha);

         psystem->imaging().bitmap_blend(pgraphics, ::int_point(), imageFast.get_size(), imageFast.get_graphics(), ::int_point(), 255 - uchAlpha);

      }
      else
      {

/*         pgraphics->from(::int_point(), pimage->get_size(), pimage->g(), ::int_point());

      }

   }


   //::image::image_pointer & render::image23(const ::scoped_string & scopedstrImage)
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

/*   //         ::image::image *pimage = nullptr;

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

//      m_timeSlideStart = ::time::now() - m_timeSlidePeriod + 50;

   }


   bool render::in_anime()
   {
      if (m_bFast || m_timeLastFast.elapsed() < m_timeFastAnime)
         return true;
      if (m_timeLastOk.elapsed() < m_timeAnime)
         return true;
      return false;
   }


   void render::browser_fast_render(const ::scoped_string & scopedstrHelloBrowser)
   {

      if (m_cx <= 0 || m_cy <= 0)
      {

         return;

      }

      synchronous_lock slDraw(m_pmutexDraw);

      ::int_size sizeNew = ::int_size(m_cx, m_cy);


      bool bNewSize = m_pimageFast->width() != sizeNew->cx() || m_pimageFast->height() != sizeNew->cy();

/*      m_pimageFast = create_image(sizeNew);

      m_pimageFast->fill(0, 0, 0, 0);

      ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

      float fHeight = 100.0;

      auto pfont = øcreate < ::write_text::font > ();

      pfont->create_pixel_font(m_pimpact->m_prender->m_strFont, fHeight, e_font_weight_bold);

      pgraphics->set_font(font);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      ::int_size size = pgraphics->get_text_extent(strHelloBrowser);

      double ratey = fHeight * 0.84 / size.cy();

      pfont->create_pixel_font(m_pimpact->m_prender->m_strFont, minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()), e_font_weight_bold);

      m_dMinRadius = maximum(1.0, minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()) / 46.0);

      m_dMaxRadius = m_dMinRadius * 2.3;

      m_pfont = font;

      pgraphics->set_font(m_pfont);

      size = pgraphics->get_text_extent(strHelloBrowser);

      auto ppath = øcreate < ::draw2d::path > ();

      ppath->m_bFill = false;

      ppath->add_string((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBrowser, m_pfont);

      auto ppen = øcreate < ::draw2d::pen > ();

      ppen->create_solid(1.0, argb(255, 90, 90, 80));

      auto ppenW = øcreate < ::draw2d::pen > ();

      ppenW->create_solid(3.0, argb(84, 255, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->draw(path, ppenW);

      pgraphics->draw(ppath, ppen);

   }


} // namespace browser



