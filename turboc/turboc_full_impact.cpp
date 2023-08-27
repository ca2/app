#include "framework.h"
#include <math.h>


namespace turboc
{


   full_impact::full_impact(::particle * pparticle):
      ::object(pparticle),
      impact(pparticle)
   {

      m_bLite = false;

   }


   full_impact::~full_impact()
   {

   }


   void full_impact::assert_ok() const
   {

      ::aura::impact::assert_ok();

   }


   void full_impact::dump(dump_context & dumpcontext) const
   {

      ::aura::impact::dump(dumpcontext);

   }


   void full_impact::install_message_handling(::message::dispatch * pdispatch)
   {

      impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(e_message_create,pdispatch,this,&full_impact::on_message_create);

   }


   void full_impact::on_message_create(signal_details * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      //if(papp->m_etype == application::type_normal)
      //{

      //   papp->load_ai_font();

      //   __begin_thread(get_app(),&thread_proc_render,this,::e_priority_normal,0,0,NULL);

      //}

   }


   void full_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      UNREFERENCED_PARAMETER(ptopic);
   }


   void full_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      impact::_001OnDraw(pgraphics);

   }

/*   void full_impact::turboc_render(::image * pimage)
   {

      turboc_render_full_impact(pgraphics);

   }


/*   void impact::turboc_render_full_impact(::image * pimage)
   {

      if(m_pimageWork->area() <= 0)
         return;

      ::rectangle_i32 rectangleX;

      rectangleX.left = 0;

      rectangleX.top = 0;

      rectangleX.right = m_cx;

      rectangleX.bottom = m_cy;

      if(rectangleX.area() <= 0)
         return;

//      i32 iCount = 30;

      ::draw2d::brush_pointer pbrushText(this_create);

      double T = 2.3;

      if(false)
      {

         T = 2.3;

      }
      else if(m_bAlternate)
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

      if(false)
      {

         double dPeriod = (5000) * 11;

         ca.set_hls(fmod(::get_tick(),dPeriod) / dPeriod,0.49,0.84);

      }
      else if(m_bAlternate)
      {

         double dPeriod = (5100) * 8;

         ca.set_hls(fmod(::get_tick(),dPeriod) / dPeriod,0.49,0.84);

      }
      else
      {

         double dPeriod = (4900) * 11;

         ca.set_hls(fmod(::get_tick(),dPeriod) / dPeriod,0.23,0.84);

      }

      pgraphics->set_font(m_pfont);

      string strHelloMultiverse = get_processed_turboc();

      ::size_i32 size = pgraphics->get_text_extent(strHelloMultiverse);

      if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         if(m_dMinRadius > 3.0)
         {

/*            m_pimage->initialize(m_cx,m_cy,dBlur);

         }
         else
         {

/*            m_pimage->initialize(m_cx,m_cy,5);

         }

/*         m_pimage->defer_realize(pgraphics);

/*         m_pimage->Fill(0,0,0,0);

/*         m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

/*         m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pbrushText->create_solid(argb(255,255,255,255));

/*         m_pimage->g()->SelectObject(pbrushText);

/*         m_pimage->g()->set_font(m_pfont);

/*         m_pimage->g()->text_out((m_cx - size_i32->cx()) / 2,(m_cy - size_i32->cy()) / 2,strHelloMultiverse);

         if(m_dMinRadius > 3.0)
         {

/*            m_pimage->blur(m_cx,m_cy);

         }
         else
         {

            for(i32 i = 0; i < dBlur * 2; i++)
            {

/*               m_pimage->blur(m_cx,m_cy);

            }

         }

         if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

/*            m_pimage->channel_copy(::color::e_channel_opacity,::color::e_channel_green);

/*            m_pimage->set_rgb(ca->m_iR,ca->m_iG,ca->m_iB);

         }

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

/*         pgraphics->BitBlt(rectangleX,m_pimage->g());

      }

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if(psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         pbrushText->create_solid(argb(255,ca.m_iR,ca.m_iG,ca.m_iB));

      }
      else
      {

         if(m_bAlternate)
         {

            pbrushText->create_solid(argb(255,184,184,177));

         }
         else
         {

            pbrushText->create_solid(argb(255,255,255,255));

         }

      }

      pgraphics->SelectObject(pbrushText);

      pgraphics->text_out((m_cx - size.cx()) / 2,(m_cy - size.cy()) / 2,strHelloMultiverse);

      ::u8 a,R,g,b;

      if(m_bAlternate)
      {
         a = 184;
         R = 177;
         g = 77;
         b = 184;
      }
      else
      {
         a = 184;
         R = 77;
         g = 184;
         b = 84;
      }

#if 0
      if(papp->m_iErrorAiFont == 0)
      {

         synchronous_lock slAiFont(&papp->m_pmutexAiFont);

         FT_Face & face = (FT_Face &)papp->m_faceAi;

         i32 error;

         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  800 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               i64 iChar =  unicode_index(unicode_to_utf8(L"Love"));

               i32 glyph_index = FT_Get_Char_Index(face,(i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi1;

/*                     pimage = create_image({face->glyph->bitmap.width, face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(0,0,pimage->width() / 40,pimage->height() / 40,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

/*                     pgraphics->StretchBlt(0,m_cy - pimage->height() / 40,pimage->width() / 40,pimage->height() / 40,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

                  }

               }

            }

         }


         error = FT_Set_Char_Size(face,        /* handle to face object */
                                  0,          /* char_width in 1/64th of points */
                                  640 * 64,          /* char_height in 1/64th of points */
                                  72,         /* horizontal device resolution */
                                  72);         /* vertical device resolution */

         if(error == 0)
         {

            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

            if(error == 0)
            {

               i64 iChar =  unicode_index(unicode_to_utf8(L"Love"));

               i32 glyph_index = FT_Get_Char_Index(face,(i32)iChar);

               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */

               if(error == 0)
               {

                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */

                  if(error == 0)
                  {

/*                     ::image_pointer & pimage = m_pimageAi2;

/*                     pimage = create_image({face->glyph->bitmap.width, face->glyph->bitmap.rows});

/*                     pimage->realize(pgraphics);

/*                     draw_freetype_bitmap(pimage->m_p,0,0,&face->glyph->bitmap,0,0,a,R,g,b);

                     pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32,0,pimage->width() / 32,pimage->height() / 32,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

/*                     pgraphics->StretchBlt(m_cx - pimage->width() / 32,m_cy - pimage->height() / 32,pimage->width() / 32,pimage->height() / 32,pimage->get_graphics(),0,0,pimage->width(),pimage->height());

                  }

               }

            }

         }

      }

#endif

      GetClientRect(rectangleX);

      if(strHelloMultiverse == get_processed_turboc() && m_cx == rectangleX.width() && m_cy == rectangleX.height())
      {

         m_bFirstDone = true;

      }

   }


} // namespace turboc

















