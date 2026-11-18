// Created by camilo on 2026-11-01 11:35 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "aura/user/user/main_window.h"
#include "bred/user/user/gpu_shader_host.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER host :
      virtual public app_consumer < application, ::user::gpu_shader_host >
   {
   public:





      //__creatable(main_window);


      //string                                 m_strCurrentShaderPath;
      //// map_base : shader path - render
      //string_map_base < ::pointer<render > >      m_maprender;
      //bool                                   m_bSaveFrame;


      host();
      ~host() override;


      void install_message_routing(::channel * psender) override;


      ::image::image * drawn_frame_image() override;

      //void on_user_gpu_interaction_draw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      void _001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      void _001DrawItem(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      

      bool keyboard_focus_is_focusable() override;

      ::user::enum_translucency get_translucency(::user::style * pstyle) override;

      //virtual void update_shader(const ::scoped_string & scopedstrShaderPath);

      virtual ::app_shader::render * get_current_render();

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      void on_user_interface_switch() override;

      virtual void switch_shader();

      string get_next_path(const ::scoped_string & scopedstrPath);


   };


} // namespace app_shader



