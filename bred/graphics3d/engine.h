// Created by camilo on 2025-05-17 03:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "bred/gpu/compositor.h"
#include "bred/graphics3d/camera.h"
#include "bred/graphics3d/transform.h"
#include "bred/platform/application.h"


#include <atomic>
#include <chrono>


namespace graphics3d
{


	class CLASS_DECL_BRED engine :
		virtual public ::app_consumer < ::bred::application, ::object, ::gpu::compositor >
	{
	public:


      ::std::atomic<::f32>                              m_fDesiredFps{60.0f};



		::f32                                              m_fYScale;
		//::pointer < ::gpu::approach >					      m_papproach;
		//::gpu::context_pointer					      m_pgpucontext;
		//::gpu::context_pointer					      m_pgpucontextGraphics3D;
		::pointer < ::user::graphics3d >				         m_pusergraphics3d;

	   ::pointer < ::graphics3d::immersion_layer >        m_pimmersionlayer;
	   ::pointer < ::graphics3d::input >			         m_pinput;

		::graphics3d::transform					               m_transform;
		::f32													         m_fFrameTime;

		bool													         m_bWireframeMode = false;

		::std::chrono::high_resolution_clock::time_point	m_stdtimepoint;
		bool	                                             m_bCreatedGlobalUbo;
		::i32_rectangle									         m_rectanglePlacementNew;
		::i32_rectangle									         m_rectanglePlacement;
		bool													         m_bEngineOnFrameContextInitialization = false;

		bool                                               m_bLoadedEngine = false;
      ::f32 m_fInputPitchFlip;
		//::image32_callback                        m_callbackImage32CpuBuffer;
      ::pointer<::graphics3d::shape_factory> m_pshapefactory;


		engine();
		~engine() override;


		virtual void initialize_engine(::user::graphics3d* pimpact);

      void set_gpu_performance_diagnostics(bool bEnabled);
      bool gpu_performance_diagnostics_enabled() const;
      void set_gpu_performance_diagnostics_interval(::i32 iMilliseconds);
      ::i32 gpu_performance_diagnostics_interval() const;


      virtual void defer_process_load_assets_commands();


		//virtual void create_global_ubo(::gpu::context *pgpucontext);

		virtual ::gpu::enum_output get_engine_gpu_eoutput();

		virtual void defer_start(::user::graphics3d * pusergraphics3d, const ::i32_rectangle& rectangle);

		virtual void on_begin_frame();
		virtual void on_end_frame();

		//void start_gpu_layer(::gpu::layer * pgpulayer) override;
		//::gpu::frame* end_gpu_layer(::gpu::layer * pgpulayer) override;


		//virtual void update_global_ubo(::gpu::context* pgpucontext);

      virtual ::graphics3d::shape_factory *shape_factory();

		virtual ::gpu::context* get_gpu_context();



		virtual void engine_on_after_load_scene(::graphics3d::scene_base* pscene);


		::f32 dt() { return m_fFrameTime; }

		virtual floating_matrix4 model_matrix(::graphics3d::transform& transformcomponent);
		virtual floating_matrix4 normal_matrix(::graphics3d::transform& transformcomponent);

		//void on_begin_frame() override;
		virtual void run_cpu_buffer();

		void run() override;

		
      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics);

      virtual ::graphics3d::scene_base * current_scene();


		///virtual void do_frame_step(::gpu::context * pgpucontextUpper);

      //virtual void do_draw_layer(::gpu::context *pgpucontextUpper);

      virtual void do_draw_layer();

		virtual void _prepare_frame();

		virtual void _engine_on_frame_context_initialization();

		virtual void draw_layer();
		virtual void on_after_done_frame_step(::draw2d::graphics_pointer& pgraphics);
      virtual void defer_update_engine(const ::i32_rectangle &rectangle);

		virtual void on_layout(const ::i32_rectangle & rectanglePlacement);

		virtual void on_mouse_move(::f32 x, ::f32 y);

		//virtual void on_render_layer(::graphics::context * pgraphicscontext);
      virtual void on_render_layer();

		//virtual floating_sequence3 camera_pole_up();

		virtual void on_update_frame();

		//virtual ::pointer<::graphics3d::renderable> _load_wavefront_obj_renderable(const ::gpu::renderable_t &model);

		//virtual void on_offscreen_frame_pixels(const ::image32_t* pimage32, ::i32 w, ::i32 h, ::i32 stride);

      virtual floating_matrix4 perspective(const ::f32_angle & angleFovY, ::f32 aspect, ::f32 zNear, ::f32 zFar);

      virtual void calculate_impact(::floating_matrix4 &matrixImpact, const ::graphics3d::camera &camera);
      virtual void calculate_projection(::floating_matrix4 &matrixProjection, const ::graphics3d::camera &camera);


	};

	//floating_sequence3 camera::pole_up() { return m_pengine->camera_pole_up(); }
} // namespace graphics3d


