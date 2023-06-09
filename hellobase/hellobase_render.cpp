//
//  hellobase_render.cpp
//  app_core_hellobase
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//


#include "framework.h"
#include <math.h>


namespace hellobase
{


   render::render(::particle * pparticle) :
      object(pparticle),
      thread(pparticle),
      helloaura::render(pparticle),
      helloaxis::render(pparticle)
   {

      m_bFirst23 = false;
      m_bFastOnEmpty = true;
      m_bFast = true;
      m_timeLastFast = 0;
      m_timeAnime = 2000;
      m_timeFastAnime = 500;
      m_timeLastOk = 0;

      m_pimpact = nullptr;

      m_bImageEnable = true;

      m_bDib1 = false;

      m_bAlternate = false;

      m_bLite = true;

      m_bNewLayout = false;
      m_bHelloRender = false;
      //m_cx = 0;
      //m_cy = 0;
      m_cxCache1 = 0;
      m_cyCache1 = 0;

      m_bVoidTransfer = false;
      m_bFirstDone = false;

      m_dMinRadius = 0.0;
      m_dMaxRadius = 0.0;

      m_rectangleClient.null();


      m_bVoidTransfer = false;

      m_bFirstDone = true;

      //m_cx = 0;

      //m_cy = 0;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bNewLayout = false;

      m_bHelloRender = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;


   }


   render::~render()
   {

   }


