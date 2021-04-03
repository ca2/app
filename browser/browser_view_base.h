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
      ::write_text::font_pointer       m_fontDrawStatus;
      color32_t                m_colorDrawStatus;

      double                  m_dFps;
      millis                    m_millisRoll;

      __pointer(regex)               m_ppcre;

      e_effect                m_eeffect;


      ::mutex                   m_mutexText;
      string                  m_strNewHelloBrowser;
      string                  m_strHelloBrowser;


      ::image_pointer        m_pimagePost;
      ::image_pointer        m_pimageTime;

      ::image_pointer        m_pimage1;
      ::image_pointer        m_pimage2;

      __pointer(render)              m_prender;


      tick_array                    m_tickaFrame;



      impact_base(::object * pobject);
      virtual ~impact_base();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnPostProcess(::draw2d::graphics_pointer & pgraphics);
      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_check_on_draw_layout();

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(on_message_left_button_down);


   };


} // namespace browser



