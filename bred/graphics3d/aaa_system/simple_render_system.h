#pragma once


#include "bred/graphics3d/properties.h"
//#include "context.h"
//#include "pipeline.h"
//#include "scene_object.h"
//#include "frame_info.h"
//#include "bred/graphics3d/camera.h"


//
//#include <memory>
//#include <vector>



namespace graphics3d
{


	//struct SimplePushConstantData {
	//	floating_matrix4 modelMatrix{ 1.f };
	//	floating_matrix4 normalMatrix{ 1.f };
	//};


	inline ::gpu::properties simple_render_properties()
	{

		static ::gpu::property s_properties[] =
		{
			{"modelMatrix", ::gpu::e_type_mat4},
			{"normalMatrix", ::gpu::e_type_mat4},
			{ nullptr, ::gpu::e_type_none}

		};

		return s_properties;

	}


	class simple_render_system:
		virtual public ::particle 
	{
	public:
		

		::pointer < ::gpu::context> m_pgpucontext;
		//::pointer < ::graphics3d::engine> m_pengine;


		::pointer<::graphics3d::shader> m_pshader;
		//VkPipelineLayout pipelineLayout;

		
		//simple_render_system(context *pvkcdevice, VkRenderPass renderPass, aaaVkDescriptorSetLayout globalSetLayout);
		simple_render_system();
		~simple_render_system();


		virtual void initialize_simple_render_system(::gpu::context* pgpucontext);



		virtual void renderGameObjects(::graphics3d::scene* pscene);
	//private:
		//virtual void createPipelineLayout();
		//virtual void createPipeline();

	};


} // namespace graphics3d




