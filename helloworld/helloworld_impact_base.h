#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD impact_base :
      virtual public ::hellobase::impact_base
   {
   public:

      enum e_effect
      {

         effect_none,
         effect_crt,

      };


      int                     m_yDrawStatus;
      ::write_text::font_pointer       m_pfontDrawStatus;
      color32_t                m_colorDrawStatus;

      ::frequency                  m_frequencyFramesPerSecond;
      ::u32                   m_dwRoll;

      string                  m_strHoverFont;
      string                  m_strNewFont;
      string                  m_strFont;
      e_effect                m_eeffect;


      ::pointer < ::mutex >                   m_pmutexText;
      string                  m_strNewHelloWorld;
      string                  m_strHelloWorld;


      ::image::image_pointer        m_pimagePost;
      ::image::image_pointer        m_pimageTime;

      ::image::image_pointer        m_pimage1;
      ::image::image_pointer        m_pimage2;

      render *                m_prender;


      u32_array            m_dwaFrame;



      impact_base(::particle * pparticle);
      virtual ~impact_base();

      virtual i64 increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual i64 decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnPostProcess(::draw2d::graphics_pointer & pgraphics);
      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_check_on_draw_layout();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace helloworld





















