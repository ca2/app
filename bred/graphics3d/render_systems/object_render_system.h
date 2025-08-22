#pragma once
#include "bred/graphics3d/render_system.h"


#include "bred/gpu/properties.h"
//#include "SceneFoundry/graphics3d/device.h"
//#include "SceneFoundry/graphics3d/pipeline.h"
//#include <vulkan/vulkan.h>

// STD
//#include <memory>
//#include <vector>

namespace graphics3d
{



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


	class CLASS_DECL_BRED object_render_system :
		virtual public ::graphics3d::render_system
	{
	public:


		//::pointer < ::graphics3d::device > m_pgpudevice;

		//VkDescriptorSetLayout m_globalSetLayout;

		//::pointer<::gpu::pipeline> m_ppipeline;
		//::pointer < ::gpu::shader > m_pshader;
		///	VkPipelineLayout m_pipelineLayout;

		//object_render_system(::graphics3d::device *pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		object_render_system();
		~object_render_system();

		//object_render_system(const object_render_system&) = delete;
		//object_render_system& operator=(const object_render_system&) = delete;

		// void init(
		// 	::graphics3d::device * pdevice,
		// 	VkRenderPass            renderPass,
		// 	VkDescriptorSetLayout   globalSetLayout,
		// 	::graphics3d::sandbox_descriptor_pool& descriptorPool,
		// 	size_t frameCount)override;

	   void initialize_render_system(::graphics3d::engine* pengine) override;



	   void on_prepare(::gpu::context* pgpucontext) override;
	   void on_update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene) override;
	   void on_render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene) override;


		//void on_render() override;
		//private:
		//void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);

	};


} // namespace graphics3d


