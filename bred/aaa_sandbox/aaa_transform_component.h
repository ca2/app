#pragma once
#include <glm/glm.hpp>


namespace graphics3d
{

	class ::graphics3d::transform {
		//::graphics3d::transform() = default;
		floating_sequence3 translation{};
		floating_sequence3 scale{ 1.f };
		floating_sequence3 rotation{};

		floating_matrix4 floating_matrix4() const;
		floating_matrix3 normalMatrix() const;
	};


} // namespace graphics3d


