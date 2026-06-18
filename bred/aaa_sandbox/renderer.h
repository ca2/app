#pragma once
//#include <memory>
//#include <cstdint>
//#include <vulkan/vulkan.h>
//#include <vector>

#include "bred/graphics3d/frame.h"


namespace graphics3d
{


	class IRenderer :
		virtual public ::particle
	{
	public:
		// struct FrameContext {
		// 	::array_base<VkCommandBuffer> graphicsCommandBuffers;
		// 	VkCommandBuffer primaryGraphicsCommandBuffer = VK_NULL_HANDLE;
		// 	VkFence frameFence = VK_NULL_HANDLE;
		// 	uint32_t frameIndex = 0;
		//
		// 	bool isValid() const { return primaryGraphicsCommandBuffer != VK_NULL_HANDLE; }
		// };
		//

		// :
		//virtual public ::particlevirtual ~ISandboxRenderer() = default;

		virtual void renderSystems(::gpu::layer * pgpulayer) = 0;
		virtual void updateSystems(
			::gpu::layer * pgpulayer,
			::gpu::properties * ppropertisGlobalUbo,
			::f32 deltaTime) {};
		virtual IFrame * beginFrame() = 0;
		virtual void beginSwapChainRenderPass(IFrame * pframe) = 0;
		virtual void endSwapChainRenderPass(IFrame * pframe) = 0;
		virtual void endFrame(IFrame * pframe) = 0;

		virtual void waitDeviceIdle() = 0;

	};
} // namespace graphics3d


