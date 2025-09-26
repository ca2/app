//
// From point_light_render_system by camilo on 2025-08-19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <glm/glm.hpp>


namespace graphics3d
{

 //
 //    struct point_light_component
 //    {
 //
 //        float lightIntensity = 1.0f;
 //
 //    };
 //
	struct CLASS_DECL_BRED ::graphics3d::transform
	{
		//::graphics3d::transform() = default;
		glm::vec3 translation{};
		glm::vec3 scale{ 1.f };
		glm::vec3 rotation{};

		glm::mat4 mat4() const;
		glm::mat3 normalMatrix() const;

	};


} // namespace graphics3d



