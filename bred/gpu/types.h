// Created by camilo on 2025-05-22 09:30 PM <3ThomasBorregaardSoerensen!!
#pragma once


#include "acme/constant/gpu.h"
#include "bred/gpu/properties.h"


#include <functional>


#include "acme/graphics/image/image32.h"


namespace gpu
{



	// from: https://stackoverflow.com/a/57595105
	template <typename T, typename... Rest>
	void hash_combine(::hash32& seed, const T& v, const Rest&... rest)
	{
		seed.m_u ^= ::hash32((::uptr)(size_t)::std::hash<T>{}(v)).m_u + 0x9e3779b9 + (seed.m_u << 6) + (seed.m_u >> 2);
		(hash_combine(seed, rest), ...);
	};

	struct projection_quad_texcoords_textColor
	{

		glm::mat4 projection;
		glm::vec4 quad;
		glm::vec4 texcoords;
		glm::vec4 textColor;  // r, g, b, a

	};

	struct quad_texcoords_textColor
	{

		glm::vec4 quad;
		glm::vec4 texcoords;
		glm::vec4 textColor;  // r, g, b, a

	};

   struct model_view_projection_hdriSampler
   {
      glm::mat4 model;
      glm::mat4 view;
      glm::mat4 projection;
      int hdri;
   };

   struct model_view_projection_environmentCubeSampler
   {
      glm::mat4 model;
      glm::mat4 view;
      glm::mat4 projection;
      int environmentCube;
   };

   struct model_normal
   {
      glm::mat4 modelMatrix;
      glm::mat4 normalMatrix;
   };

   struct position3
   {
      glm::vec3 position;

      position3() {}
      position3(float x, float y, float z) : position(x, y, z) {}
   };

   struct position2_uv
   {
      glm::vec2 position;
      glm::vec2 uv;
   };

} // namespace gpu


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::projection_quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_hdriSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_environmentCubeSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_normal)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position3)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position2_uv)
