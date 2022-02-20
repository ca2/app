#pragma once


namespace app_shader
{


   class CLASS_DECL_APP_SHADER main_window :
      virtual public application_consumer < application, ::user::main_window >
   {
   public:


      //__creatable(main_window);


      string                                 m_strCurrentShaderPath;
      // map : shader path - render
      string_map < __pointer(render) >       m_maprender;
      bool                                   m_bSaveFrame;


      main_window();
      ~main_window() override;


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_switch);

      virtual bool keyboard_focus_is_focusable() const override;

      virtual ::user::enum_translucency get_translucency(::user::style* pstyle) const override;

      virtual void update_shader(const ::string & strShaderPath);

      virtual bool on_click(::item * pitem) override;

      virtual void switch_shader();

      string get_next_path(const string& strPath);


   };


} // namespace app_shader



