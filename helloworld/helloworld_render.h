//
//  helloworld_render.h
//  app_core_helloworld
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD render :
      virtual public ::hellobase::render
   {
   public:


      //class bilbo
      //{
      //public:

      //   string         m_strPath;
      //   bool           m_b;
      //   bool           m_bNew;

      //   bilbo();
      //   bilbo(string strPath);
      //   ~bilbo();

      //};

      //double                           m_dRenderFps;
      //bool                             m_bDib1;

      //bool                             m_bAlternate;

      //bool                             m_bLite;

      //bool                             m_bImageEnable;

      //::pointer < ::mutex >                            m_pmutexWork;
      //::pointer < ::mutex >                            m_pmutexDraw;
      //::pointer < ::mutex >                            m_pmutexSwap;
      //::pointer < ::mutex >                            m_pmutexDib;
      //::pointer < ::mutex >                            m_pmutexDib23;

      //bool                             m_bNewLayout;
      //bool                             m_bHelloRender;
      //int                              m_cx;
      //int                              m_cy;
      //int                              m_cxCache1;
      //int                              m_cyCache1;
      //int                              m_cxTarget;
      //int                              m_cyTarget;

      //::draw2d::fastblur               m_pimageImage;
      //::image::image_pointer                 m_pimageOut;
      //::image::image_pointer                 m_pimageA;
      //::image::image_pointer                 m_pimageB;
      //::image::image_pointer                 m_pimageWork;
      //::draw2d::fastblur               m_pimage;
      //::draw2d::fastblur               m_pimageTint;
      //::image::image_pointer                 m_pimageTemplate;
      //::image::image_pointer                 m_pimageTemplate2;

      //bool                             m_bVoidTransfer;
      //bool                             m_bFirstDone;

      //::write_text::font_pointer                m_pfont;

      //double                           m_dMinRadius;
      //double                           m_dMaxRadius;

      //string                           m_strHelloWorld;

      //::rectangle_i32                           m_rectangleX;


      //::pointer< ::mutex >                          m_pmutexText;

      //impact *                           m_pimpact;


      //class ::time                            m_timeAnime;
      //class ::time m_timeLastFast;
      //::u32                            m_timeFastAnime;
      //::image::image_pointer                 m_pimageFast;


      //string_array                          m_stra23;
      //string_map < ::image::image_pointer >    m_mapDib23;
      //bool                             m_b23;
      //u32                         m_uiCurrent23;
      //string                           m_strCurrent23;
      //string                           m_strLast23;
      //bool                             m_bFirst23;
      //::u32                            m_dw23;

      //array < bilbo >                  m_bilboa;
      //class ::time m_timeLastOk;


      //bool                             m_bFast;
      //bool                             m_bFastOnEmpty;


      render(::particle * pparticle);
      virtual ~render();


      virtual string get_helloaura() override;

      // { synchronous_lock slText(m_pmutexText);  string str(m_strHelloWorld.c_str()); return str; }


      virtual i32 run();

      virtual bool initialize_render(string strId);


      virtual void full_render();
      virtual void helloaura_render();
      virtual void helloaura_draw();
      virtual void helloaura_render(::draw2d::graphics_pointer & pgraphics);
      //virtual void helloaura_render(::draw2d::graphics_pointer & pgraphics);

      virtual void helloaura_render_full_impact(::draw2d::graphics_pointer & pgraphics);
      virtual void helloaura_render_lite_impact(::draw2d::graphics_pointer & pgraphics);


      //virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      //virtual void defer_update_bilbo();

      //::image::image_pointer & image23(string strDib);

      //virtual bool in_anime();
      //virtual void helloaura_fast_render(const ::string & strHelloWorld);


//      virtual string get_helloaura() override;

   };


} // namespace helloworld


