#pragma once


namespace simple_shader
{


   class CLASS_DECL_APP_SHADER window :
      virtual public ::user::main_window
   {
   public:


      int                           m_iShader;
      __pointer_array(render)       m_rendera;
      bool                          m_bSaveFrame;


      window();
      virtual ~window();



      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void update(::update * pupdate) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool keyboard_focus_is_focusable() override;

      virtual ::user::e_translucency get_translucency(::user::style* pstyle) const override;


      void update_shader();

      virtual bool on_click(const ::user::item& item);


   };


} // namespace simple_shader


