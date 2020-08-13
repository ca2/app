#pragma once


namespace simple_shader
{


   class CLASS_DECL_APP_SHADER window :
      virtual public ::user::interaction
   {
   public:


      int                     m_iView;
      __pointer(render)       m_prender;
      bool                    m_bSaveFrame;


      window();
      virtual ~window();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void update(::update * pupdate) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool keyboard_focus_is_focusable() override;

   };


} // namespace simple_shader


