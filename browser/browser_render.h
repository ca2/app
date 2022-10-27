//
//  browser_render.h
//  app_core_browser
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER render :
      virtual public ::thread,
      virtual public ::gcom::slide_drawer
   {
   public:


      double                           m_dRenderFps;
      bool                             m_bDib1;

      ::duration m_durationSlidePeriod;

      bool                             m_bAlternate;

      bool                             m_bLite;

      bool                             m_bImageEnable;

      ::pointer < ::mutex >                            m_pmutexWork;
      ::pointer < ::mutex >                            m_pmutexDraw;
      ::pointer < ::mutex >                            m_pmutexSwap;
      ::pointer < ::mutex >                            m_pmutexDib;
      //::pointer < ::mutex >                            m_pmutexDibSlideShow;

      bool                             m_bNewLayout;
      bool                             m_bHelloRender;
      int                              m_cx;
      int                              m_cy;
      int                              m_cxCache1;
      int                              m_cyCache1;
      int                              m_cxTarget;
      int                              m_cyTarget;

      bool                             m_bImageChanged;

      ::draw2d::fastblur               m_blurImageImage;
      ::image_pointer                            m_pimageImage;
      ::image_pointer                            m_pimageImageStretched;
      ::image_pointer                            m_pimageOut;
      ::image_pointer                            m_pimageA;
      ::image_pointer                            m_pimageB;
      ::image_pointer                            m_pimageWork;
      ::draw2d::fastblur               m_blurImage;
/*      ::image_pointer                            m_pimage;
      ::draw2d::fastblur               m_blurImageTint;
      ::image_pointer                            m_pimageTint;
      ::image_pointer                            m_pimageTemplate;
      ::image_pointer                            m_pimageTemplate2;

      ::color::color::color::hls                     m_hlsForeground;

      bool                             m_bVoidTransfer;
      bool                             m_bFirstDone;

      ::write_text::font_pointer                m_pfont;

      double                           m_dMinRadius;
      double                           m_dMaxRadius;

      string                           m_strHelloBrowser;

      ::rectangle_i32                           m_rectangleClient;


      ::pointer < ::mutex >                            m_pmutexText;

      impact *                           m_pimpact;


      ::duration                            m_durationAnime;
      ::duration m_durationLastFast;
      ::u32                            m_durationFastAnime;
      ::image_pointer                            m_pimageFast;


      image_array                      m_pimageaSlide;
      ::pointer<::object>                    m_pslideshow;

      ::duration m_durationLastOk;


      bool                             m_bFast;
      bool                             m_bFastOnEmpty;

      string                           m_strFontSel;
      string                           m_strFontHover;
      string                           m_strFont;


      render(::object * pobjectParent, bool bAlternate);
      virtual ~render();


      virtual double get_fps();

      ::gcom::slide_show & slideshow();


      void get_browser(string & strHellomultiverse);


      virtual void     run() override;

      virtual void term_thread() override;

      virtual bool initialize_render(string strId);


      virtual void slide_draw(::draw2d::graphics_pointer & pgraphics, ::gcom::slide * pslide);

      virtual void full_render();
      virtual void browser_render();
      virtual void browser_draw();
      virtual void browser_render(::draw2d::graphics_pointer & pgraphics);

      virtual void browser_render_full_impact(::draw2d::graphics_pointer & pgraphics);
      virtual void browser_render_lite_impact(::draw2d::graphics_pointer & pgraphics);


      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_update_slide_show();

      virtual bool in_anime();
      virtual void browser_fast_render(const ::string & strHelloBrowser);

   };


} // namespace browser



