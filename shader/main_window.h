#pragma once


#include "apex/platform/app_consumer.h"
#include "aura/user/user/main_window.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER main_window :
      virtual public app_consumer < application, ::user::main_window >
   {
   public:


      //__creatable(main_window);


      string                                 m_strCurrentShaderPath;
      // map : shader path - render
      string_map < ::pointer<render > >      m_maprender;
      bool                                   m_bSaveFrame;


      main_window();
      ~main_window() override;


      void install_message_routing(::channel * psender) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item & useritem, const ::user::e_state & estate) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_switch);

      bool keyboard_focus_is_focusable() override;

      ::user::enum_translucency get_translucency(::user::style* pstyle) override;

      virtual void update_shader(const ::string & strShaderPath);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      virtual void switch_shader();

      string get_next_path(const string& strPath);


   };


} // namespace app_shader



