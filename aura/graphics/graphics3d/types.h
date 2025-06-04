// From landen by camilo on 2025-05-18 03:39
#pragma once


#include "aura/graphics/gpu/types.h"

// libs
//namespace graphics3d
//{
//
//	namespace geometry = glm;
//
//	using glm::vec3 = glm::vec3;
//	using glm::vec3 = glm::vec3;
//	using quad_matrix = glm::mat4;
//
//
//
//} // namespace graphics3d
//



namespace user
{


	enum enum_key_state
	{

		e_key_state_none,
		e_key_state_pressed = 1,

	};


} // namespace user


namespace graphics3d
{

	/** @brief State of mouse/touch input */
	struct mouse_state
	{


		struct
		{


			bool left = false;
			bool right = false;
			bool middle = false;


		} m_buttons;


		::glm::vec2		m_position;


	};



	struct CLASS_DECL_AURA TransformComponent
	{
	
		glm::vec3 translation{};
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation{};

		// Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
		// Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)

		//glm::mat4 mat4();
		//glm::mat4 normalMatrix();

	};


} // namespace graphics3d



