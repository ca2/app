#pragma once


namespace app_shader
{


   class CLASS_DECL_APP_SHADER main_window :
      virtual public ::user::main_window
   {
   public:


      int                           m_iShader;
      __pointer_array(render)       m_rendera;
      bool                          m_bSaveFrame;


      main_window();
      virtual ~main_window();


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item* pitem) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      virtual bool keyboard_focus_is_focusable() const override;

      virtual ::user::enum_translucency get_translucency(::user::style* pstyle) const override;

      virtual void update_shader(int iShader);

      virtual bool on_click(const ::user::item& item) override;


   };


} // namespace app_shader



