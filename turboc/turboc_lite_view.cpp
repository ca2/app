#include "framework.h"
#include <math.h>


namespace turboc
{


   lite_view::lite_view(::layered * pobjectContext):
      ::object(pobject),
      view(pobject)
   {


   }


   lite_view::~lite_view()
   {

   }


   void lite_view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void lite_view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }

   void lite_view::install_message_handling(::message::dispatch * pdispatch)
   {

      view::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(e_message_create,pdispatch,this,&lite_view::_001OnCreate);

   }

   i64 lite_view::add_ref()
   {
      return ::root::add_ref(OBJ_REF_DBG_ARGS);
   }
   i64 lite_view::dec_ref()
   {
      return ::root::dec_ref(OBJ_REF_DBG_ARGS);
   }

   void lite_view::_001OnCreate(signal_details * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

//      if(Application.m_etype == application::type_normal)
//      {
//
////         load_ai_font();
//
//         __begin_thread(get_context_application(),&thread_proc_render,this,::priority_normal,0,0,NULL);
//
//      }


   }


   void lite_view::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      UNREFERENCED_PARAMETER(psubject);
   }


   void lite_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      view::_001OnDraw(pgraphics);

   }


/*   void lite_view::turboc_render(::image * pimage)
   {

      turboc_render_lite_view(pgraphics);

   }


/*   void view::turboc_render_lite_view(::image * pimage)
   {



      //if(m_pimage->area() <= 0)
      //   return;

      if(m_pimageWork->area() <= 0)
         return;

      ::rect rectClient;

      rectClient.left = 0;

      rectClient.top = 0;

      rectClient.right = m_cx;

      rectClient.bottom = m_cy;

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->FillSolidRect(rectClient,ARGB(0, 0, 0, 0));

//      i32 iCount = 30;

      ::draw2d::brush_pointer brushText(this_create);

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

      double t= ::millis::now() / 1000.0;

      double w = 2.0 * 3.1415 / T;

      double r = (tri(w * t) + 1.0) / 2.0;

//      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;

      //i32 i= ::millis::now()  / 100 % iCount;

      //i32 iBlur;

      //if(i <= (iCount / 2))
      //   iBlur = i;
      //else
      //   iBlur = iCount - i;
      string strHelloMultiverse = get_processed_turboc();

      pgraphics->set_font(m_font);

      ::size size = pgraphics->GetTextExtent(strHelloMultiverse);


      if(!m_bFirstDone)
      {

         if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
         {

            m_cxCache1 = m_cx;

            m_cyCache1 = m_cy;

/*            m_pimage->initialize(m_cxCache1,m_cyCache1,m_dMaxRadius);

            //m_pimage->defer_realize(pgraphics);

/*            m_pimage->Fill(0,0,0,0);

/*            m_pimage->g()->set_font(m_font);

/*            m_pimage->g()->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

/*            m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

            brushText->create_solid(ARGB(255,255,255,255));

/*            m_pimage->g()->SelectObject(brushText);

/*            m_pimage->g()->text_out((m_cxCache1 - size->cx) / 2,(m_cyCache1 - size->cy) / 2,strHelloMultiverse);

/*            m_pimage->blur(m_cxCache1,m_cyCache1);

/*            m_pimage->blur(m_cxCache1,m_cyCache1);

/*            m_pimage->blur(m_cxCache1,m_cyCache1);

/*            m_pimage->blur(m_cxCache1,m_cyCache1);

            if(m_cxCache1 + 100 > m_pimageTemplate->width() || m_cyCache1 + 100 > m_pimageTemplate->height())
            {

/*               m_pimageTemplate = create_image({m_cxCache1+100, m_cyCache1 + 100});

            }

            m_pimageTemplate->Fill(0,0,0,0);

/*            m_pimageTemplate->channel_copy(::color::channel_alpha,::color::channel_green,m_pimage);


         }

      }

      if(strHelloMultiverse != get_processed_turboc() || m_cxCache1 != m_cx || m_cyCache1 != m_cy || m_pimageTemplate->area() <= 0)
         return;

      ::color ca;


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

      if(!psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         m_pimageTemplate->set_rgb(ca->m_iR,ca->m_iG,ca->m_iB);

      }

      pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      System.draw2d().imaging().bitmap_blend(pgraphics,::point(),rectClient.size(),m_pimageTemplate->get_graphics(),::point(),140 + 220 * r);

      //pgraphics->BitBlt(rectClient,m_pimageTemplate->get_graphics());

      pgraphics->set_font(m_font);

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      if(psession->savings().is_trying_to_save(::e_resource_display_bandwidth))
      {

         brushText->create_solid(ARGB(255,ca.m_iR,ca.m_iG,ca.m_iB));

      }
      else
      {

         if(m_bAlternate)
         {

            brushText->create_solid(ARGB(255,184,184,177));

         }
         else
         {

            brushText->create_solid(ARGB(255,255,255,255));

         }

      }

      pgraphics->SelectObject(brushText);

      //if(!m_bAlternate)
      {

         pgraphics->text_out((m_cx - size.cx) / 2,(m_cy - size.cy) / 2,strHelloMultiverse);

      }

      //pgraphics->FillSolidRect(200,200,100,100,ARGB(128,128,128,0));


      if(strHelloMultiverse == get_processed_turboc() && m_cxCache1 == m_cx && m_cyCache1 == m_cy)
      {

         m_bFirstDone = true;

      }

   }









} // namespace turboc

















