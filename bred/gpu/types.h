// Created by camilo on 2025-05-22 09:30 PM <3ThomasBorregaardSoerensen!!
#pragma once


#include "acme/constant/gpu.h"
#include "bred/gpu/properties.h"
#include "acme/prototype/geometry/sequence.h"
#include "acme/prototype/geometry/matrix.h"

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

		floating_matrix4 projection;
		floating_sequence4 quad;
		floating_sequence4 texcoords;
		floating_sequence4 textColor;  // r, g, b, a

	};

	struct quad_texcoords_textColor
	{

		floating_sequence4 quad;
		floating_sequence4 texcoords;
		floating_sequence4 textColor;  // r, g, b, a

	};

   struct model_view_projection_hdriSampler
   {
      floating_matrix4 model;
      floating_matrix4 view;
      floating_matrix4 projection;
      int hdri;
   };

   struct model_view_projection_environmentCubeSampler
   {
      floating_matrix4 model;
      floating_matrix4 view;
      floating_matrix4 projection;
      int environmentCubemap;
   };

   struct model_normal
   {
      floating_matrix4 modelMatrix;
      floating_matrix4 normalMatrix;
   };

   struct position3
   {
      floating_sequence3 position;

      position3() {}
      position3(float x, float y, float z) : position(x, y, z) {}
   };

   struct position2_uv
   {
      floating_sequence2 position;
      floating_sequence2 uv;
   };

} // namespace gpu


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::projection_quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_hdriSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_environmentCubeSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_normal)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position3)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position2_uv)
