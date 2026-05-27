#pragma once

#include "bred/graphics3d/camera.h"
#include "bred/gpu/frame.h"
#include "bred/graphics3d/scene_object.h"

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
	//	::i32 frameIndex;
	//	::f32 frameTime;
	//	//VkCommandBuffer commandBuffer;
	//	::graphics3d::camera &camera;
	//	//VkDescriptorSet globalDescriptorSet;
	//	::graphics3d::scene_object::map_base& gameObjects;
	//};


} // namespace graphics3d_opengl 



