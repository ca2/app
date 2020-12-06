#include "framework.h"
#include <math.h>



//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;

void rainbow_main();


namespace turboc
{


   view::view(::layered * pobjectContext):
      ::object(pobject),
      m_pimage1,
      m_pimage2,

      m_pimageColor,
      m_pimageWork,
      m_pimageTemplate,
      m_pimageFast,
      m_font(this_create),




      m_pimageAi1,
      m_pimageAi2,
      m_pimageImage,
      m_pimagePost
   {

      m_bLite = true;

      m_bVoidTransfer =  false;

      m_millisAnime = 2000;

      m_bNewLayout = false;

      m_millisFastAnime = 584;

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

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }

   void view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::aura::impact::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(e_message_create,pdispatch,this,&view::_001OnCreate);

   }


   void view::_001OnCreate(signal_details * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      if(Application.m_etype == application::type_normal)
      {

         if(!m_bLite)
         {

            Application.load_ai_font();

         }

         __begin_thread(get_context_application(),&thread_proc_render,this,::priority_normal,0,0,NULL);

      }

      Application.start_main();


   }


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
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

         ::turboc::view::on_layout(pgraphics);

      }
      else
      {

         on_layout(::draw2d::graphics_pointer & pgraphics);

      }

   }




   void view::on_update(::aura::impact * pSender, e_update eupdate, object* pupdate)
   {
      UNREFERENCED_PARAMETER(psubject);
   }

   bool view::in_anime()
   {
      if(m_bFast || m_millisLastFast.elapsed() < m_millisFastAnime)
         return true;
      if(m_millisLastOk.elapsed() < m_millisAnime)
         return true;
      return false;
   }


