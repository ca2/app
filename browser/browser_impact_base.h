#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER impact_base :
      virtual public ::user::impact
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
      class ::time                    m_timeRoll;

      ::pointer<regex>              m_ppcre;

      e_effect                m_eeffect;


      ::pointer < ::mutex >                   m_pmutexText;
      string                  m_strNewHelloBrowser;
      string                  m_strHelloBrowser;


      ::image_pointer        m_pimagePost;
      ::image_pointer        m_pimageTime;

      ::image_pointer        m_pimage1;
      ::image_pointer        m_pimage2;

      ::pointer<render>             m_prender;


      musical_tick_array                    m_tickaFrame;



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
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);


   };


} // namespace browser



