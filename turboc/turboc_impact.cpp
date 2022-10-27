#include "framework.h"
#include <math.h>



//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;

void rainbow_main();


namespace turboc
{


   impact::impact(::particle * pparticle):
      ::object(pparticle),
      m_pimage1,
      m_pimage2,

      m_pimageColor,
      m_pimageWork,
      m_pimageTemplate,
      m_pimageFast,
      m_pfont(this_create),




      m_pimageAi1,
      m_pimageAi2,
      m_pimageImage,
      m_pimagePost
   {

      m_bLite = true;

      m_bVoidTransfer =  false;

      m_durationAnime = 2000;

      m_bNewLayout = false;

      m_durationFastAnime = 584;

      m_bOkPending = true;

      m_cx = 0;

      m_cy = 0;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_bHelloRender = true;

      m_bFastOnEmpty = true;

      m_bFirstDone = true;

      m_dMinRadius = 1.0;

      m_dMaxRadius = 2.0;

      m_bAlternate = false;

      m_bFast = true;

      m_cxCache1 = 0;

      m_cyCache1 = 0;

   }

   impact::~impact()
   {
   }

   void impact::assert_ok() const
   {
      ::aura::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }

   void impact::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(e_message_create,pdispatch,this,&impact::on_message_create);

   }


   void impact::on_message_create(signal_details * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      if(papp->m_etype == application::type_normal)
      {

         if(!m_bLite)
         {

            papp->load_ai_font();

         }

         __begin_thread(get_app(),&thread_proc_render,this,::e_priority_normal,0,0,NULL);

      }

      papp->start_main();


   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_strNewHelloMultiverse.is_empty())
      {

         if(m_bFastOnEmpty)
         {

            m_bFast = true;

         }

         return;

      }

      m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         ::turboc::impact::on_layout(pgraphics);

      }
      else
      {

         on_layout(pgraphics);

      }

   }




   void impact::on_update(::aura::impact * pSender, e_update eupdate, object* pupdate)
   {
      __UNREFERENCED_PARAMETER(ptopic);
   }

   bool impact::in_anime()
   {
      if(m_bFast || m_durationLastFast.elapsed() < m_durationFastAnime)
         return true;
      if(m_durationLastOk.elapsed() < m_durationAnime)
         return true;
      return false;
   }


