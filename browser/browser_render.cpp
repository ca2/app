//
//  browser_render.cpp
//  app_core_browser
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include <math.h>
#include "app-core/gcom/gcom/gcom_slide.h"


namespace browser
{


   render::render(::object * pobjectParent, bool bAlternate) :
      object(pobjectParent->get_context_application()),
      thread(pobjectParent),
      m_font(e_create),




      m_bAlternate(bAlternate),
      m_blurImageImage(this),
      m_blurImage(this),
      m_blurImageTint(this)
   {
      if (m_bAlternate)
      {

         color c(ARGB(255, 200, 200, 180));

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
      m_millisLastFast = 0;
      m_millisAnime = 300;
      m_millisFastAnime = 300;
      m_millisLastOk = 0;

      m_strFontSel = FONT_SANS;

      m_pview = nullptr;

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

      m_millisSlidePeriod = 5000;

   }


   render::~render()
   {

   }


   void render::full_render()
   {

      size sizeNew = size(m_cx, m_cy);

      if (m_bNewLayout)
      {

         sync_lock sl2(&m_mutexWork);
         sync_lock sl3(&m_mutexDraw);
         sync_lock sl4(&m_mutexSwap);

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

      //      ::database::client::initialize_data_client(&Application.dataserver());

      if (Application.m_strAppId == "app-core/flag")
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

         m_pview->data_get("slide." + pslide->m_strPath, pslide->m_bDatabase);

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

      sync_lock sl(&m_mutexText);

      strHellomultiverse = m_strHelloBrowser.c_str();

   }


   double render::get_fps()
   {

      try
      {

         auto pview = m_pview;

         if(::is_null(pview))
         {

            return 0.0;

         }

         double dFps = pview->get_config_fps();

         return dFps / 4.0;

      }
      catch(...)
      {

      }

      return 0.0;

   }


   ::e_status     render::run()
   {

      ::parallelization::set_priority(::priority_below_normal);

      nano_timer nanotimer;

      u64 uNow = get_nanos();

      u64 uFrameNanos = (u64)(1000000000LL / get_fps());

      uFrameNanos = min(max(100000, uFrameNanos), 1000000000);

      u64 uFrameId = uNow / uFrameNanos;

      u64 uLastFrameId = uFrameId;

      u64 uNextFrame;

      u64 uWait;

      ::count cLost;

      while (thread_get_run())
      {

         try
         {

            if (m_bHelloRender)
            {

               full_render();

            }

            uNow = get_nanos();

            uFrameNanos = (u64)(1000000000ULL / get_fps());

            uFrameNanos = min(max(100000ULL, uFrameNanos), 1000000000ULL);

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

      sync_lock sl(&m_mutexWork);

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

         browser_render_lite_view(pgraphics);

      }
      //   else
      //   {
      //
      //      browser_render_full_view(pimage->g());
      //
      //   }

   }


   void render::browser_draw()
   {

      if (m_bVoidTransfer)
         return;

      sync_lock slDraw(&m_mutexDraw);

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

      sync_lock slSwap(&m_mutexSwap);

      if (m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }

   void render::browser_render_lite_view(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageWork->area() <= 0)
      {

         return;

      }

      ::get_task()->m_bThreadToolsForIncreasedFps = true;

      ::rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      ::draw2d::brush_pointer brushText(e_create);

      double T = 2.3;

      if (m_bAlternate)
      {

         T = 1.2;

      }
      else
      {

         T = 2.3;

      }

      double t= ::millis::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      ::size size;

      string strHelloBrowser;

      {

         sync_lock sl(&m_mutexText);

         get_browser(strHelloBrowser);

      }

      pgraphics->set_font(m_font);

      size = pgraphics->GetTextExtent(strHelloBrowser);

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

               sync_lock slDib(&m_mutexDib);

/*               m_pimage->create_image(this, ::size(m_cxCache1, m_cyCache1));

/*               if (m_pimage)
               {

/*                  m_pimage->fill(0, 0, 0, 0);

/*                  m_pimage->g()->set_font(m_font);

/*                  m_pimage->g()->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

/*                  m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

                  brushText->create_solid(ARGB(255, 255, 255, 255));

/*                  m_pimage->g()->SelectObject(brushText);

/*                  m_pimage->g()->text_out((m_cxCache1 - size->cx) / 2, (m_cyCache1 - size->cy) / 2, strHelloBrowser);

/*                  m_pimage->map();

/*                  System.imaging().spread(m_pimage->g(), ::point(), m_pimage->get_size(), m_pimage->g(), ::point(), int (m_dMaxRadius));

/*                  m_blurImage.blur(m_pimage, int(m_dMaxRadius));

/*                  m_pimageTemplate = create_image(m_pimage->get_size());

                  m_pimageTemplate->fill(0, 0, 0, 0);

/*                  m_pimageTemplate->channel_copy(::color::channel_alpha, ::color::channel_green, m_pimage);

               }

            }

         }

      }

      string strGetHelloBrowser;

      {

         sync_lock sl(&m_mutexText);

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




      ::color ca;


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

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      System.imaging().bitmap_blend(pgraphics,
                                         point((m_cx - m_pimageTemplate2->width()) / 2, (m_cy - m_pimageTemplate2->height()) / 2)
                                         , m_pimageTemplate2->get_size(),
                                         m_pimageTemplate2->get_graphics(), ::point(), byte (128 + (255 - 128) * r));

      //pgraphics->from(rectClient.top_left(),m_pimageTemplate, ::point(), rectClient>si);

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         brushText->create_solid(A_RGB(255, ca));

      }
      else
      {

         color color(m_hlsForeground);

         color.m_iA = 255;

         brushText->create_solid(color);

      }

      pgraphics->SelectObject(brushText);

      //if(!m_bAlternate)
      {

         pgraphics->text_out((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser);

      }
      //      pgraphics->FillSolidRect(200,00,100,100,ARGB(128,128,128,255));

      //    pgraphics->FillSolidRect(200,200,100,100,ARGB(128,128,128,0));

      if(!m_bFirstDone)
      {

         string strGetHelloBrowser;

         {

            sync_lock sl(&m_mutexText);

            get_browser(strGetHelloBrowser);

         }

         if (strHelloBrowser == strGetHelloBrowser && m_cxCache1 == m_cxTarget && m_cyCache1 == m_cyTarget)
         {

            m_bFirstDone = true;

         }

      }

   }


   void render::browser_render_full_view(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pimageWork->area() <= 0)
         return;

      ::rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      if (rectClient.area() <= 0)
         return;

      //      i32 iCount = 30;

      ::draw2d::brush_pointer brushText(e_create);

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

      double t= ::millis::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      ::color ca;

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

      pgraphics->set_font(m_font);


      string strGetHelloBrowser;

      {

         sync_lock sl(&m_mutexText);

         get_browser(strGetHelloBrowser);

      }

      string strHelloBrowser = strGetHelloBrowser;

      ::size size = pgraphics->GetTextExtent(strHelloBrowser);

      m_cxTarget = int(size.cx * 1.2);

      m_cyTarget = int(size.cy * 1.2);

      {

         sync_lock slDib(&m_mutexDib);

         if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

            int iBlur = 5;

            if (m_dMinRadius > 3.0)
            {

               iBlur = dBlur;

            }

/*            m_pimage->create_image(this, ::size(m_cx, m_cy));

/*            m_pimage->defer_realize(pgraphics);

/*            m_pimage->fill(0, 0, 0, 0);

/*            m_pimage->g()->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

/*            m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

            brushText->create_solid(ARGB(255, 255, 255, 255));

/*            m_pimage->g()->SelectObject(brushText);

/*            m_pimage->g()->set_font(m_font);

/*            m_pimage->g()->text_out((m_cx - size->cx) / 2, (m_cy - size->cy) / 2, strHelloBrowser);

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

/*               m_pimage->channel_copy(::color::channel_alpha, ::color::channel_green);

/*               m_pimageTint->tint(m_pimage, ca);

            }

         }

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->draw(rectClient, m_pimageTint->get_graphics());

      }

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         brushText->create_solid(A_RGB(255, ca));

      }
      else
      {

         color color(m_hlsForeground);

         color.m_iA = 255;

         brushText->create_solid(color);

      }

      pgraphics->SelectObject(brushText);

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
      if (Application.m_iErrorAiFont == 0)
      {

         sync_lock slAiFont(&Application.m_mutexAiFont);

         FT_Face & face = (FT_Face &)Application.m_faceAi;

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

               i64 iChar = ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

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

               i64 iChar = ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));

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

      if (strHelloBrowser == strGetHelloBrowser && m_cx == m_rectClient.width() && m_cy == m_rectClient.height())
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

/*      System.imaging().bitmap_blend(pgraphics, ::point(), pimage->get_size(), pimage, ::point(), pslide->m_iAlpha);

   }


   void render::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      rectClient.left = 0;
      rectClient.top = 0;
      rectClient.right = m_cx;
      rectClient.bottom = m_cy;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      millis tickPeriod = m_millisSlidePeriod;
      millis tickRampUp = tickPeriod / 2;
      millis tickSlide = 0;

      try
      {

         slideshow().draw(pgraphics);

      }
      catch (...)
      {

      }

      if (Application.m_etype == application::type_mili)
      {

         {

            string strHelloBrowser;

            {

               sync_lock sl(&m_mutexText);

               strHelloBrowser = m_pview->m_strProcessedHellomultiverse.c_str();

            }

            if (m_bNewLayout)
            {

               float fHeight = 100.0;

               ::draw2d::font_pointer font(e_create);

               font->create_pixel_font(FONT_SANS, fHeight, e_font_weight_bold);

               pgraphics->set_font(font);

               pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

               ::size size = pgraphics->GetTextExtent(strHelloBrowser);

               double ratey = fHeight * 0.84 / size.cy;

               font->create_pixel_font(FONT_SANS, min(m_cy * ratey, m_cx * size.cy * ratey / size.cx), e_font_weight_bold);

               m_font = font;

               m_bNewLayout = false;

            }

            ::color ca;

            double dPeriod = (500) * 11;

            ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

            ::draw2d::brush_pointer brush(e_create);

            brush->create_solid(A_RGB(255, ca));

            pgraphics->SelectObject(brush);

            pgraphics->set_font(m_font);

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

            ::size size = pgraphics->GetTextExtent(strHelloBrowser);

            pgraphics->text_out((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser);

            return;

         }

      }

      //::u32 dw= ::millis::now();

      if (m_bFast || !m_bFirstDone || m_millisLastFast.elapsed() < m_millisFastAnime)
      {

         sync_lock sl1(m_pview->get_wnd()->mutex());

         sync_lock slDraw(&m_mutexDraw);

         if (m_bFast || m_pimageFast->is_null())
         {

            m_bFast = false;


            string strFork;

            {

               sync_lock slText(&m_pview->m_mutexText);

               strFork = m_pview->m_strProcessedHellomultiverse.c_str();

            }

            browser_fast_render(strFork);

            m_bFirstDone = false;

         }

         if (m_bFast || !m_bFirstDone)
         {

            m_millisLastFast= ::millis::now();

         }

         if (m_pimageFast->is_ok())
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->draw(::point(), size(m_cx, m_cy), m_pimageFast->get_graphics());

         }

         m_pview->m_bOkPending = true;

         return;

      }

      if (m_pview->m_bOkPending)
      {

         m_pview->m_bOkPending = false;

         m_millisLastOk= ::millis::now();

      }

/*      ::image_pointer pimage;

      ::image_pointer imageFast = m_pimageFast;

      sync_lock sl(&m_mutexDraw);

      sync_lock slSwap(&m_mutexSwap);

/*      pimage = m_pimageOut;

/*      if (pimage->area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if (m_millisLastOk.elapsed() < m_millisAnime)
      {

         byte uchAlpha;

         uchAlpha = byte(max(0, min(255, (m_millisLastOk.elapsed()) * 255 / m_millisAnime)));

/*         System.imaging().bitmap_blend(pgraphics, ::point(), pimage->get_size(), pimage->g(), ::point(), uchAlpha);

         System.imaging().bitmap_blend(pgraphics, ::point(), imageFast.get_size(), imageFast.get_graphics(), ::point(), 255 - uchAlpha);

      }
      else
      {

/*         pgraphics->from(::point(), pimage->get_size(), pimage->g(), ::point());

      }

   }


   //::image_pointer & render::image23(string strImage)
   //{

   //   sync_lock sl(mutex());

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

   //            sync_lock sl(mutex());

   //            pimage = &m_mapDib23[strImage];

   //         }

/*   //         if (!pimage->load_image(strImage, false, true))
   //         {

   //            __throw(::exception::exception("Failed to load \"" + strImage + "\""));

   //         }

   //      });

   //   }

   //   return pimage;

   //}


   void render::defer_update_slide_show()
   {

      sync_lock sl(mutex());

      //for (auto & pslide : slideshow())
      //{

      //   if (is_different(slide.m_bNew, slide.m_bActive))
      //   {

      //      slide.m_bActive = slide.m_bNew;

      //      m_pimageaSlide->add_remove(slide->m_bActive, get_image(slide->m_strPath));

      //m_pview->data_set("slide." + slide.m_strPath, slide.m_bActive);

      //   }

      //}

//      m_millisSlideStart = ::millis::now() - m_millisSlidePeriod + 50;

   }


   bool render::in_anime()
   {
      if (m_bFast || m_millisLastFast.elapsed() < m_millisFastAnime)
         return true;
      if (m_millisLastOk.elapsed() < m_millisAnime)
         return true;
      return false;
   }


   void render::browser_fast_render(const string & strHelloBrowser)
   {

      if (m_cx <= 0 || m_cy <= 0)
      {

         return;

      }

      sync_lock slDraw(&m_mutexDraw);

      ::size sizeNew = ::size(m_cx, m_cy);


      bool bNewSize = m_pimageFast->width() != sizeNew->cx || m_pimageFast->height() != sizeNew->cy;

/*      m_pimageFast = create_image(sizeNew);

      m_pimageFast->fill(0, 0, 0, 0);

      ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

      float fHeight = 100.0;

      ::draw2d::font_pointer font(e_create);

      font->create_pixel_font(m_pview->m_prender->m_strFont, fHeight, e_font_weight_bold);

      pgraphics->set_font(font);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      ::size size = pgraphics->GetTextExtent(strHelloBrowser);

      double ratey = fHeight * 0.84 / size.cy;

      font->create_pixel_font(m_pview->m_prender->m_strFont, min(m_cy * ratey, m_cx * size.cy * ratey / size.cx), e_font_weight_bold);

      m_dMinRadius = max(1.0, min(m_cy * ratey, m_cx * size.cy * ratey / size.cx) / 46.0);

      m_dMaxRadius = m_dMinRadius * 2.3;

      m_font = font;

      pgraphics->set_font(m_font);

      size = pgraphics->GetTextExtent(strHelloBrowser);

      ::draw2d::path_pointer path(e_create);

      path->m_bFill = false;

      path->add_string((m_cx - size.cx) / 2, (m_cy - size.cy) / 2, strHelloBrowser, m_font);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, ARGB(255, 90, 90, 80));

      ::draw2d::pen_pointer penW(e_create);

      penW->create_solid(3.0, ARGB(84, 255, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->draw_path(path, penW);

      pgraphics->draw_path(path, pen);

   }


} // namespace browser



