// Created by camilo on 2025-05-22 09:30 PM <3ThomasBorregaardSoerensen!!
#pragma once


#include "bred/gpu/properties.h"
#include "acme/prototype/geometry2d/matrix.h"

//#include <functional>



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
   struct quad
   {

      floating_sequence4 quad;

   };

   struct model_view_projection_hdriSampler
   {
      floating_matrix4 model;
      floating_matrix4 view;
      floating_matrix4 projection;
      ::i32 hdri;
   };

   struct model_view_projection_environmentCubeSampler
   {
      floating_matrix4 model;
      floating_matrix4 view;
      floating_matrix4 projection;
      ::i32 environmentCubemap;
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
      position3(::f32 x, ::f32 y, ::f32 z) : position(x, y, z) {}
   };

   struct position2_uv
   {
      floating_sequence2 position;
      floating_sequence2 uv;
   };

   struct uniformFragmentColor
   {
      floating_sequence4 color;
   };

   struct circle_vertex
   {
      ::floating_sequence2 position;
      ::floating_sequence2 local_position;
   };

   struct circle_uniform_set
   {
      floating_sequence4 uniformFragmentColor;
      float radius;
      float thickness;

   };

} // namespace gpu


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::projection_quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::quad_texcoords_textColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::quad)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_hdriSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_view_projection_environmentCubeSampler)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::model_normal)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position3)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::position2_uv)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::floating_sequence2)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::uniformFragmentColor)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::circle_vertex)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::circle_uniform_set)


namespace geometry2d
{


   template < >
   inline void global_transform<::gpu::circle_vertex>(const matrix & m, ::gpu::circle_vertex & vertex)
   {

      m.transform(vertex.position);

   }


} // namespace geometry2d