   void render::full_render()
   {

      ::helloaxis::render::full_render();

      return;

      //size_i32 sizeNew = size_i32(m_cx, m_cy);

      //if (m_bNewLayout)
      //{

      //   synchronous_lock sl2(m_pmutexWork);
      //   synchronous_lock sl3(m_pmutexDraw);
      //   synchronous_lock sl4(m_pmutexSwap);

/*      //   bool bNewSize = m_pimage->width() != sizeNew.cx() || m_pimage->m_size.cy() != sizeNew.cy();

      //   m_bNewLayout = false;

      //   m_pimageWork = create_image(sizeNew);

      //   if (bNewSize)
      //   {

      //      m_pimageA = create_image(sizeNew);

      //      m_pimageB = create_image(sizeNew);

      //   }

      //}

      //hellobase_draw();
      //hellobase_render();

      ////if(m_bFirstDone)
      //{



      //}
      ////else
      //{
      //   //TRACE("XXX123546");
      //}

   }

   bool render::initialize_render(string strId)
   {

      return ::helloaxis::render::initialize_render(strId);

      ////      ::database::client::initialize_data_client(&papp->dataserver());

      //if (papp->m_strAppId == "app-core/flag")
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
      //   m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));
      //   m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
      //   m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      //}
      //else if (strId == "switcher")
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
      //   m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      //}
      //else
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
      //   m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));

      //}

      //int i = 1;

      //for (auto & bilbo : m_bilboa)
      //{

      //   m_pimpact->datastream()->get("bilbo." + bilbo.m_strPath, bilbo.m_bNew);

      //   i++;

      //}

      //defer_update_bilbo();


      //return true;

   }


   i32 render::run()
   {

      return helloaxis::render::run();

      //::parallelization::set_priority(::e_priority_time_critical);

      //::frequency frequencyFramesPerSecond = m_pimpact->get_wnd()->m_pimpl.cast < ::user::interaction_impl >()->m_frequencyFramesPerSecond;

      //double dPeriod = 1000.0 / frequencyFramesPerSecond;

      //dPeriod = minimum(maximum(1.0, dPeriod), 1000.0);

      ////#ifdef WINDOWS_DESKTOP
      ////
      ////      HANDLE timer;
      ////
      ////      LARGE_INTEGER li = {};
      ////
      ////      timer = CreateWaitableTimer(nullptr, true, nullptr);
      ////
      ////#endif

      //double_array daFrame;

      //index iLastFrameId;

      //iLastFrameId = (index) (::get_millis() / dPeriod);

      //index iFrameId;

      //while (task_get_run())
      //{

      //   try
      //   {

      //      if (m_bHelloRender)
      //      {

      //         full_render();

      //      }

      //      double dNow = ::get_millis();

      //      double dWait = dPeriod - fmod(dNow + dPeriod / 3.0, dPeriod);

      //      iFrameId = (index)(dNow / dPeriod);

      //      ::count cLost = iFrameId - iLastFrameId - 1;

      //      if (cLost < 0)
      //      {

      //         dWait = dPeriod;

      //      }

      //      sleep(::time(dWait));

      //      iLastFrameId = iFrameId;

      //      if (m_bHelloRender)
      //      {

      //         for (index i = 0; i < daFrame.get_size(); i++)
      //         {

      //            if (dNow - daFrame[i] >= 1000.0)
      //            {

      //               daFrame.erase_at(i);

      //            }
      //            else
      //            {

      //               break;

      //            }

      //         }

      //      }

      //      m_dRenderFps = double(daFrame.get_size());

      //      daFrame.add(dNow);

      //   }
      //   catch (...)
      //   {

      //      break;

      //   }

      //}

      //return 0;

   }


   void render::helloaura_render()
   {

      {

         synchronous_lock synchronouslock(m_pmutexWork);

/*         ::image_pointer pimage = m_pimageWork;

/*         if (pimage->area() <= 0)
            return;

/*         pimage->Fill(0, 0, 0, 0);

/*         helloaura_render(pimage->g());


      }

   }

   void render::helloaura_render(::draw2d::graphics_pointer & pgraphics)
   {



      //   if(m_bLite)
      {

         helloaura_render_lite_impact(pgraphics);

      }
      //   else
      //   {
      //
      //      helloaura_render_full_impact(pimage->g());
      //
      //   }

   }


   void render::helloaura_draw()
   {

      if (m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_pimageWork);

      synchronous_lock slDraw(m_pmutexDraw);

      if (m_bDib1)
      {

         m_pimageOut = m_pimageA;
         m_pimageWork->m_p = m_pimageB->m_p;

      }
      else
      {

         m_pimageOut = m_pimageB;
         m_pimageWork->m_p = m_pimageA->m_p;

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

   void render::helloaura_render_lite_impact(::draw2d::graphics_pointer & pgraphics)
   {

      return ::helloaura::render::helloaura_render_lite_impact(pgraphics);

//      if (m_pimageWork->area() <= 0)
//         return;
//
//      ::get_task()->m_bThreadToolsForIncreasedFps = true;
//
//      ::rectangle_i32 rectangleClient;
//
//      rectangleClient.left = 0;
//
//      rectangleClient.top = 0;
//
//      rectangleClient.right = m_cx;
//
//      rectangleClient.bottom = m_cy;
//
//      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//      //pgraphics->FillSolidRect(rectangleClient,argb(0, 0, 0, 0));
//
//      //      i32 iCount = 30;
//
//      auto pbrushText = __create < ::draw2d::brush > ();
//
//      double T = 2.3;
//
////      if (false)
////      {
////
////         T = 2.3;
////
////      }
////      else
//      if (m_bAlternate)
//      {
//
//         T = 1.2;
//
//      }
//      else
//      {
//
//         T = 2.3;
//
//      }
//
//      double t= ::time::now() / 1000.0;
//
//      double w = 2.0 * 3.1415 / T;
//
//      double r = (tri(w * t) + 1.0) / 2.0;
//
//      ::size_i32 size;
//
//      string strHelloBase;
//
//      {
//
//         synchronous_lock slText(m_pmutexText);
//
//         strHelloBase = get_helloaura().c_str(); // rationale : string allocation fork *for parallelization*
//
//      }
//
//      pgraphics->set_font(m_pfont);
//
//      size = pgraphics->get_text_extent(strHelloBase);
//
//      m_cxTarget = int (size.cx() * 1.2);
//      m_cyTarget = int (size.cy() * 1.2);
//
//      if (!m_bFirstDone)
//      {
//
//         if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//         {
//
//            sleep(47_ms);
//
//         }
//         else
//         {
//
//            m_cxCache1 = m_cxTarget;
//
//            m_cyCache1 = m_cyTarget;
//
//            {
//
//               synchronous_lock slDib(m_pmutexDib);
//
//               if (m_pimage->initialize(m_cxCache1, m_cyCache1, int (m_dMaxRadius)))
//               {
//
//                  //m_pimage->defer_realize(pgraphics);
//
//                  m_pimage->Fill(0, 0, 0, 0);
//
//                  m_pimage->g()->set_font(m_pfont);
//
//                  m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);
//
//                  m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//                  pbrushText->create_solid(argb(255, 255, 255, 255));
//
//                  m_pimage->g()->SelectObject(pbrushText);
//
//                  m_pimage->g()->text_out((m_cxCache1 - size_i32->cx()) / 2, (m_cyCache1 - size_i32->cy()) / 2, strHelloBase);
//
//                  m_pimage->map();
//
/*                  psystem->imaging().spread(m_pimage->g(), ::point_i32(), m_pimage->get_size(), m_pimage->g(), ::point_i32(), int (m_dMaxRadius));
//
//                  m_pimage->blur();
//
/*                  m_pimageTemplate = create_image(m_pimage->get_size());
//
//                  m_pimageTemplate->Fill(0, 0, 0, 0);
//
//                  m_pimageTemplate->channel_copy(::color::e_channel_alpha, ::color::e_channel_green, m_pimage);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      {
//
//         synchronous_lock slText(m_pmutexText);
//
//         if (strHelloBase != get_helloaura() || m_cxCache1 != m_cxTarget || m_cyCache1 != m_cyTarget || m_pimageTemplate->area() <= 0)
//            return;
//
//      }
//
//
//
//
//      ::color::color ca;
//
//
////      if (false)
////      {
////
////         double dPeriod = (5000) * 11;
////
////         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
////
////      }
////      else if (m_bAlternate)
//      if(m_bAlternate)
//      {
//
//         double dPeriod = (5100) * 8;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else
//      {
//
//         double dPeriod = (4900) * 11;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.23, 0.84);
//
//      }
//
//      if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//      {
//
//         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR,ca->m_iG,ca->m_iB, 140 + 220 * r);
//         //m_pimageTemplate->set_rgb_pre_alpha(ca->m_iR, ca->m_iG, ca->m_iB);
//
//         m_pimageTemplate2->tint(m_pimageTemplate, ca->m_iR, ca->m_iG, ca->m_iB);
//
//      }
//
//      pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//      psystem->imaging().bitmap_blend(pgraphics,
//                                             point_i32((m_cx - m_pimageTemplate2->width()) / 2, (m_cy - m_pimageTemplate2->height()) / 2)
//                                             , m_pimageTemplate2->m_size,
//                                             m_pimageTemplate2->get_graphics(), ::point_i32(), byte (128 + (255 - 128) * r));
//
//      //pgraphics->from(rectangleClient.top_left(),m_pimageTemplate, ::point_i32(), rectangleClient>si);
//
//      pgraphics->set_font(m_pfont);
//
//      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);
//
//      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//      {
//
//         pbrushText->create_solid(argb(255, ca.m_iR, ca.m_iG, ca.m_iB));
//
//      }
//      else
//      {
//
//         if (m_bAlternate)
//         {
//
//            pbrushText->create_solid(argb(255, 184, 184, 177));
//
//         }
//         else
//         {
//
//            pbrushText->create_solid(argb(255, 255, 255, 255));
//
//         }
//
//      }
//
//      pgraphics->SelectObject(pbrushText);
//
//      //if(!m_bAlternate)
//      {
//
//         pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBase);
//
//      }
//      //      pgraphics->FillSolidRect(200,00,100,100,argb(128,128,128,255));
//
//      //    pgraphics->FillSolidRect(200,200,100,100,argb(128,128,128,0));
//
//      if(!m_bFirstDone)
//      {
//
//         synchronous_lock slText(m_pmutexText);
//
//         if (strHelloBase == get_helloaura() && m_cxCache1 == m_cxTarget && m_cyCache1 == m_cyTarget)
//         {
//
//            m_bFirstDone = true;
//
//         }
//
//      }

   }


   void render::helloaura_render_full_impact(::draw2d::graphics_pointer & pgraphics)
   {

      return ::helloaura::render::helloaura_render_full_impact(pgraphics);

//      if (m_pimageWork->area() <= 0)
//         return;
//
//      ::rectangle_i32 rectangleClient;
//
//      rectangleClient.left = 0;
//
//      rectangleClient.top = 0;
//
//      rectangleClient.right = m_cx;
//
//      rectangleClient.bottom = m_cy;
//
//      if (rectangleClient.area() <= 0)
//         return;
//
//      //      i32 iCount = 30;
//
//      auto pbrushText = __create < ::draw2d::brush > ();
//
//      double T = 2.3;
//
////      if (false)
////      {
////
////         T = 2.3;
////
////      }
////      else
//      if (m_bAlternate)
//      {
//
//         T = 1.2;
//
//      }
//      else
//      {
//
//         T = 2.3;
//
//      }
//
//      double t= ::time::now() / 1000.0;
//
//      double w = 2.0 * 3.1415 / T;
//
//      double r = (tri(w * t) + 1.0) / 2.0;
//
//      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;
//
//      ::color::color ca;
//
////      if (false)
////      {
////
////         double dPeriod = (5000) * 11;
////
////         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
////
////      }
////      else
////
//      if (m_bAlternate)
//      {
//
//         double dPeriod = (5100) * 8;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else
//      {
//
//         double dPeriod = (4900) * 11;
//
//         ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.23, 0.84);
//
//      }
//
//
//
//      pgraphics->set_font(m_pfont);
//
//      string strHelloBase = get_helloaura();
//
//      ::size_i32 size = pgraphics->get_text_extent(strHelloBase);
//
//      m_cxTarget = int(size.cx() * 1.2);
//      m_cyTarget = int(size.cy() * 1.2);
//
//      {
//
//         synchronous_lock slDib(m_pmutexDib);
//
//         if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//         {
//
//            if (m_dMinRadius > 3.0)
//            {
//
//               m_pimage->initialize(m_cxTarget, m_cyTarget, int (dBlur));
//
//            }
//            else
//            {
//
//               m_pimage->initialize(m_cxTarget, m_cyTarget, 5);
//
//            }
//
//            m_pimage->defer_realize(pgraphics);
//
//            m_pimage->Fill(0, 0, 0, 0);
//
//            m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);
//
//            m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//            pbrushText->create_solid(argb(255, 255, 255, 255));
//
//            m_pimage->g()->SelectObject(pbrushText);
//
//            m_pimage->g()->set_font(m_pfont);
//
//            m_pimage->g()->text_out((m_cx - size_i32->cx()) / 2, (m_cy - size_i32->cy()) / 2, strHelloBase);
//
//            if (m_dMinRadius > 3.0)
//            {
//
//               m_pimage->blur(m_cx, m_cy);
//
//            }
//            else
//            {
//
//               for (i32 i = 0; i < dBlur * 2; i++)
//               {
//
//                  m_pimage->blur(m_cx, m_cy);
//
//               }
//
//            }
//
//            if (!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//            {
//
//               m_pimage->channel_copy(::color::e_channel_alpha, ::color::e_channel_green);
//
//               m_pimageTint->tint(m_pimage, ca->m_iR, ca->m_iG, ca->m_iB);
//
//            }
//
//         }
//
//         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//         pgraphics->BitBlt(rectangleClient, m_pimageTint->get_graphics());
//
//      }
//
//      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);
//
//      if (psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
//      {
//
//         pbrushText->create_solid(argb(255, ca.m_iR, ca.m_iG, ca.m_iB));
//
//      }
//      else
//      {
//
//         if (m_bAlternate)
//         {
//
//            pbrushText->create_solid(argb(255, 184, 184, 177));
//
//         }
//         else
//         {
//
//            pbrushText->create_solid(argb(255, 255, 255, 255));
//
//         }
//
//      }
//
//      pgraphics->SelectObject(pbrushText);
//
//      pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBase);
//
//      byte a, R, g, b;
//
//      if (m_bAlternate)
//      {
//         a = 184;
//         R = 177;
//         g = 77;
//         b = 184;
//      }
//      else
//      {
//         a = 184;
//         R = 77;
//         g = 184;
//         b = 84;
//      }
//
//#if 0
//      if (papp->m_iErrorAiFont == 0)
//      {
//
//         synchronous_lock slAiFont(&papp->m_pmutexAiFont);
//
//         FT_Face & face = (FT_Face &)papp->m_faceAi;
//
//         i32 error;
//
//         error = FT_Set_Char_Size(face,        /* handle to face object */
//                                  0,          /* char_width in 1/64th of points */
//                                  800 * 64,          /* char_height in 1/64th of points */
//                                  72,         /* horizontal device resolution */
//                                  72);         /* vertical device resolution */
//
//         if (error == 0)
//         {
//
//            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */
//
//            if (error == 0)
//            {
//
//               i64 iChar = unicode_index(unicode_to_utf8(L"愛"));
//
//               i32 glyph_index = FT_Get_Char_Index(face, (i32)iChar);
//
//               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */
//
//               if (error == 0)
//               {
//
//                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */
//
//                  if (error == 0)
//                  {
//
//                     ::image_pointer & pimage = m_pimageAi1;
//
/*                     pimage = create_image({face->glyph->bitmap.width,  face->glyph->bitmap.rows});
//
//                     pimage->realize(pgraphics);
//
//                     draw_freetype_bitmap(pimage->m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);
//
//                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
/*                     pgraphics->StretchBlt(0, 0, pimage->width() / 40, pimage->height() / 40, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());
//
/*                     pgraphics->StretchBlt(0, m_cy - pimage->height() / 40, pimage->width() / 40, pimage->height() / 40, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());
//
//                  }
//
//               }
//
//            }
//
//         }
//
//
//         error = FT_Set_Char_Size(face,        /* handle to face object */
//                                  0,          /* char_width in 1/64th of points */
//                                  640 * 64,          /* char_height in 1/64th of points */
//                                  72,         /* horizontal device resolution */
//                                  72);         /* vertical device resolution */
//
//         if (error == 0)
//         {
//
//            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */
//
//            if (error == 0)
//            {
//
//               i64 iChar = unicode_index(unicode_to_utf8(L"愛"));
//
//               i32 glyph_index = FT_Get_Char_Index(face, (i32)iChar);
//
//               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */
//
//               if (error == 0)
//               {
//
//                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */
//
//                  if (error == 0)
//                  {
//
//                     ::image_pointer & pimage = m_pimageAi2;
//
/*                     pimage = create_image({face->glyph->bitmap.width,  face->glyph->bitmap.rows});
//
//                     pimage->realize(pgraphics);
//
//                     draw_freetype_bitmap(pimage->m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);
//
//                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32, 0, pimage->width() / 32, pimage->height() / 32, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());
//
/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32, m_cy - pimage->height() / 32, pimage->width() / 32, pimage->height() / 32, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      }
//
//#endif
//
//      if (strHelloBase == get_helloaura() && m_cx == m_rectangleClient.width() && m_cy == m_rectangleClient.height())
//      {
//
//         m_bFirstDone = true;
//
//      }

   }


   void render::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      return ::helloaura::render::_006OnDraw(pgraphics);

      //::rectangle_i32 rectangleClient;

      //rectangleClient.left = 0;
      //rectangleClient.top = 0;
      //rectangleClient.right = m_cx;
      //rectangleClient.bottom = m_cy;

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      //int period = 5000;
      //int border = 2500;
      //int t;

      //try
      //{

      //   if (m_stra23.get_size() > 0 || m_strLast23.has_char() || m_strCurrent23.has_char())
      //   {

      //      if (!m_bFirst23)
      //      {
      // auto m_tick23 = ::time::now();
      //         m_uiCurrent23 = 0;
      //         m_strLast23.empty();
      //         m_strCurrent23.empty();
      //         m_bFirst23 = true;
      //         t = 0;
      //      }
      //      else
      //      {

      //         t = (m_tick23.elapsed());

      //         u32 uiCurrent23 = (t) / period;

      //         t %= period;

      //         if (m_uiCurrent23 != uiCurrent23)
      //         {

      //            m_strLast23 = m_strCurrent23;

      //            // pulse!!
      //            if (m_stra23.get_size() <= 0)
      //            {

      //               m_strCurrent23.empty();

      //            }
      //            else
      //            {

      //               m_strCurrent23 = m_stra23[uiCurrent23 % m_stra23.get_size()];

      //            }

      //            m_uiCurrent23 = uiCurrent23;

      //         }

      //      }

      //      if (t < border && m_strLast23 != m_strCurrent23)
      //      {

      //         byte uchAlpha = 255 * t / border;

      //         if (m_strLast23.has_char())
      //         {

      //            synchronous_lock synchronouslock(m_pmutexDib23);

      //            auto & pimage = image23(m_strLast23);

      //            if (pimage->m_eload == ::draw2d::load_ok)
      //            {

      //               pimage->defer_update();

/*      //               psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), pimage->get_size(), pimage->get_graphics(), ::point_i32(), 255 - uchAlpha);

      //            }

      //         }

      //         if (m_strCurrent23.has_char())
      //         {

      //            synchronous_lock synchronouslock(m_pmutexDib23);

      //            auto & pimage = image23(m_strCurrent23);

      //            if (pimage->m_eload == ::draw2d::load_ok)
      //            {

      //               pimage->defer_update();

/*      //               psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), pimage->get_size(), pimage->get_graphics(), ::point_i32(), uchAlpha);

      //            }

      //         }

      //      }
      //      else if (m_strCurrent23.has_char())
      //      {

      //         synchronous_lock synchronouslock(m_pmutexDib23);

      //         auto & pimage = image23(m_strCurrent23);

      //         if (pimage->m_eload == ::draw2d::load_ok)
      //         {

      //            pimage->defer_update();

/*      //            pgraphics->BitBlt(0, 0, pimage->width(), pimage->height(), pimage->get_graphics(), 0, 0);

      //         }

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

      //if (papp->m_etype == application::type_mili)
      //{

      //   {

      //      string strHelloBase;

      //      {

      //         synchronous_lock slText(&m_pimpact->m_pmutexText);

      //         strHelloBase = m_pimpact->get_processed_helloaura().c_str();

      //      }

      //      if (m_bNewLayout)
      //      {

      //         float fHeight = 100.0;

      //         auto pfont = __create < ::write_text::font > ();

      //         pfont->create_pixel_font(pnode->font_name(e_font_sans), fHeight, e_font_weight_bold);

      //         pgraphics->set_font(font);

      //         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      //         ::size_i32 size = pgraphics->get_text_extent(strHelloBase);

      //         double ratey = fHeight * 0.84 / size.cy();

      //         pfont->create_pixel_font(pnode->font_name(e_font_sans), minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()), e_font_weight_bold);

      //         m_pfont = font;

      //         m_bNewLayout = false;

      //      }

      //      ::color::color ca;

      //      double dPeriod = (500) * 11;

      //      ca.set_hls(fmod(__double(::get_tick()), dPeriod) / dPeriod, 0.49, 0.84);

      //      auto pbrush = __create < ::draw2d::brush >();

      //      pbrush->create_solid(argb(255, ca.m_iR, ca.m_iG, ca.m_iB));

      //      pgraphics->SelectObject(brush);

      //      pgraphics->set_font(m_pfont);

      //      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      //      ::size_i32 size = pgraphics->get_text_extent(strHelloBase);

      //      pgraphics->text_out((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBase);

      //      return;

      //   }

      //}

      ////::u32 dw= ::time::now();

      //if (m_bFast || !m_bFirstDone || m_timeLastFast.elapsed() < m_timeFastAnime)
      //{

      //   synchronous_lock sl1(m_pimpact->get_wnd()->synchronization());

      //   synchronous_lock slDraw(m_pmutexDraw);

      //   if (m_bFast || m_pimageFast->is_null())
      //   {

      //      m_bFast = false;

      //      {

      //         synchronous_lock slText(&m_pimpact->m_pmutexText);

      //         helloaura_fast_render(m_pimpact->get_processed_helloaura());

      //      }

      //      m_bFirstDone = false;

      //   }

      //   if (m_bFast || !m_bFirstDone)
      //   {

      //      m_timeLastFast= ::time::now();

      //   }

      //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //   pgraphics->BitBlt(::point_i32(), size_i32(m_cx, m_cy), m_pimageFast->get_graphics());

      //   //pgraphics->FillSolidRect(400,400,100,100,argb(128,0,0,128));

      //   m_pimpact->m_bOkPending = true;

      //   return;

      //}

      //if (m_pimpact->m_bOkPending)
      //{

      //   m_pimpact->m_bOkPending = false;

      //   m_timeLastOk= ::time::now();

      //}

      //::image_pointer pimage = nullptr;

      //::image_pointer pimageFast = m_pimageFast;

      //synchronous_lock synchronouslock(m_pmutexDraw);

      //synchronous_lock slSwap(m_pmutexSwap);

      //pimage = m_pimageOut;

      //if (pimage->area() <= 0)
      //   return;

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //if (m_timeLastOk.elapsed() < m_timeAnime)
      //{

      //   byte uchAlpha;

      //   uchAlpha = byte(maximum(0, minimum(255, (m_timeLastOk.elapsed()) * 255 / m_timeAnime)));

/*      //   psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), pimage->get_size(), pimage->g(), ::point_i32(), uchAlpha);

      //   psystem->imaging().bitmap_blend(pgraphics, ::point_i32(), imageFast.get_size(), imageFast.get_graphics(), ::point_i32(), 255 - uchAlpha);

      //}
      //else
      //{

/*      //   pgraphics->from(::point_i32(), pimage->get_size(), pimage->g(), ::point_i32());

      //}

   }


   //::image_pointer & render::image23(string strImage)
   //{

   //   auto & pimage = m_mapDib23[strImage];

   //   if (pimage->is_null())
   //   {

   //      pimage->create(this);

   //   }

   //   if (pimage->m_eload == ::draw2d::load_none)
   //   {

   //      pimage->m_eload = ::draw2d::load_going_to_load;

   //      ::fork(get_app(), [=]()
   //      {

   //         if (!m_mapDib23[strImage].load_image(strImage, true, true))
   //         {

   //            throw ::exception(::exception("Failed to load \"" + strImage + "\""));

   //         }

   //      });

   //   }

   //   return pimage;

   //}


   //void render::defer_update_bilbo()
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   for (auto & bilbo : m_bilboa)
   //   {

   //      if (bilbo.m_bNew && !bilbo.m_b)
   //      {

   //         m_stra23.add_unique(bilbo.m_strPath);

   //         bilbo.m_b = true;

   //         m_pimpact->datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);

   //      }
   //      else if (!bilbo.m_bNew && bilbo.m_b)
   //      {

   //         m_stra23.erase(bilbo.m_strPath);

   //         bilbo.m_b = false;

   //         m_pimpact->datastream()->set("bilbo." + bilbo.m_strPath, bilbo.m_b);

   //      }

   //   }

   //   for (auto str23 : m_stra23)
   //   {

   //      synchronous_lock synchronouslock(m_pmutexDib23);

   //      image23(str23);

   //   }

   //}

   //bool render::in_anime()
   //{
   //   if (m_bFast || m_timeLastFast.elapsed() < m_timeFastAnime)
   //      return true;
   //   if (m_timeLastOk.elapsed() < m_timeAnime)
   //      return true;
   //   return false;
   //}

   //void render::helloaura_fast_render(const ::string & strHelloBase)
   //{

   //   if (m_cx <= 0 || m_cy <= 0)
   //      return;

   //   synchronous_lock slDraw(m_pmutexDraw);

   //   ::size_i32 sizeNew = ::size_i32(m_cx, m_cy);

   //   bool bNewSize = m_pimageFast->width() != sizeNew->cx() || m_pimageFast->height() != sizeNew->cy();

   //   if (bNewSize)
   //   {

   //      m_pimageFast = create_image(sizeNew);

   //   }

   //   m_pimageFast->Fill(0, 0, 0, 0);

   //   ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

   //   float fHeight = 100.0;

   //   auto pfont = __create < ::write_text::font > ();

   //   pfont->create_pixel_font(m_pimpact->m_strFont, fHeight, e_font_weight_bold);

   //   pgraphics->set_font(font);

   //   pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

   //   ::size_i32 size = pgraphics->get_text_extent(strHelloBase);

   //   double ratey = fHeight * 0.84 / size.cy();

   //   pfont->create_pixel_font(m_pimpact->m_strFont, minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()), e_font_weight_bold);

   //   m_dMinRadius = maximum(1.0, minimum(m_cy * ratey, m_cx * size.cy() * ratey / size.cx()) / 46.0);

   //   m_dMaxRadius = m_dMinRadius * 2.3;

   //   m_pfont = font;

   //   pgraphics->set_font(m_pfont);

   //   size = pgraphics->get_text_extent(strHelloBase);

   //   auto ppath = __create < ::draw2d::path > ();

   //   ppath->m_bFill = false;

   //   ppath->add_string((m_cx - size.cx()) / 2, (m_cy - size.cy()) / 2, strHelloBase, m_pfont);

   //   auto ppen = __create < ::draw2d::pen > ();

   //   ppen->create_solid(1.0, argb(255, 90, 90, 80));

   //   auto ppenW = __create < ::draw2d::pen > ();

   //   ppenW->create_solid(3.0, argb(84, 255, 255, 255));

   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //   //      pgraphics->FillSolidRect((m_cx - size.cx()) / 2,(m_cy - size.cy()) / 2, 100, 100, argb(255,255,200,240));

   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   pgraphics->draw(path, ppenW);
   //   pgraphics->draw(ppath, ppen);
   //   //pgraphics->FillSolidRect(00,00,100,100,argb(128,128,0,0));

   //}


} // namespace hellobase