/*   void impact::_006OnDraw(::image * pimage)
   {

      ::rectangle_i32 rectangleClient;

      GetClientRect(rectangleClient);

/*      pgraphics->BitBlt(rectangleClient,papp->m_pcontext->m_pimage->g());


      if(papp->m_etype == application::type_mili)
      {

         string strHelloMultiverse = get_processed_turboc();

         if(m_bNewLayout)
         {

            float fHeight = 100.0;




            m_pfont->create_pixel_font(pnode->font_name(e_font_sans),fHeight,e_font_weight_bold);

            pgraphics->set_font(m_pfont);

            pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            ::size_i32 size = pgraphics->get_text_extent(strHelloMultiverse);

            double ratey = fHeight * 0.84 / size.cy;

            m_pfont->create_pixel_font(pnode->font_name(e_font_sans),minimum(m_cy * ratey,m_cx * size.cy * ratey / size.cx),e_font_weight_bold);

            //m_dMinRadius = maximum(1.0,m_pfont->m_dFontSize / 23.0);

            //m_dMaxRadius = m_dMinRadius * 2.3;

            //m_pimageFast->Fill(0,0,0,0);

            //pgraphics->set_font(m_pfont);

            //size = pgraphics->get_text_extent(strHelloMultiverse);

            //::draw2d::path_pointer path(this_create);

            //ppath->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_pfont);

            //::draw2d::pen_pointer pen(this_create);

            //ppen->create_solid(1.0,argb(255,84 / 2,84 / 2,77 / 2));

            //pgraphics->FillSolidRect(0,0,m_cx,m_cy,argb(0,0,0,0));

            //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            //pgraphics->draw(path,pen);

            m_bNewLayout = false;

         }


         ::color::color ca;

         double dPeriod = (500) * 11;

         ca.set_hls(fmod(::get_tick(),dPeriod) / dPeriod,0.49,0.84);

         ::draw2d::brush_pointer brush(this_create);

         pbrush->create_solid(argb(255,ca.m_iR,ca.m_iG,ca.m_iB));

         pgraphics->SelectObject(brush);

         pgraphics->set_font(m_pfont);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         ::size_i32 size = pgraphics->get_text_extent(strHelloMultiverse);

         pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

         return;

      }

      if(m_bFast || !m_bFirstDone || m_durationLastFast.elapsed() < m_durationFastAnime)
      {

         synchronous_lock slDraw(m_pmutexDraw);

         if(m_bFast || m_pimageFast->is_null())
         {

            m_bFast = false;

            turboc_fast_render(get_processed_turboc());

            m_bFirstDone = false;

         }

         if(m_bFast || !m_bFirstDone)
         {

            m_durationLastFast= ::duration::now();

         }

         pgraphics->BitBlt(::point_i32(),size_i32(m_cx,m_cy),m_pimageFast->get_graphics());

         //pgraphics->FillSolidRect(400,400,100,100,argb(128,0,0,128));

         m_bOkPending = true;

         return;

      }

      if(m_bOkPending)
      {

         m_bOkPending = false;

         m_durationLastOk= ::duration::now();

      }

/*      ::image_pointer pimage = NULL;

      ::image_pointer pimageFast = m_pimageFast;

      synchronous_lock synchronouslock(m_pmutexDraw);

      synchronous_lock slSwap(m_pmutexSwap);

      if(m_bDib1)
      {

/*         pimage = m_pimage1;

         //         imageFast = m_pimageFast1;

      }
      else
      {

/*         pimage = m_pimage2;

         //         imageFast = m_pimageFast2;

      }

/*      if(pimage->area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if(m_durationLastOk.elapsed() < m_durationAnime)
      {

         byte uchAlpha = maximum(0,minimum(255,(m_durationLastOk.elapsed()) * 255 / m_durationAnime));

         ::rectangle_i32 rectangleClient;

         GetClientRect(rectangleClient);

         //pgraphics->FillSolidRect(rectangleClient,0);

/*         pdraw2d->imaging().bitmap_blend(pgraphics,::point_i32(),pimage->get_size(),pimage->g(),::point_i32(),uchAlpha);

         pdraw2d->imaging().bitmap_blend(pgraphics,::point_i32(),imageFast.m_size,imageFast.get_graphics(),::point_i32(),255 - uchAlpha);

      }
      else
      {

/*         pgraphics->from(pimage->get_size(),pimage->g());

      }

      //pdraw2d->imaging().bitmap_blend(pgraphics,::point_i32(),imageFast.m_size,imageFast.get_graphics(),::point_i32(),255);


      //pgraphics->FillSolidRect(100,100,100,100,argb(128,0,128,0));

   }

   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      GetClientRect(rectangleClient);

      if(rectangleClient.area() <= 0)
         return;

/*      m_pimagePost = create_image(rectangleClient->size());

      m_pimagePost->Fill(0,0,0,0);

      ::draw2d::graphics_pointer & pgraphics = m_pimagePost->get_graphics();

      _006OnDraw(pgraphics);

      _001OnPostProcess(m_pimagePost);

      pdcScreen->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdcScreen->from(::point_i32(),m_pimagePost->m_size,m_pimagePost.get_graphics(),::point_i32());

//      pdcScreen->FillSolidRect(500,200,100,100,argb(255,255,210,0));

      //    pdcScreen->Draw3dRect(200,200,100,100,argb(255,0,255,0),argb(255,0,0,255));

   }

   void impact::turboc_fast_render(const ::string & strHelloMultiverse)
   {

      if(m_cx <= 0 || m_cy <= 0)
         return;

      synchronous_lock slDraw(m_pmutexDraw);

      ::size_i32 sizeNew = ::size_i32(m_cx,m_cy) + ::size_i32(100,100);

      bool bNewSize = m_pimageFast->width() < sizeNew->cx || m_pimageFast->height() < sizeNew->cy;

      if(bNewSize)
      {

/*         m_pimageFast = create_image(sizeNew);

      }

      m_pimageFast->Fill(0,0,0,0);

      ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

      float fHeight = 100.0;

      m_pfont->create_pixel_font(pnode->font_name(e_font_sans),fHeight,e_font_weight_bold);

      pgraphics->set_font(m_pfont);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      ::size_i32 size = pgraphics->get_text_extent(strHelloMultiverse);

      double ratey = fHeight * 0.84 / size.cy;

      m_pfont->create_pixel_font(pnode->font_name(e_font_sans),minimum(m_cy * ratey,m_cx * size.cy * ratey / size.cx),e_font_weight_bold);

      m_dMinRadius = maximum(1.0,m_pfont->m_dFontSize / 23.0);

      m_dMaxRadius = m_dMinRadius * 2.3;



      pgraphics->set_font(m_pfont);

      size = pgraphics->get_text_extent(strHelloMultiverse);

      ::draw2d::path_pointer path(this_create);

      ppath->m_bFill = false;

      ppath->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_pfont);

      ::draw2d::pen_pointer pen(this_create);

      ppen->create_solid(1.0,argb(255,84 / 2,84 / 2,77 / 2));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //pgraphics->FillSolidRect(0, 0, m_cx, m_cy, argb(0,0,0,0));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->draw(path,pen);
      //pgraphics->FillSolidRect(00,00,100,100,argb(128,128,0,0));

   }




   ::aura::document * impact::get_document()
   {

      return  (::aura::impact::get_document());

   }

   void impact::turboc_render()
   {

      {

         synchronous_lock synchronouslock(m_pmutexWork);

/*         ::image_pointer pimage = m_pimageWork;

/*         pimage->Fill(0,0,0,0);

/*         turboc_render(pimage);


      }

   }

   void impact::full_render()
   {

      size_i32 sizeNew = size_i32(m_cx, m_cy) + size(100,100);

      if(m_bNewLayout)
      {

         synchronous_lock sl1(m_spmutex);
         synchronous_lock sl2(m_pmutexWork);
         synchronous_lock sl3(m_pmutexDraw);
         synchronous_lock sl4(m_pmutexSwap);

/*         bool bNewSize = m_pimage->width() < sizeNew.cx || m_pimage->m_size.cy < sizeNew.cy;

         m_bNewLayout = false;


         {


            //          ::u32 dwTime2= ::duration::now();

            //FORMATTED_TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
//            FORMATTED_TRACE("hello_impact::lyot call timeA= %d ms",(u64) (dwTime2 - t_time1.operator DWORD_PTR()));

         }


         {

            if(bNewSize)
            {

               //if(!m_pimage->initialize(sizeNew->cx,sizeNew->cy,5))
               //   return;

               //m_pimage->Fill(0,0,0,0);

            }


            if(bNewSize)
            {

/*               m_pimageWork = create_image(sizeNew);

               //m_pimageWork->Fill(0,0,0,0);

               //m_pimageFast = create_image(sizeNew);

               //m_pimageFast->Fill(0,0,0,0);

            }

         }

         if(bNewSize)
         {


/*            m_pimage1 = create_image(sizeNew);

            //m_pimage1->Fill(0,0,0,0);

/*            m_pimage2 = create_image(sizeNew);

            //m_pimage2->Fill(0,0,0,0);

         }
         {

//            ::u32 dwTime2= ::duration::now();

            //FORMATTED_TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            //FORMATTED_TRACE("hello_impact::lyot call timeB= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

         }

      }


      turboc_render();

      if(m_bFirstDone)
      {

         synchronous_lock slUser(m_spmutex);

         turboc_draw();

      }
      else
      {
         TRACE("XXX123546");
      }

   }


/*   void impact::_001OnPostProcess(::image * pimage)
   {

      if(m_eeffect == effect_crt)
      {

         int iFactor = 3;
         int iMult = 1 << iFactor;

/*         pimage->g()->StretchBlt(0,0,pimage->width() / iMult,pimage->height() / iMult,pimage->g(),0,0,pimage->width(),pimage->height());
/*         pimage->g()->StretchBlt(0,0,pimage->width(),pimage->height(),pimage->g(),0,0,pimage->width() / iMult,pimage->height() / iMult);

         color32_t color32;

         byte a,r,g,b,rm,gm,bm;

/*         int h = (pimage->height() / 3) * 3;

/*         int w = (pimage->width() / 3) * 3;

         for(int i = 0; i < h; i+=3)
         {
            for(int j = 0; j < w; j+=3)
            {
/*               color32 = pimage->get_data()[i * pimage->width() + j];
               a = colorref_get_a_value(color32);
               r = colorref_get_r_value(color32);
               g = colorref_get_g_value(color32);
               b = colorref_get_b_value(color32);
               rm = (g + b) / 4;
               gm = (r + b) / 4;
               bm = (r + g) / 4;
/*               pimage->get_data()[i * pimage->width() + j] = argb(a,r,rm,rm);
/*               pimage->get_data()[i * pimage->width() + j+1] = argb(a,gm,g,gm);
/*               pimage->get_data()[i * pimage->width() + j+2] = argb(a,bm,bm,b);
/*               pimage->get_data()[(i+1) * pimage->width() + j] = argb(a,r,rm,rm);
/*               pimage->get_data()[(i + 1) * pimage->width() + j + 1] = argb(a,gm,g,gm);
/*               pimage->get_data()[(i + 1) * pimage->width() + j + 2] = argb(a,bm,bm,b);
/*               pimage->get_data()[(i + 2) * pimage->width() + j] = argb(a,r,rm,rm);
/*               pimage->get_data()[(i + 2) * pimage->width() + j + 1] = argb(a,gm,g,gm);
/*               pimage->get_data()[(i + 2) * pimage->width() + j + 2] = argb(a,bm,bm,b);
            }
         }

         ::draw2d::pen_pointer pen(this_create);

         ppen->create_solid(0.5,argb(84,0,0,0));

/*         pimage->g()->SelectObject(pen);

/*         for(int i = 0; i < pimage->height(); i+=3)
         {

/*            pimage->g()->draw_line(0,i,pimage->width(),i);

         }


      }

   }


   void impact::turboc_draw()
   {

      if(m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_pimageWork);

      synchronous_lock slDraw(m_pmutexDraw);

      if(m_bDib1)
      {

         *m_pimage2 = *m_pimageWork;

      }
      else
      {

         *m_pimage1 = *m_pimageWork;

      }

      synchronous_lock slSwap(m_pmutexSwap);

      if(m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }


   ::u32 impact::thread_proc_render(void * pparam)
   {

      impact * pviewParam = (impact *)pparam;

      {

         ::pointer<impact>pimpact = pviewParam;

         while(::task_get_run() && pimpact->IsWindow())
         {

            try
            {

               if(pimpact->m_bHelloRender)
               {

                  pimpact->full_render();

               }

               sleep(100_ms);

            }
            catch(...)
            {

               break;

            }

         }

      }

      return 0;

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      GetClientRect(rectangleClient);

      if(rectangleClient.area() <= 0)
         return;

      m_cx = rectangleClient.width();

      m_cy = rectangleClient.height();

      ::draw2d::graphics_pointer g(this_create);

      m_bNewLayout = true;

      m_bOkPending = true;

      m_bFast = true;

   }


   string impact::get_processed_turboc()
   {

      string str = get_turboc();

      if(::str().begins_eat_ci(str,"image:"))
      {

         string strImage = str;

         strsize iFind = strImage.find(",");

         if(iFind >= 0)
         {

            strImage = strImage.Mid(0,iFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;

/*            if(m_pimageImage->load_image(m_strImage))
            {
            }

         }


         if(m_pimageImage->is_set() && m_pimageImage->area() > 0)
         {

            if(::str().begins_eat_ci(str,m_strImage))
            {
               ::str().begins_eat_ci(str,",");
            }

         }

      }

      if(::str().begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string impact::get_turboc()
   {

      synchronous_lock synchronouslock(m_pmutexText);

      if(m_strHelloMultiverse != m_strNewHelloMultiverse)
      {

         m_strHelloMultiverse = m_strNewHelloMultiverse;

      }

      if(m_strHelloMultiverse.is_empty())
      {

         if(m_bAlternate)
         {

            return papp->m_strAlternateTurboC;

         }
         else
         {

            return papp->m_strTurboC;

         }

      }
      else
      {

         return m_strHelloMultiverse;

      }

   }


/*   void impact::turboc_render(::image * pimage)
   {

      if(m_pimageImage->is_set() && m_pimageImage->area() > 0)
      {

         m_bFirstDone = true;

         ::rectangle_i32 rectangleWork(0,0,m_pimageWork->width(),m_pimageWork->height());
         ::rectangle_i32 rectangleImage(0,0,m_pimageImage->width(),m_pimageImage->height());

         rectangleImage.FitOnCenterOf(rectangleWork);

/*         pimage->g()->StretchBlt(rectangleImage.left,rectangleImage.top,rectangleImage.width(),rectangleImage.height(),m_pimagepimage->g(),0,0,m_pimageImage->width(),m_pimageImage->height());


      }

      if(m_bLite)
      {

/*         turboc_render_lite_impact(pimage->g());

      }
      else
      {

/*         turboc_render_full_impact(pimage->g());

      }

   }


} // namespace turboc

















