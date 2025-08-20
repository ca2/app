#pragma once
//#include "SceneFoundry/sandbox_interfaces/renderer_i.h"
///#include <vulkan/vulkan.h>
///
///
namespace sandbox_interfaces
{

    struct IModel :
        virtual public ::particle
    {
    public:
        //virtual ~IModel() = default;
        // virtual void bind(VkCommandBuffer cmd) {};
        //
        //
        // virtual void draw(VkCommandBuffer cmd) {};
        virtual void bind(::gpu::command_buffer * pcommandbuffer) {};


        virtual void draw(::gpu::command_buffer * pcommandbuffer) {};

        // virtual void gltfDraw(
        // 	VkCommandBuffer cmd,
        // 	uint32_t renderFlags = 0,
        // 	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE,
        // 	uint32_t bindImageSet = 1
        // ) {}


        // virtual void gltfDraw(
        // 	VkCommandBuffer cmd,
        // 	uint32_t renderFlags = 0,
        // 	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE,
        // 	uint32_t bindImageSet = 1
        // ) {}



    };


} // namespace sandbox_interfaces



