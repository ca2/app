//
// From point_light_render_system by camilo on 2025-08-19 <3ThomasBorregaardSorensen!!
//
#pragma once





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
		floating_sequence3 translation{};
		floating_sequence3 scale{ 1.f };
		floating_sequence3 rotation{};

		floating_matrix4 floating_matrix4() const;
		floating_matrix3 normalMatrix() const;

	};


} // namespace graphics3d



