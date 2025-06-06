#pragma once

#include "aura/graphics/graphics3d/camera.h"
#include "aura/graphics/gpu/frame.h"
#include "aura/graphics/graphics3d/scene_object.h"

// lib
//#include "_opengl/opengl.h>

namespace gpu_opengl
{

	class frame :
		virtual public ::gpu::frame
	{
	public:


	};

	//struct FrameInfo {
	//	int frameIndex;
	//	float frameTime;
	//	//VkCommandBuffer commandBuffer;
	//	::graphics3d::camera &camera;
	//	//VkDescriptorSet globalDescriptorSet;
	//	::graphics3d::scene_object::map& gameObjects;
	//};


} // namespace graphics3d_opengl 



