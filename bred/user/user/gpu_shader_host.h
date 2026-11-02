// Created by camilo on 2026-11-01 11:41 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
// Created by camilo on 2026-11-01 11:35 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#pragma once



#include "aura/user/user/box.h"
#include "bred/graphics3d/engine_instance.h"
#include "bred/graphics3d/immersion_layer.h"
#include "bred/graphics3d/key_map.h"
#include "bred/graphics3d/types.h"
#include "apex/platform/app_consumer.h"
#include "bred/platform/application.h"
#include "apex/platform/session.h"
#include "bred/platform/fps_counter.h"
#include "bred/user/user/gpu_interaction.h"


namespace user
{



   class CLASS_DECL_BRED gpu_shader_host :
      virtual public ::app_consumer < ::bred::application, ::user::gpu_interaction>
   {
   public:


      string                                 m_strCurrentShaderPath;
      // map_base : shader path - render
      string_map_base < ::pointer<::user::gpu_render > >      m_mapusergpurender;
      bool                                   m_bSaveFrame = false;


      //memory m_memory;
      //::i32 m_i32;

      //::i32                                           m_iFrameCounter = 0;
      //::write_text::font_pointer                      m_pfontThomasBS_;
      //::string_array                                  m_straLineStats;
      //int                                             m_iImpactSerial;
      //::string                                        m_strGpuStatisticsTitle;

      //::graphics3d::enum_mouse                      m_emouse;
      //::graphics3d::enum_keyboard                   m_ekeyboard;
      //bool                                          m_bAbsoluteMousePosition;
      //fps_counter                                     m_fpscounter;
      //::pointer < ::gpu::context >                    m_pgpucontext;
      //::pointer < ::gpu::shader >                     m_pgpushader;

      //::pointer < ::graphics3d::key_map >			      m_pkeymap;
      //::task_pointer                                m_ptaskEngine;
      //::pointer < ::image::target >                 m_pimagetarget;

      //bool		m_bShouldClose;
      //::i32		m_iWidth;
      //::i32		m_iHeight;
      //bool		m_bFramebufferResized;

      //::platform::session * m_psession;


      gpu_shader_host();
      ~gpu_shader_host() override;


      ::i64 increment_reference_count() override;
      ::i64 decrement_reference_count() override;


      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpgpucontext) const override;
            //::i32_size size() override;

            //virtual ::block global_ubo_block();

      void install_message_routing(::channel * pchannel) override;
      //void on_kill_keyboard_focus() override;
      //void _on_show_window() override;


      //virtual void on_mouse_move(const i32_point & point);
      //virtual void on_mouse_out();

      ////virtual ::user::enum_key_state get_key_state(const ::user::e_key & ekey) ;
      //::key::e_state get_key_state(const ::user::e_key & ekey) {
      //   return m_psession->_key_state(ekey);
      //}
      //void _001OnNcClip(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      //void _001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics) override;


      //void _001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      void _001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      //void _000OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //::user::document * get_document();

      //virtual void draw_gpu_statistics(::i32 y, const ::scoped_string & scopedstrTitle, ::draw2d::graphics_pointer & pdraw2dgraphics);

      //virtual ::pointer < ::graphics3d::application > start_graphics3d_application();


      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_key_down);
      //DECLARE_MESSAGE_HANDLER(on_message_key_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);

      void operator()(::timer * ptimer) override;

      //void reset_mouse_last_position();


      bool keyboard_focus_is_focusable() override;


      //virtual bool is_absolute_mouse_position();

      //virtual bool shouldClose();
      //virtual ::i32_size size();
      virtual bool wasWindowResized();
      virtual void resetWindowResizedFlag();
      //
        //    virtual ::user::enum_key_state get_key_state(const ::user::e_key & ekey);

            //virtual void initWindow();


      virtual void defer_initialize_gpu_shader_host(const ::i32_rectangle & rectangle);

      //virtual ::pointer < ::prodevian::immersion > create_immersion();

      //virtual void on_load_engine();



      //virtual ::pointer < ::graphics3d::key_map > get_default_key_map();
      virtual ::f32 getAspectRatio();

      //virtual void prepare_mouse_input();
      //virtual void process_mouse_input();

      //virtual void process_keyboard_input();





      //void install_message_routing(::channel * psender) override;


      ::image::image * drawn_frame_image() override;

      //void on_user_gpu_interaction_draw(::draw2d::graphics_pointer & pdraw2dgraphics) override;
      //void _001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      //void _001DrawItem(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate) override;

      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      //DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_key_down);


      //bool keyboard_focus_is_focusable() override;

      //::user::enum_translucency get_translucency(::user::style * pstyle) override;

      //virtual void update_shader(const ::scoped_string & scopedstrShaderPath);

      virtual ::user::gpu_render * get_current_render();

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      void on_user_interface_switch() override;

      virtual void switch_shader();

      string get_next_path(const ::scoped_string & scopedstrPath);



   };


} // namespace graphics3d



