#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC impact :
      public ::aura::impact
   {
   public:


      enum e_effect
      {

         effect_none,
         effect_crt,

      };


      e_effect                m_eeffect;
      bool                    m_bLite;

      //main_impact *             m_pmainimpact;

      string                  m_strServer;
      ::pointer < ::mutex >                   m_pmutexWork;
      ::pointer < ::mutex >                   m_pmutexDraw;
      ::pointer < ::mutex >                   m_pmutexSwap;
      ::pointer < ::mutex >                   m_pmutexText;
      ::image::image_pointer        m_pimageAi1;
      ::image::image_pointer        m_pimageAi2;

      ::image::image_pointer        m_pimage1;
      ::image::image_pointer        m_pimage2;
      bool                    m_bDib1;
      bool                    m_bVoidTransfer;

      string                  m_strImage;
      ::image::image_pointer        m_pimagePost;
      ::image::fastblur      m_pimageImage;
/*      ::image::fastblur      m_pimage;
      ::image::image_pointer        m_pimageColor;
      ::image::image_pointer        m_pimageWork;
      ::image::image_pointer        m_pimageFast;
      ::image::image_pointer        m_pimageTemplate;

      ::write_text::font_pointer       m_pfont;
      string                  m_strNewHelloMultiverse;
      string                  m_strHelloMultiverse;
      bool                    m_bOkPending;
      class ::time m_timeLastOk;
      class ::time                   m_timeAnime;
      bool                    m_bNewLayout;
      class ::time m_timeLastFast;
      unsigned int                   m_timeFastAnime;
      bool                    m_bFast;
      bool                    m_bFirstDone;
      bool                    m_bFastOnEmpty;

      int                     m_cx;
      int                     m_cy;
      int                     m_cxCache1;
      int                     m_cyCache1;

      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;
      bool                    m_bHelloRender;


      double                  m_dMinRadius;
      double                  m_dMaxRadius;

      bool                    m_bAlternate;


      impact(::particle * pparticle);
      virtual ~impact();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void install_message_handling(::message::dispatch * pdispatch);


/*      virtual void _001OnPostProcess(::image::image *pimage);

/*      virtual void _006OnDraw(::image::image *pimage);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender, e_update eupdate, object* pHint);

      ::aura::document * get_document();

      virtual void turboc_render();
/*      virtual void turboc_render(::image::image *pimage);
      virtual void turboc_fast_render(const ::string & strHelloMultiverse);
      virtual void turboc_draw();
      virtual void full_render();

      static unsigned int thread_proc_render(void * pparam);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual string get_turboc();

      virtual string get_processed_turboc();

      virtual bool in_anime();


/*      virtual void turboc_render_lite_impact(::image::image *pimage);
/*      virtual void turboc_render_full_impact(::image::image *pimage);

   };


} // namespace turboc





















