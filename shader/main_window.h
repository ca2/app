#pragma once


#include "apex/platform/app_consumer.h"
#include "aura/user/user/main_window.h"
//#include "app/shader/user/user/graphics3d.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER main_window :
      virtual public app_consumer < application, ::user::main_window >
   {
   public:


      //__creatable(main_window);
      ::pointer < ::user::gpu_shader_host > m_pappshaderhost;


      //::item_pointer m_pitemSwitch, m_pitemClose, m_pitemMaximize, m_pitemMinimize;
      //::item_pointer hit_test(const ::i32_point & point, ::user::e_zorder ezorder) override;

      main_window();
      ~main_window() override;


      void install_message_routing(::channel * psender) override;

      void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      void _001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      //void _001DrawItem(::draw2d::graphics_pointer& pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      //DECLARE_MESSAGE_HANDLER(on_message_switch);

      bool keyboard_focus_is_focusable() override;

      ::user::enum_translucency get_translucency(::user::style* pstyle) override;

      //virtual void update_shader(const ::scoped_string & scopedstrShaderPath);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      //virtual void switch_shader();

      //string get_next_path(const ::scoped_string & scopedstrPath);


   };


} // namespace app_shader