/*   void view::_006OnDraw(::image * pimage)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

/*      pgraphics->BitBlt(rectClient,Application.m_pcontext->m_pimage->g());


      if(Application.m_etype == application::type_mili)
      {

         string strHelloMultiverse = get_processed_turboc();

         if(m_bNewLayout)
         {

            float fHeight = 100.0;




            m_font->create_pixel_font(FONT_SANS,fHeight,e_font_weight_bold);

            pgraphics->set_font(m_font);

            pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

            ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

            double ratey = fHeight * 0.84 / size.cy;

            m_font->create_pixel_font(FONT_SANS,min(m_cy * ratey,m_cx * size.cy * ratey / size.cx),e_font_weight_bold);

            //m_dMinRadius = max(1.0,m_font->m_dFontSize / 23.0);

            //m_dMaxRadius = m_dMinRadius * 2.3;

            //m_pimageFast->Fill(0,0,0,0);

            //pgraphics->set_font(m_font);

            //size = pgraphics->GetTextExtent(strHelloMultiverse);

            //::draw2d::path_pointer path(this_create);

            //path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

            //::draw2d::pen_pointer pen(this_create);

            //pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

            //pgraphics->FillSolidRect(0,0,m_cx,m_cy,ARGB(0,0,0,0));

            //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            //pgraphics->draw_path(path,pen);

            m_bNewLayout = false;

         }


         ::color ca;

         double dPeriod = (500) * 11;

         ca.set_hls(fmod(::get_tick(),dPeriod) / dPeriod,0.49,0.84);

         ::draw2d::brush_pointer brush(this_create);

         brush->create_solid(ARGB(255,ca.m_iR,ca.m_iG,ca.m_iB));

         pgraphics->SelectObject(brush);

         pgraphics->set_font(m_font);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

         ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

         pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

         return;

      }

      if(m_bFast || !m_bFirstDone || m_millisLastFast.elapsed() < m_millisFastAnime)
      {

         sync_lock slDraw(&m_mutexDraw);

         if(m_bFast || m_pimageFast->is_null())
         {

            m_bFast = false;

            turboc_fast_render(get_processed_turboc());

            m_bFirstDone = false;

         }

         if(m_bFast || !m_bFirstDone)
         {

            m_millisLastFast= ::millis::now();

         }

         pgraphics->BitBlt(::point(),size(m_cx,m_cy),m_pimageFast->get_graphics());

         //pgraphics->FillSolidRect(400,400,100,100,ARGB(128,0,0,128));

         m_bOkPending = true;

         return;

      }

      if(m_bOkPending)
      {

         m_bOkPending = false;

         m_millisLastOk= ::millis::now();

      }

/*      ::image_pointer pimage = NULL;

      ::image_pointer pimageFast = m_pimageFast;

      sync_lock sl(&m_mutexDraw);

      sync_lock slSwap(&m_mutexSwap);

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

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(m_millisLastOk.elapsed() < m_millisAnime)
      {

         byte uchAlpha = max(0,min(255,(m_millisLastOk.elapsed()) * 255 / m_millisAnime));

         ::rect rectClient;

         GetClientRect(rectClient);

         //pgraphics->FillSolidRect(rectClient,0);

/*         System.draw2d().imaging().bitmap_blend(pgraphics,::point(),pimage->get_size(),pimage->g(),::point(),uchAlpha);

         System.draw2d().imaging().bitmap_blend(pgraphics,::point(),imageFast.m_size,imageFast.get_graphics(),::point(),255 - uchAlpha);

      }
      else
      {

/*         pgraphics->from(pimage->get_size(),pimage->g());

      }

      //System.draw2d().imaging().bitmap_blend(pgraphics,::point(),imageFast.m_size,imageFast.get_graphics(),::point(),255);


      //pgraphics->FillSolidRect(100,100,100,100,ARGB(128,0,128,0));

   }

   void view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

/*      m_pimagePost = create_image(rectClient->size());

      m_pimagePost->Fill(0,0,0,0);

      ::draw2d::graphics_pointer & pgraphics = m_pimagePost->get_graphics();

      _006OnDraw(pgraphics);

      _001OnPostProcess(m_pimagePost);

      pdcScreen->set_alpha_mode(::draw2d::alpha_mode_blend);

      pdcScreen->from(::point(),m_pimagePost->m_size,m_pimagePost.get_graphics(),::point());

//      pdcScreen->FillSolidRect(500,200,100,100,ARGB(255,255,210,0));

      //    pdcScreen->Draw3dRect(200,200,100,100,ARGB(255,0,255,0),ARGB(255,0,0,255));

   }

   void view::turboc_fast_render(const string & strHelloMultiverse)
   {

      if(m_cx <= 0 || m_cy <= 0)
         return;

      sync_lock slDraw(&m_mutexDraw);

      ::size sizeNew = ::size(m_cx,m_cy) + ::size(100,100);

      bool bNewSize = m_pimageFast->width() < sizeNew->cx || m_pimageFast->height() < sizeNew->cy;

      if(bNewSize)
      {

/*         m_pimageFast = create_image(sizeNew);

      }

      m_pimageFast->Fill(0,0,0,0);

      ::draw2d::graphics_pointer & pgraphics = m_pimageFast->get_graphics();

      float fHeight = 100.0;

      m_font->create_pixel_font(FONT_SANS,fHeight,e_font_weight_bold);

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      ::size size = pgraphics->GetTextExtent(strHelloMultiverse);

      double ratey = fHeight * 0.84 / size.cy;

      m_font->create_pixel_font(FONT_SANS,min(m_cy * ratey,m_cx * size.cy * ratey / size.cx),e_font_weight_bold);

      m_dMinRadius = max(1.0,m_font->m_dFontSize / 23.0);

      m_dMaxRadius = m_dMinRadius * 2.3;



      pgraphics->set_font(m_font);

      size = pgraphics->GetTextExtent(strHelloMultiverse);

      ::draw2d::path_pointer path(this_create);

      path->m_bFill = false;

      path->add_string((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse,m_font);

      ::draw2d::pen_pointer pen(this_create);

      pen->create_solid(1.0,ARGB(255,84 / 2,84 / 2,77 / 2));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(0, 0, m_cx, m_cy, ARGB(0,0,0,0));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->draw_path(path,pen);
      //pgraphics->FillSolidRect(00,00,100,100,ARGB(128,128,0,0));

   }




   ::aura::document * view::get_document()
   {

      return  (::aura::impact::get_document());

   }

   void view::turboc_render()
   {

      {

         sync_lock sl(&m_mutexWork);

/*         ::image_pointer pimage = m_pimageWork;

/*         pimage->Fill(0,0,0,0);

/*         turboc_render(pimage);


      }

   }

   void view::full_render()
   {

      size sizeNew = size(m_cx, m_cy) + size(100,100);

      if(m_bNewLayout)
      {

         sync_lock sl1(m_spmutex);
         sync_lock sl2(&m_mutexWork);
         sync_lock sl3(&m_mutexDraw);
         sync_lock sl4(&m_mutexSwap);

/*         bool bNewSize = m_pimage->width() < sizeNew.cx || m_pimage->m_size.cy < sizeNew.cy;

         m_bNewLayout = false;


         {


            //          ::u32 dwTime2= ::millis::now();

            //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
//            TRACE("hello_view::lyot call timeA= %d ms",(u64) (dwTime2 - t_time1.operator DWORD_PTR()));

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

//            ::u32 dwTime2= ::millis::now();

            //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
            //TRACE("hello_view::lyot call timeB= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

         }

      }


      turboc_render();

      if(m_bFirstDone)
      {

         sync_lock slUser(m_spmutex);

         turboc_draw();

      }
      else
      {
         TRACE("XXX123546");
      }

   }


/*   void view::_001OnPostProcess(::image * pimage)
   {

      if(m_eeffect == effect_crt)
      {

         int iFactor = 3;
         int iMult = 1 << iFactor;

/*         pimage->g()->StretchBlt(0,0,pimage->width() / iMult,pimage->height() / iMult,pimage->g(),0,0,pimage->width(),pimage->height());
/*         pimage->g()->StretchBlt(0,0,pimage->width(),pimage->height(),pimage->g(),0,0,pimage->width() / iMult,pimage->height() / iMult);

         color32_t cr;

         byte a,r,g,b,rm,gm,bm;

/*         int h = (pimage->height() / 3) * 3;

/*         int w = (pimage->width() / 3) * 3;

         for(int i = 0; i < h; i+=3)
         {
            for(int j = 0; j < w; j+=3)
            {
/*               cr = pimage->get_data()[i * pimage->width() + j];
               a = colorref_get_a_value(cr);
               r = colorref_get_r_value(cr);
               g = colorref_get_g_value(cr);
               b = colorref_get_b_value(cr);
               rm = (g + b) / 4;
               gm = (r + b) / 4;
               bm = (r + g) / 4;
/*               pimage->get_data()[i * pimage->width() + j] = ARGB(a,r,rm,rm);
/*               pimage->get_data()[i * pimage->width() + j+1] = ARGB(a,gm,g,gm);
/*               pimage->get_data()[i * pimage->width() + j+2] = ARGB(a,bm,bm,b);
/*               pimage->get_data()[(i+1) * pimage->width() + j] = ARGB(a,r,rm,rm);
/*               pimage->get_data()[(i + 1) * pimage->width() + j + 1] = ARGB(a,gm,g,gm);
/*               pimage->get_data()[(i + 1) * pimage->width() + j + 2] = ARGB(a,bm,bm,b);
/*               pimage->get_data()[(i + 2) * pimage->width() + j] = ARGB(a,r,rm,rm);
/*               pimage->get_data()[(i + 2) * pimage->width() + j + 1] = ARGB(a,gm,g,gm);
/*               pimage->get_data()[(i + 2) * pimage->width() + j + 2] = ARGB(a,bm,bm,b);
            }
         }

         ::draw2d::pen_pointer pen(this_create);

         pen->create_solid(0.5,ARGB(84,0,0,0));

/*         pimage->g()->SelectObject(pen);

/*         for(int i = 0; i < pimage->height(); i+=3)
         {

/*            pimage->g()->draw_line(0,i,pimage->width(),i);

         }


      }

   }


   void view::turboc_draw()
   {

      if(m_bVoidTransfer)
         return;

      //_001OnPostProcess(m_pimageWork);

      sync_lock slDraw(&m_mutexDraw);

      if(m_bDib1)
      {

         *m_pimage2 = *m_pimageWork;

      }
      else
      {

         *m_pimage1 = *m_pimageWork;

      }

      sync_lock slSwap(&m_mutexSwap);

      if(m_bDib1)
      {

         m_bDib1 = false;

      }
      else
      {

         m_bDib1 = true;

      }

   }


   ::u32 view::thread_proc_render(void * pparam)
   {

      view * pviewParam = (view *)pparam;

      {

         __pointer(view) pview = pviewParam;

         while(::thread_get_run() && pview->IsWindow())
         {

            try
            {

               if(pview->m_bHelloRender)
               {

                  pview->full_render();

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


   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      m_cx = rectClient.width();

      m_cy = rectClient.height();

      ::draw2d::graphics_pointer g(this_create);

      m_bNewLayout = true;

      m_bOkPending = true;

      m_bFast = true;

   }


   string view::get_processed_turboc()
   {

      string str = get_turboc();

      if(::str::begins_eat_ci(str,"image:"))
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

            if(::str::begins_eat_ci(str,m_strImage))
            {
               ::str::begins_eat_ci(str,",");
            }

         }

      }

      if(::str::begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string view::get_turboc()
   {

      sync_lock sl(&m_mutexText);

      if(m_strHelloMultiverse != m_strNewHelloMultiverse)
      {

         m_strHelloMultiverse = m_strNewHelloMultiverse;

      }

      if(m_strHelloMultiverse.is_empty())
      {

         if(m_bAlternate)
         {

            return Application.m_strAlternateTurboC;

         }
         else
         {

            return Application.m_strTurboC;

         }

      }
      else
      {

         return m_strHelloMultiverse;

      }

   }


/*   void view::turboc_render(::image * pimage)
   {

      if(m_pimageImage->is_set() && m_pimageImage->area() > 0)
      {

         m_bFirstDone = true;

         ::rect rectWork(0,0,m_pimageWork->width(),m_pimageWork->height());
         ::rect rectImage(0,0,m_pimageImage->width(),m_pimageImage->height());

         rectImage.FitOnCenterOf(rectWork);

/*         pimage->g()->StretchBlt(rectImage.left,rectImage.top,rectImage.width(),rectImage.height(),m_pimagepimage->g(),0,0,m_pimageImage->width(),m_pimageImage->height());


      }

      if(m_bLite)
      {

/*         turboc_render_lite_view(pimage->g());

      }
      else
      {

/*         turboc_render_full_view(pimage->g());

      }

   }


} // namespace turboc

















