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


} // namespace gpu



BEGIN_GPU_PROPERTIES(::gpu::projection_quad_texcoords_textColor)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("quad", ::gpu::e_type_seq4)
GPU_PROPERTY("texcoords", ::gpu::e_type_seq4)
GPU_PROPERTY("textColor", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()



BEGIN_GPU_PROPERTIES(::gpu::quad_texcoords_textColor)
GPU_PROPERTY("quad", ::gpu::e_type_seq4)
GPU_PROPERTY("texcoords", ::gpu::e_type_seq4)
GPU_PROPERTY("textColor", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()



