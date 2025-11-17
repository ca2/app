// From landen by camilo on 2025-05-18 03:39
#pragma once


#include "bred/gpu/properties.h"
#include "bred/gpu/types.h"

//
// namespace user
// {
//
//
// 	enum enum_key_state
// 	{
//
// 		e_key_state_none,
// 		e_key_state_pressed = 1,
//
// 	};
//
//
//
// } // namespace user
//
//
// namespace graphics3d
// {
//
// 	/** @brief State of mouse/touch input */
// 	struct mouse_state
// 	{
//
//
// 		struct
// 		{
//
//
// 			bool left = false;
// 			bool right = false;
// 			bool middle = false;
//
//
// 		} m_buttons;
//
//
// 		::floating_sequence2		m_position;
//
//
// 	};
//
//
//
// 	// struct CLASS_DECL_BRED ::graphics3d::transform
// 	// {
// 	//
// 	// 	floating_sequence3 translation{};
// 	// 	floating_sequence3 scale{ 1.f, 1.f, 1.f };
// 	// 	floating_sequence3 rotation{};
// 	//
// 	// 	// Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
// 	// 	// Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
// 	//
// 	// 	//floating_matrix4 floating_matrix4();
// 	// 	//floating_matrix4 normalMatrix();
// 	//
// 	// };
//    struct CLASS_DECL_BRED transform
//    {
//       //::graphics3d::transform() = default;
//       floating_sequence3 translation{};
//       floating_sequence3 scale{ 1.f };
//       floating_sequence3 rotation{};
//
//       floating_matrix4 floating_matrix4() const;
//       floating_matrix3 normalMatrix() const;
//
//    };
//
//
// 	struct sequence3_color
// 	{
//
// 		floating_sequence3 position; // x, y, z
// 		floating_sequence4 color;  // r, g, b, a
//
// 	};
//
// } // namespace graphics3d
//
//
// BEGIN_GPU_PROPERTIES(::graphics3d::sequence3_color)
// 	GPU_PROPERTY("position", ::gpu::e_type_seq3)
// 	GPU_PROPERTY("color", ::gpu::e_type_seq4)
// END_GPU_PROPERTIES()
//
//
// namespace graphics3d
// {
//
//
// 	struct sequence2_color
// 	{
//
// 		floating_sequence2 position; // x, y
// 		floating_sequence4 color;  // r, g, b, a
//
// 	};
//
//
// } // namespace graphics3d
//
//
// BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_color)
// 	GPU_PROPERTY("position", ::gpu::e_type_seq2)
// 	GPU_PROPERTY("color", ::gpu::e_type_seq4)
// END_GPU_PROPERTIES()
//
//
// namespace graphics3d
// {
//
//
// 	struct sequence2_uv
// 	{
//
// 		floating_sequence2 position{};
// 		floating_sequence2 uv{};
//
// 	};
//
//
// } // namespace graphics3d
//
//
//
// BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_uv)
// 	GPU_PROPERTY("position", ::gpu::e_type_seq2)
// 	GPU_PROPERTY("uv", ::gpu::e_type_seq2)
// END_GPU_PROPERTIES()
//
//
// namespace graphics3d
// {
//
// 	struct Vertex
// 	{
//
// 		floating_sequence3 position{};
// 		floating_sequence3 color{};
// 		floating_sequence3 normal{};
// 		floating_sequence2 uv{};
//
// 		//static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
// 		//static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
//
// 		bool operator==(const Vertex& other) const { return position == other.position && normal == other.normal && uv == other.uv; }
//
// 	};
//
// } // namespace graphics3d
//
//
// BEGIN_GPU_PROPERTIES(::graphics3d::Vertex)
// 	GPU_PROPERTY("position", ::gpu::e_type_seq3)
// 	GPU_PROPERTY("color", ::gpu::e_type_seq3)
// 	GPU_PROPERTY("normal", ::gpu::e_type_seq3)
// 	GPU_PROPERTY("uv", ::gpu::e_type_seq2)
// END_GPU_PROPERTIES()
//
//
// template < >
// inline ::hash32 as_hash32<::graphics3d::Vertex>(const ::graphics3d::Vertex& vertex)
// {
//
// 	hash32 seed{};
//
// 	::gpu::hash_combine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
//
// 	return seed;
//
// }




DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence2_uv)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::floating_sequence3)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence3_color)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence2_color)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::Vertex)


template < >
inline ::hash32 as_hash32<::graphics3d::Vertex>(const ::graphics3d::Vertex& vertex)
{

   hash32 seed{};

   ::gpu::hash_combine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);

   return seed;

}

