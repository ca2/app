// Created by camilo on 2025-05-17 03:59 <3ThomasBorregaardSorensen!!
#pragma once



#include "apex/platform/app_consumer.h"
#include "bred/graphics3d/camera.h"
#include "bred/graphics3d/scene_object.h"
#include "bred/gpu/properties.h"
#include "bred/gpu/shader.h"

// libs
#include <glm/gtc/matrix_transform.hpp>
//
//// std
//#include <memory>
//#include <unordered_map>


#include <chrono>


namespace graphics3d
{


	class CLASS_DECL_BRED engine :
		virtual public ::app_consumer < ::aura::application, ::object >
	{
	public:



		float m_fYScale;
		//::pointer < ::gpu::approach >					m_papproach;
		//::pointer < ::gpu::context >					m_pgpucontext;
		::pointer < ::gpu::context >					m_pgpucontextGraphics3D;
		::pointer < ::user::graphics3d >				m_pusergraphics3d;
		::string_map < ::pointer < scene > >		m_mapScene;
		::pointer < scene >								m_pscene;
		::pointer < ::graphics3d::input >			m_pinput;
		::pointer < ::graphics3d::camera >			m_pcamera;

		TransformComponent								m_transform;
		float													m_fFrameTime;

		bool													m_bWireframeMode = false;

		::std::chrono::steady_clock::time_point	m_stdtimepoint;
		bool	m_bCreatedGlobalUbo;
		::int_rectangle									m_rectanglePlacementNew;
		::int_rectangle									m_rectanglePlacement;
		bool													m_bEngineOnFrameContextInitialization = false;

		bool m_bLoadedEngine = false;

		//::image32_callback                        m_callbackImage32CpuBuffer;


		engine();
		~engine() override;


		virtual void initialize_engine(::user::graphics3d* pimpact);


		virtual void create_global_ubo(::gpu::context * pgpucontext);

		virtual ::gpu::enum_output get_engine_gpu_eoutput();

		virtual void defer_start(::user::graphics3d * pusergraphics3d, const ::int_rectangle& rectangle);

		virtual void on_begin_frame();
		virtual void on_end_frame();

		virtual void update_global_ubo(::gpu::context* pgpucontext);



		virtual ::gpu::context* get_gpu_context();




		virtual void engine_on_after_load_scene(::graphics3d::scene* pscene);


		float dt() { return m_fFrameTime; }

		virtual glm::mat4 model_matrix(TransformComponent& transformcomponent);
		virtual glm::mat4 normal_matrix(TransformComponent& transformcomponent);

		//void on_begin_frame() override;
		virtual void run_cpu_buffer();

		virtual void run();

		
      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics);


		virtual void do_frame_step(::gpu::context * pgpucontextUpper);

		virtual void _prepare_frame();

		virtual void _engine_on_frame_context_initialization();

		virtual void _do_frame_step();
		virtual void on_after_done_frame_step(::draw2d::graphics_pointer& pgraphics);
		virtual void defer_update_engine(const ::int_rectangle & rectangle);

		virtual void on_layout(const ::int_rectangle & rectanglePlacement);

		virtual void on_mouse_move(float x, float y);

		virtual void on_render_frame();

		//virtual glm::vec3 camera_pole_up();

		virtual void on_update_frame();

		virtual ::pointer<model> create_tinyobjloader_model(const ::file::path& path);

		virtual void add_scene(::graphics3d::scene* pscene);

		virtual void set_current_scene(::graphics3d::scene* pscene);

		//virtual void on_offscreen_frame_pixels(const ::image32_t* pimage32, int w, int h, int stride);


	};

	//glm::vec3 camera::pole_up() { return m_pengine->camera_pole_up(); }
} // namespace cube


