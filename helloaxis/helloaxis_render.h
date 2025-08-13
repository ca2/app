//
//  helloaxis_render.h
//  app_core_helloaxis
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


#pragma once


namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS render :
      virtual public ::helloaura::render
   {
   public:

      /*

               double                           m_dRenderFps;
               bool                             m_bDib1;

               bool                             m_bAlternate;

               bool                             m_bLite;

               bool                             m_bImageEnable;

               ::pointer < ::mutex >                            m_pmutexWork;
               ::pointer < ::mutex >                            m_pmutexDraw;
               ::pointer < ::mutex >                            m_pmutexSwap;
               ::pointer < ::mutex >                            m_pmutexDib;
               ::pointer < ::mutex >                            m_pmutexDib23;

               bool                             m_bNewLayout;
               bool                             m_bHelloRender;
               int                              m_cx;
               int                              m_cy;
               int                              m_cxCache1;
               int                              m_cyCache1;
               int                              m_cxTarget;
               int                              m_cyTarget;

               ::image::fastblur               m_pimageImage;
               ::image::image_pointer                 m_pimageOut;
               ::image::image_pointer                 m_pimageA;
               ::image::image_pointer                 m_pimageB;
               ::image::image_pointer                 m_pimageWork;
/*               ::image::fastblur               m_pimage;
               ::image::fastblur               m_pimageTint;
               ::image::image_pointer                 m_pimageTemplate;
               ::image::image_pointer                 m_pimageTemplate2;

               bool                             m_bVoidTransfer;
               bool                             m_bFirstDone;

               ::write_text::font_pointer                m_pfont;

               double                           m_dMinRadius;
               double                           m_dMaxRadius;

               string                           m_strHelloAxis;

               ::int_rectangle                           m_rectangleX;


               ::pointer< ::mutex >                          m_pmutexText;

               class ::time                            m_timeAnime;
               class ::time m_timeLastFast;
               unsigned int                            m_timeFastAnime;
               ::image::image_pointer                 m_pimageFast;


               string_array_base                          m_stra23;
               string_map_base < ::image::image_pointer >    m_mapDib23;
               bool                             m_b23;
               unsigned int                         m_uiCurrent23;
               string                           m_strCurrent23;
               string                           m_strLast23;
               bool                             m_bFirst23;
               unsigned int                            m_dw23;

               array < bilbo >                  m_bilboa;
               class ::time m_timeLastOk;


               bool                             m_bFast;
               bool                             m_bFastOnEmpty;
      */

      render(::particle * pparticle);
      virtual ~render();


      string get_helloaura() { synchronous_lock slText(m_pmutexText);  string str(m_strHelloAxis.c_str()); return str; }


      virtual void     run() override;

      virtual bool initialize_render(const ::scoped_string & scopedstrId) override;


      //virtual void full_render();
      //virtual void helloaura_render();
      //virtual void helloaura_draw();
      //virtual void helloaura_render(::draw2d::graphics_pointer & pgraphics);
      //virtual void helloaura_render(::draw2d::graphics_pointer & pgraphics);

      virtual void helloaura_render_full_impact(::draw2d::graphics_pointer & pgraphics) override;
      virtual void helloaura_render_lite_impact(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void defer_update_bilbo() override;

      ::image::image_pointer & image23(const ::scoped_string & scopedstrDib) override;

      virtual bool in_anime() override;
      virtual void helloaura_fast_render(const ::scoped_string & scopedstrHelloAxis) override;


   };


} // namespace helloaxis


