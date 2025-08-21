#pragma once
#include <glm/glm.hpp>


namespace graphics3d
{

	class TransformComponent {
		//TransformComponent() = default;
		glm::vec3 translation{};
		glm::vec3 scale{ 1.f };
		glm::vec3 rotation{};

		glm::mat4 mat4() const;
		glm::mat3 normalMatrix() const;
	};


} // namespace graphics3d


