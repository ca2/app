// Created by camilo on 2026-09-04 17:33 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "bred/platform/application.h"


namespace graphics3d
{


   class CLASS_DECL_BRED graphics3d :
      virtual public ::app_consumer < ::bred::application, ::object >
   {
   public:


      ::graphics3d::skybox_map               m_mapSkybox;


      graphics3d();
      ~graphics3d() override;


      virtual void initialize_graphics3d();

      void set_gpu_performance_diagnostics(bool bEnabled);
      bool gpu_performance_diagnostics_enabled() const;
      void set_gpu_performance_diagnostics_interval(::i32 iMilliseconds);
      ::i32 gpu_performance_diagnostics_interval() const;



      virtual void defer_load_skyboxes(::gpu::context * pgpucontext);

      //virtual void defer_process_load_assets_commands();


      //virtual void create_global_ubo(::gpu::context *pgpucontext);

      //virtual ::gpu::enum_output get_engine_gpu_eoutput();

      //virtual void defer_start(::user::graphics3d * pusergraphics3d, const ::i32_rectangle & rectangle);

      //virtual void on_begin_frame();
      //virtual void on_end_frame();

      //void start_gpu_layer(::gpu::layer * pgpulayer) override;
      //::gpu::frame* end_gpu_layer(::gpu::layer * pgpulayer) override;


      //virtual void update_global_ubo(::gpu::context* pgpucontext);

      //virtual ::graphics3d::shape_factory * shape_factory();

      //virtual ::gpu::context * get_gpu_context();



      //virtual void engine_on_after_load_scene(::graphics3d::scene_base * pscene);


      //::f32 dt() { return m_fFrameTime; }

      //virtual floating_matrix4 model_matrix(::graphics3d::transform & transformcomponent);
      //virtual floating_matrix4 normal_matrix(::graphics3d::transform & transformcomponent);

      ////void on_begin_frame() override;
      ////virtual void run_cpu_buffer();

      //void run() override;


      //virtual void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics);

      //virtual ::graphics3d::scene_base * current_scene();


      /////virtual void do_frame_step(::gpu::context * pgpucontextUpper);

      ////virtual void do_draw_layer(::gpu::context *pgpucontextUpper);

      //virtual void do_draw_layer();

      //virtual void _prepare_frame();

      //virtual void _engine_on_frame_context_initialization();

      //virtual void draw_layer();
      //virtual void on_after_done_frame_step(::draw2d::graphics_pointer & pdraw2dgraphics);
      //virtual void defer_update_engine(const ::i32_rectangle & rectangle);

      //virtual void on_layout(const ::i32_rectangle & rectanglePlacement);

      //virtual void on_mouse_move(::f32 x, ::f32 y);

      ////virtual void on_render_layer(::graphics::context * pgraphicscontext);
      //virtual void on_render_layer();

      ////virtual floating_sequence3 camera_pole_up();

      //virtual void on_update_frame();

      ////virtual ::pointer<::graphics3d::renderable> _load_wavefront_obj_renderable(const ::gpu::renderable_t &model);

      ////virtual void on_offscreen_frame_pixels(const ::image32_t* pimage32, ::i32 w, ::i32 h, ::i32 stride);

      //virtual floating_matrix4 perspective(const ::f32_angle & angleFovY, ::f32 aspect, ::f32 zNear, ::f32 zFar);

      //virtual void calculate_impact(::floating_matrix4 & matrixImpact, const ::graphics3d::camera & camera);
      //virtual void calculate_projection(::floating_matrix4 & matrixProjection, const ::graphics3d::camera & camera);


   };

   //floating_sequence3 camera::pole_up() { return m_pgraphics3dengineinstance->camera_pole_up(); }
} // namespace graphics3d


